// Snapshot all detected functions and every byte of the executable CODE block.
// @category TSW
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import com.google.gson.*;
import java.nio.file.*;
import java.util.*;

public class InventoryWholeProgram extends GhidraScript {
    private String hex(Address a) { return String.format("0x%08x", a.getOffset()); }
    private JsonArray ranges(AddressSetView set) {
        JsonArray out = new JsonArray();
        for (AddressRange r : set) {
            JsonArray pair = new JsonArray(); pair.add(hex(r.getMinAddress())); pair.add(hex(r.getMaxAddress()));
            out.add(pair);
        }
        return out;
    }
    @Override public void run() throws Exception {
        String hash = "41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779";
        if (!hash.equalsIgnoreCase(currentProgram.getExecutableSHA256())) throw new IllegalStateException("Imported image hash differs");
        Path output = Paths.get(getScriptArgs()[0]); Files.createDirectories(output.getParent());
        JsonObject report = new JsonObject(); report.addProperty("original_sha256", hash);
        report.addProperty("ghidra_version", ghidra.framework.Application.getApplicationVersion());
        report.addProperty("language", currentProgram.getLanguageID().toString());
        report.addProperty("compiler_spec", currentProgram.getCompilerSpec().getCompilerSpecID().toString());
        var block = currentProgram.getMemory().getBlock("CODE");
        AddressSet code = new AddressSet(block.getStart(), block.getEnd());
        report.addProperty("code_start", hex(block.getStart())); report.addProperty("code_end", hex(block.getEnd()));
        JsonArray functions = new JsonArray();
        var iterator = currentProgram.getFunctionManager().getFunctions(true);
        while (iterator.hasNext()) {
            Function f = iterator.next(); if (!code.contains(f.getEntryPoint())) continue;
            JsonObject row = new JsonObject(); row.addProperty("entry", hex(f.getEntryPoint()));
            row.addProperty("name", f.getName()); row.add("body_ranges", ranges(f.getBody()));
            row.addProperty("body_bytes", f.getBody().getNumAddresses());
            row.addProperty("thunk", f.isThunk()); functions.add(row);
        }
        report.add("functions", functions);
        JsonArray calls = new JsonArray(), indirect = new JsonArray(), addressRefs = new JsonArray();
        AddressSet instructionBytes = new AddressSet(), definedBytes = new AddressSet();
        StringBuilder assembly = new StringBuilder("; Complete detected CODE instruction listing\n; Original SHA-256 " + hash + "\n");
        var instructions = currentProgram.getListing().getInstructions(code, true);
        while (instructions.hasNext()) {
            Instruction i = instructions.next(); instructionBytes.add(i.getMinAddress(), i.getMaxAddress());
            assembly.append(i.getAddress()).append("  ").append(HexFormat.of().formatHex(i.getBytes())).append("  ").append(i).append("\n");
            var flow = i.getFlowType();
            if (flow.isCall() || (flow.isJump() && flow.isComputed())) {
                JsonObject row = new JsonObject(); row.addProperty("site", hex(i.getAddress()));
                row.addProperty("instruction", i.toString());
                Function owner = getFunctionContaining(i.getAddress());
                if (owner != null) row.addProperty("owner", hex(owner.getEntryPoint()));
                JsonArray targets = new JsonArray(); for (Address target : i.getFlows()) targets.add(hex(target));
                row.add("targets", targets); row.addProperty("computed", flow.isComputed());
                if (flow.isComputed()) indirect.add(row); else calls.add(row);
            }
            for (var ref : i.getReferencesFrom()) {
                if (!ref.getReferenceType().isData() || !code.contains(ref.getToAddress())) continue;
                JsonObject row = new JsonObject(); row.addProperty("site", hex(i.getAddress()));
                row.addProperty("target", hex(ref.getToAddress())); row.addProperty("kind", ref.getReferenceType().toString());
                addressRefs.add(row);
            }
        }
        var data = currentProgram.getListing().getDefinedData(code, true);
        while (data.hasNext()) { Data d = data.next(); definedBytes.add(d.getMinAddress(), d.getMaxAddress()); }
        AddressSet undefined = code.subtract(instructionBytes.union(definedBytes));
        report.add("instruction_ranges", ranges(instructionBytes)); report.add("defined_data_ranges", ranges(definedBytes));
        report.add("undefined_ranges", ranges(undefined));
        report.addProperty("instruction_bytes", instructionBytes.getNumAddresses());
        report.addProperty("defined_data_bytes", definedBytes.getNumAddresses()); report.addProperty("undefined_bytes", undefined.getNumAddresses());
        report.add("direct_calls", calls); report.add("indirect_transfers", indirect); report.add("code_address_references", addressRefs);
        report.addProperty("limits", "Ghidra analysis snapshot, not proof that decoded instructions are correct or that defined data is non-executable. Undefined executable bytes remain unresolved. Address materializations are candidates, not proven callback registrations.");
        Files.writeString(output, new GsonBuilder().setPrettyPrinting().create().toJson(report) + "\n");
        Files.writeString(output.getParent().resolve("CODE.asm"), assembly.toString());
        println("Whole-program snapshot: " + functions.size() + " functions, " + undefined.getNumAddresses() + " undefined CODE bytes");
    }
}
