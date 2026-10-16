// Export reviewable C-like source from the original, read-only PE image.
// Run as a Ghidra headless post-script; see reference/original/README.md.
// @category TSW
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.security.MessageDigest;
import java.util.*;

public class ExportOriginal extends GhidraScript {
    private static final String HASH = "41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779";
    private static final long START = 0x440000, END = 0x489000;

    private String sourceFile(Function f) {
        return String.format("%08x_%s.c", f.getEntryPoint().getOffset(),
            f.getName().replaceAll("[^a-zA-Z0-9_]", "_"));
    }

    private void data(long address, String name, DataType type) throws Exception {
        Address start = toAddr(address);
        clearListing(start, start.add(type.getLength() - 1));
        createData(start, type);
        currentProgram.getSymbolTable().createLabel(start, name, SourceType.USER_DEFINED).setPrimary();
    }

    @Override public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) throw new IllegalArgumentException("Pass the source export directory");
        Path output = Paths.get(args[0]);
        String executablePath = currentProgram.getExecutablePath();
        // Ghidra stores imported Windows paths in slash-prefixed URI form.
        if (executablePath.matches("^/[A-Za-z]:/.*")) executablePath = executablePath.substring(1);
        String hash = HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256")
            .digest(Files.readAllBytes(Paths.get(executablePath))));
        if (!HASH.equals(hash)) throw new IllegalStateException("Review addresses for a different executable: " + hash);
        Files.createDirectories(output);

        StructureDataType hero = new StructureDataType("OriginalHero", 0x2ac);
        Object[][] fields = {
            {0x00,"hp"},{0x04,"attack"},{0x08,"defense"},{0x0c,"gold"},
            {0x10,"floor"},{0x18,"x"},{0x1c,"y"},{0x20,"yellow_keys"},{0x24,"red_keys"},{0x28,"blue_keys"},
            {0x3c,"sword"},{0x40,"shield"},{0x44,"hero_orb"},{0x48,"wisdom_orb"},{0x4c,"flight_orb"},
            {0x50,"cross"},{0x54,"elixir"},{0x58,"mattock"},{0x5c,"bomb"},{0x60,"warp_staff"},
            {0x64,"ascent_wing"},{0x68,"descent_wing"},{0x6c,"dragon_slayer"},{0x70,"snow_crystal"},
            {0x74,"magic_key"},{0x78,"super_mattock"},{0x7c,"lucky_gold"},
            {0x180,"floor2_thief_tunnel_started"},{0x1d8,"floor29_thief_heard"},{0x1e8,"floor35_thief_heard"},
            {0x26c,"floor32_arrival_seen"},{0x270,"zeno_sealed"},{0x27c,"cycle_factor_minus_one"},{0x280,"later_cycle"}
        };
        for (Object[] field : fields) hero.replaceAtOffset((Integer)field[0], IntegerDataType.dataType, 4, (String)field[1], null);
        data(0x4b8688, "original_hero", hero);
        StructureDataType enemy = new StructureDataType("OriginalEnemy", 0);
        for (String field : new String[]{"hp","attack","defense","gold"}) enemy.add(IntegerDataType.dataType, field, null);
        data(0x489910, "original_monsters", new ArrayDataType(enemy, 33, 16));
        data(0x4b8934, "original_maps", new ArrayDataType(new ArrayDataType(ByteDataType.dataType, 123, 1), 51, 123));
        StructureDataType record = new StructureDataType("OriginalCommand", 0);
        for (String field : new String[]{"opcode","a","b"}) record.add(WordDataType.dataType, field, null);
        // Name one record at the base; do not invent an unverified capacity.
        data(0x48c74c, "event_stack", new ArrayDataType(record, 1, 6));
        Object[][] globals = {{0x48c554L,"door_opened"},{0x48c558L,"scratch_index"},
            {0x48c55cL,"neighbor_index"},{0x48c574L,"selected_item"},{0x48c584L,"contact_index"},
            {0x48c58cL,"tile_class_or_message"},{0x48c594L,"bomb_gold"},{0x48c5acL,"event_cursor"},
            {0x48c5b8L,"monster_index"},{0x48c5a4L,"dialogue_continue_stage"}};
        for (Object[] field : globals) data((Long)field[0], (String)field[1], DWordDataType.dataType);

        Object[][] routines = {{0x442dc8L,"kaidanwork"},{0x444490L,"handan"},{0x449014L,"syounin"},{0x449708L,"roujin"},
            {0x44a480L,"taisen"},{0x44bc0cL,"start_event_timer"},{0x44bc34L,"toroad2"},
            {0x44c5c4L,"mazyutu1"},{0x44da10L,"dialogue_continue"},{0x450bc5L,"use_selected_item"},
            {0x451c20L,"classify_neighbor"},{0x455cb8L,"initialize_cycle"},{0x46397cL,"mevent"},
            {0x464048L,"opening_capture"},{0x465900L,"touzoku"},{0x4660d0L,"doorstackin"},
            {0x4664e4L,"moncheck"},{0x46cb1cL,"ichicheck"},{0x47beacL,"doorcheck"}};
        for (Object[] routine : routines) {
            Address address = toAddr((Long)routine[0]);
            Function f = getFunctionContaining(address);
            if (f == null) f = createFunction(address, (String)routine[1]);
            if (f == null) throw new IllegalStateException("No function for " + routine[1]);
            f.setName((String)routine[1], SourceType.USER_DEFINED);
        }

        DecompInterface decompiler = new DecompInterface();
        if (!decompiler.openProgram(currentProgram)) throw new IllegalStateException(decompiler.getLastMessage());
        StringBuilder index = new StringBuilder("# Original game function export\n\n");
        index.append("Source SHA-256: `").append(hash).append("`. Generated with Ghidra ")
             .append(ghidra.framework.Application.getApplicationVersion()).append(".\n\n")
             .append("C-like decompiler output for every detected function entering 0x440000..0x488FFF. ")
             .append("This is an inspection corpus, not compilable game source or proof that each branch is verified. ")
             .append("Unknown fields and helper names remain explicit. Reviewed routines and probe evidence are indexed in ../README.md.\n\n")
             .append("| Entry | Function | Source | Result |\n|---|---|---|---|\n");
        StringBuilder calls = new StringBuilder("# Original direct-call inventory\n\n");
        calls.append("Detected direct calls from the exported function range. Indirect calls through Delphi objects, ")
             .append("callbacks and computed dispatch need separate inspection; this list is not a complete runtime call graph. ")
             .append("Callees outside the exported range are named with addresses but have no source link here.\n\n")
             .append("| Caller | Detected callees |\n|---|---|\n");
        int count = 0, failed = 0;
        var functions = currentProgram.getFunctionManager().getFunctions(true);
        while (functions.hasNext()) {
            Function f = functions.next();
            long entry = f.getEntryPoint().getOffset();
            if (entry < START || entry >= END) continue;
            String file = sourceFile(f);
            DecompileResults result = decompiler.decompileFunction(f, f.getName().equals("moncheck") ? 600 : 120, monitor);
            boolean success = result.decompileCompleted();
            String source = "/* Original TSW v1.2, SHA-256 " + hash + ".\n"
                + " * Function entry " + f.getEntryPoint() + ". Ghidra C-like inspection output.\n"
                + " * Review assembly/probes before treating inferred types or arithmetic as verified.\n */\n\n";
            source += success ? result.getDecompiledFunction().getC() : "/* Decompiler failed: " + result.getErrorMessage() + " */\n";
            Files.writeString(output.resolve(file), source.replace("\r\n", "\n")
                .replaceAll("(?m)[ \\t]+$", "").stripTrailing() + "\n", StandardCharsets.UTF_8);
            index.append(String.format("| `0x%08X` | `%s` | [%s](%s) | %s |\n", entry, f.getName(), file, file, success ? "Exported" : "FAILED"));
            List<Function> callees = new ArrayList<>(f.getCalledFunctions(monitor));
            callees.sort(Comparator.comparingLong(callee -> callee.getEntryPoint().getOffset()));
            List<String> links = new ArrayList<>();
            for (Function callee : callees) {
                long target = callee.getEntryPoint().getOffset();
                String label = String.format("%s (0x%08X)", callee.getName(), target);
                links.add(target >= START && target < END
                    ? "[" + label + "](" + sourceFile(callee) + ")" : "`" + label + "` (outside export)");
            }
            calls.append("| [").append(f.getName()).append("](").append(file).append(") | ")
                 .append(links.isEmpty() ? "None detected" : String.join(", ", links)).append(" |\n");
            count++;
            if (!success) failed++;
        }
        decompiler.dispose();
        index.append("\nExported ").append(count).append(" detected functions; failed ").append(failed).append(".\n");
        Files.writeString(output.resolve("INDEX.md"), index.toString(), StandardCharsets.UTF_8);
        Files.writeString(output.resolve("CALLS.md"), calls.toString(), StandardCharsets.UTF_8);
        println("Exported " + count + " game functions; failures " + failed);
        if (failed != 0) throw new IllegalStateException("Review failed decompilations before claiming complete export");
    }
}
