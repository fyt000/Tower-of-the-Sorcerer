// Recover the shared save writer and the original eight paired menu callbacks.
// @category TSW
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;

public class RecoverSaves extends GhidraScript {
    @Override public void run() throws Exception {
        Path output = Paths.get(getScriptArgs()[0]); Files.createDirectories(output);
        Object[][] entries = {{0x47eadcL,"write_original_save"},
            {0x47ecc4L,"save_slot_1"},{0x47edb8L,"save_slot_2"},{0x47eeacL,"save_slot_3"},
            {0x47efa0L,"save_slot_4"},{0x47f094L,"save_slot_5"},{0x47f188L,"save_slot_6"},
            {0x47f27cL,"save_slot_7"},{0x47f370L,"save_slot_8"},
            {0x47db94L,"load_slot_2"},{0x47dd54L,"load_slot_3"},{0x47df14L,"load_slot_4"},
            {0x47e0d4L,"load_slot_5"},{0x47e294L,"load_slot_6"},{0x47e454L,"load_slot_7"},
            {0x47e614L,"load_slot_8"}};
        DecompInterface decompiler = new DecompInterface(); decompiler.openProgram(currentProgram);
        for (Object[] entry : entries) {
            var address = toAddr((Long)entry[0]); disassemble(address);
            Function f = getFunctionAt(address);
            if (f == null) f = createFunction(address,(String)entry[1]);
            if (f == null) throw new IllegalStateException("Cannot create save callback at "+address);
            f.setName((String)entry[1],SourceType.USER_DEFINED);
            DecompileResults result = decompiler.decompileFunction(f,120,monitor);
            if (!result.decompileCompleted()) throw new IllegalStateException(result.getErrorMessage());
            Files.writeString(output.resolve(String.format("%08x_%s.c",(Long)entry[0],entry[1])),
                "/* Original Delphi save routine at "+address+"; review assembly for inferred types. */\n"+
                result.getDecompiledFunction().getC(),StandardCharsets.UTF_8);
            println("Recovered "+entry[1]+" at "+address);
        }
        decompiler.dispose();
    }
}
