// Retain every detected function and independently rooted missing entry.
// Never replace containing functions or disassemble validated Delphi metadata.
// @category TSW
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.nio.file.*;
import java.security.MessageDigest;
import java.util.*;

public class RecoverWholeProgram extends GhidraScript {
    private static final String HASH = "41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779";
    private String hex(Address a) { return String.format("0x%08x", a.getOffset()); }
    private String digest(Path p) throws Exception {
        return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(Files.readAllBytes(p)));
    }
    private void restoreFlows(JsonObject row, AddressSet allowed) {
        if (!row.has("switch_tables")) return;
        for (JsonElement item : row.getAsJsonArray("switch_tables")) {
            JsonObject table = item.getAsJsonObject(); Address site = toAddr(Long.decode(table.get("site").getAsString()));
            for (JsonElement target : table.getAsJsonArray("cases")) {
                Address address = toAddr(Long.decode(target.getAsString()));
                if (allowed.contains(address)) currentProgram.getReferenceManager().addMemoryReference(
                    site, address, RefType.COMPUTED_JUMP, SourceType.ANALYSIS, 0);
            }
        }
        for (JsonElement item : row.getAsJsonArray("flow_ranges")) {
            Address address = toAddr(Long.decode(item.getAsJsonArray().get(0).getAsString()));
            if (allowed.contains(address)) new DisassembleCommand(address, allowed, true).applyTo(currentProgram, monitor);
        }
    }
    @Override public void run() throws Exception {
        if (!HASH.equalsIgnoreCase(currentProgram.getExecutableSHA256()))
            throw new IllegalStateException("Imported program hash differs");
        String[] args = getScriptArgs();
        Path rootsPath = Paths.get(args[0]), metadataPath = Paths.get(args[1]), output = Paths.get(args[2]);
        Files.createDirectories(output);
        Map<String, JsonObject> previous = new HashMap<>();
        if (args.length > 3 && args[3].equals("reuse-unchanged") && Files.exists(output.resolve("export-manifest.json"))) {
            JsonObject prior = JsonParser.parseString(Files.readString(output.resolve("export-manifest.json"))).getAsJsonObject();
            if (!HASH.equals(prior.get("original_sha256").getAsString())) throw new IllegalStateException("Cached image differs");
            for (JsonElement item : prior.getAsJsonArray("exports")) {
                JsonObject row = item.getAsJsonObject(); previous.put(row.get("entry").getAsString(), row);
            }
        }
        var block = currentProgram.getMemory().getBlock("CODE");
        AddressSet code = new AddressSet(block.getStart(), block.getEnd()), metadata = new AddressSet();
        for (String line : Files.readAllLines(metadataPath)) {
            String[] columns = line.split("\t");
            metadata.add(toAddr(Long.decode(columns[0])), toAddr(Long.decode(columns[1]) - 1));
        }
        AddressSet allowed = code.subtract(metadata);
        for (JsonObject row : previous.values()) restoreFlows(row, allowed);
        SortedMap<Long, String> roots = new TreeMap<>();
        for (String line : Files.readAllLines(rootsPath)) {
            String[] columns = line.split("\t"); roots.put(Long.decode(columns[0]), columns[1]);
        }
        JsonObject report = new JsonObject(); report.addProperty("original_sha256", HASH);
        report.addProperty("roots_sha256", digest(rootsPath)); report.addProperty("metadata_sha256", digest(metadataPath));
        JsonArray repairs = new JsonArray();
        // ExportOriginal created this setup-fragment function before the real
        // published entry was recovered. It has no independent call/table root.
        Function fragment = getFunctionAt(toAddr(0x450bc5));
        if (fragment != null && fragment.getName().equals("use_selected_item") && !roots.containsKey(0x450bc5L)) {
            removeFunction(fragment); JsonObject row = new JsonObject();
            row.addProperty("entry", "0x00450bc5"); row.addProperty("repair", "remove-known-unrooted-setup-fragment");
            row.addProperty("published_entry", "0x00450ba0"); repairs.add(row);
            // The historical fragment remains in the original corpus. Retire
            // only this new corpus's superseded files, not the old evidence.
            Files.deleteIfExists(output.resolve("00450bc5.c"));
            Files.deleteIfExists(output.resolve("00450bc5.asm"));
        }
        // A named function can have been created before its bytes were decoded.
        // Recover its listing and flow body; preserve other established entries.
        List<Function> established = new ArrayList<>();
        var originalFunctions = currentProgram.getFunctionManager().getFunctions(true);
        while (originalFunctions.hasNext()) {
            Function f = originalFunctions.next(); if (allowed.contains(f.getEntryPoint())) established.add(f);
        }
        for (Function f : established) {
            Address address = f.getEntryPoint(); long before = f.getBody().getNumAddresses();
            if (getInstructionAt(address) == null) {
                Data data = getDataContaining(address);
                if (data != null && data.isDefined() && !metadata.intersects(data.getMinAddress(), data.getMaxAddress()))
                    clearListing(data.getMinAddress(), data.getMaxAddress());
            }
            new DisassembleCommand(address, allowed, true).applyTo(currentProgram, monitor);
            CreateFunctionCmd.fixupFunctionBody(currentProgram, f, monitor);
            if (before != f.getBody().getNumAddresses()) {
                JsonObject row = new JsonObject(); row.addProperty("entry", hex(address));
                row.addProperty("repair", "recompute-decoded-flow-body"); row.addProperty("previous_body_bytes", before);
                row.addProperty("body_bytes", f.getBody().getNumAddresses()); repairs.add(row);
            }
        }
        JsonArray outcomes = new JsonArray();
        Set<Long> visited = new HashSet<>(); int created = 0;
        // Newly decoded bodies can expose more direct call roots. Close that
        // set without promoting signature aliases or arbitrary code pointers.
        for (int pass = 0; pass < 20; pass++) {
            int before = visited.size();
            for (var root : new TreeMap<>(roots).entrySet()) {
                long entry = root.getKey(); if (!visited.add(entry)) continue;
                Address address = toAddr(entry); JsonObject row = new JsonObject();
                row.addProperty("entry", hex(address)); row.addProperty("evidence", root.getValue());
                Function f = getFunctionAt(address), containing = getFunctionContaining(address);
                if (f != null) row.addProperty("status", "existing-entry");
                else if (containing != null) {
                    if (allowed.contains(address)) new DisassembleCommand(address, allowed, true).applyTo(currentProgram, monitor);
                    row.addProperty("status", "interior-or-shared-entry");
                    row.addProperty("containing_entry", hex(containing.getEntryPoint()));
                } else if (!allowed.contains(address)) row.addProperty("status", "protected-metadata-or-outside-code");
                else {
                    Instruction overlap = getInstructionContaining(address);
                    if (overlap != null && getInstructionAt(address) == null) {
                        // Independent structural/call seed with a masked shape
                        // was decoded from the wrong alignment in the import.
                        if (getFunctionContaining(overlap.getAddress()) != null ||
                            metadata.intersects(overlap.getMinAddress(), overlap.getMaxAddress())) {
                            row.addProperty("status", "interior-instruction"); outcomes.add(row); continue;
                        }
                        row.addProperty("previous_instruction_start", hex(overlap.getAddress()));
                        clearListing(overlap.getMinAddress(), overlap.getMaxAddress());
                    }
                    Data data = getDataContaining(address);
                    boolean protectedData = data != null && data.isDefined() &&
                        metadata.intersects(data.getMinAddress(), data.getMaxAddress());
                    if (protectedData) row.addProperty("status", "defined-data-overlaps-metadata");
                    else {
                        if (data != null && data.isDefined()) clearListing(data.getMinAddress(), data.getMaxAddress());
                        if (getInstructionAt(address) == null) {
                            DisassembleCommand command = new DisassembleCommand(address, allowed, true);
                            command.applyTo(currentProgram, monitor);
                        }
                        f = createFunction(address, "root_" + String.format("%08x", entry));
                        if (f != null) CreateFunctionCmd.fixupFunctionBody(currentProgram, f, monitor);
                        row.addProperty("status", f == null ? "function-creation-failed" : "created-entry");
                        if (f != null) created++;
                    }
                }
                outcomes.add(row);
            }
            var instructions = currentProgram.getListing().getInstructions(code, true);
            while (instructions.hasNext()) {
                Instruction instruction = instructions.next();
                if (!instruction.getFlowType().isCall() || instruction.getFlowType().isComputed()) continue;
                for (Address target : instruction.getFlows()) {
                    if (code.contains(target)) roots.putIfAbsent(target.getOffset(), "direct-call:" + hex(instruction.getAddress()));
                }
            }
            println("Root pass " + pass + ": " + visited.size() + " entries, " + created + " newly created");
            if (visited.size() == before || visited.size() == roots.size()) break;
        }
        report.add("root_outcomes", outcomes); report.addProperty("created_functions", created);
        report.add("boundary_repairs", repairs);
        report.addProperty("root_closure_complete", visited.size() == roots.size());
        JsonArray exports = new JsonArray(); DecompInterface dc = new DecompInterface();
        dc.openProgram(currentProgram); int failed = 0, index = 0;
        var functions = currentProgram.getFunctionManager().getFunctions(true);
        while (functions.hasNext()) {
            Function f = functions.next(); if (!code.contains(f.getEntryPoint())) continue;
            monitor.checkCancelled(); long entry = f.getEntryPoint().getOffset();
            JsonObject cached = previous.get(hex(f.getEntryPoint()));
            if (cached != null && cached.has("flow_ranges") && cached.get("status").getAsString().equals("decompiled") &&
                cached.get("name").getAsString().equals(f.getName()) &&
                cached.get("body_bytes").getAsLong() == f.getBody().getNumAddresses()) {
                StringBuilder assembly = new StringBuilder("; " + f.getName() + " at " + hex(f.getEntryPoint()) +
                    "\n; Original SHA-256 " + HASH + "\n");
                var body = currentProgram.getListing().getInstructions(f.getBody(), true);
                while (body.hasNext()) {
                    Instruction i = body.next(); assembly.append(i.getAddress()).append("  ")
                        .append(HexFormat.of().formatHex(i.getBytes())).append("  ").append(i).append("\n");
                }
                Path cp = output.resolve(cached.get("c").getAsString()), ap = output.resolve(cached.get("assembly").getAsString());
                if (digest(cp).equals(cached.get("c_sha256").getAsString()) &&
                    digest(ap).equals(cached.get("assembly_sha256").getAsString()) &&
                    Files.readString(ap).equals(assembly.toString())) {
                    exports.add(cached); index++; continue;
                }
            }
            DecompileResults result = dc.decompileFunction(f, entry == 0x4664e4 ? 600 : 60, monitor);
            boolean success = result.decompileCompleted() && result.getDecompiledFunction() != null;
            if (!success) {
                dc.flushCache(); result = dc.decompileFunction(f, entry == 0x4664e4 ? 600 : 180, monitor);
                success = result.decompileCompleted() && result.getDecompiledFunction() != null;
            }
            if (!success) failed++;
            JsonArray flowRanges = new JsonArray(), switches = new JsonArray(), flowConflicts = new JsonArray();
            if (success && result.getHighFunction() != null) {
                var high = result.getHighFunction();
                for (var table : high.getJumpTables()) {
                    JsonObject jump = new JsonObject(); jump.addProperty("site", hex(table.getSwitchAddress()));
                    JsonArray cases = new JsonArray(), loads = new JsonArray();
                    for (Address target : table.getCases()) cases.add(hex(target));
                    for (var load : table.getLoadTables()) {
                        JsonObject range = new JsonObject(); range.addProperty("start", hex(load.getAddress()));
                        range.addProperty("end_exclusive", hex(load.getAddress().add((long)load.getSize() * load.getNum())));
                        range.addProperty("element_size", load.getSize()); range.addProperty("element_count", load.getNum()); loads.add(range);
                    }
                    jump.add("cases", cases); jump.add("loads", loads); switches.add(jump);
                }
                AddressSet expanded = new AddressSet(f.getBody());
                for (var basic : high.getBasicBlocks()) {
                    Address start = basic.getStart(), stop = basic.getStop();
                    if (start == null || stop == null || !allowed.contains(start)) continue;
                    new DisassembleCommand(start, allowed, true).applyTo(currentProgram, monitor);
                    Instruction last = getInstructionContaining(stop);
                    if (last != null) stop = last.getMaxAddress();
                    JsonArray pair = new JsonArray(); pair.add(hex(start)); pair.add(hex(stop)); flowRanges.add(pair);
                    AddressSet span = new AddressSet(start, stop);
                    var owners = currentProgram.getFunctionManager().getFunctionsOverlapping(span);
                    boolean conflict = false;
                    while (owners.hasNext()) {
                        Function other = owners.next(); if (!other.equals(f)) { conflict = true; break; }
                    }
                    if (conflict || metadata.intersects(start, stop)) flowConflicts.add(pair);
                    else expanded.add(start, stop);
                }
                f.setBody(expanded);
                JsonObject recoveredFlow = new JsonObject(); recoveredFlow.add("switch_tables", switches); recoveredFlow.add("flow_ranges", flowRanges);
                restoreFlows(recoveredFlow, allowed);
            }
            String stem = String.format("%08x", entry), error = result.getErrorMessage();
            if (error == null) error = "";
            String c = "/* Original SHA-256 " + HASH + "; entry " + hex(f.getEntryPoint()) + ".\n" +
                " * Inferred types, shared tails and runtime effects require assembly review. */\n" +
                (success ? result.getDecompiledFunction().getC() : "/* FAILED: " + error.replace("*/", "* /") + " */\n");
            Files.writeString(output.resolve(stem + ".c"), c);
            StringBuilder assembly = new StringBuilder("; " + f.getName() + " at " + hex(f.getEntryPoint()) +
                "\n; Original SHA-256 " + HASH + "\n");
            long instructionBytes = 0; int instructionCount = 0;
            var body = currentProgram.getListing().getInstructions(f.getBody(), true);
            while (body.hasNext()) {
                Instruction i = body.next(); instructionBytes += i.getLength(); instructionCount++;
                assembly.append(i.getAddress()).append("  ").append(HexFormat.of().formatHex(i.getBytes())).append("  ").append(i).append("\n");
            }
            Files.writeString(output.resolve(stem + ".asm"), assembly.toString());
            JsonObject row = new JsonObject(); row.addProperty("entry", hex(f.getEntryPoint()));
            row.addProperty("name", f.getName()); row.addProperty("status", success ? "decompiled" : "failed");
            row.addProperty("diagnostic", error); row.addProperty("body_bytes", f.getBody().getNumAddresses());
            row.addProperty("instruction_bytes", instructionBytes); row.addProperty("instruction_count", instructionCount);
            row.add("flow_ranges", flowRanges); row.add("switch_tables", switches); row.add("flow_conflicts", flowConflicts);
            row.addProperty("c", stem + ".c"); row.addProperty("assembly", stem + ".asm");
            row.addProperty("c_sha256", digest(output.resolve(stem + ".c")));
            row.addProperty("assembly_sha256", digest(output.resolve(stem + ".asm"))); exports.add(row);
            if (++index % 100 == 0) println("Exported " + index + " functions; failed " + failed);
        }
        dc.dispose(); report.add("exports", exports); report.addProperty("failed_decompilations", failed);
        report.addProperty("limits", "All detected functions exported; metadata protected; interior roots unresolved. Decompiled output and signature names do not establish correct boundaries, effect equivalence, or full executable discovery.");
        Files.writeString(output.resolve("export-manifest.json"), new GsonBuilder().setPrettyPrinting().create().toJson(report) + "\n");
        println("Whole-program export complete: " + exports.size() + " functions; failed " + failed);
    }
}
