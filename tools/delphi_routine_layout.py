"""Trace Delphi 2 routine bodies, including SEH continuations and switch data.

The caller supplies independently reviewed bounds. Decode the executable rather
than trusting Ghidra exports, which can omit returns and misdecode literals.
"""
import struct

import capstone as cs
from capstone import x86 as x


NOP = {0: b"", 1: b"\x90", 2: b"\x8b\xc0", 3: b"\x8d\x40\x00"}
DISPATCHERS = {0x402F4C, 0x403140}  # @HandleAnyException, @HandleFinally
DONE_EXCEPT = 0x403268


def trace_layout(pe, start, limit):
    base = pe.OPTIONAL_HEADER.ImageBase
    relocations = {base + item.rva for block in pe.DIRECTORY_ENTRY_BASERELOC
                   for item in block.entries if item.type == 3}
    md = cs.Cs(cs.CS_ARCH_X86, cs.CS_MODE_32)
    md.detail = True

    def read(at, length):
        return pe.get_data(at - base, length)

    def decode(at):
        ins = next(md.disasm(read(at, 15), at, count=1), None)
        if ins is None or ins.address + ins.size > limit:
            raise ValueError(f"Instruction crosses reviewed boundary at {at:#x}")
        return ins

    pending, visited, tables, continuations = [start], {}, set(), set()
    while pending:
        at = pending.pop()
        if at in visited:
            continue
        if not start <= at < limit:
            raise ValueError(f"Control flow crosses reviewed boundary at {at:#x}")
        ins = decode(at)
        visited[at] = ins
        end = at + ins.size
        if ins.mnemonic.startswith("ret"):
            continue
        if ins.mnemonic == "push" and ins.operands[0].type == x.X86_OP_IMM:
            target = ins.operands[0].imm
            after = decode(end)
            installs_frame = (after.mnemonic == "push" and after.operands[0].type == x.X86_OP_MEM
                              and after.operands[0].mem.segment == x.X86_REG_FS)
            restores_frame = read(at - 3, 3) == b"\x64\x89\x10"  # mov fs:[eax], edx
            if installs_frame or restores_frame:
                if at + ins.imm_offset not in relocations or not start <= target < limit:
                    raise ValueError(f"Unverified SEH continuation at {at:#x}")
                pending.append(target)
                continuations.add(target)
                if installs_frame:
                    thunk = decode(target)
                    if (thunk.mnemonic != "jmp" or thunk.operands[0].type != x.X86_OP_IMM
                            or thunk.operands[0].imm not in DISPATCHERS):
                        raise ValueError(f"Unrecognized exception dispatcher at {target:#x}")
                    # Delphi dispatch returns to the instruction after this JMP.
                    pending.append(target + thunk.size)
        if ins.mnemonic.startswith(("j", "loop")):
            op = ins.operands[0]
            if op.type == x.X86_OP_IMM:
                if start <= op.imm < limit:
                    pending.append(op.imm)
                elif ins.mnemonic != "jmp":
                    raise ValueError(f"Conditional branch crosses boundary at {at:#x}")
            else:
                table = op.mem.disp if op.type == x.X86_OP_MEM and op.mem.scale == 4 and not op.mem.base else 0
                slot = table
                if start <= slot < limit:
                    while slot in relocations:
                        target = struct.unpack("<I", read(slot, 4))[0]
                        if not start <= target < limit:
                            raise ValueError(f"Switch target crosses boundary at {slot:#x}")
                        pending.append(target)
                        slot += 4
                if slot == table:
                    raise ValueError(f"Unresolved indirect branch at {at:#x}")
                tables.add((table, slot))
            if ins.mnemonic == "jmp":
                continue
        if ins.mnemonic == "call" and ins.operands[0].type == x.X86_OP_IMM:
            target = ins.operands[0].imm
            if target == DONE_EXCEPT:
                continue
            if start <= target < limit:
                pending.append(target)
        pending.append(end)

    records = [(at, bytes(ins.bytes)) for at, ins in sorted(visited.items())]
    code_end = max(at + len(raw) for at, raw in records)
    if not visited[max(visited)].mnemonic.startswith("ret"):
        raise ValueError(f"Unverified routine endpoint at {code_end:#x}")
    # Every interior gap must be a switch address table, possibly preceded by
    # the byte lookup table used for sparse case labels. Nothing is discarded.
    previous, gaps = start, []
    for at, raw in records:
        if at < previous:
            raise ValueError(f"Overlapping instruction boundaries at {at:#x}")
        if at > previous:
            matches = [(a, b) for a, b in tables if previous <= a and b == at]
            if len(matches) != 1:
                raise ValueError(f"Unexplained instruction gap at {previous:#x}")
            table, stop = matches[0]
            if table > previous:
                lookup = read(previous, table - previous)
                refs = [ins for ins in visited.values() if ins.mnemonic in ("mov", "movzx")
                        and any(op.type == x.X86_OP_MEM and op.mem.disp == previous
                                and op.size == 1 for op in ins.operands)]
                if not refs or max(lookup) >= (stop - table) // 4:
                    raise ValueError(f"Unverified switch lookup at {previous:#x}")
            gaps.append((previous, at))
        previous = at + len(raw)

    # Attribute the trailing pool to actual operands, including ANSI headers,
    # PChar literals and scalar constants. Require zero alignment around data.
    pools = set()
    for ins in visited.values():
        for op in ins.operands:
            ref = op.imm if op.type == x.X86_OP_IMM else op.mem.disp if op.type == x.X86_OP_MEM else 0
            if not code_end <= ref < limit:
                continue
            operand_offset = ins.imm_offset if op.type == x.X86_OP_IMM else ins.disp_offset
            if ins.address + operand_offset not in relocations:
                raise ValueError(f"Unrelocated pool reference at {ins.address:#x}")
            begin = ref
            count, length = struct.unpack("<iI", read(ref - 8, 8))
            if count == -1 and length < limit - ref and read(ref + length, 1) == b"\0":
                begin, end, kind = ref - 8, ref + length + 1, "ansi-string"
            elif op.type == x.X86_OP_MEM:
                end, kind = ref + op.size, "scalar"
            else:
                end = ref + len(read(ref, limit - ref).split(b"\0", 1)[0]) + 1
                kind = "pchar"
            if begin < code_end or end > limit:
                raise ValueError(f"Literal crosses reviewed boundary at {ref:#x}")
            pools.add((begin, end, kind))
    if pools:
        covered = {at for a, b, _ in pools for at in range(a, b)}
        padding = set(range(code_end, (code_end + 3) & ~3))
        for _, end, _ in pools:
            padding.update(range(end, (end + 3) & ~3))
        for at in range(code_end, limit):
            if at not in covered and (at not in padding or read(at, 1) != b"\0"):
                raise ValueError(f"Unexplained literal-pool byte at {at:#x}")
        pool_bytes = limit - code_end
    else:
        padding = (-code_end) % 4
        if limit != code_end + padding or read(code_end, padding) != NOP[padding]:
            raise ValueError(f"Unexplained bytes after routine at {code_end:#x}")
        pool_bytes = 0
    return dict(records=records, code_bytes=code_end - start, literal_pool_bytes=pool_bytes,
                switch_tables=sorted(tables), literal_pools=sorted(pools),
                exception_continuations=sorted(continuations))
