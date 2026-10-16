// Recover all Delphi published method entries, preserving the original corpus.
// @category TSW
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.*;

public class RecoverPresentation extends GhidraScript {
    private static final String HASH = "41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779";
    @Override public void run() throws Exception {
        String[] args = getScriptArgs();
        Path manifest = Paths.get(args[0]), output = Paths.get(args[1]);
        String path = args.length > 2 ? args[2] : currentProgram.getExecutablePath();
        if (path.matches("^/[A-Za-z]:/.*")) path = path.substring(1);
        String hash = HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(Files.readAllBytes(Paths.get(path))));
        if (!HASH.equals(hash)) throw new IllegalStateException("Executable hash differs");
        // A hash-pinned path can outlive the import location. Also check the
        // imported image's hash, so a stale project cannot silently be used.
        if (!HASH.equalsIgnoreCase(currentProgram.getExecutableSHA256()))
            throw new IllegalStateException("Imported program hash differs");
        Files.createDirectories(output);
        List<Long> entries = new ArrayList<>();
        Map<Long, String> names = new TreeMap<>();
        for (String line : Files.readAllLines(manifest)) {
            String[] parts = line.split("\t");
            long entry = Long.decode(parts[0]);
            entries.add(entry); names.put(entry, parts[1].replaceAll("[^a-zA-Z0-9_]", "_"));
        }
        // These are only the two confirmed VCL setters and message dispatcher
        // relevant to control gating. Exporting them does not emulate Windows.
        for (long entry : new long[]{0x413500,0x41353c,0x410378,0x413cb8}) {
            entries.add(entry); names.put(entry, "vcl_" + Long.toHexString(entry));
        }
        for (long entry : new long[]{0x43f1c0,0x43e08c,0x416c60}) {
            entries.add(entry); names.put(entry, "helper_" + Long.toHexString(entry));
        }
        StringBuilder index = new StringBuilder("# Recovered presentation and input methods\n\nOriginal SHA-256: `"+hash+"`.\n\nPublished entries come from the executable's Delphi method tables, independently reconciled against DFM event bindings. Source and assembly are inspection evidence. Shared tails and inferred types require review. The original export is retained.\n\n| Entry | Published method | C-like output | Assembly | Result |\n|---|---|---|---|---|\n");
        StringBuilder boundaries = new StringBuilder("entry\tprevious_containing_entry\tmethod\n");
        // Correct known interior-entry analysis without overwriting old exports.
        for (long entry : entries) {
            var address = toAddr(entry);
            Function f = getFunctionAt(address);
            if (f == null) {
                Function containing = getFunctionContaining(address);
                if (containing != null) {
                    boundaries.append(String.format("0x%08x\t%s\t%s\n",entry,containing.getEntryPoint(),names.get(entry)));
                    removeFunction(containing);
                }
                // Initial analysis marks some unreachable callback bytes as
                // data. Clear only their entry instruction span, not constants
                // or tables in the rest of the routine.
                if (getInstructionAt(address) == null) clearListing(address,address.add(15));
                disassemble(address);
                f = createFunction(address,names.get(entry));
            }
            if (f == null) throw new IllegalStateException("Cannot recover " + address);
            // Keep established names on existing functions: other evidence refers to them.
        }
        DecompInterface dc = new DecompInterface(); dc.openProgram(currentProgram);
        int failed = 0;
        for (long entry : entries) {
            if (monitor.isCancelled()) break;
            Function f = getFunctionAt(toAddr(entry));
            String stem = String.format("%08x_%s",entry,names.get(entry));
            DecompileResults result = dc.decompileFunction(f,entry == 0x4664e4 ? 600 : 120,monitor);
            boolean success = result.decompileCompleted();
            if (!success) failed++;
            Files.writeString(output.resolve(stem+".c"),"/* Original SHA-256 "+hash+"; published entry "+f.getEntryPoint()+".\n * Inferred types and shared tails require assembly review. */\n" + (success ? result.getDecompiledFunction().getC() : "/* FAILED: "+result.getErrorMessage()+" */\n"),StandardCharsets.UTF_8);
            StringBuilder asm = new StringBuilder("; "+names.get(entry)+" at "+f.getEntryPoint()+"\n; Original SHA-256 "+hash+"\n");
            InstructionIterator instructions = currentProgram.getListing().getInstructions(f.getBody(),true);
            while (instructions.hasNext()) {
                Instruction i = instructions.next();
                asm.append(i.getAddress()).append("  ").append(HexFormat.of().formatHex(i.getBytes())).append("  ").append(i).append("\n");
            }
            Files.writeString(output.resolve(stem+".asm"),asm.toString(),StandardCharsets.UTF_8);
            index.append(String.format("| `0x%08x` | `%s` | [%s.c](%s.c) | [%s.asm](%s.asm) | %s |\n",entry,names.get(entry),stem,stem,stem,stem,success ? "Recovered" : "FAILED"));
            println("Recovered "+stem+(success ? "" : " FAILED"));
        }
        dc.dispose();
        index.append("\nRecovered "+entries.size()+" entries; failed "+failed+".\n");
        Files.writeString(output.resolve("INDEX.md"),index.toString(),StandardCharsets.UTF_8);
        Files.writeString(output.resolve("boundary-repairs.tsv"),boundaries.toString(),StandardCharsets.UTF_8);
        if (failed != 0) throw new IllegalStateException("Review failed decompilations: "+failed);
    }
}
