// Recover the two-level Delphi switch missed by the initial source export.
// @category TSW
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.JumpTable;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.util.*;

public class RecoverArrival extends GhidraScript {
    public void run() throws Exception {
        Function f = getFunctionAt(toAddr(0x46cb1c));
        Address branch = toAddr(0x46cb5c);
        getInstructionAt(branch).setFlowOverride(FlowOverride.NONE);
        ArrayList<Address> targets = new ArrayList<>();
        for (int i = 0; i < 15; i++) {
            Address target = toAddr(Integer.toUnsignedLong(getInt(toAddr(0x46cb8b + i * 4))));
            targets.add(target);
            currentProgram.getReferenceManager().addMemoryReference(branch, target,
                RefType.COMPUTED_JUMP, SourceType.USER_DEFINED, 0);
            disassemble(target);
        }
        f.setBody(new AddressSet(toAddr(0x46cb1c), toAddr(0x4770cf)));
        new JumpTable(branch, targets, true).writeOverride(f);
        DecompInterface dc = new DecompInterface();
        dc.openProgram(currentProgram);
        var result = dc.decompileFunction(f, 600, monitor);
        if (!result.decompileCompleted()) throw new IllegalStateException(result.getErrorMessage());
        Files.writeString(Paths.get(getScriptArgs()[0]), result.getDecompiledFunction().getC());
        println("Recovered arrival source: " + getScriptArgs()[0]);
        dc.dispose();
    }
}
