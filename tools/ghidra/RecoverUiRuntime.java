// Additional runtime boundaries reached by the recovered presentation methods.
// @category TSW
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.Function;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.HexFormat;

public class RecoverUiRuntime extends GhidraScript {
    @Override public void run() throws Exception {
        String hash = "41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779";
        if (!hash.equalsIgnoreCase(currentProgram.getExecutableSHA256())) throw new IllegalStateException("Imported image hash differs");
        Path output = Paths.get(getScriptArgs()[0]);
        long[] entries = {0x41c160,0x42cec8,0x42c454};
        DecompInterface dc = new DecompInterface(); dc.openProgram(currentProgram);
        for (long entry : entries) {
            var address = toAddr(entry);
            Function f = getFunctionAt(address);
            if (f == null) {
                if (getInstructionAt(address) == null) clearListing(address,address.add(15));
                disassemble(address); f = createFunction(address,"runtime_"+Long.toHexString(entry));
            }
            if (f == null) throw new IllegalStateException("Cannot recover "+address);
            DecompileResults result = dc.decompileFunction(f,120,monitor);
            if (!result.decompileCompleted()) throw new IllegalStateException(result.getErrorMessage());
            String stem = String.format("%08x_runtime_%x",entry,entry);
            Files.writeString(output.resolve(stem+".c"),"/* Original SHA-256 "+hash+"; runtime boundary "+address+". */\n"+result.getDecompiledFunction().getC(),StandardCharsets.UTF_8);
            StringBuilder asm = new StringBuilder("; Runtime boundary "+address+"; original SHA-256 "+hash+"\n");
            var instructions = currentProgram.getListing().getInstructions(f.getBody(),true);
            while (instructions.hasNext()) {
                var i = instructions.next();
                asm.append(i.getAddress()).append("  ").append(HexFormat.of().formatHex(i.getBytes())).append("  ").append(i).append("\n");
            }
            Files.writeString(output.resolve(stem+".asm"),asm.toString(),StandardCharsets.UTF_8);
            println("Recovered "+stem);
        }
        dc.dispose();
    }
}
