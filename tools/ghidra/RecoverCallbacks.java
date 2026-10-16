// Recover Delphi UI callbacks not reached by Ghidra's initial direct-call analysis.
// @category TSW
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;

public class RecoverCallbacks extends GhidraScript {
    @Override public void run() throws Exception {
        Path output = Paths.get(getScriptArgs()[0]); Files.createDirectories(output);
        Object[][] entries = {{0x44e1ccL,"accept_merchant_or_altar"},{0x44eaf4L,"confirm_flight"},
            {0x44ed1cL,"preview_flight_down"},{0x44ed94L,"preview_flight_up"},{0x44f0e8L,"close_wisdom"},
            {0x451b98L,"mattock_wall"},{0x451d3cL,"crystal_lava"},
            {0x451e1cL,"altar_health"},{0x4520b4L,"altar_attack"},{0x452360L,"altar_defense"}};
        DecompInterface decompiler = new DecompInterface(); decompiler.openProgram(currentProgram);
        for (Object[] entry : entries) {
            var address = toAddr((Long)entry[0]); disassemble(address);
            Function f = getFunctionAt(address);
            if (f == null) f = createFunction(address,(String)entry[1]);
            if (f == null) throw new IllegalStateException("Cannot create callback at "+address);
            f.setName((String)entry[1],SourceType.USER_DEFINED);
            DecompileResults result = decompiler.decompileFunction(f,120,monitor);
            if (!result.decompileCompleted()) throw new IllegalStateException(result.getErrorMessage());
            Files.writeString(output.resolve(String.format("%08x_%s.c",(Long)entry[0],entry[1])),
                "/* Original Delphi callback at "+address+"; review assembly for inferred types. */\n"+
                result.getDecompiledFunction().getC(),StandardCharsets.UTF_8);
            println("Recovered "+entry[1]+" at "+address);
        }
        decompiler.dispose();
    }
}
