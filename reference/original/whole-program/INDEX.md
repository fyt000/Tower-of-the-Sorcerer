# Whole-program accounting index

Pinned original SHA-256: `41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.

3,298 detected functions have C-like and assembly exports; 0 failed decompilations. Decompilation success does not mean the function was translated or behaviorally verified.

| CODE byte classification | Virtual bytes |
|---|---:|
| validated-delphi-metadata | 50,850 |
| unresolved | 14,369 |
| defined-data-unreviewed | 6,718 |
| decoded-instruction | 482,146 |
| validated-switch-data | 2,508 |
| metadata-instruction-conflict | 101 |

These add to 556,692 virtual CODE bytes; 364 raw padding bytes are separate. Unresolved bytes and metadata/instruction conflicts remain open findings.

See [REVIEW.md](REVIEW.md) for conclusions, [ledger.json](ledger.json) for the complete ledger, [structural-inventory.json](structural-inventory.json) for classes/properties/signatures, and [byte-ledger.tsv](byte-ledger.tsv) for the byte partition. The ledger also inventories every PE section/file byte, import and resource.

| Entry | Ghidra name | Runtime name candidates | C-like | Assembly |
|---|---|---|---|---|
| `0x00401228` | `CloseHandle` |  | [decompiled](decompiled/00401228.c) | [assembly](decompiled/00401228.asm) |
| `0x00401230` | `CreateFileA` |  | [decompiled](decompiled/00401230.c) | [assembly](decompiled/00401230.asm) |
| `0x00401238` | `ExitProcess` |  | [decompiled](decompiled/00401238.c) | [assembly](decompiled/00401238.asm) |
| `0x00401240` | `GetFileType` |  | [decompiled](decompiled/00401240.c) | [assembly](decompiled/00401240.asm) |
| `0x00401248` | `GetFileSize` |  | [decompiled](decompiled/00401248.c) | [assembly](decompiled/00401248.asm) |
| `0x00401250` | `GetStdHandle` |  | [decompiled](decompiled/00401250.c) | [assembly](decompiled/00401250.asm) |
| `0x00401258` | `GetStartupInfoA` |  | [decompiled](decompiled/00401258.c) | [assembly](decompiled/00401258.asm) |
| `0x00401260` | `MessageBoxA` |  | [decompiled](decompiled/00401260.c) | [assembly](decompiled/00401260.asm) |
| `0x00401268` | `RaiseException` |  | [decompiled](decompiled/00401268.c) | [assembly](decompiled/00401268.asm) |
| `0x00401270` | `ReadFile` |  | [decompiled](decompiled/00401270.c) | [assembly](decompiled/00401270.asm) |
| `0x00401278` | `RtlUnwind` |  | [decompiled](decompiled/00401278.c) | [assembly](decompiled/00401278.asm) |
| `0x00401280` | `SetEndOfFile` |  | [decompiled](decompiled/00401280.c) | [assembly](decompiled/00401280.asm) |
| `0x00401288` | `SetFilePointer` |  | [decompiled](decompiled/00401288.c) | [assembly](decompiled/00401288.asm) |
| `0x00401290` | `WriteFile` |  | [decompiled](decompiled/00401290.c) | [assembly](decompiled/00401290.asm) |
| `0x00401298` | `GetCurrentDirectoryA` |  | [decompiled](decompiled/00401298.c) | [assembly](decompiled/00401298.asm) |
| `0x004012a0` | `GetCommandLineA` |  | [decompiled](decompiled/004012a0.c) | [assembly](decompiled/004012a0.asm) |
| `0x004012a8` | `GetLastError` |  | [decompiled](decompiled/004012a8.c) | [assembly](decompiled/004012a8.asm) |
| `0x004012b0` | `GetModuleHandleA` |  | [decompiled](decompiled/004012b0.c) | [assembly](decompiled/004012b0.asm) |
| `0x004012b8` | `MultiByteToWideChar` |  | [decompiled](decompiled/004012b8.c) | [assembly](decompiled/004012b8.asm) |
| `0x004012c0` | `SetCurrentDirectoryA` |  | [decompiled](decompiled/004012c0.c) | [assembly](decompiled/004012c0.asm) |
| `0x004012c8` | `TlsGetValue` |  | [decompiled](decompiled/004012c8.c) | [assembly](decompiled/004012c8.asm) |
| `0x004012d0` | `TlsSetValue` |  | [decompiled](decompiled/004012d0.c) | [assembly](decompiled/004012d0.asm) |
| `0x004012d8` | `WideCharToMultiByte` |  | [decompiled](decompiled/004012d8.c) | [assembly](decompiled/004012d8.asm) |
| `0x004012e0` | `SysAllocStringLen` |  | [decompiled](decompiled/004012e0.c) | [assembly](decompiled/004012e0.asm) |
| `0x004012e8` | `SysStringLen` |  | [decompiled](decompiled/004012e8.c) | [assembly](decompiled/004012e8.asm) |
| `0x004012f0` | `VariantClear` |  | [decompiled](decompiled/004012f0.c) | [assembly](decompiled/004012f0.asm) |
| `0x004012f8` | `VariantCopyInd` |  | [decompiled](decompiled/004012f8.c) | [assembly](decompiled/004012f8.asm) |
| `0x00401300` | `VariantChangeTypeEx` |  | [decompiled](decompiled/00401300.c) | [assembly](decompiled/00401300.asm) |
| `0x00401308` | `LocalAlloc` |  | [decompiled](decompiled/00401308.c) | [assembly](decompiled/00401308.asm) |
| `0x00401310` | `LocalFree` |  | [decompiled](decompiled/00401310.c) | [assembly](decompiled/00401310.asm) |
| `0x00401318` | `VirtualAlloc` |  | [decompiled](decompiled/00401318.c) | [assembly](decompiled/00401318.asm) |
| `0x00401320` | `VirtualFree` |  | [decompiled](decompiled/00401320.c) | [assembly](decompiled/00401320.asm) |
| `0x00401328` | `InitializeCriticalSection` |  | [decompiled](decompiled/00401328.c) | [assembly](decompiled/00401328.asm) |
| `0x00401330` | `EnterCriticalSection` |  | [decompiled](decompiled/00401330.c) | [assembly](decompiled/00401330.asm) |
| `0x00401338` | `LeaveCriticalSection` |  | [decompiled](decompiled/00401338.c) | [assembly](decompiled/00401338.asm) |
| `0x00401340` | `DeleteCriticalSection` |  | [decompiled](decompiled/00401340.c) | [assembly](decompiled/00401340.asm) |
| `0x00401348` | `FUN_00401348` |  | [decompiled](decompiled/00401348.c) | [assembly](decompiled/00401348.asm) |
| `0x00401398` | `FUN_00401398` |  | [decompiled](decompiled/00401398.c) | [assembly](decompiled/00401398.asm) |
| `0x004013a0` | `FUN_004013a0` |  | [decompiled](decompiled/004013a0.c) | [assembly](decompiled/004013a0.asm) |
| `0x004013d0` | `FUN_004013d0` |  | [decompiled](decompiled/004013d0.c) | [assembly](decompiled/004013d0.asm) |
| `0x004013e8` | `FUN_004013e8` |  | [decompiled](decompiled/004013e8.c) | [assembly](decompiled/004013e8.asm) |
| `0x0040145c` | `FUN_0040145c` |  | [decompiled](decompiled/0040145c.c) | [assembly](decompiled/0040145c.asm) |
| `0x004014ec` | `FUN_004014ec` |  | [decompiled](decompiled/004014ec.c) | [assembly](decompiled/004014ec.asm) |
| `0x00401550` | `FUN_00401550` |  | [decompiled](decompiled/00401550.c) | [assembly](decompiled/00401550.asm) |
| `0x004015c8` | `FUN_004015c8` |  | [decompiled](decompiled/004015c8.c) | [assembly](decompiled/004015c8.asm) |
| `0x00401680` | `FUN_00401680` |  | [decompiled](decompiled/00401680.c) | [assembly](decompiled/00401680.asm) |
| `0x00401714` | `FUN_00401714` |  | [decompiled](decompiled/00401714.c) | [assembly](decompiled/00401714.asm) |
| `0x00401794` | `FUN_00401794` |  | [decompiled](decompiled/00401794.c) | [assembly](decompiled/00401794.asm) |
| `0x00401824` | `FUN_00401824` |  | [decompiled](decompiled/00401824.c) | [assembly](decompiled/00401824.asm) |
| `0x00401948` | `FUN_00401948` |  | [decompiled](decompiled/00401948.c) | [assembly](decompiled/00401948.asm) |
| `0x004019d4` | `FUN_004019d4` |  | [decompiled](decompiled/004019d4.c) | [assembly](decompiled/004019d4.asm) |
| `0x00401a8a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00401a8a.c) | [assembly](decompiled/00401a8a.asm) |
| `0x00401a8f` | `root_00401a8f` |  | [decompiled](decompiled/00401a8f.c) | [assembly](decompiled/00401a8f.asm) |
| `0x00401a98` | `FUN_00401a98` |  | [decompiled](decompiled/00401a98.c) | [assembly](decompiled/00401a98.asm) |
| `0x00401b70` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00401b70.c) | [assembly](decompiled/00401b70.asm) |
| `0x00401b75` | `root_00401b75` |  | [decompiled](decompiled/00401b75.c) | [assembly](decompiled/00401b75.asm) |
| `0x00401b7c` | `FUN_00401b7c` |  | [decompiled](decompiled/00401b7c.c) | [assembly](decompiled/00401b7c.asm) |
| `0x00401bd0` | `FUN_00401bd0` |  | [decompiled](decompiled/00401bd0.c) | [assembly](decompiled/00401bd0.asm) |
| `0x00401c00` | `FUN_00401c00` |  | [decompiled](decompiled/00401c00.c) | [assembly](decompiled/00401c00.asm) |
| `0x00401c30` | `FUN_00401c30` |  | [decompiled](decompiled/00401c30.c) | [assembly](decompiled/00401c30.asm) |
| `0x00401c54` | `FUN_00401c54` |  | [decompiled](decompiled/00401c54.c) | [assembly](decompiled/00401c54.asm) |
| `0x00401c7c` | `FUN_00401c7c` |  | [decompiled](decompiled/00401c7c.c) | [assembly](decompiled/00401c7c.asm) |
| `0x00401cec` | `FUN_00401cec` |  | [decompiled](decompiled/00401cec.c) | [assembly](decompiled/00401cec.asm) |
| `0x00401d24` | `FUN_00401d24` |  | [decompiled](decompiled/00401d24.c) | [assembly](decompiled/00401d24.asm) |
| `0x00401dbc` | `FUN_00401dbc` |  | [decompiled](decompiled/00401dbc.c) | [assembly](decompiled/00401dbc.asm) |
| `0x00401e3c` | `FUN_00401e3c` |  | [decompiled](decompiled/00401e3c.c) | [assembly](decompiled/00401e3c.asm) |
| `0x00401e88` | `FUN_00401e88` |  | [decompiled](decompiled/00401e88.c) | [assembly](decompiled/00401e88.asm) |
| `0x00401f14` | `FUN_00401f14` |  | [decompiled](decompiled/00401f14.c) | [assembly](decompiled/00401f14.asm) |
| `0x00401f40` | `FUN_00401f40` |  | [decompiled](decompiled/00401f40.c) | [assembly](decompiled/00401f40.asm) |
| `0x00401f74` | `FUN_00401f74` |  | [decompiled](decompiled/00401f74.c) | [assembly](decompiled/00401f74.asm) |
| `0x00401f9c` | `FUN_00401f9c` |  | [decompiled](decompiled/00401f9c.c) | [assembly](decompiled/00401f9c.asm) |
| `0x00402090` | `FUN_00402090` | system.SysGetMem | [decompiled](decompiled/00402090.c) | [assembly](decompiled/00402090.asm) |
| `0x00402204` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00402204.c) | [assembly](decompiled/00402204.asm) |
| `0x00402209` | `root_00402209` |  | [decompiled](decompiled/00402209.c) | [assembly](decompiled/00402209.asm) |
| `0x00402218` | `FUN_00402218` | system.SysFreeMem | [decompiled](decompiled/00402218.c) | [assembly](decompiled/00402218.asm) |
| `0x004023aa` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004023aa.c) | [assembly](decompiled/004023aa.asm) |
| `0x004023af` | `root_004023af` |  | [decompiled](decompiled/004023af.c) | [assembly](decompiled/004023af.asm) |
| `0x004023bc` | `FUN_004023bc` |  | [decompiled](decompiled/004023bc.c) | [assembly](decompiled/004023bc.asm) |
| `0x0040258c` | `FUN_0040258c` | system.SysReallocMem | [decompiled](decompiled/0040258c.c) | [assembly](decompiled/0040258c.asm) |
| `0x0040263e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040263e.c) | [assembly](decompiled/0040263e.asm) |
| `0x00402643` | `root_00402643` |  | [decompiled](decompiled/00402643.c) | [assembly](decompiled/00402643.asm) |
| `0x00402650` | `FUN_00402650` |  | [decompiled](decompiled/00402650.c) | [assembly](decompiled/00402650.asm) |
| `0x00402668` | `FUN_00402668` |  | [decompiled](decompiled/00402668.c) | [assembly](decompiled/00402668.asm) |
| `0x00402680` | `FUN_00402680` | system.@ReallocMem | [decompiled](decompiled/00402680.c) | [assembly](decompiled/00402680.asm) |
| `0x004026d0` | `FUN_004026d0` |  | [decompiled](decompiled/004026d0.c) | [assembly](decompiled/004026d0.asm) |
| `0x00402710` | `FUN_00402710` | system.@_IOTest | [decompiled](decompiled/00402710.c) | [assembly](decompiled/00402710.asm) |
| `0x00402730` | `FUN_00402730` |  | [decompiled](decompiled/00402730.c) | [assembly](decompiled/00402730.asm) |
| `0x00402740` | `FUN_00402740` |  | [decompiled](decompiled/00402740.c) | [assembly](decompiled/00402740.asm) |
| `0x0040274c` | `FUN_0040274c` | system.@ChDir, system.@RmDir | [decompiled](decompiled/0040274c.c) | [assembly](decompiled/0040274c.asm) |
| `0x00402768` | `FUN_00402768` | system.@LGetDir | [decompiled](decompiled/00402768.c) | [assembly](decompiled/00402768.asm) |
| `0x004027e0` | `FUN_004027e0` | system.@SGetDir | [decompiled](decompiled/004027e0.c) | [assembly](decompiled/004027e0.asm) |
| `0x00402848` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00402848.c) | [assembly](decompiled/00402848.asm) |
| `0x0040284d` | `root_0040284d` |  | [decompiled](decompiled/0040284d.c) | [assembly](decompiled/0040284d.asm) |
| `0x00402870` | `FUN_00402870` | system.Move | [decompiled](decompiled/00402870.c) | [assembly](decompiled/00402870.asm) |
| `0x004028b0` | `FUN_004028b0` |  | [decompiled](decompiled/004028b0.c) | [assembly](decompiled/004028b0.asm) |
| `0x004028c0` | `FUN_004028c0` |  | [decompiled](decompiled/004028c0.c) | [assembly](decompiled/004028c0.asm) |
| `0x004028cc` | `FUN_004028cc` | system.@PStrNCat | [decompiled](decompiled/004028cc.c) | [assembly](decompiled/004028cc.asm) |
| `0x004028fc` | `FUN_004028fc` | system.@PStrCpy | [decompiled](decompiled/004028fc.c) | [assembly](decompiled/004028fc.asm) |
| `0x00402918` | `FUN_00402918` | system.@PStrNCpy | [decompiled](decompiled/00402918.c) | [assembly](decompiled/00402918.asm) |
| `0x00402948` | `FUN_00402948` | system.@AStrCmp | [decompiled](decompiled/00402948.c) | [assembly](decompiled/00402948.asm) |
| `0x004029b8` | `FUN_004029b8` | system.@FillChar | [decompiled](decompiled/004029b8.c) | [assembly](decompiled/004029b8.asm) |
| `0x004029d8` | `FUN_004029d8` | system.@ValLong | [decompiled](decompiled/004029d8.c) | [assembly](decompiled/004029d8.asm) |
| `0x00402a80` | `FUN_00402a80` | system.@_CLenToPasStr | [decompiled](decompiled/00402a80.c) | [assembly](decompiled/00402a80.asm) |
| `0x00402aa4` | `RegOpenKeyExA` |  | [decompiled](decompiled/00402aa4.c) | [assembly](decompiled/00402aa4.asm) |
| `0x00402aac` | `RegQueryValueExA` |  | [decompiled](decompiled/00402aac.c) | [assembly](decompiled/00402aac.asm) |
| `0x00402ab4` | `RegCloseKey` |  | [decompiled](decompiled/00402ab4.c) | [assembly](decompiled/00402ab4.asm) |
| `0x00402abc` | `FUN_00402abc` |  | [decompiled](decompiled/00402abc.c) | [assembly](decompiled/00402abc.asm) |
| `0x00402b6c` | `FUN_00402b6c` |  | [decompiled](decompiled/00402b6c.c) | [assembly](decompiled/00402b6c.asm) |
| `0x00402b78` | `FUN_00402b78` |  | [decompiled](decompiled/00402b78.c) | [assembly](decompiled/00402b78.asm) |
| `0x00402b7c` | `FUN_00402b7c` | system.TObject.ClassName | [decompiled](decompiled/00402b7c.c) | [assembly](decompiled/00402b7c.asm) |
| `0x00402b90` | `FUN_00402b90` | system.TObject.ClassNameIs | [decompiled](decompiled/00402b90.c) | [assembly](decompiled/00402b90.asm) |
| `0x00402bb8` | `FUN_00402bb8` |  | [decompiled](decompiled/00402bb8.c) | [assembly](decompiled/00402bb8.asm) |
| `0x00402bbc` | `root_00402bbc` | system.TObject.NewInstance | [decompiled](decompiled/00402bbc.c) | [assembly](decompiled/00402bbc.asm) |
| `0x00402be4` | `root_00402be4` | system.TObject.FreeInstance | [decompiled](decompiled/00402be4.c) | [assembly](decompiled/00402be4.asm) |
| `0x00402c08` | `root_00402c08` |  | [decompiled](decompiled/00402c08.c) | [assembly](decompiled/00402c08.asm) |
| `0x00402c0c` | `FUN_00402c0c` | system.TObject.Create | [decompiled](decompiled/00402c0c.c) | [assembly](decompiled/00402c0c.asm) |
| `0x00402c28` | `FUN_00402c28` |  | [decompiled](decompiled/00402c28.c) | [assembly](decompiled/00402c28.asm) |
| `0x00402c34` | `FUN_00402c34` |  | [decompiled](decompiled/00402c34.c) | [assembly](decompiled/00402c34.asm) |
| `0x00402c40` | `root_00402c40` | system.TObject.InitInstance | [decompiled](decompiled/00402c40.c) | [assembly](decompiled/00402c40.asm) |
| `0x00402c5c` | `root_00402c5c` | system.TObject.CleanupInstance | [decompiled](decompiled/00402c5c.c) | [assembly](decompiled/00402c5c.asm) |
| `0x00402c7c` | `FUN_00402c7c` | system.@IsClass | [decompiled](decompiled/00402c7c.c) | [assembly](decompiled/00402c7c.asm) |
| `0x00402c94` | `root_00402c94` | system.@AsClass | [decompiled](decompiled/00402c94.c) | [assembly](decompiled/00402c94.asm) |
| `0x00402cb0` | `FUN_00402cb0` |  | [decompiled](decompiled/00402cb0.c) | [assembly](decompiled/00402cb0.asm) |
| `0x00402cdc` | `FUN_00402cdc` |  | [decompiled](decompiled/00402cdc.c) | [assembly](decompiled/00402cdc.asm) |
| `0x00402cf4` | `root_00402cf4` |  | [decompiled](decompiled/00402cf4.c) | [assembly](decompiled/00402cf4.asm) |
| `0x00402d04` | `FUN_00402d04` |  | [decompiled](decompiled/00402d04.c) | [assembly](decompiled/00402d04.asm) |
| `0x00402d08` | `root_00402d08` |  | [decompiled](decompiled/00402d08.c) | [assembly](decompiled/00402d08.asm) |
| `0x00402d0c` | `FUN_00402d0c` | system.TObject.Dispatch | [decompiled](decompiled/00402d0c.c) | [assembly](decompiled/00402d0c.asm) |
| `0x00402d34` | `FUN_00402d34` | system.TObject.MethodAddress | [decompiled](decompiled/00402d34.c) | [assembly](decompiled/00402d34.asm) |
| `0x00402d80` | `FUN_00402d80` | system.TObject.MethodName | [decompiled](decompiled/00402d80.c) | [assembly](decompiled/00402d80.asm) |
| `0x00402dbc` | `FUN_00402dbc` | system.TObject.FieldAddress | [decompiled](decompiled/00402dbc.c) | [assembly](decompiled/00402dbc.asm) |
| `0x00402e0c` | `FUN_00402e0c` | system.@ClassCreate | [decompiled](decompiled/00402e0c.c) | [assembly](decompiled/00402e0c.asm) |
| `0x00402e48` | `FUN_00402e48` |  | [decompiled](decompiled/00402e48.c) | [assembly](decompiled/00402e48.asm) |
| `0x00402e50` | `root_00402e50` |  | [decompiled](decompiled/00402e50.c) | [assembly](decompiled/00402e50.asm) |
| `0x00402e6c` | `FUN_00402e6c` |  | [decompiled](decompiled/00402e6c.c) | [assembly](decompiled/00402e6c.asm) |
| `0x00402e8c` | `FUN_00402e8c` |  | [decompiled](decompiled/00402e8c.c) | [assembly](decompiled/00402e8c.asm) |
| `0x00402ea0` | `FUN_00402ea0` |  | [decompiled](decompiled/00402ea0.c) | [assembly](decompiled/00402ea0.asm) |
| `0x00402eb4` | `FUN_00402eb4` |  | [decompiled](decompiled/00402eb4.c) | [assembly](decompiled/00402eb4.asm) |
| `0x00402ec8` | `FUN_00402ec8` |  | [decompiled](decompiled/00402ec8.c) | [assembly](decompiled/00402ec8.asm) |
| `0x00402ee8` | `FUN_00402ee8` |  | [decompiled](decompiled/00402ee8.c) | [assembly](decompiled/00402ee8.asm) |
| `0x00402f10` | `FUN_00402f10` |  | [decompiled](decompiled/00402f10.c) | [assembly](decompiled/00402f10.asm) |
| `0x00402f2c` | `FUN_00402f2c` |  | [decompiled](decompiled/00402f2c.c) | [assembly](decompiled/00402f2c.asm) |
| `0x00402f4c` | `FUN_00402f4c` | system.@HandleAnyException | [decompiled](decompiled/00402f4c.c) | [assembly](decompiled/00402f4c.asm) |
| `0x00403010` | `FUN_00403010` | system.@HandleOnException | [decompiled](decompiled/00403010.c) | [assembly](decompiled/00403010.asm) |
| `0x00403140` | `FUN_00403140` | system.@HandleFinally | [decompiled](decompiled/00403140.c) | [assembly](decompiled/00403140.asm) |
| `0x00403178` | `root_00403178` | system.@SafeCall | [decompiled](decompiled/00403178.c) | [assembly](decompiled/00403178.asm) |
| `0x004031a8` | `root_004031a8` |  | [decompiled](decompiled/004031a8.c) | [assembly](decompiled/004031a8.asm) |
| `0x004031f8` | `FUN_004031f8` | system.@RaiseExcept | [decompiled](decompiled/004031f8.c) | [assembly](decompiled/004031f8.asm) |
| `0x00403214` | `root_00403214` | system.@RaiseAgain | [decompiled](decompiled/00403214.c) | [assembly](decompiled/00403214.asm) |
| `0x00403268` | `FUN_00403268` | system.@DoneExcept | [decompiled](decompiled/00403268.c) | [assembly](decompiled/00403268.asm) |
| `0x00403298` | `FUN_00403298` | system.@TryFinallyExit | [decompiled](decompiled/00403298.c) | [assembly](decompiled/00403298.asm) |
| `0x004032b0` | `FUN_004032b0` |  | [decompiled](decompiled/004032b0.c) | [assembly](decompiled/004032b0.asm) |
| `0x004033d8` | `FUN_004033d8` |  | [decompiled](decompiled/004033d8.c) | [assembly](decompiled/004033d8.asm) |
| `0x004033f8` | `FUN_004033f8` |  | [decompiled](decompiled/004033f8.c) | [assembly](decompiled/004033f8.asm) |
| `0x00403420` | `FUN_00403420` | system.@InitExe | [decompiled](decompiled/00403420.c) | [assembly](decompiled/00403420.asm) |
| `0x00403450` | `FUN_00403450` |  | [decompiled](decompiled/00403450.c) | [assembly](decompiled/00403450.asm) |
| `0x00403498` | `FUN_00403498` |  | [decompiled](decompiled/00403498.c) | [assembly](decompiled/00403498.asm) |
| `0x004034dc` | `FUN_004034dc` | system.@LStrClr | [decompiled](decompiled/004034dc.c) | [assembly](decompiled/004034dc.asm) |
| `0x004034fc` | `FUN_004034fc` | system.@LStrArrayClr | [decompiled](decompiled/004034fc.c) | [assembly](decompiled/004034fc.asm) |
| `0x0040352c` | `FUN_0040352c` | system.@LStrAsg | [decompiled](decompiled/0040352c.c) | [assembly](decompiled/0040352c.asm) |
| `0x00403570` | `FUN_00403570` | system.@LStrLAsg | [decompiled](decompiled/00403570.c) | [assembly](decompiled/00403570.asm) |
| `0x00403598` | `FUN_00403598` | system.@NewAnsiString | [decompiled](decompiled/00403598.c) | [assembly](decompiled/00403598.asm) |
| `0x004035bc` | `FUN_004035bc` | system.@LStrFromLenStr | [decompiled](decompiled/004035bc.c) | [assembly](decompiled/004035bc.asm) |
| `0x004035ec` | `FUN_004035ec` |  | [decompiled](decompiled/004035ec.c) | [assembly](decompiled/004035ec.asm) |
| `0x004035fc` | `FUN_004035fc` |  | [decompiled](decompiled/004035fc.c) | [assembly](decompiled/004035fc.asm) |
| `0x00403608` | `FUN_00403608` | system.@LStrFromPChar | [decompiled](decompiled/00403608.c) | [assembly](decompiled/00403608.asm) |
| `0x00403638` | `FUN_00403638` | system.@LStrFromArray | [decompiled](decompiled/00403638.c) | [assembly](decompiled/00403638.asm) |
| `0x00403650` | `FUN_00403650` |  | [decompiled](decompiled/00403650.c) | [assembly](decompiled/00403650.asm) |
| `0x00403658` | `FUN_00403658` | system.@LStrCat | [decompiled](decompiled/00403658.c) | [assembly](decompiled/00403658.asm) |
| `0x0040369c` | `FUN_0040369c` | system.@LStrCat3 | [decompiled](decompiled/0040369c.c) | [assembly](decompiled/0040369c.asm) |
| `0x004036be` | `FUN_004036be` |  | [decompiled](decompiled/004036be.c) | [assembly](decompiled/004036be.asm) |
| `0x00403710` | `FUN_00403710` | system.@LStrCatN | [decompiled](decompiled/00403710.c) | [assembly](decompiled/00403710.asm) |
| `0x00403760` | `FUN_00403760` | system.@LStrCmp | [decompiled](decompiled/00403760.c) | [assembly](decompiled/00403760.asm) |
| `0x00403804` | `FUN_00403804` |  | [decompiled](decompiled/00403804.c) | [assembly](decompiled/00403804.asm) |
| `0x00403814` | `FUN_00403814` |  | [decompiled](decompiled/00403814.c) | [assembly](decompiled/00403814.asm) |
| `0x00403820` | `FUN_00403820` | system.UniqueString | [decompiled](decompiled/00403820.c) | [assembly](decompiled/00403820.asm) |
| `0x00403854` | `FUN_00403854` | system.@LStrCopy | [decompiled](decompiled/00403854.c) | [assembly](decompiled/00403854.asm) |
| `0x00403894` | `FUN_00403894` | system.@LStrDelete | [decompiled](decompiled/00403894.c) | [assembly](decompiled/00403894.asm) |
| `0x004038dc` | `FUN_004038dc` | system.@LStrPos | [decompiled](decompiled/004038dc.c) | [assembly](decompiled/004038dc.asm) |
| `0x00403924` | `FUN_00403924` | system.@LStrSetLength | [decompiled](decompiled/00403924.c) | [assembly](decompiled/00403924.asm) |
| `0x00403988` | `FUN_00403988` | system.@LStrToString | [decompiled](decompiled/00403988.c) | [assembly](decompiled/00403988.asm) |
| `0x004039ac` | `FUN_004039ac` | system.@AddRefRecord, system.@FinalizeRecord, system.@InitializeRecord | [decompiled](decompiled/004039ac.c) | [assembly](decompiled/004039ac.asm) |
| `0x004039d4` | `FUN_004039d4` | system.@InitializeArray | [decompiled](decompiled/004039d4.c) | [assembly](decompiled/004039d4.asm) |
| `0x00403a58` | `FUN_00403a58` |  | [decompiled](decompiled/00403a58.c) | [assembly](decompiled/00403a58.asm) |
| `0x00403a64` | `FUN_00403a64` | system.@AddRefRecord, system.@FinalizeRecord, system.@InitializeRecord | [decompiled](decompiled/00403a64.c) | [assembly](decompiled/00403a64.asm) |
| `0x00403a8c` | `FUN_00403a8c` | system.@FinalizeArray | [decompiled](decompiled/00403a8c.c) | [assembly](decompiled/00403a8c.asm) |
| `0x00403b14` | `FUN_00403b14` |  | [decompiled](decompiled/00403b14.c) | [assembly](decompiled/00403b14.asm) |
| `0x00403b20` | `FUN_00403b20` | system.WideCharLenToStrVar | [decompiled](decompiled/00403b20.c) | [assembly](decompiled/00403b20.asm) |
| `0x00403bac` | `FUN_00403bac` | system.OleStrToStrVar | [decompiled](decompiled/00403bac.c) | [assembly](decompiled/00403bac.asm) |
| `0x00403bc8` | `FUN_00403bc8` | system.StringToOleStr | [decompiled](decompiled/00403bc8.c) | [assembly](decompiled/00403bc8.asm) |
| `0x00403c4c` | `thunk_FUN_004026d0` |  | [decompiled](decompiled/00403c4c.c) | [assembly](decompiled/00403c4c.asm) |
| `0x00403c5c` | `FUN_00403c5c` | system.VarClear | [decompiled](decompiled/00403c5c.c) | [assembly](decompiled/00403c5c.asm) |
| `0x00403c90` | `FUN_00403c90` |  | [decompiled](decompiled/00403c90.c) | [assembly](decompiled/00403c90.asm) |
| `0x00403d04` | `FUN_00403d04` |  | [decompiled](decompiled/00403d04.c) | [assembly](decompiled/00403d04.asm) |
| `0x00403d74` | `FUN_00403d74` |  | [decompiled](decompiled/00403d74.c) | [assembly](decompiled/00403d74.asm) |
| `0x00403da4` | `FUN_00403da4` |  | [decompiled](decompiled/00403da4.c) | [assembly](decompiled/00403da4.asm) |
| `0x00403dc4` | `FUN_00403dc4` | system.VarCast | [decompiled](decompiled/00403dc4.c) | [assembly](decompiled/00403dc4.asm) |
| `0x00403e3d` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00403e3d.c) | [assembly](decompiled/00403e3d.asm) |
| `0x00403e42` | `root_00403e42` |  | [decompiled](decompiled/00403e42.c) | [assembly](decompiled/00403e42.asm) |
| `0x00403e9c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00403e9c.c) | [assembly](decompiled/00403e9c.asm) |
| `0x00403ea1` | `root_00403ea1` |  | [decompiled](decompiled/00403ea1.c) | [assembly](decompiled/00403ea1.asm) |
| `0x00403ef0` | `thunk_FUN_00403c5c` |  | [decompiled](decompiled/00403ef0.c) | [assembly](decompiled/00403ef0.asm) |
| `0x00403f14` | `FUN_00403f14` |  | [decompiled](decompiled/00403f14.c) | [assembly](decompiled/00403f14.asm) |
| `0x00403f38` | `FUN_00403f38` |  | [decompiled](decompiled/00403f38.c) | [assembly](decompiled/00403f38.asm) |
| `0x0040414d` | `FUN_0040414d` | system.@Assign | [decompiled](decompiled/0040414d.c) | [assembly](decompiled/0040414d.asm) |
| `0x004041c8` | `FUN_004041c8` | system.@Flush | [decompiled](decompiled/004041c8.c) | [assembly](decompiled/004041c8.asm) |
| `0x004041f0` | `FUN_004041f0` | system.@BlockRead | [decompiled](decompiled/004041f0.c) | [assembly](decompiled/004041f0.asm) |
| `0x00404254` | `FUN_00404254` | system.@BlockWrite | [decompiled](decompiled/00404254.c) | [assembly](decompiled/00404254.asm) |
| `0x004042b8` | `FUN_004042b8` | system.@Close | [decompiled](decompiled/004042b8.c) | [assembly](decompiled/004042b8.asm) |
| `0x004042f4` | `FUN_004042f4` |  | [decompiled](decompiled/004042f4.c) | [assembly](decompiled/004042f4.asm) |
| `0x0040441c` | `FUN_0040441c` |  | [decompiled](decompiled/0040441c.c) | [assembly](decompiled/0040441c.asm) |
| `0x00404420` | `FUN_00404420` |  | [decompiled](decompiled/00404420.c) | [assembly](decompiled/00404420.asm) |
| `0x00404431` | `FUN_00404431` |  | [decompiled](decompiled/00404431.c) | [assembly](decompiled/00404431.asm) |
| `0x0040443c` | `FUN_0040443c` |  | [decompiled](decompiled/0040443c.c) | [assembly](decompiled/0040443c.asm) |
| `0x0040447e` | `FUN_0040447e` |  | [decompiled](decompiled/0040447e.c) | [assembly](decompiled/0040447e.asm) |
| `0x0040448c` | `FUN_0040448c` |  | [decompiled](decompiled/0040448c.c) | [assembly](decompiled/0040448c.asm) |
| `0x0040458d` | `FUN_0040458d` |  | [decompiled](decompiled/0040458d.c) | [assembly](decompiled/0040458d.asm) |
| `0x004045a4` | `FUN_004045a4` |  | [decompiled](decompiled/004045a4.c) | [assembly](decompiled/004045a4.asm) |
| `0x004045c4` | `FUN_004045c4` |  | [decompiled](decompiled/004045c4.c) | [assembly](decompiled/004045c4.asm) |
| `0x0040462f` | `FUN_0040462f` |  | [decompiled](decompiled/0040462f.c) | [assembly](decompiled/0040462f.asm) |
| `0x0040468f` | `FUN_0040468f` |  | [decompiled](decompiled/0040468f.c) | [assembly](decompiled/0040468f.asm) |
| `0x0040470c` | `FUN_0040470c` |  | [decompiled](decompiled/0040470c.c) | [assembly](decompiled/0040470c.asm) |
| `0x00404a10` | `FUN_00404a10` |  | [decompiled](decompiled/00404a10.c) | [assembly](decompiled/00404a10.asm) |
| `0x00404abc` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00404abc.c) | [assembly](decompiled/00404abc.asm) |
| `0x00404ac1` | `root_00404ac1` |  | [decompiled](decompiled/00404ac1.c) | [assembly](decompiled/00404ac1.asm) |
| `0x00404acc` | `CloseHandle` |  | [decompiled](decompiled/00404acc.c) | [assembly](decompiled/00404acc.asm) |
| `0x00404ad4` | `CompareStringA` |  | [decompiled](decompiled/00404ad4.c) | [assembly](decompiled/00404ad4.asm) |
| `0x00404adc` | `CreateDirectoryA` |  | [decompiled](decompiled/00404adc.c) | [assembly](decompiled/00404adc.asm) |
| `0x00404ae4` | `CreateFileA` |  | [decompiled](decompiled/00404ae4.c) | [assembly](decompiled/00404ae4.asm) |
| `0x00404aec` | `CreateThread` |  | [decompiled](decompiled/00404aec.c) | [assembly](decompiled/00404aec.asm) |
| `0x00404af4` | `FileTimeToDosDateTime` |  | [decompiled](decompiled/00404af4.c) | [assembly](decompiled/00404af4.asm) |
| `0x00404afc` | `FileTimeToLocalFileTime` |  | [decompiled](decompiled/00404afc.c) | [assembly](decompiled/00404afc.asm) |
| `0x00404b04` | `FindClose` |  | [decompiled](decompiled/00404b04.c) | [assembly](decompiled/00404b04.asm) |
| `0x00404b0c` | `FindFirstFileA` |  | [decompiled](decompiled/00404b0c.c) | [assembly](decompiled/00404b0c.asm) |
| `0x00404b14` | `FindNextFileA` |  | [decompiled](decompiled/00404b14.c) | [assembly](decompiled/00404b14.asm) |
| `0x00404b1c` | `FindResourceA` |  | [decompiled](decompiled/00404b1c.c) | [assembly](decompiled/00404b1c.asm) |
| `0x00404b24` | `FreeLibrary` |  | [decompiled](decompiled/00404b24.c) | [assembly](decompiled/00404b24.asm) |
| `0x00404b2c` | `FreeResource` |  | [decompiled](decompiled/00404b2c.c) | [assembly](decompiled/00404b2c.asm) |
| `0x00404b34` | `GetCurrentDirectoryA` |  | [decompiled](decompiled/00404b34.c) | [assembly](decompiled/00404b34.asm) |
| `0x00404b3c` | `GetCurrentProcess` |  | [decompiled](decompiled/00404b3c.c) | [assembly](decompiled/00404b3c.asm) |
| `0x00404b44` | `GetCurrentProcessId` |  | [decompiled](decompiled/00404b44.c) | [assembly](decompiled/00404b44.asm) |
| `0x00404b4c` | `GetCurrentThreadId` |  | [decompiled](decompiled/00404b4c.c) | [assembly](decompiled/00404b4c.asm) |
| `0x00404b54` | `GetDriveTypeA` |  | [decompiled](decompiled/00404b54.c) | [assembly](decompiled/00404b54.asm) |
| `0x00404b5c` | `GetLastError` |  | [decompiled](decompiled/00404b5c.c) | [assembly](decompiled/00404b5c.asm) |
| `0x00404b64` | `GetLocaleInfoA` |  | [decompiled](decompiled/00404b64.c) | [assembly](decompiled/00404b64.asm) |
| `0x00404b6c` | `GetLogicalDrives` |  | [decompiled](decompiled/00404b6c.c) | [assembly](decompiled/00404b6c.asm) |
| `0x00404b74` | `GetModuleFileNameA` |  | [decompiled](decompiled/00404b74.c) | [assembly](decompiled/00404b74.asm) |
| `0x00404b7c` | `GetModuleHandleA` |  | [decompiled](decompiled/00404b7c.c) | [assembly](decompiled/00404b7c.asm) |
| `0x00404b84` | `GetProcAddress` |  | [decompiled](decompiled/00404b84.c) | [assembly](decompiled/00404b84.asm) |
| `0x00404b8c` | `GetSystemDefaultLCID` |  | [decompiled](decompiled/00404b8c.c) | [assembly](decompiled/00404b8c.asm) |
| `0x00404b94` | `GetVersion` |  | [decompiled](decompiled/00404b94.c) | [assembly](decompiled/00404b94.asm) |
| `0x00404b9c` | `GetVersionExA` |  | [decompiled](decompiled/00404b9c.c) | [assembly](decompiled/00404b9c.asm) |
| `0x00404ba4` | `GetVolumeInformationA` |  | [decompiled](decompiled/00404ba4.c) | [assembly](decompiled/00404ba4.asm) |
| `0x00404bac` | `GetWindowsDirectoryA` |  | [decompiled](decompiled/00404bac.c) | [assembly](decompiled/00404bac.asm) |
| `0x00404bb4` | `GlobalAddAtomA` |  | [decompiled](decompiled/00404bb4.c) | [assembly](decompiled/00404bb4.asm) |
| `0x00404bbc` | `GlobalAlloc` |  | [decompiled](decompiled/00404bbc.c) | [assembly](decompiled/00404bbc.asm) |
| `0x00404bc4` | `GlobalDeleteAtom` |  | [decompiled](decompiled/00404bc4.c) | [assembly](decompiled/00404bc4.asm) |
| `0x00404bcc` | `GlobalFree` |  | [decompiled](decompiled/00404bcc.c) | [assembly](decompiled/00404bcc.asm) |
| `0x00404bd4` | `GlobalLock` |  | [decompiled](decompiled/00404bd4.c) | [assembly](decompiled/00404bd4.asm) |
| `0x00404bdc` | `GlobalHandle` |  | [decompiled](decompiled/00404bdc.c) | [assembly](decompiled/00404bdc.asm) |
| `0x00404be4` | `GlobalReAlloc` |  | [decompiled](decompiled/00404be4.c) | [assembly](decompiled/00404be4.asm) |
| `0x00404bec` | `GlobalUnlock` |  | [decompiled](decompiled/00404bec.c) | [assembly](decompiled/00404bec.asm) |
| `0x00404bf4` | `IsDBCSLeadByte` |  | [decompiled](decompiled/00404bf4.c) | [assembly](decompiled/00404bf4.asm) |
| `0x00404bfc` | `LoadLibraryA` |  | [decompiled](decompiled/00404bfc.c) | [assembly](decompiled/00404bfc.asm) |
| `0x00404c04` | `LoadResource` |  | [decompiled](decompiled/00404c04.c) | [assembly](decompiled/00404c04.asm) |
| `0x00404c0c` | `LockResource` |  | [decompiled](decompiled/00404c0c.c) | [assembly](decompiled/00404c0c.asm) |
| `0x00404c14` | `MulDiv` |  | [decompiled](decompiled/00404c14.c) | [assembly](decompiled/00404c14.asm) |
| `0x00404c1c` | `ReadFile` |  | [decompiled](decompiled/00404c1c.c) | [assembly](decompiled/00404c1c.asm) |
| `0x00404c24` | `SetErrorMode` |  | [decompiled](decompiled/00404c24.c) | [assembly](decompiled/00404c24.asm) |
| `0x00404c2c` | `SetFilePointer` |  | [decompiled](decompiled/00404c2c.c) | [assembly](decompiled/00404c2c.asm) |
| `0x00404c34` | `SizeofResource` |  | [decompiled](decompiled/00404c34.c) | [assembly](decompiled/00404c34.asm) |
| `0x00404c3c` | `TerminateThread` |  | [decompiled](decompiled/00404c3c.c) | [assembly](decompiled/00404c3c.asm) |
| `0x00404c44` | `VirtualAlloc` |  | [decompiled](decompiled/00404c44.c) | [assembly](decompiled/00404c44.asm) |
| `0x00404c4c` | `WriteFile` |  | [decompiled](decompiled/00404c4c.c) | [assembly](decompiled/00404c4c.asm) |
| `0x00404c54` | `WNetGetConnectionA` |  | [decompiled](decompiled/00404c54.c) | [assembly](decompiled/00404c54.asm) |
| `0x00404c5c` | `BitBlt` |  | [decompiled](decompiled/00404c5c.c) | [assembly](decompiled/00404c5c.asm) |
| `0x00404c64` | `CopyEnhMetaFileA` |  | [decompiled](decompiled/00404c64.c) | [assembly](decompiled/00404c64.asm) |
| `0x00404c6c` | `CreateBitmap` |  | [decompiled](decompiled/00404c6c.c) | [assembly](decompiled/00404c6c.asm) |
| `0x00404c74` | `CreateBrushIndirect` |  | [decompiled](decompiled/00404c74.c) | [assembly](decompiled/00404c74.asm) |
| `0x00404c7c` | `CreateCompatibleBitmap` |  | [decompiled](decompiled/00404c7c.c) | [assembly](decompiled/00404c7c.asm) |
| `0x00404c84` | `CreateCompatibleDC` |  | [decompiled](decompiled/00404c84.c) | [assembly](decompiled/00404c84.asm) |
| `0x00404c8c` | `CreateDIBitmap` |  | [decompiled](decompiled/00404c8c.c) | [assembly](decompiled/00404c8c.asm) |
| `0x00404c94` | `CreateFontIndirectA` |  | [decompiled](decompiled/00404c94.c) | [assembly](decompiled/00404c94.asm) |
| `0x00404c9c` | `CreatePalette` |  | [decompiled](decompiled/00404c9c.c) | [assembly](decompiled/00404c9c.asm) |
| `0x00404ca4` | `CreatePenIndirect` |  | [decompiled](decompiled/00404ca4.c) | [assembly](decompiled/00404ca4.asm) |
| `0x00404cac` | `CreateRectRgn` |  | [decompiled](decompiled/00404cac.c) | [assembly](decompiled/00404cac.asm) |
| `0x00404cb4` | `CreateSolidBrush` |  | [decompiled](decompiled/00404cb4.c) | [assembly](decompiled/00404cb4.asm) |
| `0x00404cbc` | `DeleteDC` |  | [decompiled](decompiled/00404cbc.c) | [assembly](decompiled/00404cbc.asm) |
| `0x00404cc4` | `DeleteEnhMetaFile` |  | [decompiled](decompiled/00404cc4.c) | [assembly](decompiled/00404cc4.asm) |
| `0x00404ccc` | `DeleteObject` |  | [decompiled](decompiled/00404ccc.c) | [assembly](decompiled/00404ccc.asm) |
| `0x00404cd4` | `EnumFontFamiliesA` |  | [decompiled](decompiled/00404cd4.c) | [assembly](decompiled/00404cd4.asm) |
| `0x00404cdc` | `EnumFontsA` |  | [decompiled](decompiled/00404cdc.c) | [assembly](decompiled/00404cdc.asm) |
| `0x00404ce4` | `ExcludeClipRect` |  | [decompiled](decompiled/00404ce4.c) | [assembly](decompiled/00404ce4.asm) |
| `0x00404cec` | `GetBitmapBits` |  | [decompiled](decompiled/00404cec.c) | [assembly](decompiled/00404cec.asm) |
| `0x00404cf4` | `GetClipBox` |  | [decompiled](decompiled/00404cf4.c) | [assembly](decompiled/00404cf4.asm) |
| `0x00404cfc` | `GetCurrentPositionEx` |  | [decompiled](decompiled/00404cfc.c) | [assembly](decompiled/00404cfc.asm) |
| `0x00404d04` | `GetDIBits` |  | [decompiled](decompiled/00404d04.c) | [assembly](decompiled/00404d04.asm) |
| `0x00404d0c` | `GetDeviceCaps` |  | [decompiled](decompiled/00404d0c.c) | [assembly](decompiled/00404d0c.asm) |
| `0x00404d14` | `GetEnhMetaFileBits` |  | [decompiled](decompiled/00404d14.c) | [assembly](decompiled/00404d14.asm) |
| `0x00404d1c` | `GetEnhMetaFileHeader` |  | [decompiled](decompiled/00404d1c.c) | [assembly](decompiled/00404d1c.asm) |
| `0x00404d24` | `GetEnhMetaFilePaletteEntries` |  | [decompiled](decompiled/00404d24.c) | [assembly](decompiled/00404d24.asm) |
| `0x00404d2c` | `GetObjectA` |  | [decompiled](decompiled/00404d2c.c) | [assembly](decompiled/00404d2c.asm) |
| `0x00404d34` | `GetPaletteEntries` |  | [decompiled](decompiled/00404d34.c) | [assembly](decompiled/00404d34.asm) |
| `0x00404d3c` | `GetPixel` |  | [decompiled](decompiled/00404d3c.c) | [assembly](decompiled/00404d3c.asm) |
| `0x00404d44` | `GetStockObject` |  | [decompiled](decompiled/00404d44.c) | [assembly](decompiled/00404d44.asm) |
| `0x00404d4c` | `GetSystemPaletteEntries` |  | [decompiled](decompiled/00404d4c.c) | [assembly](decompiled/00404d4c.asm) |
| `0x00404d54` | `GetTextExtentPointA` |  | [decompiled](decompiled/00404d54.c) | [assembly](decompiled/00404d54.asm) |
| `0x00404d5c` | `GetTextMetricsA` |  | [decompiled](decompiled/00404d5c.c) | [assembly](decompiled/00404d5c.asm) |
| `0x00404d64` | `GetWinMetaFileBits` |  | [decompiled](decompiled/00404d64.c) | [assembly](decompiled/00404d64.asm) |
| `0x00404d6c` | `GetWindowOrgEx` |  | [decompiled](decompiled/00404d6c.c) | [assembly](decompiled/00404d6c.asm) |
| `0x00404d74` | `IntersectClipRect` |  | [decompiled](decompiled/00404d74.c) | [assembly](decompiled/00404d74.asm) |
| `0x00404d7c` | `LineTo` |  | [decompiled](decompiled/00404d7c.c) | [assembly](decompiled/00404d7c.asm) |
| `0x00404d84` | `MoveToEx` |  | [decompiled](decompiled/00404d84.c) | [assembly](decompiled/00404d84.asm) |
| `0x00404d8c` | `PatBlt` |  | [decompiled](decompiled/00404d8c.c) | [assembly](decompiled/00404d8c.asm) |
| `0x00404d94` | `PlayEnhMetaFile` |  | [decompiled](decompiled/00404d94.c) | [assembly](decompiled/00404d94.asm) |
| `0x00404d9c` | `Polyline` |  | [decompiled](decompiled/00404d9c.c) | [assembly](decompiled/00404d9c.asm) |
| `0x00404da4` | `RealizePalette` |  | [decompiled](decompiled/00404da4.c) | [assembly](decompiled/00404da4.asm) |
| `0x00404dac` | `RectVisible` |  | [decompiled](decompiled/00404dac.c) | [assembly](decompiled/00404dac.asm) |
| `0x00404db4` | `Rectangle` |  | [decompiled](decompiled/00404db4.c) | [assembly](decompiled/00404db4.asm) |
| `0x00404dbc` | `RestoreDC` |  | [decompiled](decompiled/00404dbc.c) | [assembly](decompiled/00404dbc.asm) |
| `0x00404dc4` | `SaveDC` |  | [decompiled](decompiled/00404dc4.c) | [assembly](decompiled/00404dc4.asm) |
| `0x00404dcc` | `SelectObject` |  | [decompiled](decompiled/00404dcc.c) | [assembly](decompiled/00404dcc.asm) |
| `0x00404dd4` | `SelectPalette` |  | [decompiled](decompiled/00404dd4.c) | [assembly](decompiled/00404dd4.asm) |
| `0x00404ddc` | `SetBkColor` |  | [decompiled](decompiled/00404ddc.c) | [assembly](decompiled/00404ddc.asm) |
| `0x00404de4` | `SetBkMode` |  | [decompiled](decompiled/00404de4.c) | [assembly](decompiled/00404de4.asm) |
| `0x00404dec` | `SetEnhMetaFileBits` |  | [decompiled](decompiled/00404dec.c) | [assembly](decompiled/00404dec.asm) |
| `0x00404df4` | `SetROP2` |  | [decompiled](decompiled/00404df4.c) | [assembly](decompiled/00404df4.asm) |
| `0x00404dfc` | `SetStretchBltMode` |  | [decompiled](decompiled/00404dfc.c) | [assembly](decompiled/00404dfc.asm) |
| `0x00404e04` | `SetTextColor` |  | [decompiled](decompiled/00404e04.c) | [assembly](decompiled/00404e04.asm) |
| `0x00404e0c` | `SetViewportOrgEx` |  | [decompiled](decompiled/00404e0c.c) | [assembly](decompiled/00404e0c.asm) |
| `0x00404e14` | `SetWinMetaFileBits` |  | [decompiled](decompiled/00404e14.c) | [assembly](decompiled/00404e14.asm) |
| `0x00404e1c` | `SetWindowOrgEx` |  | [decompiled](decompiled/00404e1c.c) | [assembly](decompiled/00404e1c.asm) |
| `0x00404e24` | `StretchBlt` |  | [decompiled](decompiled/00404e24.c) | [assembly](decompiled/00404e24.asm) |
| `0x00404e2c` | `StretchDIBits` |  | [decompiled](decompiled/00404e2c.c) | [assembly](decompiled/00404e2c.asm) |
| `0x00404e34` | `TextOutA` |  | [decompiled](decompiled/00404e34.c) | [assembly](decompiled/00404e34.asm) |
| `0x00404e3c` | `UnrealizeObject` |  | [decompiled](decompiled/00404e3c.c) | [assembly](decompiled/00404e3c.asm) |
| `0x00404e44` | `AdjustWindowRectEx` |  | [decompiled](decompiled/00404e44.c) | [assembly](decompiled/00404e44.asm) |
| `0x00404e4c` | `CharLowerA` |  | [decompiled](decompiled/00404e4c.c) | [assembly](decompiled/00404e4c.asm) |
| `0x00404e54` | `BeginPaint` |  | [decompiled](decompiled/00404e54.c) | [assembly](decompiled/00404e54.asm) |
| `0x00404e5c` | `CallNextHookEx` |  | [decompiled](decompiled/00404e5c.c) | [assembly](decompiled/00404e5c.asm) |
| `0x00404e64` | `CallWindowProcA` |  | [decompiled](decompiled/00404e64.c) | [assembly](decompiled/00404e64.asm) |
| `0x00404e6c` | `CharLowerBuffA` |  | [decompiled](decompiled/00404e6c.c) | [assembly](decompiled/00404e6c.asm) |
| `0x00404e74` | `CheckMenuItem` |  | [decompiled](decompiled/00404e74.c) | [assembly](decompiled/00404e74.asm) |
| `0x00404e7c` | `ClientToScreen` |  | [decompiled](decompiled/00404e7c.c) | [assembly](decompiled/00404e7c.asm) |
| `0x00404e84` | `CreateIcon` |  | [decompiled](decompiled/00404e84.c) | [assembly](decompiled/00404e84.asm) |
| `0x00404e8c` | `CreateMenu` |  | [decompiled](decompiled/00404e8c.c) | [assembly](decompiled/00404e8c.asm) |
| `0x00404e94` | `CreatePopupMenu` |  | [decompiled](decompiled/00404e94.c) | [assembly](decompiled/00404e94.asm) |
| `0x00404e9c` | `CreateWindowExA` |  | [decompiled](decompiled/00404e9c.c) | [assembly](decompiled/00404e9c.asm) |
| `0x00404ea4` | `DefFrameProcA` |  | [decompiled](decompiled/00404ea4.c) | [assembly](decompiled/00404ea4.asm) |
| `0x00404eb4` | `DefWindowProcA` |  | [decompiled](decompiled/00404eb4.c) | [assembly](decompiled/00404eb4.asm) |
| `0x00404ebc` | `DeleteMenu` |  | [decompiled](decompiled/00404ebc.c) | [assembly](decompiled/00404ebc.asm) |
| `0x00404ec4` | `DestroyCursor` |  | [decompiled](decompiled/00404ec4.c) | [assembly](decompiled/00404ec4.asm) |
| `0x00404ecc` | `DestroyIcon` |  | [decompiled](decompiled/00404ecc.c) | [assembly](decompiled/00404ecc.asm) |
| `0x00404ed4` | `DestroyMenu` |  | [decompiled](decompiled/00404ed4.c) | [assembly](decompiled/00404ed4.asm) |
| `0x00404edc` | `DestroyWindow` |  | [decompiled](decompiled/00404edc.c) | [assembly](decompiled/00404edc.asm) |
| `0x00404ee4` | `DispatchMessageA` |  | [decompiled](decompiled/00404ee4.c) | [assembly](decompiled/00404ee4.asm) |
| `0x00404eec` | `DrawFocusRect` |  | [decompiled](decompiled/00404eec.c) | [assembly](decompiled/00404eec.asm) |
| `0x00404ef4` | `DrawFrameControl` |  | [decompiled](decompiled/00404ef4.c) | [assembly](decompiled/00404ef4.asm) |
| `0x00404efc` | `DrawIcon` |  | [decompiled](decompiled/00404efc.c) | [assembly](decompiled/00404efc.asm) |
| `0x00404f04` | `DrawMenuBar` |  | [decompiled](decompiled/00404f04.c) | [assembly](decompiled/00404f04.asm) |
| `0x00404f0c` | `DrawTextA` |  | [decompiled](decompiled/00404f0c.c) | [assembly](decompiled/00404f0c.asm) |
| `0x00404f14` | `EnableMenuItem` |  | [decompiled](decompiled/00404f14.c) | [assembly](decompiled/00404f14.asm) |
| `0x00404f1c` | `EnableWindow` |  | [decompiled](decompiled/00404f1c.c) | [assembly](decompiled/00404f1c.asm) |
| `0x00404f24` | `EndPaint` |  | [decompiled](decompiled/00404f24.c) | [assembly](decompiled/00404f24.asm) |
| `0x00404f2c` | `EnumThreadWindows` |  | [decompiled](decompiled/00404f2c.c) | [assembly](decompiled/00404f2c.asm) |
| `0x00404f34` | `EnumWindows` |  | [decompiled](decompiled/00404f34.c) | [assembly](decompiled/00404f34.asm) |
| `0x00404f3c` | `EqualRect` |  | [decompiled](decompiled/00404f3c.c) | [assembly](decompiled/00404f3c.asm) |
| `0x00404f44` | `FillRect` |  | [decompiled](decompiled/00404f44.c) | [assembly](decompiled/00404f44.asm) |
| `0x00404f4c` | `FindWindowA` |  | [decompiled](decompiled/00404f4c.c) | [assembly](decompiled/00404f4c.asm) |
| `0x00404f54` | `FrameRect` |  | [decompiled](decompiled/00404f54.c) | [assembly](decompiled/00404f54.asm) |
| `0x00404f5c` | `GetActiveWindow` |  | [decompiled](decompiled/00404f5c.c) | [assembly](decompiled/00404f5c.asm) |
| `0x00404f64` | `GetCapture` |  | [decompiled](decompiled/00404f64.c) | [assembly](decompiled/00404f64.asm) |
| `0x00404f6c` | `GetClassInfoA` |  | [decompiled](decompiled/00404f6c.c) | [assembly](decompiled/00404f6c.asm) |
| `0x00404f74` | `GetClientRect` |  | [decompiled](decompiled/00404f74.c) | [assembly](decompiled/00404f74.asm) |
| `0x00404f7c` | `GetClipboardData` |  | [decompiled](decompiled/00404f7c.c) | [assembly](decompiled/00404f7c.asm) |
| `0x00404f84` | `GetCursor` |  | [decompiled](decompiled/00404f84.c) | [assembly](decompiled/00404f84.asm) |
| `0x00404f8c` | `GetCursorPos` |  | [decompiled](decompiled/00404f8c.c) | [assembly](decompiled/00404f8c.asm) |
| `0x00404f94` | `GetDC` |  | [decompiled](decompiled/00404f94.c) | [assembly](decompiled/00404f94.asm) |
| `0x00404f9c` | `GetDCEx` |  | [decompiled](decompiled/00404f9c.c) | [assembly](decompiled/00404f9c.asm) |
| `0x00404fa4` | `GetDesktopWindow` |  | [decompiled](decompiled/00404fa4.c) | [assembly](decompiled/00404fa4.asm) |
| `0x00404fac` | `GetFocus` |  | [decompiled](decompiled/00404fac.c) | [assembly](decompiled/00404fac.asm) |
| `0x00404fb4` | `GetForegroundWindow` |  | [decompiled](decompiled/00404fb4.c) | [assembly](decompiled/00404fb4.asm) |
| `0x00404fbc` | `GetIconInfo` |  | [decompiled](decompiled/00404fbc.c) | [assembly](decompiled/00404fbc.asm) |
| `0x00404fc4` | `GetKeyNameTextA` |  | [decompiled](decompiled/00404fc4.c) | [assembly](decompiled/00404fc4.asm) |
| `0x00404fcc` | `GetKeyState` |  | [decompiled](decompiled/00404fcc.c) | [assembly](decompiled/00404fcc.asm) |
| `0x00404fd4` | `GetLastActivePopup` |  | [decompiled](decompiled/00404fd4.c) | [assembly](decompiled/00404fd4.asm) |
| `0x00404fdc` | `GetMenu` |  | [decompiled](decompiled/00404fdc.c) | [assembly](decompiled/00404fdc.asm) |
| `0x00404fe4` | `GetMenuItemCount` |  | [decompiled](decompiled/00404fe4.c) | [assembly](decompiled/00404fe4.asm) |
| `0x00404fec` | `GetMenuState` |  | [decompiled](decompiled/00404fec.c) | [assembly](decompiled/00404fec.asm) |
| `0x00404ff4` | `GetMenuStringA` |  | [decompiled](decompiled/00404ff4.c) | [assembly](decompiled/00404ff4.asm) |
| `0x00404ffc` | `GetParent` |  | [decompiled](decompiled/00404ffc.c) | [assembly](decompiled/00404ffc.asm) |
| `0x00405004` | `GetPropA` |  | [decompiled](decompiled/00405004.c) | [assembly](decompiled/00405004.asm) |
| `0x0040500c` | `GetScrollPos` |  | [decompiled](decompiled/0040500c.c) | [assembly](decompiled/0040500c.asm) |
| `0x00405014` | `GetSubMenu` |  | [decompiled](decompiled/00405014.c) | [assembly](decompiled/00405014.asm) |
| `0x0040501c` | `GetSysColor` |  | [decompiled](decompiled/0040501c.c) | [assembly](decompiled/0040501c.asm) |
| `0x00405024` | `GetSystemMenu` |  | [decompiled](decompiled/00405024.c) | [assembly](decompiled/00405024.asm) |
| `0x0040502c` | `GetSystemMetrics` |  | [decompiled](decompiled/0040502c.c) | [assembly](decompiled/0040502c.asm) |
| `0x00405034` | `GetUpdateRect` |  | [decompiled](decompiled/00405034.c) | [assembly](decompiled/00405034.asm) |
| `0x0040503c` | `GetWindow` |  | [decompiled](decompiled/0040503c.c) | [assembly](decompiled/0040503c.asm) |
| `0x00405044` | `GetWindowLongA` |  | [decompiled](decompiled/00405044.c) | [assembly](decompiled/00405044.asm) |
| `0x0040504c` | `GetWindowPlacement` |  | [decompiled](decompiled/0040504c.c) | [assembly](decompiled/0040504c.asm) |
| `0x00405054` | `GetWindowRect` |  | [decompiled](decompiled/00405054.c) | [assembly](decompiled/00405054.asm) |
| `0x0040505c` | `GetWindowRgn` |  | [decompiled](decompiled/0040505c.c) | [assembly](decompiled/0040505c.asm) |
| `0x00405064` | `GetWindowTextA` |  | [decompiled](decompiled/00405064.c) | [assembly](decompiled/00405064.asm) |
| `0x0040506c` | `GetWindowThreadProcessId` |  | [decompiled](decompiled/0040506c.c) | [assembly](decompiled/0040506c.asm) |
| `0x00405074` | `InflateRect` |  | [decompiled](decompiled/00405074.c) | [assembly](decompiled/00405074.asm) |
| `0x0040507c` | `InsertMenuA` |  | [decompiled](decompiled/0040507c.c) | [assembly](decompiled/0040507c.asm) |
| `0x00405084` | `InsertMenuItemA` |  | [decompiled](decompiled/00405084.c) | [assembly](decompiled/00405084.asm) |
| `0x0040508c` | `IntersectRect` |  | [decompiled](decompiled/0040508c.c) | [assembly](decompiled/0040508c.asm) |
| `0x00405094` | `InvalidateRect` |  | [decompiled](decompiled/00405094.c) | [assembly](decompiled/00405094.asm) |
| `0x0040509c` | `IsDialogMessageA` |  | [decompiled](decompiled/0040509c.c) | [assembly](decompiled/0040509c.asm) |
| `0x004050a4` | `IsIconic` |  | [decompiled](decompiled/004050a4.c) | [assembly](decompiled/004050a4.asm) |
| `0x004050ac` | `IsRectEmpty` |  | [decompiled](decompiled/004050ac.c) | [assembly](decompiled/004050ac.asm) |
| `0x004050b4` | `IsWindow` |  | [decompiled](decompiled/004050b4.c) | [assembly](decompiled/004050b4.asm) |
| `0x004050bc` | `IsWindowEnabled` |  | [decompiled](decompiled/004050bc.c) | [assembly](decompiled/004050bc.asm) |
| `0x004050c4` | `IsWindowVisible` |  | [decompiled](decompiled/004050c4.c) | [assembly](decompiled/004050c4.asm) |
| `0x004050cc` | `IsZoomed` |  | [decompiled](decompiled/004050cc.c) | [assembly](decompiled/004050cc.asm) |
| `0x004050d4` | `KillTimer` |  | [decompiled](decompiled/004050d4.c) | [assembly](decompiled/004050d4.asm) |
| `0x004050dc` | `LoadBitmapA` |  | [decompiled](decompiled/004050dc.c) | [assembly](decompiled/004050dc.asm) |
| `0x004050e4` | `LoadCursorA` |  | [decompiled](decompiled/004050e4.c) | [assembly](decompiled/004050e4.asm) |
| `0x004050ec` | `LoadIconA` |  | [decompiled](decompiled/004050ec.c) | [assembly](decompiled/004050ec.asm) |
| `0x004050f4` | `LoadStringA` |  | [decompiled](decompiled/004050f4.c) | [assembly](decompiled/004050f4.asm) |
| `0x004050fc` | `MapVirtualKeyA` |  | [decompiled](decompiled/004050fc.c) | [assembly](decompiled/004050fc.asm) |
| `0x00405104` | `MapWindowPoints` |  | [decompiled](decompiled/00405104.c) | [assembly](decompiled/00405104.asm) |
| `0x0040510c` | `MessageBoxA` |  | [decompiled](decompiled/0040510c.c) | [assembly](decompiled/0040510c.asm) |
| `0x00405114` | `OemToCharA` |  | [decompiled](decompiled/00405114.c) | [assembly](decompiled/00405114.asm) |
| `0x0040511c` | `OffsetRect` |  | [decompiled](decompiled/0040511c.c) | [assembly](decompiled/0040511c.asm) |
| `0x00405124` | `PeekMessageA` |  | [decompiled](decompiled/00405124.c) | [assembly](decompiled/00405124.asm) |
| `0x0040512c` | `PostMessageA` |  | [decompiled](decompiled/0040512c.c) | [assembly](decompiled/0040512c.asm) |
| `0x00405134` | `PostQuitMessage` |  | [decompiled](decompiled/00405134.c) | [assembly](decompiled/00405134.asm) |
| `0x0040513c` | `PtInRect` |  | [decompiled](decompiled/0040513c.c) | [assembly](decompiled/0040513c.asm) |
| `0x00405144` | `RegisterClassA` |  | [decompiled](decompiled/00405144.c) | [assembly](decompiled/00405144.asm) |
| `0x0040514c` | `RegisterWindowMessageA` |  | [decompiled](decompiled/0040514c.c) | [assembly](decompiled/0040514c.asm) |
| `0x00405154` | `ReleaseCapture` |  | [decompiled](decompiled/00405154.c) | [assembly](decompiled/00405154.asm) |
| `0x0040515c` | `ReleaseDC` |  | [decompiled](decompiled/0040515c.c) | [assembly](decompiled/0040515c.asm) |
| `0x00405164` | `RemoveMenu` |  | [decompiled](decompiled/00405164.c) | [assembly](decompiled/00405164.asm) |
| `0x0040516c` | `RemovePropA` |  | [decompiled](decompiled/0040516c.c) | [assembly](decompiled/0040516c.asm) |
| `0x00405174` | `ScreenToClient` |  | [decompiled](decompiled/00405174.c) | [assembly](decompiled/00405174.asm) |
| `0x0040517c` | `ScrollWindow` |  | [decompiled](decompiled/0040517c.c) | [assembly](decompiled/0040517c.asm) |
| `0x00405184` | `SendMessageA` |  | [decompiled](decompiled/00405184.c) | [assembly](decompiled/00405184.asm) |
| `0x0040518c` | `SetActiveWindow` |  | [decompiled](decompiled/0040518c.c) | [assembly](decompiled/0040518c.asm) |
| `0x00405194` | `SetCapture` |  | [decompiled](decompiled/00405194.c) | [assembly](decompiled/00405194.asm) |
| `0x0040519c` | `SetCursor` |  | [decompiled](decompiled/0040519c.c) | [assembly](decompiled/0040519c.asm) |
| `0x004051a4` | `SetFocus` |  | [decompiled](decompiled/004051a4.c) | [assembly](decompiled/004051a4.asm) |
| `0x004051ac` | `SetForegroundWindow` |  | [decompiled](decompiled/004051ac.c) | [assembly](decompiled/004051ac.asm) |
| `0x004051b4` | `SetMenu` |  | [decompiled](decompiled/004051b4.c) | [assembly](decompiled/004051b4.asm) |
| `0x004051bc` | `SetPropA` |  | [decompiled](decompiled/004051bc.c) | [assembly](decompiled/004051bc.asm) |
| `0x004051c4` | `SetRect` |  | [decompiled](decompiled/004051c4.c) | [assembly](decompiled/004051c4.asm) |
| `0x004051cc` | `SetScrollInfo` |  | [decompiled](decompiled/004051cc.c) | [assembly](decompiled/004051cc.asm) |
| `0x004051d4` | `SetScrollPos` |  | [decompiled](decompiled/004051d4.c) | [assembly](decompiled/004051d4.asm) |
| `0x004051dc` | `SetTimer` |  | [decompiled](decompiled/004051dc.c) | [assembly](decompiled/004051dc.asm) |
| `0x004051e4` | `SetWindowLongA` |  | [decompiled](decompiled/004051e4.c) | [assembly](decompiled/004051e4.asm) |
| `0x004051ec` | `SetWindowPlacement` |  | [decompiled](decompiled/004051ec.c) | [assembly](decompiled/004051ec.asm) |
| `0x004051f4` | `SetWindowPos` |  | [decompiled](decompiled/004051f4.c) | [assembly](decompiled/004051f4.asm) |
| `0x004051fc` | `SetWindowTextA` |  | [decompiled](decompiled/004051fc.c) | [assembly](decompiled/004051fc.asm) |
| `0x00405204` | `SetWindowsHookExA` |  | [decompiled](decompiled/00405204.c) | [assembly](decompiled/00405204.asm) |
| `0x0040520c` | `SetWindowRgn` |  | [decompiled](decompiled/0040520c.c) | [assembly](decompiled/0040520c.asm) |
| `0x00405214` | `ShowCursor` |  | [decompiled](decompiled/00405214.c) | [assembly](decompiled/00405214.asm) |
| `0x0040521c` | `ShowOwnedPopups` |  | [decompiled](decompiled/0040521c.c) | [assembly](decompiled/0040521c.asm) |
| `0x00405224` | `ShowWindow` |  | [decompiled](decompiled/00405224.c) | [assembly](decompiled/00405224.asm) |
| `0x0040522c` | `SystemParametersInfoA` |  | [decompiled](decompiled/0040522c.c) | [assembly](decompiled/0040522c.asm) |
| `0x00405234` | `TrackPopupMenu` |  | [decompiled](decompiled/00405234.c) | [assembly](decompiled/00405234.asm) |
| `0x0040523c` | `TranslateMDISysAccel` |  | [decompiled](decompiled/0040523c.c) | [assembly](decompiled/0040523c.asm) |
| `0x00405244` | `TranslateMessage` |  | [decompiled](decompiled/00405244.c) | [assembly](decompiled/00405244.asm) |
| `0x0040524c` | `UnhookWindowsHookEx` |  | [decompiled](decompiled/0040524c.c) | [assembly](decompiled/0040524c.asm) |
| `0x00405254` | `UnregisterClassA` |  | [decompiled](decompiled/00405254.c) | [assembly](decompiled/00405254.asm) |
| `0x0040525c` | `UpdateWindow` |  | [decompiled](decompiled/0040525c.c) | [assembly](decompiled/0040525c.asm) |
| `0x00405264` | `WaitForInputIdle` |  | [decompiled](decompiled/00405264.c) | [assembly](decompiled/00405264.asm) |
| `0x0040526c` | `WaitMessage` |  | [decompiled](decompiled/0040526c.c) | [assembly](decompiled/0040526c.asm) |
| `0x00405274` | `WinHelpA` |  | [decompiled](decompiled/00405274.c) | [assembly](decompiled/00405274.asm) |
| `0x0040527c` | `WindowFromPoint` |  | [decompiled](decompiled/0040527c.c) | [assembly](decompiled/0040527c.asm) |
| `0x00405284` | `FUN_00405284` |  | [decompiled](decompiled/00405284.c) | [assembly](decompiled/00405284.asm) |
| `0x00405290` | `root_00405290` |  | [decompiled](decompiled/00405290.c) | [assembly](decompiled/00405290.asm) |
| `0x00405294` | `FUN_00405294` |  | [decompiled](decompiled/00405294.c) | [assembly](decompiled/00405294.asm) |
| `0x0040529c` | `FUN_0040529c` |  | [decompiled](decompiled/0040529c.c) | [assembly](decompiled/0040529c.asm) |
| `0x004052a0` | `FUN_004052a0` |  | [decompiled](decompiled/004052a0.c) | [assembly](decompiled/004052a0.asm) |
| `0x004052b0` | `FUN_004052b0` |  | [decompiled](decompiled/004052b0.c) | [assembly](decompiled/004052b0.asm) |
| `0x004052cc` | `FUN_004052cc` |  | [decompiled](decompiled/004052cc.c) | [assembly](decompiled/004052cc.asm) |
| `0x004052e0` | `FUN_004052e0` | windows.SmallPointToPoint | [decompiled](decompiled/004052e0.c) | [assembly](decompiled/004052e0.asm) |
| `0x004052f4` | `FUN_004052f4` | windows.PointToSmallPoint | [decompiled](decompiled/004052f4.c) | [assembly](decompiled/004052f4.asm) |
| `0x0040530c` | `FUN_0040530c` | windows.CreateWindow, windows.CreateWindowA, windows.CreateWindowW | [decompiled](decompiled/0040530c.c) | [assembly](decompiled/0040530c.asm) |
| `0x00405914` | `FUN_00405914` |  | [decompiled](decompiled/00405914.c) | [assembly](decompiled/00405914.asm) |
| `0x0040592c` | `FUN_0040592c` |  | [decompiled](decompiled/0040592c.c) | [assembly](decompiled/0040592c.asm) |
| `0x00405950` | `FUN_00405950` | sysutils.AllocMem | [decompiled](decompiled/00405950.c) | [assembly](decompiled/00405950.asm) |
| `0x00405998` | `FUN_00405998` | sysutils.AddExitProc | [decompiled](decompiled/00405998.c) | [assembly](decompiled/00405998.asm) |
| `0x004059cc` | `FUN_004059cc` | sysutils.AnsiLowerCase, sysutils.AnsiUpperCase | [decompiled](decompiled/004059cc.c) | [assembly](decompiled/004059cc.asm) |
| `0x004059fc` | `FUN_004059fc` | sysutils.AnsiCompareStr | [decompiled](decompiled/004059fc.c) | [assembly](decompiled/004059fc.asm) |
| `0x00405a34` | `FUN_00405a34` | sysutils.AnsiCompareText | [decompiled](decompiled/00405a34.c) | [assembly](decompiled/00405a34.asm) |
| `0x00405a6c` | `FUN_00405a6c` | sysutils.AdjustLineBreaks | [decompiled](decompiled/00405a6c.c) | [assembly](decompiled/00405a6c.asm) |
| `0x00405b08` | `FUN_00405b08` | sysutils.IsValidIdent | [decompiled](decompiled/00405b08.c) | [assembly](decompiled/00405b08.asm) |
| `0x00405b6c` | `FUN_00405b6c` | sysutils.IntToStr | [decompiled](decompiled/00405b6c.c) | [assembly](decompiled/00405b6c.asm) |
| `0x00405b9c` | `FUN_00405b9c` | sysutils.StrToInt | [decompiled](decompiled/00405b9c.c) | [assembly](decompiled/00405b9c.asm) |
| `0x00405bd8` | `FUN_00405bd8` | sysutils.StrToIntDef | [decompiled](decompiled/00405bd8.c) | [assembly](decompiled/00405bd8.asm) |
| `0x00405bf0` | `FUN_00405bf0` | sysutils.LoadStr | [decompiled](decompiled/00405bf0.c) | [assembly](decompiled/00405bf0.asm) |
| `0x00405c28` | `FUN_00405c28` | sysutils.FmtLoadStr | [decompiled](decompiled/00405c28.c) | [assembly](decompiled/00405c28.asm) |
| `0x00405c72` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00405c72.c) | [assembly](decompiled/00405c72.asm) |
| `0x00405c77` | `root_00405c77` |  | [decompiled](decompiled/00405c77.c) | [assembly](decompiled/00405c77.asm) |
| `0x00405c84` | `FUN_00405c84` | sysutils.FileOpen | [decompiled](decompiled/00405c84.c) | [assembly](decompiled/00405c84.asm) |
| `0x00405cc4` | `FUN_00405cc4` | sysutils.FileCreate | [decompiled](decompiled/00405cc4.c) | [assembly](decompiled/00405cc4.asm) |
| `0x00405ce8` | `FUN_00405ce8` | sysutils.FileRead, sysutils.FileWrite | [decompiled](decompiled/00405ce8.c) | [assembly](decompiled/00405ce8.asm) |
| `0x00405d14` | `FUN_00405d14` | sysutils.FileRead, sysutils.FileWrite | [decompiled](decompiled/00405d14.c) | [assembly](decompiled/00405d14.asm) |
| `0x00405d40` | `FUN_00405d40` |  | [decompiled](decompiled/00405d40.c) | [assembly](decompiled/00405d40.asm) |
| `0x00405d4c` | `FUN_00405d4c` |  | [decompiled](decompiled/00405d4c.c) | [assembly](decompiled/00405d4c.asm) |
| `0x00405d54` | `FUN_00405d54` | sysutils.FileAge | [decompiled](decompiled/00405d54.c) | [assembly](decompiled/00405d54.asm) |
| `0x00405dbc` | `FUN_00405dbc` |  | [decompiled](decompiled/00405dbc.c) | [assembly](decompiled/00405dbc.asm) |
| `0x00405dcc` | `FUN_00405dcc` |  | [decompiled](decompiled/00405dcc.c) | [assembly](decompiled/00405dcc.asm) |
| `0x00405e30` | `FUN_00405e30` | sysutils.FindFirst | [decompiled](decompiled/00405e30.c) | [assembly](decompiled/00405e30.asm) |
| `0x00405e7c` | `FUN_00405e7c` | sysutils.FindNext | [decompiled](decompiled/00405e7c.c) | [assembly](decompiled/00405e7c.asm) |
| `0x00405ea0` | `FUN_00405ea0` |  | [decompiled](decompiled/00405ea0.c) | [assembly](decompiled/00405ea0.asm) |
| `0x00405eb0` | `FUN_00405eb0` |  | [decompiled](decompiled/00405eb0.c) | [assembly](decompiled/00405eb0.asm) |
| `0x00405f04` | `FUN_00405f04` |  | [decompiled](decompiled/00405f04.c) | [assembly](decompiled/00405f04.asm) |
| `0x00405f98` | `FUN_00405f98` |  | [decompiled](decompiled/00405f98.c) | [assembly](decompiled/00405f98.asm) |
| `0x00405fec` | `FUN_00405fec` |  | [decompiled](decompiled/00405fec.c) | [assembly](decompiled/00405fec.asm) |
| `0x00406054` | `FUN_00406054` |  | [decompiled](decompiled/00406054.c) | [assembly](decompiled/00406054.asm) |
| `0x00406068` | `FUN_00406068` | sysutils.GetCurrentDir | [decompiled](decompiled/00406068.c) | [assembly](decompiled/00406068.asm) |
| `0x00406090` | `FUN_00406090` | sysutils.CreateDir | [decompiled](decompiled/00406090.c) | [assembly](decompiled/00406090.asm) |
| `0x004060ac` | `FUN_004060ac` | sysutils.StrLen | [decompiled](decompiled/004060ac.c) | [assembly](decompiled/004060ac.asm) |
| `0x004060c4` | `FUN_004060c4` | sysutils.StrEnd | [decompiled](decompiled/004060c4.c) | [assembly](decompiled/004060c4.asm) |
| `0x004060d8` | `FUN_004060d8` | sysutils.StrMove | [decompiled](decompiled/004060d8.c) | [assembly](decompiled/004060d8.asm) |
| `0x00406114` | `FUN_00406114` | sysutils.StrCopy | [decompiled](decompiled/00406114.c) | [assembly](decompiled/00406114.asm) |
| `0x0040613c` | `FUN_0040613c` | sysutils.StrECopy | [decompiled](decompiled/0040613c.c) | [assembly](decompiled/0040613c.asm) |
| `0x00406168` | `FUN_00406168` | sysutils.StrLCopy | [decompiled](decompiled/00406168.c) | [assembly](decompiled/00406168.asm) |
| `0x0040619c` | `FUN_0040619c` | sysutils.StrPCopy | [decompiled](decompiled/0040619c.c) | [assembly](decompiled/0040619c.asm) |
| `0x004061bc` | `FUN_004061bc` | sysutils.StrPLCopy | [decompiled](decompiled/004061bc.c) | [assembly](decompiled/004061bc.asm) |
| `0x004061dc` | `FUN_004061dc` | sysutils.StrComp | [decompiled](decompiled/004061dc.c) | [assembly](decompiled/004061dc.asm) |
| `0x00406200` | `FUN_00406200` | sysutils.StrScan | [decompiled](decompiled/00406200.c) | [assembly](decompiled/00406200.asm) |
| `0x00406220` | `FUN_00406220` | sysutils.StrAlloc | [decompiled](decompiled/00406220.c) | [assembly](decompiled/00406220.asm) |
| `0x00406234` | `FUN_00406234` |  | [decompiled](decompiled/00406234.c) | [assembly](decompiled/00406234.asm) |
| `0x00406240` | `FUN_00406240` | sysutils.StrNew | [decompiled](decompiled/00406240.c) | [assembly](decompiled/00406240.asm) |
| `0x0040626c` | `FUN_0040626c` |  | [decompiled](decompiled/0040626c.c) | [assembly](decompiled/0040626c.asm) |
| `0x0040627c` | `FUN_0040627c` |  | [decompiled](decompiled/0040627c.c) | [assembly](decompiled/0040627c.asm) |
| `0x004062d4` | `FUN_004062d4` |  | [decompiled](decompiled/004062d4.c) | [assembly](decompiled/004062d4.asm) |
| `0x004062e0` | `FUN_004062e0` | sysutils.FormatBuf | [decompiled](decompiled/004062e0.c) | [assembly](decompiled/004062e0.asm) |
| `0x004063b9` | `FUN_004063b9` |  | [decompiled](decompiled/004063b9.c) | [assembly](decompiled/004063b9.asm) |
| `0x00406402` | `FUN_00406402` |  | [decompiled](decompiled/00406402.c) | [assembly](decompiled/00406402.asm) |
| `0x00406498` | `FUN_00406498` |  | [decompiled](decompiled/00406498.c) | [assembly](decompiled/00406498.asm) |
| `0x004065dc` | `FUN_004065dc` |  | [decompiled](decompiled/004065dc.c) | [assembly](decompiled/004065dc.asm) |
| `0x004065e8` | `FUN_004065e8` | sysutils.StrFmt | [decompiled](decompiled/004065e8.c) | [assembly](decompiled/004065e8.asm) |
| `0x0040661c` | `FUN_0040661c` |  | [decompiled](decompiled/0040661c.c) | [assembly](decompiled/0040661c.asm) |
| `0x00406630` | `FUN_00406630` | sysutils.FmtStr | [decompiled](decompiled/00406630.c) | [assembly](decompiled/00406630.asm) |
| `0x00406694` | `FUN_00406694` |  | [decompiled](decompiled/00406694.c) | [assembly](decompiled/00406694.asm) |
| `0x004066d4` | `FUN_004066d4` |  | [decompiled](decompiled/004066d4.c) | [assembly](decompiled/004066d4.asm) |
| `0x004066ec` | `FUN_004066ec` |  | [decompiled](decompiled/004066ec.c) | [assembly](decompiled/004066ec.asm) |
| `0x004067ac` | `FUN_004067ac` | sysutils.EncodeDate | [decompiled](decompiled/004067ac.c) | [assembly](decompiled/004067ac.asm) |
| `0x004067dc` | `FUN_004067dc` | sysutils.GetLocaleStr | [decompiled](decompiled/004067dc.c) | [assembly](decompiled/004067dc.asm) |
| `0x00406828` | `FUN_00406828` | sysutils.GetLocaleChar | [decompiled](decompiled/00406828.c) | [assembly](decompiled/00406828.asm) |
| `0x00406850` | `FUN_00406850` |  | [decompiled](decompiled/00406850.c) | [assembly](decompiled/00406850.asm) |
| `0x00406986` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00406986.c) | [assembly](decompiled/00406986.asm) |
| `0x0040698b` | `root_0040698b` |  | [decompiled](decompiled/0040698b.c) | [assembly](decompiled/0040698b.asm) |
| `0x00406994` | `FUN_00406994` |  | [decompiled](decompiled/00406994.c) | [assembly](decompiled/00406994.asm) |
| `0x00406aaf` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00406aaf.c) | [assembly](decompiled/00406aaf.asm) |
| `0x00406ab4` | `root_00406ab4` |  | [decompiled](decompiled/00406ab4.c) | [assembly](decompiled/00406ab4.asm) |
| `0x00406ad8` | `FUN_00406ad8` |  | [decompiled](decompiled/00406ad8.c) | [assembly](decompiled/00406ad8.asm) |
| `0x00406cc1` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00406cc1.c) | [assembly](decompiled/00406cc1.asm) |
| `0x00406cc6` | `root_00406cc6` |  | [decompiled](decompiled/00406cc6.c) | [assembly](decompiled/00406cc6.asm) |
| `0x00406d28` | `FUN_00406d28` |  | [decompiled](decompiled/00406d28.c) | [assembly](decompiled/00406d28.asm) |
| `0x00406f35` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00406f35.c) | [assembly](decompiled/00406f35.asm) |
| `0x00406f3a` | `root_00406f3a` |  | [decompiled](decompiled/00406f3a.c) | [assembly](decompiled/00406f3a.asm) |
| `0x00406fb4` | `FUN_00406fb4` |  | [decompiled](decompiled/00406fb4.c) | [assembly](decompiled/00406fb4.asm) |
| `0x00407076` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00407076.c) | [assembly](decompiled/00407076.asm) |
| `0x0040707b` | `root_0040707b` |  | [decompiled](decompiled/0040707b.c) | [assembly](decompiled/0040707b.asm) |
| `0x00407084` | `FUN_00407084` |  | [decompiled](decompiled/00407084.c) | [assembly](decompiled/00407084.asm) |
| `0x004070e4` | `FUN_004070e4` |  | [decompiled](decompiled/004070e4.c) | [assembly](decompiled/004070e4.asm) |
| `0x00407287` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00407287.c) | [assembly](decompiled/00407287.asm) |
| `0x0040728c` | `root_0040728c` |  | [decompiled](decompiled/0040728c.c) | [assembly](decompiled/0040728c.asm) |
| `0x00407298` | `root_00407298` | sysutils.ExceptObject | [decompiled](decompiled/00407298.c) | [assembly](decompiled/00407298.asm) |
| `0x004072b8` | `root_004072b8` | sysutils.ExceptAddr | [decompiled](decompiled/004072b8.c) | [assembly](decompiled/004072b8.asm) |
| `0x004072d8` | `FUN_004072d8` |  | [decompiled](decompiled/004072d8.c) | [assembly](decompiled/004072d8.asm) |
| `0x004072e4` | `FUN_004072e4` |  | [decompiled](decompiled/004072e4.c) | [assembly](decompiled/004072e4.asm) |
| `0x00407314` | `FUN_00407314` | sysutils.ShowException | [decompiled](decompiled/00407314.c) | [assembly](decompiled/00407314.asm) |
| `0x00407498` | `FUN_00407498` | IniFiles.TIniFile.Create, sysutils.Exception.Create | [decompiled](decompiled/00407498.c) | [assembly](decompiled/00407498.asm) |
| `0x004074cc` | `FUN_004074cc` | sysutils.Exception.CreateRes | [decompiled](decompiled/004074cc.c) | [assembly](decompiled/004074cc.asm) |
| `0x0040751f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040751f.c) | [assembly](decompiled/0040751f.asm) |
| `0x00407524` | `root_00407524` |  | [decompiled](decompiled/00407524.c) | [assembly](decompiled/00407524.asm) |
| `0x0040753c` | `FUN_0040753c` | sysutils.Exception.CreateResFmt | [decompiled](decompiled/0040753c.c) | [assembly](decompiled/0040753c.asm) |
| `0x004075a8` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004075a8.c) | [assembly](decompiled/004075a8.asm) |
| `0x004075ad` | `root_004075ad` |  | [decompiled](decompiled/004075ad.c) | [assembly](decompiled/004075ad.asm) |
| `0x004075c8` | `root_004075c8` |  | [decompiled](decompiled/004075c8.c) | [assembly](decompiled/004075c8.asm) |
| `0x004075d4` | `root_004075d4` |  | [decompiled](decompiled/004075d4.c) | [assembly](decompiled/004075d4.asm) |
| `0x004075d8` | `FUN_004075d8` |  | [decompiled](decompiled/004075d8.c) | [assembly](decompiled/004075d8.asm) |
| `0x0040769c` | `FUN_0040769c` |  | [decompiled](decompiled/0040769c.c) | [assembly](decompiled/0040769c.asm) |
| `0x0040780a` | `FUN_0040780a` |  | [decompiled](decompiled/0040780a.c) | [assembly](decompiled/0040780a.asm) |
| `0x00407813` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00407813.c) | [assembly](decompiled/00407813.asm) |
| `0x00407818` | `thunk_FUN_0040780a` |  | [decompiled](decompiled/00407818.c) | [assembly](decompiled/00407818.asm) |
| `0x00407834` | `FUN_00407834` |  | [decompiled](decompiled/00407834.c) | [assembly](decompiled/00407834.asm) |
| `0x00407880` | `FUN_00407880` |  | [decompiled](decompiled/00407880.c) | [assembly](decompiled/00407880.asm) |
| `0x00407978` | `FUN_00407978` |  | [decompiled](decompiled/00407978.c) | [assembly](decompiled/00407978.asm) |
| `0x00407981` | `FUN_00407981` |  | [decompiled](decompiled/00407981.c) | [assembly](decompiled/00407981.asm) |
| `0x00407a65` | `FUN_00407a65` |  | [decompiled](decompiled/00407a65.c) | [assembly](decompiled/00407a65.asm) |
| `0x00407b1d` | `FUN_00407b1d` |  | [decompiled](decompiled/00407b1d.c) | [assembly](decompiled/00407b1d.asm) |
| `0x00408154` | `FUN_00408154` |  | [decompiled](decompiled/00408154.c) | [assembly](decompiled/00408154.asm) |
| `0x00408194` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00408194.c) | [assembly](decompiled/00408194.asm) |
| `0x00408199` | `root_00408199` |  | [decompiled](decompiled/00408199.c) | [assembly](decompiled/00408199.asm) |
| `0x004081a0` | `FUN_004081a0` |  | [decompiled](decompiled/004081a0.c) | [assembly](decompiled/004081a0.asm) |
| `0x004081ac` | `FUN_004081ac` | TypInfo.GetEnumName | [decompiled](decompiled/004081ac.c) | [assembly](decompiled/004081ac.asm) |
| `0x004081e8` | `FUN_004081e8` | TypInfo.GetEnumValue | [decompiled](decompiled/004081e8.c) | [assembly](decompiled/004081e8.asm) |
| `0x00408230` | `FUN_00408230` | TypInfo.GetPropInfo | [decompiled](decompiled/00408230.c) | [assembly](decompiled/00408230.asm) |
| `0x0040829c` | `FUN_0040829c` | TypInfo.GetPropInfos | [decompiled](decompiled/0040829c.c) | [assembly](decompiled/0040829c.asm) |
| `0x004082ec` | `FUN_004082ec` | TypInfo.IsStoredProp | [decompiled](decompiled/004082ec.c) | [assembly](decompiled/004082ec.asm) |
| `0x0040831c` | `FUN_0040831c` | TypInfo.GetOrdProp | [decompiled](decompiled/0040831c.c) | [assembly](decompiled/0040831c.asm) |
| `0x0040838c` | `FUN_0040838c` | TypInfo.SetOrdProp | [decompiled](decompiled/0040838c.c) | [assembly](decompiled/0040838c.asm) |
| `0x004083e8` | `FUN_004083e8` | TypInfo.GetShortStrProp | [decompiled](decompiled/004083e8.c) | [assembly](decompiled/004083e8.asm) |
| `0x0040842c` | `FUN_0040842c` | TypInfo.SetShortStrProp | [decompiled](decompiled/0040842c.c) | [assembly](decompiled/0040842c.asm) |
| `0x0040847c` | `FUN_0040847c` |  | [decompiled](decompiled/0040847c.c) | [assembly](decompiled/0040847c.asm) |
| `0x00408490` | `FUN_00408490` | TypInfo.GetLongStrProp | [decompiled](decompiled/00408490.c) | [assembly](decompiled/00408490.asm) |
| `0x004084d0` | `FUN_004084d0` | TypInfo.SetLongStrProp, TypInfo.SetVariantProp | [decompiled](decompiled/004084d0.c) | [assembly](decompiled/004084d0.asm) |
| `0x00408510` | `FUN_00408510` | TypInfo.GetStrProp | [decompiled](decompiled/00408510.c) | [assembly](decompiled/00408510.asm) |
| `0x00408548` | `FUN_00408548` | TypInfo.SetStrProp | [decompiled](decompiled/00408548.c) | [assembly](decompiled/00408548.asm) |
| `0x00408590` | `FUN_00408590` | TypInfo.GetFloatProp | [decompiled](decompiled/00408590.c) | [assembly](decompiled/00408590.asm) |
| `0x004085f0` | `FUN_004085f0` | TypInfo.SetFloatProp | [decompiled](decompiled/004085f0.c) | [assembly](decompiled/004085f0.asm) |
| `0x00408688` | `FUN_00408688` | TypInfo.GetMethodProp | [decompiled](decompiled/00408688.c) | [assembly](decompiled/00408688.asm) |
| `0x004086c8` | `FUN_004086c8` | TypInfo.SetMethodProp | [decompiled](decompiled/004086c8.c) | [assembly](decompiled/004086c8.asm) |
| `0x00408cc0` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00408cc0.c) | [assembly](decompiled/00408cc0.asm) |
| `0x00408cc8` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00408cc8.c) | [assembly](decompiled/00408cc8.asm) |
| `0x00408cd0` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00408cd0.c) | [assembly](decompiled/00408cd0.asm) |
| `0x00408cd8` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00408cd8.c) | [assembly](decompiled/00408cd8.asm) |
| `0x00408ce0` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00408ce0.c) | [assembly](decompiled/00408ce0.asm) |
| `0x00408e2c` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00408e2c.c) | [assembly](decompiled/00408e2c.asm) |
| `0x00408e34` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00408e34.c) | [assembly](decompiled/00408e34.asm) |
| `0x00408e3c` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00408e3c.c) | [assembly](decompiled/00408e3c.asm) |
| `0x00409020` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00409020.c) | [assembly](decompiled/00409020.asm) |
| `0x00409028` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00409028.c) | [assembly](decompiled/00409028.asm) |
| `0x00409030` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00409030.c) | [assembly](decompiled/00409030.asm) |
| `0x00409224` | `FUN_00409224` |  | [decompiled](decompiled/00409224.c) | [assembly](decompiled/00409224.asm) |
| `0x0040922c` | `FUN_0040922c` |  | [decompiled](decompiled/0040922c.c) | [assembly](decompiled/0040922c.asm) |
| `0x0040923c` | `FUN_0040923c` | Classes.Rect | [decompiled](decompiled/0040923c.c) | [assembly](decompiled/0040923c.asm) |
| `0x00409258` | `FUN_00409258` | Classes.Bounds | [decompiled](decompiled/00409258.c) | [assembly](decompiled/00409258.asm) |
| `0x00409274` | `FUN_00409274` |  | [decompiled](decompiled/00409274.c) | [assembly](decompiled/00409274.asm) |
| `0x00409280` | `FUN_00409280` | Classes.ClassNotFound | [decompiled](decompiled/00409280.c) | [assembly](decompiled/00409280.asm) |
| `0x004092e2` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004092e2.c) | [assembly](decompiled/004092e2.asm) |
| `0x004092e7` | `root_004092e7` |  | [decompiled](decompiled/004092e7.c) | [assembly](decompiled/004092e7.asm) |
| `0x004092f0` | `FUN_004092f0` | Classes.GetClass | [decompiled](decompiled/004092f0.c) | [assembly](decompiled/004092f0.asm) |
| `0x00409350` | `FUN_00409350` | Classes.FindClass | [decompiled](decompiled/00409350.c) | [assembly](decompiled/00409350.asm) |
| `0x00409370` | `FUN_00409370` | Classes.FindFieldClass | [decompiled](decompiled/00409370.c) | [assembly](decompiled/00409370.asm) |
| `0x00409426` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00409426.c) | [assembly](decompiled/00409426.asm) |
| `0x0040942b` | `root_0040942b` |  | [decompiled](decompiled/0040942b.c) | [assembly](decompiled/0040942b.asm) |
| `0x00409438` | `FUN_00409438` | Classes.RegisterClass | [decompiled](decompiled/00409438.c) | [assembly](decompiled/00409438.asm) |
| `0x004094f2` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004094f2.c) | [assembly](decompiled/004094f2.asm) |
| `0x004094f7` | `root_004094f7` |  | [decompiled](decompiled/004094f7.c) | [assembly](decompiled/004094f7.asm) |
| `0x00409500` | `FUN_00409500` | Classes.RegisterClasses, Classes.UnRegisterClasses | [decompiled](decompiled/00409500.c) | [assembly](decompiled/00409500.asm) |
| `0x00409570` | `FUN_00409570` | Classes.TIntConst.Create, Update.TUpdateObjectParams.Create | [decompiled](decompiled/00409570.c) | [assembly](decompiled/00409570.asm) |
| `0x004095a0` | `FUN_004095a0` | Classes.RegisterIntegerConsts | [decompiled](decompiled/004095a0.c) | [assembly](decompiled/004095a0.asm) |
| `0x004095cc` | `FUN_004095cc` | Classes.InternalReadComponentRes | [decompiled](decompiled/004095cc.c) | [assembly](decompiled/004095cc.asm) |
| `0x00409644` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00409644.c) | [assembly](decompiled/00409644.asm) |
| `0x00409649` | `root_00409649` |  | [decompiled](decompiled/00409649.c) | [assembly](decompiled/00409649.asm) |
| `0x00409654` | `FUN_00409654` |  | [decompiled](decompiled/00409654.c) | [assembly](decompiled/00409654.asm) |
| `0x00409678` | `FUN_00409678` | Classes.NotifyGlobalLoading | [decompiled](decompiled/00409678.c) | [assembly](decompiled/00409678.asm) |
| `0x004096a4` | `FUN_004096a4` |  | [decompiled](decompiled/004096a4.c) | [assembly](decompiled/004096a4.asm) |
| `0x004096d4` | `FUN_004096d4` | Classes.InitComponent | [decompiled](decompiled/004096d4.c) | [assembly](decompiled/004096d4.asm) |
| `0x0040975b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040975b.c) | [assembly](decompiled/0040975b.asm) |
| `0x00409760` | `root_00409760` |  | [decompiled](decompiled/00409760.c) | [assembly](decompiled/00409760.asm) |
| `0x0040976c` | `FUN_0040976c` | Classes.InitInheritedComponent | [decompiled](decompiled/0040976c.c) | [assembly](decompiled/0040976c.asm) |
| `0x004097b5` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004097b5.c) | [assembly](decompiled/004097b5.asm) |
| `0x004097ba` | `root_004097ba` |  | [decompiled](decompiled/004097ba.c) | [assembly](decompiled/004097ba.asm) |
| `0x004097c4` | `FUN_004097c4` | Classes.CompareMem | [decompiled](decompiled/004097c4.c) | [assembly](decompiled/004097c4.asm) |
| `0x004097e4` | `FUN_004097e4` | Classes.StreamsEqual, Graphics.StreamsEqual | [decompiled](decompiled/004097e4.c) | [assembly](decompiled/004097e4.asm) |
| `0x00409824` | `FUN_00409824` | Classes.WriteCollection | [decompiled](decompiled/00409824.c) | [assembly](decompiled/00409824.asm) |
| `0x0040986f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040986f.c) | [assembly](decompiled/0040986f.asm) |
| `0x00409874` | `root_00409874` |  | [decompiled](decompiled/00409874.c) | [assembly](decompiled/00409874.asm) |
| `0x0040987c` | `FUN_0040987c` | Classes.CollectionsEqual | [decompiled](decompiled/0040987c.c) | [assembly](decompiled/0040987c.asm) |
| `0x0040992f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040992f.c) | [assembly](decompiled/0040992f.asm) |
| `0x00409934` | `root_00409934` |  | [decompiled](decompiled/00409934.c) | [assembly](decompiled/00409934.asm) |
| `0x00409943` | `FUN_00409943` |  | [decompiled](decompiled/00409943.c) | [assembly](decompiled/00409943.asm) |
| `0x0040994c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040994c.c) | [assembly](decompiled/0040994c.asm) |
| `0x00409951` | `thunk_FUN_00409943` |  | [decompiled](decompiled/00409951.c) | [assembly](decompiled/00409951.asm) |
| `0x00409960` | `FUN_00409960` |  | [decompiled](decompiled/00409960.c) | [assembly](decompiled/00409960.asm) |
| `0x00409978` | `FUN_00409978` |  | [decompiled](decompiled/00409978.c) | [assembly](decompiled/00409978.asm) |
| `0x00409984` | `root_00409984` | Classes.TList.Destroy, DBCtrls.TPaintControl.Destroy | [decompiled](decompiled/00409984.c) | [assembly](decompiled/00409984.asm) |
| `0x004099a4` | `FUN_004099a4` | Classes.TList.Add | [decompiled](decompiled/004099a4.c) | [assembly](decompiled/004099a4.asm) |
| `0x004099cc` | `FUN_004099cc` |  | [decompiled](decompiled/004099cc.c) | [assembly](decompiled/004099cc.asm) |
| `0x004099e4` | `FUN_004099e4` | Classes.TList.Delete | [decompiled](decompiled/004099e4.c) | [assembly](decompiled/004099e4.asm) |
| `0x00409a20` | `root_00409a20` |  | [decompiled](decompiled/00409a20.c) | [assembly](decompiled/00409a20.asm) |
| `0x00409a28` | `FUN_00409a28` | Classes.TList.Expand | [decompiled](decompiled/00409a28.c) | [assembly](decompiled/00409a28.asm) |
| `0x00409a40` | `FUN_00409a40` | Classes.TList.Get | [decompiled](decompiled/00409a40.c) | [assembly](decompiled/00409a40.asm) |
| `0x00409a60` | `root_00409a60` | Classes.TList.Grow | [decompiled](decompiled/00409a60.c) | [assembly](decompiled/00409a60.asm) |
| `0x00409a88` | `FUN_00409a88` | Classes.TList.IndexOf | [decompiled](decompiled/00409a88.c) | [assembly](decompiled/00409a88.asm) |
| `0x00409aa8` | `FUN_00409aa8` | Classes.TList.Insert | [decompiled](decompiled/00409aa8.c) | [assembly](decompiled/00409aa8.asm) |
| `0x00409afc` | `FUN_00409afc` |  | [decompiled](decompiled/00409afc.c) | [assembly](decompiled/00409afc.asm) |
| `0x00409b08` | `FUN_00409b08` | Classes.TList.Put | [decompiled](decompiled/00409b08.c) | [assembly](decompiled/00409b08.asm) |
| `0x00409b2c` | `FUN_00409b2c` | Classes.TList.Remove, Grids.TSparseList.Remove | [decompiled](decompiled/00409b2c.c) | [assembly](decompiled/00409b2c.asm) |
| `0x00409b4c` | `FUN_00409b4c` | Classes.TList.SetCapacity | [decompiled](decompiled/00409b4c.c) | [assembly](decompiled/00409b4c.asm) |
| `0x00409b80` | `FUN_00409b80` | Classes.TList.SetCount | [decompiled](decompiled/00409b80.c) | [assembly](decompiled/00409b80.asm) |
| `0x00409bcc` | `root_00409bcc` | Classes.TBits.Destroy | [decompiled](decompiled/00409bcc.c) | [assembly](decompiled/00409bcc.asm) |
| `0x00409bf4` | `FUN_00409bf4` |  | [decompiled](decompiled/00409bf4.c) | [assembly](decompiled/00409bf4.asm) |
| `0x00409c0c` | `FUN_00409c0c` |  | [decompiled](decompiled/00409c0c.c) | [assembly](decompiled/00409c0c.asm) |
| `0x00409c18` | `FUN_00409c18` | Classes.TBits.SetSize | [decompiled](decompiled/00409c18.c) | [assembly](decompiled/00409c18.asm) |
| `0x00409cbc` | `FUN_00409cbc` | Classes.TBits.SetBit | [decompiled](decompiled/00409cbc.c) | [assembly](decompiled/00409cbc.asm) |
| `0x00409ce8` | `FUN_00409ce8` | Classes.TBits.GetBit | [decompiled](decompiled/00409ce8.c) | [assembly](decompiled/00409ce8.asm) |
| `0x00409d00` | `FUN_00409d00` | Classes.TBits.OpenBit | [decompiled](decompiled/00409d00.c) | [assembly](decompiled/00409d00.asm) |
| `0x00409d78` | `FUN_00409d78` |  | [decompiled](decompiled/00409d78.c) | [assembly](decompiled/00409d78.asm) |
| `0x00409d8c` | `FUN_00409d8c` | Classes.TPersistent.AssignError | [decompiled](decompiled/00409d8c.c) | [assembly](decompiled/00409d8c.asm) |
| `0x00409e42` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00409e42.c) | [assembly](decompiled/00409e42.asm) |
| `0x00409e47` | `root_00409e47` |  | [decompiled](decompiled/00409e47.c) | [assembly](decompiled/00409e47.asm) |
| `0x00409e5c` | `FUN_00409e5c` |  | [decompiled](decompiled/00409e5c.c) | [assembly](decompiled/00409e5c.asm) |
| `0x00409e64` | `root_00409e64` |  | [decompiled](decompiled/00409e64.c) | [assembly](decompiled/00409e64.asm) |
| `0x00409e68` | `root_00409e68` | Classes.TCollection.Destroy | [decompiled](decompiled/00409e68.c) | [assembly](decompiled/00409e68.asm) |
| `0x00409e9c` | `FUN_00409e9c` |  | [decompiled](decompiled/00409e9c.c) | [assembly](decompiled/00409e9c.asm) |
| `0x00409ea8` | `FUN_00409ea8` | Classes.TCollection.Assign | [decompiled](decompiled/00409ea8.c) | [assembly](decompiled/00409ea8.asm) |
| `0x00409f25` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00409f25.c) | [assembly](decompiled/00409f25.asm) |
| `0x00409f2a` | `root_00409f2a` |  | [decompiled](decompiled/00409f2a.c) | [assembly](decompiled/00409f2a.asm) |
| `0x00409f3c` | `FUN_00409f3c` |  | [decompiled](decompiled/00409f3c.c) | [assembly](decompiled/00409f3c.asm) |
| `0x00409f40` | `FUN_00409f40` |  | [decompiled](decompiled/00409f40.c) | [assembly](decompiled/00409f40.asm) |
| `0x00409f50` | `FUN_00409f50` | Classes.TCollection.Clear | [decompiled](decompiled/00409f50.c) | [assembly](decompiled/00409f50.asm) |
| `0x00409faa` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00409faa.c) | [assembly](decompiled/00409faa.asm) |
| `0x00409faf` | `root_00409faf` |  | [decompiled](decompiled/00409faf.c) | [assembly](decompiled/00409faf.asm) |
| `0x00409fb8` | `FUN_00409fb8` |  | [decompiled](decompiled/00409fb8.c) | [assembly](decompiled/00409fb8.asm) |
| `0x00409fc4` | `FUN_00409fc4` |  | [decompiled](decompiled/00409fc4.c) | [assembly](decompiled/00409fc4.asm) |
| `0x00409fcc` | `FUN_00409fcc` |  | [decompiled](decompiled/00409fcc.c) | [assembly](decompiled/00409fcc.asm) |
| `0x00409fd8` | `root_00409fd8` |  | [decompiled](decompiled/00409fd8.c) | [assembly](decompiled/00409fd8.asm) |
| `0x00409fdc` | `root_00409fdc` | Classes.TStrings.Add | [decompiled](decompiled/00409fdc.c) | [assembly](decompiled/00409fdc.asm) |
| `0x0040a000` | `root_0040a000` | Classes.TStrings.AddObject | [decompiled](decompiled/0040a000.c) | [assembly](decompiled/0040a000.asm) |
| `0x0040a024` | `FUN_0040a024` | Classes.TStrings.AddStrings | [decompiled](decompiled/0040a024.c) | [assembly](decompiled/0040a024.asm) |
| `0x0040a0ae` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a0ae.c) | [assembly](decompiled/0040a0ae.asm) |
| `0x0040a0b3` | `root_0040a0b3` |  | [decompiled](decompiled/0040a0b3.c) | [assembly](decompiled/0040a0b3.asm) |
| `0x0040a0c2` | `FUN_0040a0c2` |  | [decompiled](decompiled/0040a0c2.c) | [assembly](decompiled/0040a0c2.asm) |
| `0x0040a0cb` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a0cb.c) | [assembly](decompiled/0040a0cb.asm) |
| `0x0040a0d0` | `thunk_FUN_0040a0c2` |  | [decompiled](decompiled/0040a0d0.c) | [assembly](decompiled/0040a0d0.asm) |
| `0x0040a0dc` | `root_0040a0dc` | Classes.TStrings.Assign | [decompiled](decompiled/0040a0dc.c) | [assembly](decompiled/0040a0dc.asm) |
| `0x0040a134` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a134.c) | [assembly](decompiled/0040a134.asm) |
| `0x0040a139` | `root_0040a139` |  | [decompiled](decompiled/0040a139.c) | [assembly](decompiled/0040a139.asm) |
| `0x0040a14c` | `FUN_0040a14c` | Classes.TStrings.BeginUpdate | [decompiled](decompiled/0040a14c.c) | [assembly](decompiled/0040a14c.asm) |
| `0x0040a164` | `FUN_0040a164` | Classes.DoWrite | [decompiled](decompiled/0040a164.c) | [assembly](decompiled/0040a164.asm) |
| `0x0040a1b8` | `FUN_0040a1b8` | Classes.TStrings.DefineProperties | [decompiled](decompiled/0040a1b8.c) | [assembly](decompiled/0040a1b8.asm) |
| `0x0040a204` | `FUN_0040a204` | Classes.TStrings.EndUpdate | [decompiled](decompiled/0040a204.c) | [assembly](decompiled/0040a204.asm) |
| `0x0040a218` | `FUN_0040a218` | Classes.TStrings.Equals | [decompiled](decompiled/0040a218.c) | [assembly](decompiled/0040a218.asm) |
| `0x0040a2ad` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a2ad.c) | [assembly](decompiled/0040a2ad.asm) |
| `0x0040a2b2` | `root_0040a2b2` |  | [decompiled](decompiled/0040a2b2.c) | [assembly](decompiled/0040a2b2.asm) |
| `0x0040a2c0` | `root_0040a2c0` | Classes.TStrings.Exchange | [decompiled](decompiled/0040a2c0.c) | [assembly](decompiled/0040a2c0.asm) |
| `0x0040a361` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a361.c) | [assembly](decompiled/0040a361.asm) |
| `0x0040a366` | `root_0040a366` |  | [decompiled](decompiled/0040a366.c) | [assembly](decompiled/0040a366.asm) |
| `0x0040a370` | `root_0040a370` |  | [decompiled](decompiled/0040a370.c) | [assembly](decompiled/0040a370.asm) |
| `0x0040a374` | `FUN_0040a374` | Classes.TStrings.GetText | [decompiled](decompiled/0040a374.c) | [assembly](decompiled/0040a374.asm) |
| `0x0040a3bb` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a3bb.c) | [assembly](decompiled/0040a3bb.asm) |
| `0x0040a3c0` | `root_0040a3c0` |  | [decompiled](decompiled/0040a3c0.c) | [assembly](decompiled/0040a3c0.asm) |
| `0x0040a3cc` | `root_0040a3cc` | Classes.TStrings.GetTextStr | [decompiled](decompiled/0040a3cc.c) | [assembly](decompiled/0040a3cc.asm) |
| `0x0040a4a3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a4a3.c) | [assembly](decompiled/0040a4a3.asm) |
| `0x0040a4a8` | `root_0040a4a8` |  | [decompiled](decompiled/0040a4a8.c) | [assembly](decompiled/0040a4a8.asm) |
| `0x0040a4b4` | `FUN_0040a4b4` | Classes.TStrings.IndexOf | [decompiled](decompiled/0040a4b4.c) | [assembly](decompiled/0040a4b4.asm) |
| `0x0040a521` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a521.c) | [assembly](decompiled/0040a521.asm) |
| `0x0040a526` | `root_0040a526` |  | [decompiled](decompiled/0040a526.c) | [assembly](decompiled/0040a526.asm) |
| `0x0040a534` | `FUN_0040a534` |  | [decompiled](decompiled/0040a534.c) | [assembly](decompiled/0040a534.asm) |
| `0x0040a564` | `FUN_0040a564` | Classes.TStrings.LoadFromFile | [decompiled](decompiled/0040a564.c) | [assembly](decompiled/0040a564.asm) |
| `0x0040a5ac` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a5ac.c) | [assembly](decompiled/0040a5ac.asm) |
| `0x0040a5b1` | `root_0040a5b1` |  | [decompiled](decompiled/0040a5b1.c) | [assembly](decompiled/0040a5b1.asm) |
| `0x0040a5b8` | `FUN_0040a5b8` | Classes.TStrings.LoadFromStream | [decompiled](decompiled/0040a5b8.c) | [assembly](decompiled/0040a5b8.asm) |
| `0x0040a639` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a639.c) | [assembly](decompiled/0040a639.asm) |
| `0x0040a63e` | `root_0040a63e` |  | [decompiled](decompiled/0040a63e.c) | [assembly](decompiled/0040a63e.asm) |
| `0x0040a64d` | `FUN_0040a64d` |  | [decompiled](decompiled/0040a64d.c) | [assembly](decompiled/0040a64d.asm) |
| `0x0040a656` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a656.c) | [assembly](decompiled/0040a656.asm) |
| `0x0040a65b` | `thunk_FUN_0040a64d` |  | [decompiled](decompiled/0040a65b.c) | [assembly](decompiled/0040a65b.asm) |
| `0x0040a664` | `root_0040a664` | Classes.TStrings.Move | [decompiled](decompiled/0040a664.c) | [assembly](decompiled/0040a664.asm) |
| `0x0040a6d0` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a6d0.c) | [assembly](decompiled/0040a6d0.asm) |
| `0x0040a6d5` | `root_0040a6d5` |  | [decompiled](decompiled/0040a6d5.c) | [assembly](decompiled/0040a6d5.asm) |
| `0x0040a6e0` | `root_0040a6e0` | Classes.TStrings.Put | [decompiled](decompiled/0040a6e0.c) | [assembly](decompiled/0040a6e0.asm) |
| `0x0040a710` | `root_0040a710` |  | [decompiled](decompiled/0040a710.c) | [assembly](decompiled/0040a710.asm) |
| `0x0040a714` | `root_0040a714` | Classes.TStrings.ReadData | [decompiled](decompiled/0040a714.c) | [assembly](decompiled/0040a714.asm) |
| `0x0040a77a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a77a.c) | [assembly](decompiled/0040a77a.asm) |
| `0x0040a77f` | `root_0040a77f` |  | [decompiled](decompiled/0040a77f.c) | [assembly](decompiled/0040a77f.asm) |
| `0x0040a788` | `FUN_0040a788` | Classes.TStrings.SaveToFile | [decompiled](decompiled/0040a788.c) | [assembly](decompiled/0040a788.asm) |
| `0x0040a7d3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a7d3.c) | [assembly](decompiled/0040a7d3.asm) |
| `0x0040a7d8` | `root_0040a7d8` |  | [decompiled](decompiled/0040a7d8.c) | [assembly](decompiled/0040a7d8.asm) |
| `0x0040a7e0` | `root_0040a7e0` | Classes.TStrings.SaveToStream | [decompiled](decompiled/0040a7e0.c) | [assembly](decompiled/0040a7e0.asm) |
| `0x0040a835` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a835.c) | [assembly](decompiled/0040a835.asm) |
| `0x0040a83a` | `root_0040a83a` |  | [decompiled](decompiled/0040a83a.c) | [assembly](decompiled/0040a83a.asm) |
| `0x0040a844` | `root_0040a844` | Classes.TStrings.SetText | [decompiled](decompiled/0040a844.c) | [assembly](decompiled/0040a844.asm) |
| `0x0040a888` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a888.c) | [assembly](decompiled/0040a888.asm) |
| `0x0040a88d` | `root_0040a88d` |  | [decompiled](decompiled/0040a88d.c) | [assembly](decompiled/0040a88d.asm) |
| `0x0040a898` | `root_0040a898` | Classes.TStrings.SetTextStr | [decompiled](decompiled/0040a898.c) | [assembly](decompiled/0040a898.asm) |
| `0x0040a931` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a931.c) | [assembly](decompiled/0040a931.asm) |
| `0x0040a936` | `root_0040a936` |  | [decompiled](decompiled/0040a936.c) | [assembly](decompiled/0040a936.asm) |
| `0x0040a945` | `FUN_0040a945` |  | [decompiled](decompiled/0040a945.c) | [assembly](decompiled/0040a945.asm) |
| `0x0040a94e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a94e.c) | [assembly](decompiled/0040a94e.asm) |
| `0x0040a953` | `thunk_FUN_0040a945` |  | [decompiled](decompiled/0040a953.c) | [assembly](decompiled/0040a953.asm) |
| `0x0040a95c` | `root_0040a95c` |  | [decompiled](decompiled/0040a95c.c) | [assembly](decompiled/0040a95c.asm) |
| `0x0040a960` | `root_0040a960` | Classes.TStrings.WriteData | [decompiled](decompiled/0040a960.c) | [assembly](decompiled/0040a960.asm) |
| `0x0040a9d6` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040a9d6.c) | [assembly](decompiled/0040a9d6.asm) |
| `0x0040a9db` | `root_0040a9db` |  | [decompiled](decompiled/0040a9db.c) | [assembly](decompiled/0040a9db.asm) |
| `0x0040a9e4` | `root_0040a9e4` | Classes.TStringList.Destroy | [decompiled](decompiled/0040a9e4.c) | [assembly](decompiled/0040a9e4.asm) |
| `0x0040aa30` | `FUN_0040aa30` | Classes.TStringList.Add | [decompiled](decompiled/0040aa30.c) | [assembly](decompiled/0040aa30.asm) |
| `0x0040aa80` | `root_0040aa80` | Classes.TStringList.Changed | [decompiled](decompiled/0040aa80.c) | [assembly](decompiled/0040aa80.asm) |
| `0x0040aa98` | `root_0040aa98` | Classes.TStringList.Changing | [decompiled](decompiled/0040aa98.c) | [assembly](decompiled/0040aa98.asm) |
| `0x0040aab0` | `root_0040aab0` | Classes.TStringList.Clear | [decompiled](decompiled/0040aab0.c) | [assembly](decompiled/0040aab0.asm) |
| `0x0040aae8` | `root_0040aae8` | Classes.TStringList.Delete | [decompiled](decompiled/0040aae8.c) | [assembly](decompiled/0040aae8.asm) |
| `0x0040ab40` | `FUN_0040ab40` | Classes.TStringList.Exchange | [decompiled](decompiled/0040ab40.c) | [assembly](decompiled/0040ab40.asm) |
| `0x0040ab80` | `FUN_0040ab80` | Classes.TStringList.ExchangeItems | [decompiled](decompiled/0040ab80.c) | [assembly](decompiled/0040ab80.asm) |
| `0x0040aba4` | `FUN_0040aba4` | Classes.TStringList.Find | [decompiled](decompiled/0040aba4.c) | [assembly](decompiled/0040aba4.asm) |
| `0x0040ac0c` | `root_0040ac0c` | Classes.TStringList.Get | [decompiled](decompiled/0040ac0c.c) | [assembly](decompiled/0040ac0c.asm) |
| `0x0040ac34` | `root_0040ac34` |  | [decompiled](decompiled/0040ac34.c) | [assembly](decompiled/0040ac34.asm) |
| `0x0040ac38` | `root_0040ac38` | Classes.TStringList.GetObject | [decompiled](decompiled/0040ac38.c) | [assembly](decompiled/0040ac38.asm) |
| `0x0040ac58` | `FUN_0040ac58` | Classes.TStringList.Grow | [decompiled](decompiled/0040ac58.c) | [assembly](decompiled/0040ac58.asm) |
| `0x0040ac80` | `root_0040ac80` | Classes.TStringList.IndexOf | [decompiled](decompiled/0040ac80.c) | [assembly](decompiled/0040ac80.asm) |
| `0x0040acb8` | `FUN_0040acb8` | Classes.TStringList.Insert | [decompiled](decompiled/0040acb8.c) | [assembly](decompiled/0040acb8.asm) |
| `0x0040acf0` | `FUN_0040acf0` | Classes.TStringList.InsertItem | [decompiled](decompiled/0040acf0.c) | [assembly](decompiled/0040acf0.asm) |
| `0x0040ad58` | `FUN_0040ad58` | Classes.TStringList.Put | [decompiled](decompiled/0040ad58.c) | [assembly](decompiled/0040ad58.asm) |
| `0x0040ada0` | `root_0040ada0` | Classes.TStringList.PutObject | [decompiled](decompiled/0040ada0.c) | [assembly](decompiled/0040ada0.asm) |
| `0x0040add0` | `FUN_0040add0` | Classes.TStringList.QuickSort | [decompiled](decompiled/0040add0.c) | [assembly](decompiled/0040add0.asm) |
| `0x0040ae7e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040ae7e.c) | [assembly](decompiled/0040ae7e.asm) |
| `0x0040ae83` | `root_0040ae83` |  | [decompiled](decompiled/0040ae83.c) | [assembly](decompiled/0040ae83.asm) |
| `0x0040ae8c` | `FUN_0040ae8c` | Classes.TStringList.SetCapacity | [decompiled](decompiled/0040ae8c.c) | [assembly](decompiled/0040ae8c.asm) |
| `0x0040aea8` | `FUN_0040aea8` | Classes.TStringList.SetSorted | [decompiled](decompiled/0040aea8.c) | [assembly](decompiled/0040aea8.asm) |
| `0x0040aec4` | `root_0040aec4` | Classes.TStringList.SetUpdateState | [decompiled](decompiled/0040aec4.c) | [assembly](decompiled/0040aec4.asm) |
| `0x0040aed4` | `root_0040aed4` | Classes.TStringList.Sort | [decompiled](decompiled/0040aed4.c) | [assembly](decompiled/0040aed4.asm) |
| `0x0040af00` | `FUN_0040af00` |  | [decompiled](decompiled/0040af00.c) | [assembly](decompiled/0040af00.asm) |
| `0x0040af10` | `FUN_0040af10` |  | [decompiled](decompiled/0040af10.c) | [assembly](decompiled/0040af10.asm) |
| `0x0040af1c` | `FUN_0040af1c` | Classes.TStream.GetSize | [decompiled](decompiled/0040af1c.c) | [assembly](decompiled/0040af1c.asm) |
| `0x0040af50` | `FUN_0040af50` | Classes.TStream.ReadBuffer | [decompiled](decompiled/0040af50.c) | [assembly](decompiled/0040af50.asm) |
| `0x0040af88` | `FUN_0040af88` | Classes.TStream.WriteBuffer | [decompiled](decompiled/0040af88.c) | [assembly](decompiled/0040af88.asm) |
| `0x0040afc0` | `FUN_0040afc0` | Classes.TStream.ReadComponent | [decompiled](decompiled/0040afc0.c) | [assembly](decompiled/0040afc0.asm) |
| `0x0040b010` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040b010.c) | [assembly](decompiled/0040b010.asm) |
| `0x0040b015` | `root_0040b015` |  | [decompiled](decompiled/0040b015.c) | [assembly](decompiled/0040b015.asm) |
| `0x0040b020` | `root_0040b020` |  | [decompiled](decompiled/0040b020.c) | [assembly](decompiled/0040b020.asm) |
| `0x0040b030` | `root_0040b030` |  | [decompiled](decompiled/0040b030.c) | [assembly](decompiled/0040b030.asm) |
| `0x0040b040` | `root_0040b040` |  | [decompiled](decompiled/0040b040.c) | [assembly](decompiled/0040b040.asm) |
| `0x0040b04c` | `FUN_0040b04c` | Classes.TFileStream.Create | [decompiled](decompiled/0040b04c.c) | [assembly](decompiled/0040b04c.asm) |
| `0x0040b0fc` | `root_0040b0fc` | Classes.TFileStream.Destroy | [decompiled](decompiled/0040b0fc.c) | [assembly](decompiled/0040b0fc.asm) |
| `0x0040b120` | `FUN_0040b120` |  | [decompiled](decompiled/0040b120.c) | [assembly](decompiled/0040b120.asm) |
| `0x0040b128` | `FUN_0040b128` | Classes.TCustomMemoryStream.Read | [decompiled](decompiled/0040b128.c) | [assembly](decompiled/0040b128.asm) |
| `0x0040b160` | `root_0040b160` | Classes.TCustomMemoryStream.Seek | [decompiled](decompiled/0040b160.c) | [assembly](decompiled/0040b160.asm) |
| `0x0040b184` | `root_0040b184` | Classes.TCustomMemoryStream.SaveToStream | [decompiled](decompiled/0040b184.c) | [assembly](decompiled/0040b184.asm) |
| `0x0040b19c` | `root_0040b19c` | Classes.TCustomMemoryStream.SaveToFile, ComCtrls.TCustomTreeView.SaveToFile, DBTables.TBlobField.SaveToFile, OleCtnrs.TOleContainer.SaveToFile, Outline.TCustomOutline.SaveToFile | [decompiled](decompiled/0040b19c.c) | [assembly](decompiled/0040b19c.asm) |
| `0x0040b1e7` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040b1e7.c) | [assembly](decompiled/0040b1e7.asm) |
| `0x0040b1ec` | `root_0040b1ec` |  | [decompiled](decompiled/0040b1ec.c) | [assembly](decompiled/0040b1ec.asm) |
| `0x0040b1f4` | `root_0040b1f4` | Classes.TMemoryStream.Destroy, Classes.TWriter.Destroy, ComCtrls.TListItems.Destroy, ComCtrls.TTreeNodes.Destroy, Controls.TControlCanvas.Destroy, DBGrids.TGridDataLink.Destroy, DDEMan.TDdeCliItem.Destroy, DsgnWnds.TDesignWindow.Destroy, Graphics.TBitmapCanvas.Destroy, Registry.TRegistry.Destroy | [decompiled](decompiled/0040b1f4.c) | [assembly](decompiled/0040b1f4.asm) |
| `0x0040b21c` | `FUN_0040b21c` | Classes.TMemoryStream.Clear | [decompiled](decompiled/0040b21c.c) | [assembly](decompiled/0040b21c.asm) |
| `0x0040b234` | `FUN_0040b234` | Classes.TMemoryStream.LoadFromStream | [decompiled](decompiled/0040b234.c) | [assembly](decompiled/0040b234.asm) |
| `0x0040b26c` | `root_0040b26c` | Classes.TMemoryStream.LoadFromFile, ComCtrls.TCustomTreeView.LoadFromFile, DBTables.TBlobField.LoadFromFile, OleCtnrs.TOleContainer.LoadFromFile, Outline.TCustomOutline.LoadFromFile | [decompiled](decompiled/0040b26c.c) | [assembly](decompiled/0040b26c.asm) |
| `0x0040b2b4` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040b2b4.c) | [assembly](decompiled/0040b2b4.asm) |
| `0x0040b2b9` | `root_0040b2b9` |  | [decompiled](decompiled/0040b2b9.c) | [assembly](decompiled/0040b2b9.asm) |
| `0x0040b2c0` | `FUN_0040b2c0` | Classes.TMemoryStream.SetCapacity | [decompiled](decompiled/0040b2c0.c) | [assembly](decompiled/0040b2c0.asm) |
| `0x0040b2e8` | `FUN_0040b2e8` | Classes.TMemoryStream.SetSize | [decompiled](decompiled/0040b2e8.c) | [assembly](decompiled/0040b2e8.asm) |
| `0x0040b304` | `FUN_0040b304` | Classes.TMemoryStream.Realloc | [decompiled](decompiled/0040b304.c) | [assembly](decompiled/0040b304.asm) |
| `0x0040b384` | `root_0040b384` | Classes.TMemoryStream.Write | [decompiled](decompiled/0040b384.c) | [assembly](decompiled/0040b384.asm) |
| `0x0040b3d4` | `FUN_0040b3d4` | Classes.TResourceStream.Create | [decompiled](decompiled/0040b3d4.c) | [assembly](decompiled/0040b3d4.asm) |
| `0x0040b424` | `FUN_0040b424` | Classes.Error | [decompiled](decompiled/0040b424.c) | [assembly](decompiled/0040b424.asm) |
| `0x0040b48a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040b48a.c) | [assembly](decompiled/0040b48a.asm) |
| `0x0040b48f` | `root_0040b48f` |  | [decompiled](decompiled/0040b48f.c) | [assembly](decompiled/0040b48f.asm) |
| `0x0040b498` | `FUN_0040b498` | Classes.TResourceStream.Initialize | [decompiled](decompiled/0040b498.c) | [assembly](decompiled/0040b498.asm) |
| `0x0040b504` | `root_0040b504` | Classes.TResourceStream.Destroy | [decompiled](decompiled/0040b504.c) | [assembly](decompiled/0040b504.asm) |
| `0x0040b534` | `root_0040b534` |  | [decompiled](decompiled/0040b534.c) | [assembly](decompiled/0040b534.asm) |
| `0x0040b54c` | `FUN_0040b54c` | Classes.TFiler.Create | [decompiled](decompiled/0040b54c.c) | [assembly](decompiled/0040b54c.asm) |
| `0x0040b58c` | `FUN_0040b58c` | Classes.TFiler.Destroy | [decompiled](decompiled/0040b58c.c) | [assembly](decompiled/0040b58c.asm) |
| `0x0040b644` | `FUN_0040b644` | Classes.TPropFixup.Create | [decompiled](decompiled/0040b644.c) | [assembly](decompiled/0040b644.asm) |
| `0x0040b694` | `FUN_0040b694` | Classes.AddFinished | [decompiled](decompiled/0040b694.c) | [assembly](decompiled/0040b694.asm) |
| `0x0040b6cc` | `FUN_0040b6cc` | Classes.AddNotFinished | [decompiled](decompiled/0040b6cc.c) | [assembly](decompiled/0040b6cc.asm) |
| `0x0040b714` | `FUN_0040b714` | Classes.GlobalFixupReferences | [decompiled](decompiled/0040b714.c) | [assembly](decompiled/0040b714.asm) |
| `0x0040b808` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040b808.c) | [assembly](decompiled/0040b808.asm) |
| `0x0040b80d` | `root_0040b80d` |  | [decompiled](decompiled/0040b80d.c) | [assembly](decompiled/0040b80d.asm) |
| `0x0040b84e` | `FUN_0040b84e` |  | [decompiled](decompiled/0040b84e.c) | [assembly](decompiled/0040b84e.asm) |
| `0x0040b857` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040b857.c) | [assembly](decompiled/0040b857.asm) |
| `0x0040b85c` | `thunk_FUN_0040b84e` |  | [decompiled](decompiled/0040b85c.c) | [assembly](decompiled/0040b85c.asm) |
| `0x0040b868` | `FUN_0040b868` | Classes.RemoveFixupReferences | [decompiled](decompiled/0040b868.c) | [assembly](decompiled/0040b868.asm) |
| `0x0040b8c8` | `FUN_0040b8c8` |  | [decompiled](decompiled/0040b8c8.c) | [assembly](decompiled/0040b8c8.asm) |
| `0x0040b8e0` | `FUN_0040b8e0` |  | [decompiled](decompiled/0040b8e0.c) | [assembly](decompiled/0040b8e0.asm) |
| `0x0040b8ec` | `FUN_0040b8ec` |  | [decompiled](decompiled/0040b8ec.c) | [assembly](decompiled/0040b8ec.asm) |
| `0x0040b8f8` | `FUN_0040b8f8` |  | [decompiled](decompiled/0040b8f8.c) | [assembly](decompiled/0040b8f8.asm) |
| `0x0040b910` | `root_0040b910` | Classes.TReader.Destroy | [decompiled](decompiled/0040b910.c) | [assembly](decompiled/0040b910.asm) |
| `0x0040b944` | `FUN_0040b944` | Classes.TReader.CheckValue | [decompiled](decompiled/0040b944.c) | [assembly](decompiled/0040b944.asm) |
| `0x0040b968` | `FUN_0040b968` | Classes.TReader.DefineProperty | [decompiled](decompiled/0040b968.c) | [assembly](decompiled/0040b968.asm) |
| `0x0040b998` | `root_0040b998` | Classes.TReader.DefineBinaryProperty | [decompiled](decompiled/0040b998.c) | [assembly](decompiled/0040b998.asm) |
| `0x0040ba4e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040ba4e.c) | [assembly](decompiled/0040ba4e.asm) |
| `0x0040ba53` | `root_0040ba53` |  | [decompiled](decompiled/0040ba53.c) | [assembly](decompiled/0040ba53.asm) |
| `0x0040ba68` | `FUN_0040ba68` | Classes.TReader.EndOfList | [decompiled](decompiled/0040ba68.c) | [assembly](decompiled/0040ba68.asm) |
| `0x0040ba7c` | `root_0040ba7c` | Classes.TReader.Error | [decompiled](decompiled/0040ba7c.c) | [assembly](decompiled/0040ba7c.asm) |
| `0x0040ba9c` | `FUN_0040ba9c` | Classes.TReader.FindMethod | [decompiled](decompiled/0040ba9c.c) | [assembly](decompiled/0040ba9c.asm) |
| `0x0040bb04` | `FUN_0040bb04` | Classes.TReader.DoFixupReferences | [decompiled](decompiled/0040bb04.c) | [assembly](decompiled/0040bb04.asm) |
| `0x0040bb75` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040bb75.c) | [assembly](decompiled/0040bb75.asm) |
| `0x0040bb7a` | `root_0040bb7a` |  | [decompiled](decompiled/0040bb7a.c) | [assembly](decompiled/0040bb7a.asm) |
| `0x0040bb84` | `root_0040bb84` | Classes.TReader.FlushBuffer | [decompiled](decompiled/0040bb84.c) | [assembly](decompiled/0040bb84.asm) |
| `0x0040bbb0` | `FUN_0040bbb0` | Classes.TReader.FreeFixups | [decompiled](decompiled/0040bbb0.c) | [assembly](decompiled/0040bbb0.asm) |
| `0x0040bbec` | `FUN_0040bbec` |  | [decompiled](decompiled/0040bbec.c) | [assembly](decompiled/0040bbec.asm) |
| `0x0040bbfc` | `FUN_0040bbfc` |  | [decompiled](decompiled/0040bbfc.c) | [assembly](decompiled/0040bbfc.asm) |
| `0x0040bc08` | `FUN_0040bc08` | Classes.TReader.Read | [decompiled](decompiled/0040bc08.c) | [assembly](decompiled/0040bc08.asm) |
| `0x0040bc54` | `FUN_0040bc54` | Classes.TReader.ReadBuffer | [decompiled](decompiled/0040bc54.c) | [assembly](decompiled/0040bc54.asm) |
| `0x0040bc8c` | `FUN_0040bc8c` |  | [decompiled](decompiled/0040bc8c.c) | [assembly](decompiled/0040bc8c.asm) |
| `0x0040bca0` | `FUN_0040bca0` | Classes.TReader.ReadChar | [decompiled](decompiled/0040bca0.c) | [assembly](decompiled/0040bca0.asm) |
| `0x0040bd14` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040bd14.c) | [assembly](decompiled/0040bd14.asm) |
| `0x0040bd19` | `root_0040bd19` |  | [decompiled](decompiled/0040bd19.c) | [assembly](decompiled/0040bd19.asm) |
| `0x0040bd28` | `FUN_0040bd28` | Classes.TReader.ReadCollection | [decompiled](decompiled/0040bd28.c) | [assembly](decompiled/0040bd28.asm) |
| `0x0040bdd3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040bdd3.c) | [assembly](decompiled/0040bdd3.asm) |
| `0x0040bdd8` | `root_0040bdd8` |  | [decompiled](decompiled/0040bdd8.c) | [assembly](decompiled/0040bdd8.asm) |
| `0x0040bde0` | `root_0040bde0` | Classes.ComponentCreated | [decompiled](decompiled/0040bde0.c) | [assembly](decompiled/0040bde0.asm) |
| `0x0040be00` | `root_0040be00` | Classes.Recover | [decompiled](decompiled/0040be00.c) | [assembly](decompiled/0040be00.asm) |
| `0x0040be60` | `FUN_0040be60` | Classes.CreateComponent | [decompiled](decompiled/0040be60.c) | [assembly](decompiled/0040be60.asm) |
| `0x0040beb0` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0040beb0.c) | [assembly](decompiled/0040beb0.asm) |
| `0x0040beb5` | `root_0040beb5` |  | [decompiled](decompiled/0040beb5.c) | [assembly](decompiled/0040beb5.asm) |
| `0x0040bed8` | `FUN_0040bed8` | Classes.SetCompName | [decompiled](decompiled/0040bed8.c) | [assembly](decompiled/0040bed8.asm) |
| `0x0040bf25` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0040bf25.c) | [assembly](decompiled/0040bf25.asm) |
| `0x0040bf2a` | `root_0040bf2a` |  | [decompiled](decompiled/0040bf2a.c) | [assembly](decompiled/0040bf2a.asm) |
| `0x0040bf50` | `FUN_0040bf50` | Classes.FindExistingComponent | [decompiled](decompiled/0040bf50.c) | [assembly](decompiled/0040bf50.asm) |
| `0x0040bfbd` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0040bfbd.c) | [assembly](decompiled/0040bfbd.asm) |
| `0x0040bfc2` | `root_0040bfc2` |  | [decompiled](decompiled/0040bfc2.c) | [assembly](decompiled/0040bfc2.asm) |
| `0x0040bfe8` | `FUN_0040bfe8` | Classes.TReader.ReadComponent | [decompiled](decompiled/0040bfe8.c) | [assembly](decompiled/0040bfe8.asm) |
| `0x0040c0db` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0040c0db.c) | [assembly](decompiled/0040c0db.asm) |
| `0x0040c0e0` | `root_0040c0e0` |  | [decompiled](decompiled/0040c0e0.c) | [assembly](decompiled/0040c0e0.asm) |
| `0x0040c118` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040c118.c) | [assembly](decompiled/0040c118.asm) |
| `0x0040c11d` | `root_0040c11d` |  | [decompiled](decompiled/0040c11d.c) | [assembly](decompiled/0040c11d.asm) |
| `0x0040c12c` | `FUN_0040c12c` | Classes.TReader.ReadData | [decompiled](decompiled/0040c12c.c) | [assembly](decompiled/0040c12c.asm) |
| `0x0040c187` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040c187.c) | [assembly](decompiled/0040c187.asm) |
| `0x0040c18c` | `root_0040c18c` |  | [decompiled](decompiled/0040c18c.c) | [assembly](decompiled/0040c18c.asm) |
| `0x0040c19c` | `FUN_0040c19c` | Classes.TReader.ReadDataInner | [decompiled](decompiled/0040c19c.c) | [assembly](decompiled/0040c19c.asm) |
| `0x0040c25e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040c25e.c) | [assembly](decompiled/0040c25e.asm) |
| `0x0040c263` | `root_0040c263` |  | [decompiled](decompiled/0040c263.c) | [assembly](decompiled/0040c263.asm) |
| `0x0040c26c` | `FUN_0040c26c` | Classes.TReader.ReadFloat | [decompiled](decompiled/0040c26c.c) | [assembly](decompiled/0040c26c.asm) |
| `0x0040c2ac` | `FUN_0040c2ac` | Classes.TReader.ReadIdent | [decompiled](decompiled/0040c2ac.c) | [assembly](decompiled/0040c2ac.asm) |
| `0x0040c360` | `FUN_0040c360` | Classes.TReader.ReadInteger | [decompiled](decompiled/0040c360.c) | [assembly](decompiled/0040c360.asm) |
| `0x0040c3cc` | `FUN_0040c3cc` |  | [decompiled](decompiled/0040c3cc.c) | [assembly](decompiled/0040c3cc.asm) |
| `0x0040c3d4` | `FUN_0040c3d4` |  | [decompiled](decompiled/0040c3d4.c) | [assembly](decompiled/0040c3d4.asm) |
| `0x0040c3dc` | `FUN_0040c3dc` | Classes.TReader.ReadPrefix | [decompiled](decompiled/0040c3dc.c) | [assembly](decompiled/0040c3dc.asm) |
| `0x0040c508` | `FUN_0040c508` | Classes.PropPathError | [decompiled](decompiled/0040c508.c) | [assembly](decompiled/0040c508.asm) |
| `0x0040c524` | `FUN_0040c524` | Classes.TReader.ReadProperty | [decompiled](decompiled/0040c524.c) | [assembly](decompiled/0040c524.asm) |
| `0x0040c673` | `thunk_FUN_00403010` |  | [decompiled](decompiled/0040c673.c) | [assembly](decompiled/0040c673.asm) |
| `0x0040c69a` | `thunk_FUN_00403010` |  | [decompiled](decompiled/0040c69a.c) | [assembly](decompiled/0040c69a.asm) |
| `0x0040c6e5` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040c6e5.c) | [assembly](decompiled/0040c6e5.asm) |
| `0x0040c6ea` | `root_0040c6ea` |  | [decompiled](decompiled/0040c6ea.c) | [assembly](decompiled/0040c6ea.asm) |
| `0x0040c6f4` | `FUN_0040c6f4` | Classes.SetIntIdent | [decompiled](decompiled/0040c6f4.c) | [assembly](decompiled/0040c6f4.asm) |
| `0x0040c75c` | `FUN_0040c75c` | Classes.SetObjectIdent | [decompiled](decompiled/0040c75c.c) | [assembly](decompiled/0040c75c.asm) |
| `0x0040c82c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040c82c.c) | [assembly](decompiled/0040c82c.asm) |
| `0x0040c831` | `root_0040c831` |  | [decompiled](decompiled/0040c831.c) | [assembly](decompiled/0040c831.asm) |
| `0x0040c848` | `root_0040c848` | Classes.TReader.ReadPropValue | [decompiled](decompiled/0040c848.c) | [assembly](decompiled/0040c848.asm) |
| `0x0040ca6b` | `FUN_0040ca6b` |  | [decompiled](decompiled/0040ca6b.c) | [assembly](decompiled/0040ca6b.asm) |
| `0x0040ca74` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040ca74.c) | [assembly](decompiled/0040ca74.asm) |
| `0x0040ca79` | `thunk_FUN_0040ca6b` |  | [decompiled](decompiled/0040ca79.c) | [assembly](decompiled/0040ca79.asm) |
| `0x0040ca84` | `FUN_0040ca84` | Classes.FindUniqueName | [decompiled](decompiled/0040ca84.c) | [assembly](decompiled/0040ca84.asm) |
| `0x0040caf4` | `FUN_0040caf4` | Classes.TReader.ReadRootComponent | [decompiled](decompiled/0040caf4.c) | [assembly](decompiled/0040caf4.asm) |
| `0x0040ccaf` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040ccaf.c) | [assembly](decompiled/0040ccaf.asm) |
| `0x0040ccb4` | `root_0040ccb4` |  | [decompiled](decompiled/0040ccb4.c) | [assembly](decompiled/0040ccb4.asm) |
| `0x0040ccc5` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0040ccc5.c) | [assembly](decompiled/0040ccc5.asm) |
| `0x0040ccca` | `root_0040ccca` |  | [decompiled](decompiled/0040ccca.c) | [assembly](decompiled/0040ccca.asm) |
| `0x0040cd07` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040cd07.c) | [assembly](decompiled/0040cd07.asm) |
| `0x0040cd0c` | `root_0040cd0c` |  | [decompiled](decompiled/0040cd0c.c) | [assembly](decompiled/0040cd0c.asm) |
| `0x0040cd18` | `FUN_0040cd18` | Classes.TReader.ReadSet | [decompiled](decompiled/0040cd18.c) | [assembly](decompiled/0040cd18.asm) |
| `0x0040cd93` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0040cd93.c) | [assembly](decompiled/0040cd93.asm) |
| `0x0040cd98` | `root_0040cd98` |  | [decompiled](decompiled/0040cd98.c) | [assembly](decompiled/0040cd98.asm) |
| `0x0040cdc0` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040cdc0.c) | [assembly](decompiled/0040cdc0.asm) |
| `0x0040cdc5` | `root_0040cdc5` |  | [decompiled](decompiled/0040cdc5.c) | [assembly](decompiled/0040cdc5.asm) |
| `0x0040cdd0` | `FUN_0040cdd0` | Classes.TReader.ReadSignature | [decompiled](decompiled/0040cdd0.c) | [assembly](decompiled/0040cdd0.asm) |
| `0x0040cdf4` | `FUN_0040cdf4` | Classes.TReader.ReadStr | [decompiled](decompiled/0040cdf4.c) | [assembly](decompiled/0040cdf4.asm) |
| `0x0040ce30` | `FUN_0040ce30` | Classes.TReader.ReadString | [decompiled](decompiled/0040ce30.c) | [assembly](decompiled/0040ce30.asm) |
| `0x0040ce90` | `FUN_0040ce90` |  | [decompiled](decompiled/0040ce90.c) | [assembly](decompiled/0040ce90.asm) |
| `0x0040cea4` | `FUN_0040cea4` | Classes.TReader.SkipSetBody | [decompiled](decompiled/0040cea4.c) | [assembly](decompiled/0040cea4.asm) |
| `0x0040cee2` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040cee2.c) | [assembly](decompiled/0040cee2.asm) |
| `0x0040cee7` | `root_0040cee7` |  | [decompiled](decompiled/0040cee7.c) | [assembly](decompiled/0040cee7.asm) |
| `0x0040cef0` | `FUN_0040cef0` | Classes.SkipList | [decompiled](decompiled/0040cef0.c) | [assembly](decompiled/0040cef0.asm) |
| `0x0040cf18` | `FUN_0040cf18` | Classes.SkipBytes | [decompiled](decompiled/0040cf18.c) | [assembly](decompiled/0040cf18.asm) |
| `0x0040cf6c` | `FUN_0040cf6c` | Classes.SkipBinary | [decompiled](decompiled/0040cf6c.c) | [assembly](decompiled/0040cf6c.asm) |
| `0x0040cf94` | `FUN_0040cf94` | Classes.TReader.SkipValue | [decompiled](decompiled/0040cf94.c) | [assembly](decompiled/0040cf94.asm) |
| `0x0040d075` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040d075.c) | [assembly](decompiled/0040d075.asm) |
| `0x0040d07a` | `root_0040d07a` |  | [decompiled](decompiled/0040d07a.c) | [assembly](decompiled/0040d07a.asm) |
| `0x0040d084` | `FUN_0040d084` | Classes.TReader.SkipProperty | [decompiled](decompiled/0040d084.c) | [assembly](decompiled/0040d084.asm) |
| `0x0040d0c3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040d0c3.c) | [assembly](decompiled/0040d0c3.asm) |
| `0x0040d0c8` | `root_0040d0c8` |  | [decompiled](decompiled/0040d0c8.c) | [assembly](decompiled/0040d0c8.asm) |
| `0x0040d0d0` | `root_0040d0d0` | Classes.TReader.SkipComponent | [decompiled](decompiled/0040d0d0.c) | [assembly](decompiled/0040d0d0.asm) |
| `0x0040d161` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040d161.c) | [assembly](decompiled/0040d161.asm) |
| `0x0040d166` | `root_0040d166` |  | [decompiled](decompiled/0040d166.c) | [assembly](decompiled/0040d166.asm) |
| `0x0040d170` | `FUN_0040d170` |  | [decompiled](decompiled/0040d170.c) | [assembly](decompiled/0040d170.asm) |
| `0x0040d198` | `root_0040d198` | Classes.TMemoryStream.Destroy, Classes.TWriter.Destroy, ComCtrls.TListItems.Destroy, ComCtrls.TTreeNodes.Destroy, Controls.TControlCanvas.Destroy, DBGrids.TGridDataLink.Destroy, DDEMan.TDdeCliItem.Destroy, DsgnWnds.TDesignWindow.Destroy, Graphics.TBitmapCanvas.Destroy, Registry.TRegistry.Destroy | [decompiled](decompiled/0040d198.c) | [assembly](decompiled/0040d198.asm) |
| `0x0040d1cc` | `root_0040d1cc` | Classes.TWriter.DefineProperty | [decompiled](decompiled/0040d1cc.c) | [assembly](decompiled/0040d1cc.asm) |
| `0x0040d1ec` | `root_0040d1ec` | Classes.TWriter.DefineBinaryProperty | [decompiled](decompiled/0040d1ec.c) | [assembly](decompiled/0040d1ec.asm) |
| `0x0040d210` | `FUN_0040d210` |  | [decompiled](decompiled/0040d210.c) | [assembly](decompiled/0040d210.asm) |
| `0x0040d220` | `root_0040d220` |  | [decompiled](decompiled/0040d220.c) | [assembly](decompiled/0040d220.asm) |
| `0x0040d228` | `FUN_0040d228` | Classes.TWriter.SetPosition | [decompiled](decompiled/0040d228.c) | [assembly](decompiled/0040d228.asm) |
| `0x0040d260` | `FUN_0040d260` | Classes.TWriter.Write | [decompiled](decompiled/0040d260.c) | [assembly](decompiled/0040d260.asm) |
| `0x0040d2ac` | `FUN_0040d2ac` | Classes.TWriter.WriteBinary | [decompiled](decompiled/0040d2ac.c) | [assembly](decompiled/0040d2ac.asm) |
| `0x0040d324` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040d324.c) | [assembly](decompiled/0040d324.asm) |
| `0x0040d329` | `root_0040d329` |  | [decompiled](decompiled/0040d329.c) | [assembly](decompiled/0040d329.asm) |
| `0x0040d334` | `FUN_0040d334` | Classes.TWriter.WriteBuffer | [decompiled](decompiled/0040d334.c) | [assembly](decompiled/0040d334.asm) |
| `0x0040d34c` | `FUN_0040d34c` |  | [decompiled](decompiled/0040d34c.c) | [assembly](decompiled/0040d34c.asm) |
| `0x0040d360` | `FUN_0040d360` | Classes.TWriter.WriteChar | [decompiled](decompiled/0040d360.c) | [assembly](decompiled/0040d360.asm) |
| `0x0040d3a4` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040d3a4.c) | [assembly](decompiled/0040d3a4.asm) |
| `0x0040d3a9` | `root_0040d3a9` |  | [decompiled](decompiled/0040d3a9.c) | [assembly](decompiled/0040d3a9.asm) |
| `0x0040d3b4` | `FUN_0040d3b4` | Classes.TWriter.WriteCollection | [decompiled](decompiled/0040d3b4.c) | [assembly](decompiled/0040d3b4.asm) |
| `0x0040d408` | `FUN_0040d408` | Classes.FindAncestor | [decompiled](decompiled/0040d408.c) | [assembly](decompiled/0040d408.asm) |
| `0x0040d458` | `root_0040d458` | Classes.TWriter.WriteComponent | [decompiled](decompiled/0040d458.c) | [assembly](decompiled/0040d458.asm) |
| `0x0040d494` | `root_0040d494` | Classes.TWriter.WriteData | [decompiled](decompiled/0040d494.c) | [assembly](decompiled/0040d494.asm) |
| `0x0040d6bf` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040d6bf.c) | [assembly](decompiled/0040d6bf.asm) |
| `0x0040d6c4` | `root_0040d6c4` |  | [decompiled](decompiled/0040d6c4.c) | [assembly](decompiled/0040d6c4.asm) |
| `0x0040d6ef` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040d6ef.c) | [assembly](decompiled/0040d6ef.asm) |
| `0x0040d6f4` | `root_0040d6f4` |  | [decompiled](decompiled/0040d6f4.c) | [assembly](decompiled/0040d6f4.asm) |
| `0x0040d73d` | `FUN_0040d73d` |  | [decompiled](decompiled/0040d73d.c) | [assembly](decompiled/0040d73d.asm) |
| `0x0040d749` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040d749.c) | [assembly](decompiled/0040d749.asm) |
| `0x0040d74e` | `thunk_FUN_0040d73d` |  | [decompiled](decompiled/0040d74e.c) | [assembly](decompiled/0040d74e.asm) |
| `0x0040d760` | `FUN_0040d760` | Classes.TWriter.WriteFloat | [decompiled](decompiled/0040d760.c) | [assembly](decompiled/0040d760.asm) |
| `0x0040d784` | `FUN_0040d784` | Classes.TWriter.WriteIdent | [decompiled](decompiled/0040d784.c) | [assembly](decompiled/0040d784.asm) |
| `0x0040d820` | `FUN_0040d820` | Classes.TWriter.WriteInteger | [decompiled](decompiled/0040d820.c) | [assembly](decompiled/0040d820.asm) |
| `0x0040d894` | `FUN_0040d894` |  | [decompiled](decompiled/0040d894.c) | [assembly](decompiled/0040d894.asm) |
| `0x0040d89c` | `FUN_0040d89c` |  | [decompiled](decompiled/0040d89c.c) | [assembly](decompiled/0040d89c.asm) |
| `0x0040d8a4` | `FUN_0040d8a4` | Classes.TWriter.WritePrefix | [decompiled](decompiled/0040d8a4.c) | [assembly](decompiled/0040d8a4.asm) |
| `0x0040d8e8` | `FUN_0040d8e8` | Classes.TWriter.WriteProperties | [decompiled](decompiled/0040d8e8.c) | [assembly](decompiled/0040d8e8.asm) |
| `0x0040d991` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040d991.c) | [assembly](decompiled/0040d991.asm) |
| `0x0040d996` | `root_0040d996` |  | [decompiled](decompiled/0040d996.c) | [assembly](decompiled/0040d996.asm) |
| `0x0040d9ac` | `FUN_0040d9ac` | Classes.AncestorValid | [decompiled](decompiled/0040d9ac.c) | [assembly](decompiled/0040d9ac.asm) |
| `0x0040d9f8` | `FUN_0040d9f8` | Classes.WritePropPath | [decompiled](decompiled/0040d9f8.c) | [assembly](decompiled/0040d9f8.asm) |
| `0x0040da43` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040da43.c) | [assembly](decompiled/0040da43.asm) |
| `0x0040da48` | `root_0040da48` |  | [decompiled](decompiled/0040da48.c) | [assembly](decompiled/0040da48.asm) |
| `0x0040da50` | `FUN_0040da50` | Classes.WriteSet | [decompiled](decompiled/0040da50.c) | [assembly](decompiled/0040da50.asm) |
| `0x0040dad4` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040dad4.c) | [assembly](decompiled/0040dad4.asm) |
| `0x0040dad9` | `root_0040dad9` |  | [decompiled](decompiled/0040dad9.c) | [assembly](decompiled/0040dad9.asm) |
| `0x0040dae4` | `FUN_0040dae4` | Classes.WriteIntProp | [decompiled](decompiled/0040dae4.c) | [assembly](decompiled/0040dae4.asm) |
| `0x0040db71` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040db71.c) | [assembly](decompiled/0040db71.asm) |
| `0x0040db76` | `root_0040db76` |  | [decompiled](decompiled/0040db76.c) | [assembly](decompiled/0040db76.asm) |
| `0x0040db80` | `FUN_0040db80` | Classes.WriteCollectionProp | [decompiled](decompiled/0040db80.c) | [assembly](decompiled/0040db80.asm) |
| `0x0040dbfb` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040dbfb.c) | [assembly](decompiled/0040dbfb.asm) |
| `0x0040dc00` | `root_0040dc00` |  | [decompiled](decompiled/0040dc00.c) | [assembly](decompiled/0040dc00.asm) |
| `0x0040dc0f` | `FUN_0040dc0f` |  | [decompiled](decompiled/0040dc0f.c) | [assembly](decompiled/0040dc0f.asm) |
| `0x0040dc18` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040dc18.c) | [assembly](decompiled/0040dc18.asm) |
| `0x0040dc1d` | `thunk_FUN_0040dc0f` |  | [decompiled](decompiled/0040dc1d.c) | [assembly](decompiled/0040dc1d.asm) |
| `0x0040dc28` | `FUN_0040dc28` | Classes.IsDefaultValue | [decompiled](decompiled/0040dc28.c) | [assembly](decompiled/0040dc28.asm) |
| `0x0040dc78` | `FUN_0040dc78` | Classes.WriteOrdProp | [decompiled](decompiled/0040dc78.c) | [assembly](decompiled/0040dc78.asm) |
| `0x0040dd42` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040dd42.c) | [assembly](decompiled/0040dd42.asm) |
| `0x0040dd47` | `root_0040dd47` |  | [decompiled](decompiled/0040dd47.c) | [assembly](decompiled/0040dd47.asm) |
| `0x0040dd50` | `FUN_0040dd50` | Classes.IsDefaultValue | [decompiled](decompiled/0040dd50.c) | [assembly](decompiled/0040dd50.asm) |
| `0x0040dda8` | `FUN_0040dda8` | Classes.WriteFloatProp | [decompiled](decompiled/0040dda8.c) | [assembly](decompiled/0040dda8.asm) |
| `0x0040ddf4` | `FUN_0040ddf4` | Classes.IsDefault | [decompiled](decompiled/0040ddf4.c) | [assembly](decompiled/0040ddf4.asm) |
| `0x0040de6b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040de6b.c) | [assembly](decompiled/0040de6b.asm) |
| `0x0040de70` | `root_0040de70` |  | [decompiled](decompiled/0040de70.c) | [assembly](decompiled/0040de70.asm) |
| `0x0040de7c` | `FUN_0040de7c` | Classes.WriteStrProp | [decompiled](decompiled/0040de7c.c) | [assembly](decompiled/0040de7c.asm) |
| `0x0040dedf` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040dedf.c) | [assembly](decompiled/0040dedf.asm) |
| `0x0040dee4` | `root_0040dee4` |  | [decompiled](decompiled/0040dee4.c) | [assembly](decompiled/0040dee4.asm) |
| `0x0040deec` | `FUN_0040deec` | Classes.IsDefault | [decompiled](decompiled/0040deec.c) | [assembly](decompiled/0040deec.asm) |
| `0x0040df7c` | `FUN_0040df7c` | Classes.GetComponentValue | [decompiled](decompiled/0040df7c.c) | [assembly](decompiled/0040df7c.asm) |
| `0x0040dfdc` | `FUN_0040dfdc` | Classes.WriteObjectProp | [decompiled](decompiled/0040dfdc.c) | [assembly](decompiled/0040dfdc.asm) |
| `0x0040e1bf` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040e1bf.c) | [assembly](decompiled/0040e1bf.asm) |
| `0x0040e1c4` | `root_0040e1c4` |  | [decompiled](decompiled/0040e1c4.c) | [assembly](decompiled/0040e1c4.asm) |
| `0x0040e1dc` | `FUN_0040e1dc` | Classes.IsDefaultValue | [decompiled](decompiled/0040e1dc.c) | [assembly](decompiled/0040e1dc.asm) |
| `0x0040e260` | `FUN_0040e260` | Classes.WriteMethodProp | [decompiled](decompiled/0040e260.c) | [assembly](decompiled/0040e260.asm) |
| `0x0040e308` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040e308.c) | [assembly](decompiled/0040e308.asm) |
| `0x0040e30d` | `root_0040e30d` |  | [decompiled](decompiled/0040e30d.c) | [assembly](decompiled/0040e30d.asm) |
| `0x0040e318` | `FUN_0040e318` | Classes.TWriter.WriteProperty | [decompiled](decompiled/0040e318.c) | [assembly](decompiled/0040e318.asm) |
| `0x0040e3a4` | `FUN_0040e3a4` | Classes.TWriter.WritePropName | [decompiled](decompiled/0040e3a4.c) | [assembly](decompiled/0040e3a4.asm) |
| `0x0040e3f3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040e3f3.c) | [assembly](decompiled/0040e3f3.asm) |
| `0x0040e3f8` | `root_0040e3f8` |  | [decompiled](decompiled/0040e3f8.c) | [assembly](decompiled/0040e3f8.asm) |
| `0x0040e400` | `FUN_0040e400` | Classes.TWriter.WriteStr | [decompiled](decompiled/0040e400.c) | [assembly](decompiled/0040e400.asm) |
| `0x0040e448` | `FUN_0040e448` | Classes.TWriter.WriteString | [decompiled](decompiled/0040e448.c) | [assembly](decompiled/0040e448.asm) |
| `0x0040e4a4` | `FUN_0040e4a4` |  | [decompiled](decompiled/0040e4a4.c) | [assembly](decompiled/0040e4a4.asm) |
| `0x0040e4b8` | `FUN_0040e4b8` | Classes.TComponent.Create | [decompiled](decompiled/0040e4b8.c) | [assembly](decompiled/0040e4b8.asm) |
| `0x0040e4fc` | `FUN_0040e4fc` | Classes.TComponent.Destroy | [decompiled](decompiled/0040e4fc.c) | [assembly](decompiled/0040e4fc.asm) |
| `0x0040e570` | `FUN_0040e570` | Classes.TComponent.FreeNotification | [decompiled](decompiled/0040e570.c) | [assembly](decompiled/0040e570.asm) |
| `0x0040e5bc` | `root_0040e5bc` | Classes.TComponent.ReadLeft | [decompiled](decompiled/0040e5bc.c) | [assembly](decompiled/0040e5bc.asm) |
| `0x0040e5d0` | `root_0040e5d0` | Classes.TComponent.ReadTop | [decompiled](decompiled/0040e5d0.c) | [assembly](decompiled/0040e5d0.asm) |
| `0x0040e5fc` | `FUN_0040e5fc` | Classes.TComponent.Insert | [decompiled](decompiled/0040e5fc.c) | [assembly](decompiled/0040e5fc.asm) |
| `0x0040e628` | `FUN_0040e628` | Classes.TComponent.Remove | [decompiled](decompiled/0040e628.c) | [assembly](decompiled/0040e628.asm) |
| `0x0040e650` | `FUN_0040e650` | Classes.TComponent.InsertComponent | [decompiled](decompiled/0040e650.c) | [assembly](decompiled/0040e650.asm) |
| `0x0040e698` | `FUN_0040e698` | Classes.TComponent.RemoveComponent | [decompiled](decompiled/0040e698.c) | [assembly](decompiled/0040e698.asm) |
| `0x0040e6d8` | `FUN_0040e6d8` | Classes.TComponent.DestroyComponents | [decompiled](decompiled/0040e6d8.c) | [assembly](decompiled/0040e6d8.asm) |
| `0x0040e704` | `FUN_0040e704` | Classes.TComponent.Destroying | [decompiled](decompiled/0040e704.c) | [assembly](decompiled/0040e704.asm) |
| `0x0040e73c` | `FUN_0040e73c` | Classes.TComponent.Notification | [decompiled](decompiled/0040e73c.c) | [assembly](decompiled/0040e73c.asm) |
| `0x0040e7a8` | `FUN_0040e7a8` | Classes.DoWriteLeft | [decompiled](decompiled/0040e7a8.c) | [assembly](decompiled/0040e7a8.asm) |
| `0x0040e7e0` | `FUN_0040e7e0` | Classes.DoWriteTop | [decompiled](decompiled/0040e7e0.c) | [assembly](decompiled/0040e7e0.asm) |
| `0x0040e818` | `FUN_0040e818` | Classes.TComponent.DefineProperties | [decompiled](decompiled/0040e818.c) | [assembly](decompiled/0040e818.asm) |
| `0x0040e89c` | `root_0040e89c` |  | [decompiled](decompiled/0040e89c.c) | [assembly](decompiled/0040e89c.asm) |
| `0x0040e8a0` | `FUN_0040e8a0` |  | [decompiled](decompiled/0040e8a0.c) | [assembly](decompiled/0040e8a0.asm) |
| `0x0040e8a8` | `root_0040e8a8` |  | [decompiled](decompiled/0040e8a8.c) | [assembly](decompiled/0040e8a8.asm) |
| `0x0040e8ac` | `root_0040e8ac` |  | [decompiled](decompiled/0040e8ac.c) | [assembly](decompiled/0040e8ac.asm) |
| `0x0040e8b0` | `root_0040e8b0` |  | [decompiled](decompiled/0040e8b0.c) | [assembly](decompiled/0040e8b0.asm) |
| `0x0040e8b4` | `root_0040e8b4` |  | [decompiled](decompiled/0040e8b4.c) | [assembly](decompiled/0040e8b4.asm) |
| `0x0040e8b8` | `root_0040e8b8` |  | [decompiled](decompiled/0040e8b8.c) | [assembly](decompiled/0040e8b8.asm) |
| `0x0040e8bc` | `root_0040e8bc` |  | [decompiled](decompiled/0040e8bc.c) | [assembly](decompiled/0040e8bc.asm) |
| `0x0040e8c8` | `FUN_0040e8c8` |  | [decompiled](decompiled/0040e8c8.c) | [assembly](decompiled/0040e8c8.asm) |
| `0x0040e8d4` | `FUN_0040e8d4` |  | [decompiled](decompiled/0040e8d4.c) | [assembly](decompiled/0040e8d4.asm) |
| `0x0040e8e0` | `FUN_0040e8e0` |  | [decompiled](decompiled/0040e8e0.c) | [assembly](decompiled/0040e8e0.asm) |
| `0x0040e8e8` | `root_0040e8e8` |  | [decompiled](decompiled/0040e8e8.c) | [assembly](decompiled/0040e8e8.asm) |
| `0x0040e8f0` | `FUN_0040e8f0` | Classes.TComponent.ValidateRename | [decompiled](decompiled/0040e8f0.c) | [assembly](decompiled/0040e8f0.asm) |
| `0x0040e968` | `FUN_0040e968` | Classes.TComponent.FindComponent | [decompiled](decompiled/0040e968.c) | [assembly](decompiled/0040e968.asm) |
| `0x0040e9b8` | `FUN_0040e9b8` | Classes.TComponent.SetName | [decompiled](decompiled/0040e9b8.c) | [assembly](decompiled/0040e9b8.asm) |
| `0x0040ea40` | `FUN_0040ea40` |  | [decompiled](decompiled/0040ea40.c) | [assembly](decompiled/0040ea40.asm) |
| `0x0040ea54` | `FUN_0040ea54` | Classes.TComponent.GetComponent | [decompiled](decompiled/0040ea54.c) | [assembly](decompiled/0040ea54.asm) |
| `0x0040ea78` | `FUN_0040ea78` |  | [decompiled](decompiled/0040ea78.c) | [assembly](decompiled/0040ea78.asm) |
| `0x0040ea88` | `FUN_0040ea88` | Classes.TComponent.SetComponentIndex | [decompiled](decompiled/0040ea88.c) | [assembly](decompiled/0040ea88.asm) |
| `0x0040eadc` | `FUN_0040eadc` | Classes.TComponent.SetDesigning | [decompiled](decompiled/0040eadc.c) | [assembly](decompiled/0040eadc.asm) |
| `0x0040eb1c` | `FUN_0040eb1c` | Classes.TComponent.SetReference | [decompiled](decompiled/0040eb1c.c) | [assembly](decompiled/0040eb1c.asm) |
| `0x0040ebd0` | `FUN_0040ebd0` |  | [decompiled](decompiled/0040ebd0.c) | [assembly](decompiled/0040ebd0.asm) |
| `0x0040ec3c` | `ImageList_Create` |  | [decompiled](decompiled/0040ec3c.c) | [assembly](decompiled/0040ec3c.asm) |
| `0x0040ec44` | `ImageList_Destroy` |  | [decompiled](decompiled/0040ec44.c) | [assembly](decompiled/0040ec44.asm) |
| `0x0040ec4c` | `ImageList_GetImageCount` |  | [decompiled](decompiled/0040ec4c.c) | [assembly](decompiled/0040ec4c.asm) |
| `0x0040ec54` | `ImageList_Add` |  | [decompiled](decompiled/0040ec54.c) | [assembly](decompiled/0040ec54.asm) |
| `0x0040ec5c` | `ImageList_ReplaceIcon` |  | [decompiled](decompiled/0040ec5c.c) | [assembly](decompiled/0040ec5c.asm) |
| `0x0040ec64` | `ImageList_SetBkColor` |  | [decompiled](decompiled/0040ec64.c) | [assembly](decompiled/0040ec64.asm) |
| `0x0040ec6c` | `ImageList_GetBkColor` |  | [decompiled](decompiled/0040ec6c.c) | [assembly](decompiled/0040ec6c.asm) |
| `0x0040ec74` | `FUN_0040ec74` |  | [decompiled](decompiled/0040ec74.c) | [assembly](decompiled/0040ec74.asm) |
| `0x0040ec80` | `ImageList_Draw` |  | [decompiled](decompiled/0040ec80.c) | [assembly](decompiled/0040ec80.asm) |
| `0x0040ec88` | `ImageList_Replace` |  | [decompiled](decompiled/0040ec88.c) | [assembly](decompiled/0040ec88.asm) |
| `0x0040ec90` | `ImageList_AddMasked` |  | [decompiled](decompiled/0040ec90.c) | [assembly](decompiled/0040ec90.asm) |
| `0x0040ec98` | `ImageList_DrawEx` |  | [decompiled](decompiled/0040ec98.c) | [assembly](decompiled/0040ec98.asm) |
| `0x0040eca0` | `ImageList_Remove` |  | [decompiled](decompiled/0040eca0.c) | [assembly](decompiled/0040eca0.asm) |
| `0x0040eca8` | `ImageList_BeginDrag` |  | [decompiled](decompiled/0040eca8.c) | [assembly](decompiled/0040eca8.asm) |
| `0x0040ecb0` | `ImageList_EndDrag` |  | [decompiled](decompiled/0040ecb0.c) | [assembly](decompiled/0040ecb0.asm) |
| `0x0040ecb8` | `ImageList_DragEnter` |  | [decompiled](decompiled/0040ecb8.c) | [assembly](decompiled/0040ecb8.asm) |
| `0x0040ecc0` | `ImageList_DragLeave` |  | [decompiled](decompiled/0040ecc0.c) | [assembly](decompiled/0040ecc0.asm) |
| `0x0040ecc8` | `ImageList_DragMove` |  | [decompiled](decompiled/0040ecc8.c) | [assembly](decompiled/0040ecc8.asm) |
| `0x0040ecd0` | `ImageList_SetDragCursorImage` |  | [decompiled](decompiled/0040ecd0.c) | [assembly](decompiled/0040ecd0.asm) |
| `0x0040ecd8` | `ImageList_DragShowNolock` |  | [decompiled](decompiled/0040ecd8.c) | [assembly](decompiled/0040ecd8.asm) |
| `0x0040ece0` | `ImageList_GetDragImage` |  | [decompiled](decompiled/0040ece0.c) | [assembly](decompiled/0040ece0.asm) |
| `0x0040ece8` | `ImageList_GetIconSize` |  | [decompiled](decompiled/0040ece8.c) | [assembly](decompiled/0040ece8.asm) |
| `0x0040ecf0` | `ImageList_SetIconSize` |  | [decompiled](decompiled/0040ecf0.c) | [assembly](decompiled/0040ecf0.asm) |
| `0x0040ecf8` | `ImageList_GetImageInfo` |  | [decompiled](decompiled/0040ecf8.c) | [assembly](decompiled/0040ecf8.asm) |
| `0x0040ed0c` | `FUN_0040ed0c` |  | [decompiled](decompiled/0040ed0c.c) | [assembly](decompiled/0040ed0c.asm) |
| `0x0040ed20` | `FUN_0040ed20` |  | [decompiled](decompiled/0040ed20.c) | [assembly](decompiled/0040ed20.asm) |
| `0x0040ed28` | `FUN_0040ed28` |  | [decompiled](decompiled/0040ed28.c) | [assembly](decompiled/0040ed28.asm) |
| `0x0040ed64` | `FUN_0040ed64` |  | [decompiled](decompiled/0040ed64.c) | [assembly](decompiled/0040ed64.asm) |
| `0x0040ed98` | `FUN_0040ed98` |  | [decompiled](decompiled/0040ed98.c) | [assembly](decompiled/0040ed98.asm) |
| `0x0040edcc` | `FUN_0040edcc` |  | [decompiled](decompiled/0040edcc.c) | [assembly](decompiled/0040edcc.asm) |
| `0x0040ee5b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040ee5b.c) | [assembly](decompiled/0040ee5b.asm) |
| `0x0040ee60` | `root_0040ee60` |  | [decompiled](decompiled/0040ee60.c) | [assembly](decompiled/0040ee60.asm) |
| `0x0040ee6c` | `FUN_0040ee6c` |  | [decompiled](decompiled/0040ee6c.c) | [assembly](decompiled/0040ee6c.asm) |
| `0x0040ee88` | `FUN_0040ee88` |  | [decompiled](decompiled/0040ee88.c) | [assembly](decompiled/0040ee88.asm) |
| `0x0040efa0` | `FUN_0040efa0` |  | [decompiled](decompiled/0040efa0.c) | [assembly](decompiled/0040efa0.asm) |
| `0x0040f140` | `FUN_0040f140` |  | [decompiled](decompiled/0040f140.c) | [assembly](decompiled/0040f140.asm) |
| `0x0040f714` | `FUN_0040f714` |  | [decompiled](decompiled/0040f714.c) | [assembly](decompiled/0040f714.asm) |
| `0x0040f72c` | `FUN_0040f72c` | Menus.IndexError | [decompiled](decompiled/0040f72c.c) | [assembly](decompiled/0040f72c.asm) |
| `0x0040f76d` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040f76d.c) | [assembly](decompiled/0040f76d.asm) |
| `0x0040f772` | `root_0040f772` |  | [decompiled](decompiled/0040f772.c) | [assembly](decompiled/0040f772.asm) |
| `0x0040f77c` | `FUN_0040f77c` | Menus.LoadStrings | [decompiled](decompiled/0040f77c.c) | [assembly](decompiled/0040f77c.asm) |
| `0x0040f7d3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040f7d3.c) | [assembly](decompiled/0040f7d3.asm) |
| `0x0040f7d8` | `root_0040f7d8` |  | [decompiled](decompiled/0040f7d8.c) | [assembly](decompiled/0040f7d8.asm) |
| `0x0040f7e0` | `FUN_0040f7e0` | Menus.GetSpecialName | [decompiled](decompiled/0040f7e0.c) | [assembly](decompiled/0040f7e0.asm) |
| `0x0040f848` | `FUN_0040f848` | Menus.ShortCutToText | [decompiled](decompiled/0040f848.c) | [assembly](decompiled/0040f848.asm) |
| `0x0040fa35` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040fa35.c) | [assembly](decompiled/0040fa35.asm) |
| `0x0040fa3a` | `root_0040fa3a` |  | [decompiled](decompiled/0040fa3a.c) | [assembly](decompiled/0040fa3a.asm) |
| `0x0040fa50` | `FUN_0040fa50` | Menus.CompareFront | [decompiled](decompiled/0040fa50.c) | [assembly](decompiled/0040fa50.asm) |
| `0x0040fac0` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040fac0.c) | [assembly](decompiled/0040fac0.asm) |
| `0x0040fac5` | `root_0040fac5` |  | [decompiled](decompiled/0040fac5.c) | [assembly](decompiled/0040fac5.asm) |
| `0x0040fad0` | `FUN_0040fad0` | Menus.TextToShortCut | [decompiled](decompiled/0040fad0.c) | [assembly](decompiled/0040fad0.asm) |
| `0x0040fbab` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0040fbab.c) | [assembly](decompiled/0040fbab.asm) |
| `0x0040fbb0` | `root_0040fbb0` |  | [decompiled](decompiled/0040fbb0.c) | [assembly](decompiled/0040fbb0.asm) |
| `0x0040fbc8` | `root_0040fbc8` | Menus.UniqueCommand | [decompiled](decompiled/0040fbc8.c) | [assembly](decompiled/0040fbc8.asm) |
| `0x0040fbe8` | `FUN_0040fbe8` | Menus.Iterate | [decompiled](decompiled/0040fbe8.c) | [assembly](decompiled/0040fbe8.asm) |
| `0x0040fc48` | `FUN_0040fc48` | Menus.IterateMenus | [decompiled](decompiled/0040fc48.c) | [assembly](decompiled/0040fc48.asm) |
| `0x0040fd50` | `FUN_0040fd50` | Menus.TMenuItem.Create | [decompiled](decompiled/0040fd50.c) | [assembly](decompiled/0040fd50.asm) |
| `0x0040fd90` | `root_0040fd90` | Menus.TMenuItem.Destroy | [decompiled](decompiled/0040fd90.c) | [assembly](decompiled/0040fd90.asm) |
| `0x0040fe1c` | `FUN_0040fe1c` | Menus.Clear | [decompiled](decompiled/0040fe1c.c) | [assembly](decompiled/0040fe1c.asm) |
| `0x0040fe58` | `FUN_0040fe58` |  | [decompiled](decompiled/0040fe58.c) | [assembly](decompiled/0040fe58.asm) |
| `0x0040fe64` | `FUN_0040fe64` | Menus.TMenuItem.AppendTo | [decompiled](decompiled/0040fe64.c) | [assembly](decompiled/0040fe64.asm) |
| `0x00410069` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00410069.c) | [assembly](decompiled/00410069.asm) |
| `0x0041006e` | `root_0041006e` |  | [decompiled](decompiled/0041006e.c) | [assembly](decompiled/0041006e.asm) |
| `0x00410090` | `root_00410090` | Menus.AddIn | [decompiled](decompiled/00410090.c) | [assembly](decompiled/00410090.asm) |
| `0x004100a8` | `FUN_004100a8` | Menus.TMenuItem.PopulateMenu | [decompiled](decompiled/004100a8.c) | [assembly](decompiled/004100a8.asm) |
| `0x004100c8` | `root_004100c8` | Menus.TMenuItem.ReadShortCutText | [decompiled](decompiled/004100c8.c) | [assembly](decompiled/004100c8.asm) |
| `0x00410113` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00410113.c) | [assembly](decompiled/00410113.asm) |
| `0x00410118` | `root_00410118` |  | [decompiled](decompiled/00410118.c) | [assembly](decompiled/00410118.asm) |
| `0x00410120` | `FUN_00410120` |  | [decompiled](decompiled/00410120.c) | [assembly](decompiled/00410120.asm) |
| `0x00410130` | `FUN_00410130` | Menus.TMenuItem.RebuildHandle | [decompiled](decompiled/00410130.c) | [assembly](decompiled/00410130.asm) |
| `0x0041016c` | `FUN_0041016c` | Menus.TMenuItem.VerifyGroupIndex | [decompiled](decompiled/0041016c.c) | [assembly](decompiled/0041016c.asm) |
| `0x00410208` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00410208.c) | [assembly](decompiled/00410208.asm) |
| `0x0041020d` | `root_0041020d` |  | [decompiled](decompiled/0041020d.c) | [assembly](decompiled/0041020d.asm) |
| `0x0041021c` | `FUN_0041021c` | Menus.TMenuItem.GetHandle | [decompiled](decompiled/0041021c.c) | [assembly](decompiled/0041021c.asm) |
| `0x00410270` | `root_00410270` | Menus.TMenuItem.DefineProperties | [decompiled](decompiled/00410270.c) | [assembly](decompiled/00410270.asm) |
| `0x004102b4` | `root_004102b4` |  | [decompiled](decompiled/004102b4.c) | [assembly](decompiled/004102b4.asm) |
| `0x004102b8` | `root_004102b8` | Menus.TMenuItem.SetBreak | [decompiled](decompiled/004102b8.c) | [assembly](decompiled/004102b8.asm) |
| `0x004102c8` | `root_004102c8` | Menus.TMenuItem.SetCaption | [decompiled](decompiled/004102c8.c) | [assembly](decompiled/004102c8.asm) |
| `0x004102f0` | `FUN_004102f0` | Menus.TMenuItem.SetChecked | [decompiled](decompiled/004102f0.c) | [assembly](decompiled/004102f0.asm) |
| `0x00410378` | `FUN_00410378` | Menus.TMenuItem.SetEnabled | [decompiled](decompiled/00410378.c) | [assembly](decompiled/00410378.asm) |
| `0x004103dc` | `FUN_004103dc` | Menus.TMenuItem.SetGroupIndex | [decompiled](decompiled/004103dc.c) | [assembly](decompiled/004103dc.asm) |
| `0x0041040c` | `FUN_0041040c` |  | [decompiled](decompiled/0041040c.c) | [assembly](decompiled/0041040c.asm) |
| `0x0041041c` | `FUN_0041041c` | Menus.TMenuItem.GetItem | [decompiled](decompiled/0041041c.c) | [assembly](decompiled/0041041c.asm) |
| `0x0041043c` | `FUN_0041043c` |  | [decompiled](decompiled/0041043c.c) | [assembly](decompiled/0041043c.asm) |
| `0x00410448` | `root_00410448` |  | [decompiled](decompiled/00410448.c) | [assembly](decompiled/00410448.asm) |
| `0x00410454` | `root_00410454` | Menus.TMenuItem.GetMenuIndex | [decompiled](decompiled/00410454.c) | [assembly](decompiled/00410454.asm) |
| `0x0041046c` | `root_0041046c` | Menus.TMenuItem.SetMenuIndex | [decompiled](decompiled/0041046c.c) | [assembly](decompiled/0041046c.asm) |
| `0x004104b4` | `root_004104b4` | Menus.TMenuItem.GetChildren | [decompiled](decompiled/004104b4.c) | [assembly](decompiled/004104b4.asm) |
| `0x004104ec` | `root_004104ec` | Menus.TMenuItem.SetChildOrder | [decompiled](decompiled/004104ec.c) | [assembly](decompiled/004104ec.asm) |
| `0x00410508` | `FUN_00410508` | Menus.TMenuItem.SetDefault | [decompiled](decompiled/00410508.c) | [assembly](decompiled/00410508.asm) |
| `0x00410564` | `FUN_00410564` | Menus.TMenuItem.Insert | [decompiled](decompiled/00410564.c) | [assembly](decompiled/00410564.asm) |
| `0x0041061c` | `FUN_0041061c` | Menus.TMenuItem.Delete | [decompiled](decompiled/0041061c.c) | [assembly](decompiled/0041061c.asm) |
| `0x00410680` | `root_00410680` | Menus.TMenuItem.Click | [decompiled](decompiled/00410680.c) | [assembly](decompiled/00410680.asm) |
| `0x004106a4` | `FUN_004106a4` | Menus.TMenuItem.IndexOf | [decompiled](decompiled/004106a4.c) | [assembly](decompiled/004106a4.asm) |
| `0x004106bc` | `root_004106bc` | Menus.TMenuItem.Add | [decompiled](decompiled/004106bc.c) | [assembly](decompiled/004106bc.asm) |
| `0x004106d8` | `FUN_004106d8` | Menus.TMenuItem.Remove | [decompiled](decompiled/004106d8.c) | [assembly](decompiled/004106d8.asm) |
| `0x00410708` | `root_00410708` | Menus.TMenuItem.MenuChanged | [decompiled](decompiled/00410708.c) | [assembly](decompiled/00410708.asm) |
| `0x00410728` | `FUN_00410728` | Menus.TMenuItem.SubItemChanged | [decompiled](decompiled/00410728.c) | [assembly](decompiled/00410728.asm) |
| `0x00410770` | `root_00410770` | Menus.TMenuItem.GetParentComponent | [decompiled](decompiled/00410770.c) | [assembly](decompiled/00410770.asm) |
| `0x0041078c` | `root_0041078c` | Menus.TMenuItem.SetParentComponent | [decompiled](decompiled/0041078c.c) | [assembly](decompiled/0041078c.asm) |
| `0x004107dc` | `root_004107dc` | Menus.TMenuItem.SetRadioItem | [decompiled](decompiled/004107dc.c) | [assembly](decompiled/004107dc.asm) |
| `0x004107ec` | `FUN_004107ec` | Menus.TMenu.Create | [decompiled](decompiled/004107ec.c) | [assembly](decompiled/004107ec.asm) |
| `0x00410854` | `FUN_00410854` | DDEMan.TDdeClientItem.Destroy, DDEMan.TDdeServerItem.Destroy, Menus.TMenu.Destroy | [decompiled](decompiled/00410854.c) | [assembly](decompiled/00410854.asm) |
| `0x0041087c` | `FUN_0041087c` | Menus.TMenu.GetChildren | [decompiled](decompiled/0041087c.c) | [assembly](decompiled/0041087c.asm) |
| `0x00410898` | `FUN_00410898` |  | [decompiled](decompiled/00410898.c) | [assembly](decompiled/00410898.asm) |
| `0x004108a4` | `root_004108a4` |  | [decompiled](decompiled/004108a4.c) | [assembly](decompiled/004108a4.asm) |
| `0x004108c0` | `FUN_004108c0` | Menus.Find | [decompiled](decompiled/004108c0.c) | [assembly](decompiled/004108c0.asm) |
| `0x00410958` | `FUN_00410958` | Menus.TMenu.FindItem | [decompiled](decompiled/00410958.c) | [assembly](decompiled/00410958.asm) |
| `0x00410988` | `FUN_00410988` | Menus.TMenu.GetHelpContext | [decompiled](decompiled/00410988.c) | [assembly](decompiled/00410988.asm) |
| `0x004109bc` | `FUN_004109bc` | Menus.TMenu.DispatchCommand | [decompiled](decompiled/004109bc.c) | [assembly](decompiled/004109bc.asm) |
| `0x004109d8` | `FUN_004109d8` | Menus.TMenu.DispatchPopup | [decompiled](decompiled/004109d8.c) | [assembly](decompiled/004109d8.asm) |
| `0x004109f4` | `FUN_004109f4` | Menus.DoClick | [decompiled](decompiled/004109f4.c) | [assembly](decompiled/004109f4.asm) |
| `0x00410a57` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00410a57.c) | [assembly](decompiled/00410a57.asm) |
| `0x00410a5c` | `root_00410a5c` |  | [decompiled](decompiled/00410a5c.c) | [assembly](decompiled/00410a5c.asm) |
| `0x00410a80` | `FUN_00410a80` | Menus.TMenu.IsShortCut | [decompiled](decompiled/00410a80.c) | [assembly](decompiled/00410a80.asm) |
| `0x00410b08` | `FUN_00410b08` | Menus.BuildImage | [decompiled](decompiled/00410b08.c) | [assembly](decompiled/00410b08.asm) |
| `0x00410bdc` | `FUN_00410bdc` | Menus.TMenu.UpdateImage | [decompiled](decompiled/00410bdc.c) | [assembly](decompiled/00410bdc.asm) |
| `0x00410c40` | `FUN_00410c40` |  | [decompiled](decompiled/00410c40.c) | [assembly](decompiled/00410c40.asm) |
| `0x00410c4c` | `root_00410c4c` |  | [decompiled](decompiled/00410c4c.c) | [assembly](decompiled/00410c4c.asm) |
| `0x00410c50` | `root_00410c50` | Menus.TMainMenu.SetAutoMerge | [decompiled](decompiled/00410c50.c) | [assembly](decompiled/00410c50.asm) |
| `0x00410c70` | `FUN_00410c70` | Menus.TMainMenu.MenuChanged | [decompiled](decompiled/00410c70.c) | [assembly](decompiled/00410c70.asm) |
| `0x00410c90` | `FUN_00410c90` | Menus.TMainMenu.Merge | [decompiled](decompiled/00410c90.c) | [assembly](decompiled/00410c90.asm) |
| `0x00410cac` | `FUN_00410cac` | Menus.TMainMenu.Unmerge | [decompiled](decompiled/00410cac.c) | [assembly](decompiled/00410cac.asm) |
| `0x00410cc8` | `FUN_00410cc8` | Menus.TMainMenu.ItemChanged | [decompiled](decompiled/00410cc8.c) | [assembly](decompiled/00410cc8.asm) |
| `0x00410cf0` | `root_00410cf0` |  | [decompiled](decompiled/00410cf0.c) | [assembly](decompiled/00410cf0.asm) |
| `0x00410f45` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00410f45.c) | [assembly](decompiled/00410f45.asm) |
| `0x00410f4a` | `root_00410f4a` |  | [decompiled](decompiled/00410f4a.c) | [assembly](decompiled/00410f4a.asm) |
| `0x00410f64` | `FUN_00410f64` | Menus.TPopupList.Add | [decompiled](decompiled/00410f64.c) | [assembly](decompiled/00410f64.asm) |
| `0x00410f8c` | `FUN_00410f8c` | Menus.TPopupList.Remove | [decompiled](decompiled/00410f8c.c) | [assembly](decompiled/00410f8c.asm) |
| `0x00410fa8` | `root_00410fa8` | Menus.TPopupMenu.Create | [decompiled](decompiled/00410fa8.c) | [assembly](decompiled/00410fa8.asm) |
| `0x00411004` | `root_00411004` | DDEMan.TDdeServerConv.Destroy, Menus.TPopupMenu.Destroy | [decompiled](decompiled/00411004.c) | [assembly](decompiled/00411004.asm) |
| `0x00411030` | `FUN_00411030` | Menus.TPopupMenu.DoPopup | [decompiled](decompiled/00411030.c) | [assembly](decompiled/00411030.asm) |
| `0x00411040` | `root_00411040` |  | [decompiled](decompiled/00411040.c) | [assembly](decompiled/00411040.asm) |
| `0x00411048` | `root_00411048` |  | [decompiled](decompiled/00411048.c) | [assembly](decompiled/00411048.asm) |
| `0x00411050` | `FUN_00411050` | Menus.TPopupMenu.Popup | [decompiled](decompiled/00411050.c) | [assembly](decompiled/00411050.asm) |
| `0x00411098` | `FUN_00411098` | Menus.Menus | [decompiled](decompiled/00411098.c) | [assembly](decompiled/00411098.asm) |
| `0x004110f4` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004110f4.c) | [assembly](decompiled/004110f4.asm) |
| `0x004110f9` | `root_004110f9` |  | [decompiled](decompiled/004110f9.c) | [assembly](decompiled/004110f9.asm) |
| `0x0041212c` | `root_0041212c` | Controls.InitWndProc | [decompiled](decompiled/0041212c.c) | [assembly](decompiled/0041212c.asm) |
| `0x004121e4` | `FUN_004121e4` | Controls.FindControl | [decompiled](decompiled/004121e4.c) | [assembly](decompiled/004121e4.asm) |
| `0x00412200` | `FUN_00412200` | Controls.SendAppMessage | [decompiled](decompiled/00412200.c) | [assembly](decompiled/00412200.asm) |
| `0x004123c8` | `root_004123c8` | Controls.IdentToCursor | [decompiled](decompiled/004123c8.c) | [assembly](decompiled/004123c8.asm) |
| `0x00412400` | `FUN_00412400` | Controls.GetShortHint | [decompiled](decompiled/00412400.c) | [assembly](decompiled/00412400.asm) |
| `0x00412444` | `FUN_00412444` | Controls.GetLongHint | [decompiled](decompiled/00412444.c) | [assembly](decompiled/00412444.asm) |
| `0x00412488` | `FUN_00412488` | Controls.GetCaptureControl | [decompiled](decompiled/00412488.c) | [assembly](decompiled/00412488.asm) |
| `0x004124b0` | `FUN_004124b0` | Controls.SetCaptureControl | [decompiled](decompiled/004124b0.c) | [assembly](decompiled/004124b0.asm) |
| `0x004124f4` | `root_004124f4` |  | [decompiled](decompiled/004124f4.c) | [assembly](decompiled/004124f4.asm) |
| `0x004124fc` | `root_004124fc` | Controls.TDragObject.GetName | [decompiled](decompiled/004124fc.c) | [assembly](decompiled/004124fc.asm) |
| `0x00412524` | `root_00412524` |  | [decompiled](decompiled/00412524.c) | [assembly](decompiled/00412524.asm) |
| `0x00412528` | `FUN_00412528` |  | [decompiled](decompiled/00412528.c) | [assembly](decompiled/00412528.asm) |
| `0x00412540` | `FUN_00412540` |  | [decompiled](decompiled/00412540.c) | [assembly](decompiled/00412540.asm) |
| `0x00412554` | `root_00412554` | Controls.TDragObject.GetDragCursor | [decompiled](decompiled/00412554.c) | [assembly](decompiled/00412554.asm) |
| `0x0041256c` | `root_0041256c` |  | [decompiled](decompiled/0041256c.c) | [assembly](decompiled/0041256c.asm) |
| `0x00412574` | `root_00412574` |  | [decompiled](decompiled/00412574.c) | [assembly](decompiled/00412574.asm) |
| `0x00412578` | `root_00412578` |  | [decompiled](decompiled/00412578.c) | [assembly](decompiled/00412578.asm) |
| `0x0041257c` | `root_0041257c` | Controls.TDragObject.MouseMsg | [decompiled](decompiled/0041257c.c) | [assembly](decompiled/0041257c.asm) |
| `0x004125da` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/004125da.c) | [assembly](decompiled/004125da.asm) |
| `0x004125df` | `root_004125df` |  | [decompiled](decompiled/004125df.c) | [assembly](decompiled/004125df.asm) |
| `0x00412600` | `FUN_00412600` | Classes.THandleStream.Create, Controls.TDragControlObject.Create, OCXReg.TOleObjectEditor.Create, OleAuto.TAutoDispatch.Create, OleCtnrs.TAdviseSink.Create, OleCtnrs.TOleClientSite.Create, OleCtnrs.TOleInPlaceFrame.Create, OleCtnrs.TOleInPlaceSite.Create, OleCtnrs.TOleUIObjInfo.Create, OleCtrls.TAmbientDispatch.Create, OleCtrls.TEventDispatch.Create, OleCtrls.TOleClientSite.Create, OleCtrls.TOleControlSite.Create, OleCtrls.TOleInPlaceFrame.Create, OleCtrls.TOleInPlaceSite.Create, OleCtrls.TPropertyNotifySink.Create, OleCtrls.TSimpleFrameSite.Create | [decompiled](decompiled/00412600.c) | [assembly](decompiled/00412600.asm) |
| `0x00412620` | `root_00412620` |  | [decompiled](decompiled/00412620.c) | [assembly](decompiled/00412620.asm) |
| `0x0041262c` | `root_0041262c` | Controls.TDragControlObject.HideDragImage, Controls.TDragControlObject.ShowDragImage | [decompiled](decompiled/0041262c.c) | [assembly](decompiled/0041262c.asm) |
| `0x0041264c` | `root_0041264c` | Controls.TDragControlObject.HideDragImage, Controls.TDragControlObject.ShowDragImage | [decompiled](decompiled/0041264c.c) | [assembly](decompiled/0041264c.asm) |
| `0x0041266c` | `root_0041266c` | Controls.TDragControlObject.GetDragCursor | [decompiled](decompiled/0041266c.c) | [assembly](decompiled/0041266c.asm) |
| `0x00412684` | `FUN_00412684` | Controls.TDragControlObject.Finished | [decompiled](decompiled/00412684.c) | [assembly](decompiled/00412684.asm) |
| `0x004126c4` | `FUN_004126c4` | Controls.DragMessage | [decompiled](decompiled/004126c4.c) | [assembly](decompiled/004126c4.asm) |
| `0x0041270c` | `FUN_0041270c` | Controls.IsDelphiHandle | [decompiled](decompiled/0041270c.c) | [assembly](decompiled/0041270c.asm) |
| `0x00412730` | `FUN_00412730` | Controls.DragFindWindow | [decompiled](decompiled/00412730.c) | [assembly](decompiled/00412730.asm) |
| `0x0041275c` | `FUN_0041275c` | Controls.DragFindTarget | [decompiled](decompiled/0041275c.c) | [assembly](decompiled/0041275c.asm) |
| `0x00412780` | `FUN_00412780` | Controls.DoDragOver | [decompiled](decompiled/00412780.c) | [assembly](decompiled/00412780.asm) |
| `0x004127b4` | `FUN_004127b4` | Controls.DragTo | [decompiled](decompiled/004127b4.c) | [assembly](decompiled/004127b4.asm) |
| `0x00412918` | `FUN_00412918` | Controls.DragInit | [decompiled](decompiled/00412918.c) | [assembly](decompiled/00412918.asm) |
| `0x004129a4` | `FUN_004129a4` | Controls.DragInitControl | [decompiled](decompiled/004129a4.c) | [assembly](decompiled/004129a4.asm) |
| `0x00412a13` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00412a13.c) | [assembly](decompiled/00412a13.asm) |
| `0x00412a18` | `root_00412a18` |  | [decompiled](decompiled/00412a18.c) | [assembly](decompiled/00412a18.asm) |
| `0x00412a30` | `FUN_00412a30` | Controls.DragDone | [decompiled](decompiled/00412a30.c) | [assembly](decompiled/00412a30.asm) |
| `0x00412b69` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00412b69.c) | [assembly](decompiled/00412b69.asm) |
| `0x00412b6e` | `root_00412b6e` |  | [decompiled](decompiled/00412b6e.c) | [assembly](decompiled/00412b6e.asm) |
| `0x00412b7d` | `FUN_00412b7d` |  | [decompiled](decompiled/00412b7d.c) | [assembly](decompiled/00412b7d.asm) |
| `0x00412b8f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00412b8f.c) | [assembly](decompiled/00412b8f.asm) |
| `0x00412b94` | `thunk_FUN_00412b7d` |  | [decompiled](decompiled/00412b94.c) | [assembly](decompiled/00412b94.asm) |
| `0x00412b9c` | `FUN_00412b9c` |  | [decompiled](decompiled/00412b9c.c) | [assembly](decompiled/00412b9c.asm) |
| `0x00412bb4` | `FUN_00412bb4` | Controls.FindVCLWindow | [decompiled](decompiled/00412bb4.c) | [assembly](decompiled/00412bb4.asm) |
| `0x00412be8` | `FUN_00412be8` | Controls.FindDragTarget | [decompiled](decompiled/00412be8.c) | [assembly](decompiled/00412be8.asm) |
| `0x00412c2c` | `FUN_00412c2c` | Controls.ListAdd | [decompiled](decompiled/00412c2c.c) | [assembly](decompiled/00412c2c.asm) |
| `0x00412c54` | `FUN_00412c54` | Controls.ListRemove | [decompiled](decompiled/00412c54.c) | [assembly](decompiled/00412c54.asm) |
| `0x00412c74` | `FUN_00412c74` | Controls.MoveWindowOrg, QuickRep.MoveWindowOrg | [decompiled](decompiled/00412c74.c) | [assembly](decompiled/00412c74.asm) |
| `0x00412ca4` | `FUN_00412ca4` |  | [decompiled](decompiled/00412ca4.c) | [assembly](decompiled/00412ca4.asm) |
| `0x00412cb8` | `thunk_FUN_00412cbf` |  | [decompiled](decompiled/00412cb8.c) | [assembly](decompiled/00412cb8.asm) |
| `0x00412cbf` | `FUN_00412cbf` |  | [decompiled](decompiled/00412cbf.c) | [assembly](decompiled/00412cbf.asm) |
| `0x00412ccc` | `root_00412ccc` | Classes.TMemoryStream.Destroy, Classes.TWriter.Destroy, ComCtrls.TListItems.Destroy, ComCtrls.TTreeNodes.Destroy, Controls.TControlCanvas.Destroy, DBGrids.TGridDataLink.Destroy, DDEMan.TDdeCliItem.Destroy, DsgnWnds.TDesignWindow.Destroy, Graphics.TBitmapCanvas.Destroy, Registry.TRegistry.Destroy | [decompiled](decompiled/00412ccc.c) | [assembly](decompiled/00412ccc.asm) |
| `0x00412cf4` | `root_00412cf4` | Controls.TControlCanvas.CreateHandle | [decompiled](decompiled/00412cf4.c) | [assembly](decompiled/00412cf4.asm) |
| `0x00412d4c` | `FUN_00412d4c` | Controls.TControlCanvas.FreeHandle | [decompiled](decompiled/00412d4c.c) | [assembly](decompiled/00412d4c.asm) |
| `0x00412d80` | `FUN_00412d80` | Controls.TControlCanvas.SetControl | [decompiled](decompiled/00412d80.c) | [assembly](decompiled/00412d80.asm) |
| `0x00412d98` | `FUN_00412d98` | Controls.TControl.Create | [decompiled](decompiled/00412d98.c) | [assembly](decompiled/00412d98.asm) |
| `0x00412e20` | `FUN_00412e20` | Controls.TControl.Destroy | [decompiled](decompiled/00412e20.c) | [assembly](decompiled/00412e20.asm) |
| `0x00412e64` | `root_00412e64` |  | [decompiled](decompiled/00412e64.c) | [assembly](decompiled/00412e64.asm) |
| `0x00412e68` | `root_00412e68` |  | [decompiled](decompiled/00412e68.c) | [assembly](decompiled/00412e68.asm) |
| `0x00412e6c` | `root_00412e6c` |  | [decompiled](decompiled/00412e6c.c) | [assembly](decompiled/00412e6c.asm) |
| `0x00412e74` | `root_00412e74` |  | [decompiled](decompiled/00412e74.c) | [assembly](decompiled/00412e74.asm) |
| `0x00412e78` | `root_00412e78` |  | [decompiled](decompiled/00412e78.c) | [assembly](decompiled/00412e78.asm) |
| `0x00412e9c` | `root_00412e9c` | Controls.TControl.PaletteChanged | [decompiled](decompiled/00412e9c.c) | [assembly](decompiled/00412e9c.asm) |
| `0x00412f18` | `root_00412f18` |  | [decompiled](decompiled/00412f18.c) | [assembly](decompiled/00412f18.asm) |
| `0x00412f1c` | `FUN_00412f1c` |  | [decompiled](decompiled/00412f1c.c) | [assembly](decompiled/00412f1c.asm) |
| `0x00412f2c` | `FUN_00412f2c` |  | [decompiled](decompiled/00412f2c.c) | [assembly](decompiled/00412f2c.asm) |
| `0x00412f9c` | `FUN_00412f9c` | Controls.TControl.Notification | [decompiled](decompiled/00412f9c.c) | [assembly](decompiled/00412f9c.asm) |
| `0x00412fc8` | `root_00412fc8` |  | [decompiled](decompiled/00412fc8.c) | [assembly](decompiled/00412fc8.asm) |
| `0x0041302c` | `FUN_0041302c` | Controls.TControl.SetBounds | [decompiled](decompiled/0041302c.c) | [assembly](decompiled/0041302c.asm) |
| `0x00413098` | `FUN_00413098` |  | [decompiled](decompiled/00413098.c) | [assembly](decompiled/00413098.asm) |
| `0x004130b8` | `FUN_004130b8` |  | [decompiled](decompiled/004130b8.c) | [assembly](decompiled/004130b8.asm) |
| `0x004130d8` | `FUN_004130d8` |  | [decompiled](decompiled/004130d8.c) | [assembly](decompiled/004130d8.asm) |
| `0x004130f8` | `FUN_004130f8` |  | [decompiled](decompiled/004130f8.c) | [assembly](decompiled/004130f8.asm) |
| `0x00413118` | `FUN_00413118` | Controls.TControl.GetBoundsRect | [decompiled](decompiled/00413118.c) | [assembly](decompiled/00413118.asm) |
| `0x00413138` | `FUN_00413138` |  | [decompiled](decompiled/00413138.c) | [assembly](decompiled/00413138.asm) |
| `0x00413160` | `root_00413160` | Controls.TControl.GetClientRect | [decompiled](decompiled/00413160.c) | [assembly](decompiled/00413160.asm) |
| `0x00413178` | `FUN_00413178` | Controls.TControl.GetClientWidth | [decompiled](decompiled/00413178.c) | [assembly](decompiled/00413178.asm) |
| `0x00413190` | `FUN_00413190` | Controls.TControl.SetClientWidth, Dialogs.TFindDialog.SetLeft | [decompiled](decompiled/00413190.c) | [assembly](decompiled/00413190.asm) |
| `0x004131bc` | `FUN_004131bc` | Controls.TControl.GetClientHeight | [decompiled](decompiled/004131bc.c) | [assembly](decompiled/004131bc.asm) |
| `0x004131d4` | `FUN_004131d4` | Controls.TControl.SetClientHeight, Dialogs.TFindDialog.SetTop | [decompiled](decompiled/004131d4.c) | [assembly](decompiled/004131d4.asm) |
| `0x004131fc` | `FUN_004131fc` | Controls.TControl.GetClientOrigin | [decompiled](decompiled/004131fc.c) | [assembly](decompiled/004131fc.asm) |
| `0x0041324c` | `FUN_0041324c` | Controls.TControl.ClientToScreen | [decompiled](decompiled/0041324c.c) | [assembly](decompiled/0041324c.asm) |
| `0x00413278` | `FUN_00413278` | Controls.TControl.ScreenToClient | [decompiled](decompiled/00413278.c) | [assembly](decompiled/00413278.asm) |
| `0x004132a4` | `FUN_004132a4` |  | [decompiled](decompiled/004132a4.c) | [assembly](decompiled/004132a4.asm) |
| `0x004132bc` | `FUN_004132bc` |  | [decompiled](decompiled/004132bc.c) | [assembly](decompiled/004132bc.asm) |
| `0x004133d0` | `root_004133d0` | Controls.TControl.SetName | [decompiled](decompiled/004133d0.c) | [assembly](decompiled/004133d0.asm) |
| `0x0041345f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041345f.c) | [assembly](decompiled/0041345f.asm) |
| `0x00413464` | `root_00413464` |  | [decompiled](decompiled/00413464.c) | [assembly](decompiled/00413464.asm) |
| `0x00413470` | `FUN_00413470` | Controls.TControl.SetClientSize | [decompiled](decompiled/00413470.c) | [assembly](decompiled/00413470.asm) |
| `0x004134b8` | `FUN_004134b8` | Controls.TControl.SetParent | [decompiled](decompiled/004134b8.c) | [assembly](decompiled/004134b8.asm) |
| `0x00413500` | `FUN_00413500` | Controls.TControl.SetVisible | [decompiled](decompiled/00413500.c) | [assembly](decompiled/00413500.asm) |
| `0x0041353c` | `FUN_0041353c` | Controls.TControl.SetEnabled | [decompiled](decompiled/0041353c.c) | [assembly](decompiled/0041353c.asm) |
| `0x00413554` | `FUN_00413554` |  | [decompiled](decompiled/00413554.c) | [assembly](decompiled/00413554.asm) |
| `0x00413564` | `FUN_00413564` |  | [decompiled](decompiled/00413564.c) | [assembly](decompiled/00413564.asm) |
| `0x00413570` | `FUN_00413570` |  | [decompiled](decompiled/00413570.c) | [assembly](decompiled/00413570.asm) |
| `0x00413580` | `FUN_00413580` | Controls.TControl.SetTextBuf | [decompiled](decompiled/00413580.c) | [assembly](decompiled/00413580.asm) |
| `0x004135a4` | `FUN_004135a4` | Controls.TControl.GetText | [decompiled](decompiled/004135a4.c) | [assembly](decompiled/004135a4.asm) |
| `0x004135d4` | `FUN_004135d4` | Controls.TControl.SetText | [decompiled](decompiled/004135d4.c) | [assembly](decompiled/004135d4.asm) |
| `0x0041362a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041362a.c) | [assembly](decompiled/0041362a.asm) |
| `0x0041362f` | `root_0041362f` |  | [decompiled](decompiled/0041362f.c) | [assembly](decompiled/0041362f.asm) |
| `0x00413638` | `FUN_00413638` | Controls.TControl.FontChanged | [decompiled](decompiled/00413638.c) | [assembly](decompiled/00413638.asm) |
| `0x00413670` | `FUN_00413670` |  | [decompiled](decompiled/00413670.c) | [assembly](decompiled/00413670.asm) |
| `0x0041367c` | `root_0041367c` |  | [decompiled](decompiled/0041367c.c) | [assembly](decompiled/0041367c.asm) |
| `0x00413684` | `root_00413684` |  | [decompiled](decompiled/00413684.c) | [assembly](decompiled/00413684.asm) |
| `0x0041368c` | `FUN_0041368c` | Controls.TControl.SetParentFont | [decompiled](decompiled/0041368c.c) | [assembly](decompiled/0041368c.asm) |
| `0x004136ac` | `FUN_004136ac` | Controls.TControl.SetShowHint | [decompiled](decompiled/004136ac.c) | [assembly](decompiled/004136ac.asm) |
| `0x004136c8` | `root_004136c8` | Controls.TControl.SetParentShowHint | [decompiled](decompiled/004136c8.c) | [assembly](decompiled/004136c8.asm) |
| `0x004136e8` | `FUN_004136e8` | Controls.TControl.SetColor | [decompiled](decompiled/004136e8.c) | [assembly](decompiled/004136e8.asm) |
| `0x00413704` | `root_00413704` |  | [decompiled](decompiled/00413704.c) | [assembly](decompiled/00413704.asm) |
| `0x0041370c` | `FUN_0041370c` | Controls.TControl.SetParentColor | [decompiled](decompiled/0041370c.c) | [assembly](decompiled/0041370c.asm) |
| `0x0041372c` | `root_0041372c` | Controls.TControl.SetCursor | [decompiled](decompiled/0041372c.c) | [assembly](decompiled/0041372c.asm) |
| `0x00413748` | `FUN_00413748` |  | [decompiled](decompiled/00413748.c) | [assembly](decompiled/00413748.asm) |
| `0x00413758` | `FUN_00413758` | Controls.TControl.SetMouseCapture | [decompiled](decompiled/00413758.c) | [assembly](decompiled/00413758.asm) |
| `0x00413780` | `FUN_00413780` |  | [decompiled](decompiled/00413780.c) | [assembly](decompiled/00413780.asm) |
| `0x00413794` | `FUN_00413794` | Controls.TControl.SetZOrderPosition | [decompiled](decompiled/00413794.c) | [assembly](decompiled/00413794.asm) |
| `0x00413814` | `root_00413814` | Controls.TControl.SetZOrder | [decompiled](decompiled/00413814.c) | [assembly](decompiled/00413814.asm) |
| `0x00413838` | `FUN_00413838` | Controls.TControl.GetDeviceContext | [decompiled](decompiled/00413838.c) | [assembly](decompiled/00413838.asm) |
| `0x0041389c` | `FUN_0041389c` | Controls.BackgroundClipped | [decompiled](decompiled/0041389c.c) | [assembly](decompiled/0041389c.asm) |
| `0x00413924` | `FUN_00413924` | Controls.TControl.InvalidateControl | [decompiled](decompiled/00413924.c) | [assembly](decompiled/00413924.asm) |
| `0x004139b0` | `root_004139b0` |  | [decompiled](decompiled/004139b0.c) | [assembly](decompiled/004139b0.asm) |
| `0x004139c0` | `root_004139c0` |  | [decompiled](decompiled/004139c0.c) | [assembly](decompiled/004139c0.asm) |
| `0x004139d4` | `FUN_004139d4` |  | [decompiled](decompiled/004139d4.c) | [assembly](decompiled/004139d4.asm) |
| `0x004139dc` | `root_004139dc` | Controls.TControl.Repaint | [decompiled](decompiled/004139dc.c) | [assembly](decompiled/004139dc.asm) |
| `0x00413ab5` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00413ab5.c) | [assembly](decompiled/00413ab5.asm) |
| `0x00413aba` | `root_00413aba` |  | [decompiled](decompiled/00413aba.c) | [assembly](decompiled/00413aba.asm) |
| `0x00413ad4` | `FUN_00413ad4` | Controls.TControl.BeginDrag | [decompiled](decompiled/00413ad4.c) | [assembly](decompiled/00413ad4.asm) |
| `0x00413b68` | `root_00413b68` |  | [decompiled](decompiled/00413b68.c) | [assembly](decompiled/00413b68.asm) |
| `0x00413b6c` | `FUN_00413b6c` |  | [decompiled](decompiled/00413b6c.c) | [assembly](decompiled/00413b6c.asm) |
| `0x00413b78` | `root_00413b78` | Controls.TControl.DragOver | [decompiled](decompiled/00413b78.c) | [assembly](decompiled/00413b78.asm) |
| `0x00413bb4` | `FUN_00413bb4` | Controls.TControl.DragDrop | [decompiled](decompiled/00413bb4.c) | [assembly](decompiled/00413bb4.asm) |
| `0x00413bd8` | `root_00413bd8` | Controls.TControl.DoStartDrag | [decompiled](decompiled/00413bd8.c) | [assembly](decompiled/00413bd8.asm) |
| `0x00413bf8` | `FUN_00413bf8` | Controls.TControl.DoEndDrag | [decompiled](decompiled/00413bf8.c) | [assembly](decompiled/00413bf8.asm) |
| `0x00413c24` | `root_00413c24` |  | [decompiled](decompiled/00413c24.c) | [assembly](decompiled/00413c24.asm) |
| `0x00413cb8` | `FUN_00413cb8` | Controls.TControl.Perform | [decompiled](decompiled/00413cb8.c) | [assembly](decompiled/00413cb8.asm) |
| `0x00413ce4` | `root_00413ce4` |  | [decompiled](decompiled/00413ce4.c) | [assembly](decompiled/00413ce4.asm) |
| `0x00413ce8` | `FUN_00413ce8` |  | [decompiled](decompiled/00413ce8.c) | [assembly](decompiled/00413ce8.asm) |
| `0x00413d94` | `FUN_00413d94` | Controls.TControl.DefaultHandler | [decompiled](decompiled/00413d94.c) | [assembly](decompiled/00413d94.asm) |
| `0x00413e2c` | `FUN_00413e2c` | Controls.DoWrite | [decompiled](decompiled/00413e2c.c) | [assembly](decompiled/00413e2c.asm) |
| `0x00413e5c` | `FUN_00413e5c` | Controls.TControl.DefineProperties | [decompiled](decompiled/00413e5c.c) | [assembly](decompiled/00413e5c.asm) |
| `0x00413eac` | `FUN_00413eac` | Controls.TControl.Click | [decompiled](decompiled/00413eac.c) | [assembly](decompiled/00413eac.asm) |
| `0x00413ec8` | `root_00413ec8` | Controls.TControl.DblClick | [decompiled](decompiled/00413ec8.c) | [assembly](decompiled/00413ec8.asm) |
| `0x00413ee4` | `FUN_00413ee4` | Controls.TControl.MouseDown | [decompiled](decompiled/00413ee4.c) | [assembly](decompiled/00413ee4.asm) |
| `0x00413f14` | `FUN_00413f14` |  | [decompiled](decompiled/00413f14.c) | [assembly](decompiled/00413f14.asm) |
| `0x00413f58` | `FUN_00413f58` | Controls.TControl.WMLButtonDown | [decompiled](decompiled/00413f58.c) | [assembly](decompiled/00413f58.asm) |
| `0x00413fa4` | `root_00413fa4` | Controls.TControl.WMNCLButtonDown | [decompiled](decompiled/00413fa4.c) | [assembly](decompiled/00413fa4.asm) |
| `0x00413fc0` | `FUN_00413fc0` | Controls.TControl.WMLButtonDblClk | [decompiled](decompiled/00413fc0.c) | [assembly](decompiled/00413fc0.asm) |
| `0x00414014` | `root_00414014` |  | [decompiled](decompiled/00414014.c) | [assembly](decompiled/00414014.asm) |
| `0x00414018` | `FUN_00414018` | Controls.TControl.CheckMenuPopup | [decompiled](decompiled/00414018.c) | [assembly](decompiled/00414018.asm) |
| `0x0041408c` | `root_0041408c` | Controls.TControl.WMRButtonDown | [decompiled](decompiled/0041408c.c) | [assembly](decompiled/0041408c.asm) |
| `0x004140b4` | `root_004140b4` | Controls.TControl.WMRButtonDblClk | [decompiled](decompiled/004140b4.c) | [assembly](decompiled/004140b4.asm) |
| `0x004140dc` | `root_004140dc` | Controls.TControl.WMMButtonDown | [decompiled](decompiled/004140dc.c) | [assembly](decompiled/004140dc.asm) |
| `0x00414104` | `root_00414104` | Controls.TControl.WMMButtonDblClk | [decompiled](decompiled/00414104.c) | [assembly](decompiled/00414104.asm) |
| `0x0041412c` | `root_0041412c` | Controls.TControl.MouseMove | [decompiled](decompiled/0041412c.c) | [assembly](decompiled/0041412c.asm) |
| `0x00414154` | `FUN_00414154` |  | [decompiled](decompiled/00414154.c) | [assembly](decompiled/00414154.asm) |
| `0x00414190` | `root_00414190` | Controls.TControl.MouseUp | [decompiled](decompiled/00414190.c) | [assembly](decompiled/00414190.asm) |
| `0x004141c0` | `FUN_004141c0` |  | [decompiled](decompiled/004141c0.c) | [assembly](decompiled/004141c0.asm) |
| `0x004141fc` | `root_004141fc` | Controls.TControl.WMLButtonUp | [decompiled](decompiled/004141fc.c) | [assembly](decompiled/004141fc.asm) |
| `0x00414270` | `root_00414270` | Controls.TControl.WMRButtonUp | [decompiled](decompiled/00414270.c) | [assembly](decompiled/00414270.asm) |
| `0x00414298` | `root_00414298` | Controls.TControl.WMMButtonUp | [decompiled](decompiled/00414298.c) | [assembly](decompiled/00414298.asm) |
| `0x004142b8` | `root_004142b8` |  | [decompiled](decompiled/004142b8.c) | [assembly](decompiled/004142b8.asm) |
| `0x004142f0` | `root_004142f0` | Controls.TControl.CMVisibleChanged | [decompiled](decompiled/004142f0.c) | [assembly](decompiled/004142f0.asm) |
| `0x00414318` | `root_00414318` |  | [decompiled](decompiled/00414318.c) | [assembly](decompiled/00414318.asm) |
| `0x00414320` | `FUN_00414320` |  | [decompiled](decompiled/00414320.c) | [assembly](decompiled/00414320.asm) |
| `0x00414328` | `root_00414328` |  | [decompiled](decompiled/00414328.c) | [assembly](decompiled/00414328.asm) |
| `0x00414330` | `FUN_00414330` | Controls.TControl.CMParentColorChanged | [decompiled](decompiled/00414330.c) | [assembly](decompiled/00414330.asm) |
| `0x0041434c` | `FUN_0041434c` | Controls.TControl.CMParentShowHintChanged | [decompiled](decompiled/0041434c.c) | [assembly](decompiled/0041434c.asm) |
| `0x00414368` | `FUN_00414368` | Controls.TControl.CMParentFontChanged | [decompiled](decompiled/00414368.c) | [assembly](decompiled/00414368.asm) |
| `0x00414384` | `root_00414384` |  | [decompiled](decompiled/00414384.c) | [assembly](decompiled/00414384.asm) |
| `0x0041438c` | `root_0041438c` | Controls.TControl.CMMouseEnter | [decompiled](decompiled/0041438c.c) | [assembly](decompiled/0041438c.asm) |
| `0x004143a4` | `root_004143a4` | Controls.TControl.CMMouseLeave | [decompiled](decompiled/004143a4.c) | [assembly](decompiled/004143a4.asm) |
| `0x004143bc` | `root_004143bc` |  | [decompiled](decompiled/004143bc.c) | [assembly](decompiled/004143bc.asm) |
| `0x004143c4` | `FUN_004143c4` |  | [decompiled](decompiled/004143c4.c) | [assembly](decompiled/004143c4.asm) |
| `0x00414444` | `FUN_00414444` |  | [decompiled](decompiled/00414444.c) | [assembly](decompiled/00414444.asm) |
| `0x004144dc` | `FUN_004144dc` | Controls.TWinControl.FixupTabList | [decompiled](decompiled/004144dc.c) | [assembly](decompiled/004144dc.asm) |
| `0x004145a0` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004145a0.c) | [assembly](decompiled/004145a0.asm) |
| `0x004145a5` | `root_004145a5` |  | [decompiled](decompiled/004145a5.c) | [assembly](decompiled/004145a5.asm) |
| `0x004145b0` | `FUN_004145b0` | Controls.TWinControl.ReadState | [decompiled](decompiled/004145b0.c) | [assembly](decompiled/004145b0.asm) |
| `0x004145f0` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004145f0.c) | [assembly](decompiled/004145f0.asm) |
| `0x004145f5` | `root_004145f5` |  | [decompiled](decompiled/004145f5.c) | [assembly](decompiled/004145f5.asm) |
| `0x00414628` | `FUN_00414628` | Controls.InsertBefore | [decompiled](decompiled/00414628.c) | [assembly](decompiled/00414628.asm) |
| `0x00414688` | `FUN_00414688` |  | [decompiled](decompiled/00414688.c) | [assembly](decompiled/00414688.asm) |
| `0x00414690` | `FUN_00414690` |  | [decompiled](decompiled/00414690.c) | [assembly](decompiled/00414690.asm) |
| `0x00414824` | `FUN_00414824` | Controls.DoAlign | [decompiled](decompiled/00414824.c) | [assembly](decompiled/00414824.asm) |
| `0x00414954` | `FUN_00414954` | Controls.AlignWork | [decompiled](decompiled/00414954.c) | [assembly](decompiled/00414954.asm) |
| `0x00414990` | `FUN_00414990` | Controls.TWinControl.AlignControls | [decompiled](decompiled/00414990.c) | [assembly](decompiled/00414990.asm) |
| `0x00414a0a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00414a0a.c) | [assembly](decompiled/00414a0a.asm) |
| `0x00414a0f` | `root_00414a0f` |  | [decompiled](decompiled/00414a0f.c) | [assembly](decompiled/00414a0f.asm) |
| `0x00414a18` | `FUN_00414a18` | Controls.TWinControl.AlignControl | [decompiled](decompiled/00414a18.c) | [assembly](decompiled/00414a18.asm) |
| `0x00414a91` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00414a91.c) | [assembly](decompiled/00414a91.asm) |
| `0x00414a96` | `root_00414a96` |  | [decompiled](decompiled/00414a96.c) | [assembly](decompiled/00414a96.asm) |
| `0x00414aa0` | `FUN_00414aa0` |  | [decompiled](decompiled/00414aa0.c) | [assembly](decompiled/00414aa0.asm) |
| `0x00414aa8` | `FUN_00414aa8` | Controls.TWinControl.EnableAlign | [decompiled](decompiled/00414aa8.c) | [assembly](decompiled/00414aa8.asm) |
| `0x00414ac8` | `FUN_00414ac8` |  | [decompiled](decompiled/00414ac8.c) | [assembly](decompiled/00414ac8.asm) |
| `0x00414ad0` | `thunk_FUN_00414ad5` | Controls.TWinControl.ContainsControl | [decompiled](decompiled/00414ad0.c) | [assembly](decompiled/00414ad0.asm) |
| `0x00414ad5` | `FUN_00414ad5` |  | [decompiled](decompiled/00414ad5.c) | [assembly](decompiled/00414ad5.asm) |
| `0x00414ae4` | `FUN_00414ae4` | Controls.TWinControl.RemoveFocus | [decompiled](decompiled/00414ae4.c) | [assembly](decompiled/00414ae4.asm) |
| `0x00414b04` | `FUN_00414b04` | Controls.TWinControl.Insert | [decompiled](decompiled/00414b04.c) | [assembly](decompiled/00414b04.asm) |
| `0x00414b50` | `FUN_00414b50` | Controls.TWinControl.Remove | [decompiled](decompiled/00414b50.c) | [assembly](decompiled/00414b50.asm) |
| `0x00414b98` | `FUN_00414b98` | Controls.TWinControl.InsertControl | [decompiled](decompiled/00414b98.c) | [assembly](decompiled/00414b98.asm) |
| `0x00414c34` | `FUN_00414c34` | Controls.TWinControl.RemoveControl | [decompiled](decompiled/00414c34.c) | [assembly](decompiled/00414c34.asm) |
| `0x00414c9c` | `FUN_00414c9c` | Controls.TWinControl.GetControl | [decompiled](decompiled/00414c9c.c) | [assembly](decompiled/00414c9c.asm) |
| `0x00414ccc` | `FUN_00414ccc` | Controls.TWinControl.GetControlCount | [decompiled](decompiled/00414ccc.c) | [assembly](decompiled/00414ccc.asm) |
| `0x00414cec` | `FUN_00414cec` | Controls.TWinControl.Broadcast | [decompiled](decompiled/00414cec.c) | [assembly](decompiled/00414cec.asm) |
| `0x00414d24` | `FUN_00414d24` | Controls.TWinControl.NotifyControls | [decompiled](decompiled/00414d24.c) | [assembly](decompiled/00414d24.asm) |
| `0x00414d4c` | `FUN_00414d4c` | Controls.TWinControl.CreateSubClass | [decompiled](decompiled/00414d4c.c) | [assembly](decompiled/00414d4c.asm) |
| `0x00414d88` | `FUN_00414d88` | Controls.TWinControl.CreateParams | [decompiled](decompiled/00414d88.c) | [assembly](decompiled/00414d88.asm) |
| `0x00414e81` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00414e81.c) | [assembly](decompiled/00414e81.asm) |
| `0x00414e86` | `root_00414e86` |  | [decompiled](decompiled/00414e86.c) | [assembly](decompiled/00414e86.asm) |
| `0x00414e90` | `FUN_00414e90` | Controls.TWinControl.CreateWnd | [decompiled](decompiled/00414e90.c) | [assembly](decompiled/00414e90.asm) |
| `0x00414fd0` | `FUN_00414fd0` | Controls.TWinControl.CreateWindowHandle | [decompiled](decompiled/00414fd0.c) | [assembly](decompiled/00414fd0.asm) |
| `0x00415014` | `FUN_00415014` | Controls.TWinControl.DestroyWnd | [decompiled](decompiled/00415014.c) | [assembly](decompiled/00415014.asm) |
| `0x0041506c` | `FUN_0041506c` |  | [decompiled](decompiled/0041506c.c) | [assembly](decompiled/0041506c.asm) |
| `0x0041507c` | `FUN_0041507c` | Controls.TWinControl.PrecedingWindow | [decompiled](decompiled/0041507c.c) | [assembly](decompiled/0041507c.asm) |
| `0x004150c4` | `FUN_004150c4` | Controls.TWinControl.CreateHandle | [decompiled](decompiled/004150c4.c) | [assembly](decompiled/004150c4.asm) |
| `0x00415130` | `FUN_00415130` | Controls.TWinControl.DestroyHandle | [decompiled](decompiled/00415130.c) | [assembly](decompiled/00415130.asm) |
| `0x00415174` | `FUN_00415174` | Controls.TWinControl.RecreateWnd | [decompiled](decompiled/00415174.c) | [assembly](decompiled/00415174.asm) |
| `0x004151b4` | `FUN_004151b4` | Controls.TWinControl.UpdateShowing | [decompiled](decompiled/004151b4.c) | [assembly](decompiled/004151b4.asm) |
| `0x00415287` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00415287.c) | [assembly](decompiled/00415287.asm) |
| `0x0041528c` | `root_0041528c` |  | [decompiled](decompiled/0041528c.c) | [assembly](decompiled/0041528c.asm) |
| `0x004152ac` | `FUN_004152ac` | Controls.TWinControl.UpdateControlState | [decompiled](decompiled/004152ac.c) | [assembly](decompiled/004152ac.asm) |
| `0x004152dc` | `FUN_004152dc` | Controls.TWinControl.MainWndProc | [decompiled](decompiled/004152dc.c) | [assembly](decompiled/004152dc.asm) |
| `0x00415322` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00415322.c) | [assembly](decompiled/00415322.asm) |
| `0x00415327` | `root_00415327` |  | [decompiled](decompiled/00415327.c) | [assembly](decompiled/00415327.asm) |
| `0x00415333` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00415333.c) | [assembly](decompiled/00415333.asm) |
| `0x00415338` | `root_00415338` |  | [decompiled](decompiled/00415338.c) | [assembly](decompiled/00415338.asm) |
| `0x00415350` | `FUN_00415350` | Controls.TWinControl.ControlAtPos | [decompiled](decompiled/00415350.c) | [assembly](decompiled/00415350.asm) |
| `0x00415410` | `FUN_00415410` | Controls.TWinControl.IsControlMouseMsg | [decompiled](decompiled/00415410.c) | [assembly](decompiled/00415410.asm) |
| `0x0041549c` | `FUN_0041549c` | Controls.TWinControl.WndProc | [decompiled](decompiled/0041549c.c) | [assembly](decompiled/0041549c.asm) |
| `0x004155c4` | `FUN_004155c4` | Controls.TWinControl.DefaultHandler | [decompiled](decompiled/004155c4.c) | [assembly](decompiled/004155c4.asm) |
| `0x00415678` | `FUN_00415678` | Controls.DoControlMsg | [decompiled](decompiled/00415678.c) | [assembly](decompiled/00415678.asm) |
| `0x004156ac` | `FUN_004156ac` | Controls.TWinControl.PaintHandler | [decompiled](decompiled/004156ac.c) | [assembly](decompiled/004156ac.asm) |
| `0x004157c5` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004157c5.c) | [assembly](decompiled/004157c5.asm) |
| `0x004157ca` | `root_004157ca` |  | [decompiled](decompiled/004157ca.c) | [assembly](decompiled/004157ca.asm) |
| `0x004157d4` | `root_004157d4` |  | [decompiled](decompiled/004157d4.c) | [assembly](decompiled/004157d4.asm) |
| `0x00415800` | `FUN_00415800` | Controls.TWinControl.PaintControls | [decompiled](decompiled/00415800.c) | [assembly](decompiled/00415800.asm) |
| `0x00415a08` | `root_00415a08` | Controls.TWinControl.WMPaint | [decompiled](decompiled/00415a08.c) | [assembly](decompiled/00415a08.asm) |
| `0x00415a34` | `root_00415a34` | Controls.TWinControl.WMCharToItem, Controls.TWinControl.WMCommand, Controls.TWinControl.WMHScroll, Controls.TWinControl.WMVKeyToItem, Controls.TWinControl.WMVScroll | [decompiled](decompiled/00415a34.c) | [assembly](decompiled/00415a34.asm) |
| `0x00415a54` | `root_00415a54` | Controls.TWinControl.WMNotify | [decompiled](decompiled/00415a54.c) | [assembly](decompiled/00415a54.asm) |
| `0x00415a78` | `root_00415a78` | Controls.TWinControl.WMSysColorChange | [decompiled](decompiled/00415a78.c) | [assembly](decompiled/00415a78.asm) |
| `0x00415a94` | `root_00415a94` |  | [decompiled](decompiled/00415a94.c) | [assembly](decompiled/00415a94.asm) |
| `0x00415aa8` | `root_00415aa8` |  | [decompiled](decompiled/00415aa8.c) | [assembly](decompiled/00415aa8.asm) |
| `0x00415ab8` | `root_00415ab8` |  | [decompiled](decompiled/00415ab8.c) | [assembly](decompiled/00415ab8.asm) |
| `0x00415ac8` | `root_00415ac8` | Controls.TWinControl.WMCharToItem, Controls.TWinControl.WMCommand, Controls.TWinControl.WMHScroll, Controls.TWinControl.WMVKeyToItem, Controls.TWinControl.WMVScroll | [decompiled](decompiled/00415ac8.c) | [assembly](decompiled/00415ac8.asm) |
| `0x00415ae8` | `root_00415ae8` | Controls.TWinControl.WMCharToItem, Controls.TWinControl.WMCommand, Controls.TWinControl.WMHScroll, Controls.TWinControl.WMVKeyToItem, Controls.TWinControl.WMVScroll | [decompiled](decompiled/00415ae8.c) | [assembly](decompiled/00415ae8.asm) |
| `0x00415b08` | `root_00415b08` | Controls.TWinControl.WMCompareItem, Controls.TWinControl.WMDeleteItem, Controls.TWinControl.WMDrawItem, Controls.TWinControl.WMMeasureItem | [decompiled](decompiled/00415b08.c) | [assembly](decompiled/00415b08.asm) |
| `0x00415b2c` | `root_00415b2c` | Controls.TWinControl.WMCompareItem, Controls.TWinControl.WMDeleteItem, Controls.TWinControl.WMDrawItem, Controls.TWinControl.WMMeasureItem | [decompiled](decompiled/00415b2c.c) | [assembly](decompiled/00415b2c.asm) |
| `0x00415b50` | `root_00415b50` | Controls.TWinControl.WMCompareItem, Controls.TWinControl.WMDeleteItem, Controls.TWinControl.WMDrawItem, Controls.TWinControl.WMMeasureItem | [decompiled](decompiled/00415b50.c) | [assembly](decompiled/00415b50.asm) |
| `0x00415b74` | `root_00415b74` | Controls.TWinControl.WMCompareItem, Controls.TWinControl.WMDeleteItem, Controls.TWinControl.WMDrawItem, Controls.TWinControl.WMMeasureItem | [decompiled](decompiled/00415b74.c) | [assembly](decompiled/00415b74.asm) |
| `0x00415b98` | `root_00415b98` | Controls.TWinControl.WMEraseBkgnd | [decompiled](decompiled/00415b98.c) | [assembly](decompiled/00415b98.asm) |
| `0x00415bd4` | `FUN_00415bd4` | Controls.TWinControl.WMWindowPosChanged | [decompiled](decompiled/00415bd4.c) | [assembly](decompiled/00415bd4.asm) |
| `0x00415c64` | `FUN_00415c64` | Controls.TWinControl.WMSize | [decompiled](decompiled/00415c64.c) | [assembly](decompiled/00415c64.asm) |
| `0x00415c84` | `root_00415c84` |  | [decompiled](decompiled/00415c84.c) | [assembly](decompiled/00415c84.asm) |
| `0x00415c98` | `FUN_00415c98` | Controls.TWinControl.WMSetCursor | [decompiled](decompiled/00415c98.c) | [assembly](decompiled/00415c98.asm) |
| `0x00415d7c` | `root_00415d7c` |  | [decompiled](decompiled/00415d7c.c) | [assembly](decompiled/00415d7c.asm) |
| `0x00415d90` | `root_00415d90` |  | [decompiled](decompiled/00415d90.c) | [assembly](decompiled/00415d90.asm) |
| `0x00415da4` | `FUN_00415da4` |  | [decompiled](decompiled/00415da4.c) | [assembly](decompiled/00415da4.asm) |
| `0x00415dbc` | `FUN_00415dbc` |  | [decompiled](decompiled/00415dbc.c) | [assembly](decompiled/00415dbc.asm) |
| `0x00415dd8` | `root_00415dd8` |  | [decompiled](decompiled/00415dd8.c) | [assembly](decompiled/00415dd8.asm) |
| `0x00415df4` | `root_00415df4` |  | [decompiled](decompiled/00415df4.c) | [assembly](decompiled/00415df4.asm) |
| `0x00415e10` | `root_00415e10` |  | [decompiled](decompiled/00415e10.c) | [assembly](decompiled/00415e10.asm) |
| `0x00415e38` | `FUN_00415e38` |  | [decompiled](decompiled/00415e38.c) | [assembly](decompiled/00415e38.asm) |
| `0x00415ecc` | `root_00415ecc` | Controls.TWinControl.WMChar, Controls.TWinControl.WMKeyDown, Controls.TWinControl.WMKeyUp, Controls.TWinControl.WMSysKeyDown, Controls.TWinControl.WMSysKeyUp | [decompiled](decompiled/00415ecc.c) | [assembly](decompiled/00415ecc.asm) |
| `0x00415eec` | `root_00415eec` | Controls.TWinControl.WMChar, Controls.TWinControl.WMKeyDown, Controls.TWinControl.WMKeyUp, Controls.TWinControl.WMSysKeyDown, Controls.TWinControl.WMSysKeyUp | [decompiled](decompiled/00415eec.c) | [assembly](decompiled/00415eec.asm) |
| `0x00415f0c` | `root_00415f0c` |  | [decompiled](decompiled/00415f0c.c) | [assembly](decompiled/00415f0c.asm) |
| `0x00415f34` | `FUN_00415f34` |  | [decompiled](decompiled/00415f34.c) | [assembly](decompiled/00415f34.asm) |
| `0x00415f98` | `root_00415f98` | Controls.TWinControl.WMChar, Controls.TWinControl.WMKeyDown, Controls.TWinControl.WMKeyUp, Controls.TWinControl.WMSysKeyDown, Controls.TWinControl.WMSysKeyUp | [decompiled](decompiled/00415f98.c) | [assembly](decompiled/00415f98.asm) |
| `0x00415fb8` | `root_00415fb8` | Controls.TWinControl.WMChar, Controls.TWinControl.WMKeyDown, Controls.TWinControl.WMKeyUp, Controls.TWinControl.WMSysKeyDown, Controls.TWinControl.WMSysKeyUp | [decompiled](decompiled/00415fb8.c) | [assembly](decompiled/00415fb8.asm) |
| `0x00415fd8` | `FUN_00415fd8` |  | [decompiled](decompiled/00415fd8.c) | [assembly](decompiled/00415fd8.asm) |
| `0x00415ff8` | `FUN_00415ff8` |  | [decompiled](decompiled/00415ff8.c) | [assembly](decompiled/00415ff8.asm) |
| `0x00416054` | `root_00416054` | Controls.TWinControl.WMChar, Controls.TWinControl.WMKeyDown, Controls.TWinControl.WMKeyUp, Controls.TWinControl.WMSysKeyDown, Controls.TWinControl.WMSysKeyUp | [decompiled](decompiled/00416054.c) | [assembly](decompiled/00416054.asm) |
| `0x00416074` | `FUN_00416074` | Controls.TWinControl.WMSysCommand | [decompiled](decompiled/00416074.c) | [assembly](decompiled/00416074.asm) |
| `0x004160e8` | `root_004160e8` | Controls.TWinControl.WMCharToItem, Controls.TWinControl.WMCommand, Controls.TWinControl.WMHScroll, Controls.TWinControl.WMVKeyToItem, Controls.TWinControl.WMVScroll | [decompiled](decompiled/004160e8.c) | [assembly](decompiled/004160e8.asm) |
| `0x00416108` | `FUN_00416108` | Controls.TWinControl.WMParentNotify | [decompiled](decompiled/00416108.c) | [assembly](decompiled/00416108.asm) |
| `0x0041613c` | `root_0041613c` | Controls.TWinControl.WMCharToItem, Controls.TWinControl.WMCommand, Controls.TWinControl.WMHScroll, Controls.TWinControl.WMVKeyToItem, Controls.TWinControl.WMVScroll | [decompiled](decompiled/0041613c.c) | [assembly](decompiled/0041613c.asm) |
| `0x0041615c` | `root_0041615c` |  | [decompiled](decompiled/0041615c.c) | [assembly](decompiled/0041615c.asm) |
| `0x00416190` | `FUN_00416190` |  | [decompiled](decompiled/00416190.c) | [assembly](decompiled/00416190.asm) |
| `0x004161ac` | `root_004161ac` |  | [decompiled](decompiled/004161ac.c) | [assembly](decompiled/004161ac.asm) |
| `0x004161d0` | `root_004161d0` | Controls.TWinControl.PaletteChanged | [decompiled](decompiled/004161d0.c) | [assembly](decompiled/004161d0.asm) |
| `0x0041622c` | `FUN_0041622c` | Controls.TWinControl.WMQueryNewPalette | [decompiled](decompiled/0041622c.c) | [assembly](decompiled/0041622c.asm) |
| `0x00416250` | `root_00416250` | Controls.TWinControl.WMPaletteChanged | [decompiled](decompiled/00416250.c) | [assembly](decompiled/00416250.asm) |
| `0x00416270` | `root_00416270` |  | [decompiled](decompiled/00416270.c) | [assembly](decompiled/00416270.asm) |
| `0x00416288` | `FUN_00416288` |  | [decompiled](decompiled/00416288.c) | [assembly](decompiled/00416288.asm) |
| `0x00416294` | `root_00416294` |  | [decompiled](decompiled/00416294.c) | [assembly](decompiled/00416294.asm) |
| `0x004162a0` | `root_004162a0` | Controls.TWinControl.CMDesignHitTest | [decompiled](decompiled/004162a0.c) | [assembly](decompiled/004162a0.asm) |
| `0x004162c0` | `root_004162c0` |  | [decompiled](decompiled/004162c0.c) | [assembly](decompiled/004162c0.asm) |
| `0x004162d4` | `FUN_004162d4` |  | [decompiled](decompiled/004162d4.c) | [assembly](decompiled/004162d4.asm) |
| `0x004162dc` | `FUN_004162dc` |  | [decompiled](decompiled/004162dc.c) | [assembly](decompiled/004162dc.asm) |
| `0x004162e4` | `FUN_004162e4` |  | [decompiled](decompiled/004162e4.c) | [assembly](decompiled/004162e4.asm) |
| `0x004162ec` | `root_004162ec` | Controls.TWinControl.CMVisibleChanged | [decompiled](decompiled/004162ec.c) | [assembly](decompiled/004162ec.asm) |
| `0x0041631c` | `root_0041631c` | Controls.TWinControl.CMShowingChanged | [decompiled](decompiled/0041631c.c) | [assembly](decompiled/0041631c.asm) |
| `0x00416344` | `FUN_00416344` | Controls.TWinControl.CMEnabledChanged | [decompiled](decompiled/00416344.c) | [assembly](decompiled/00416344.asm) |
| `0x00416384` | `root_00416384` | Controls.TWinControl.CMColorChanged | [decompiled](decompiled/00416384.c) | [assembly](decompiled/00416384.asm) |
| `0x004163ac` | `FUN_004163ac` | Controls.TWinControl.CMFontChanged | [decompiled](decompiled/004163ac.c) | [assembly](decompiled/004163ac.asm) |
| `0x004163e8` | `root_004163e8` | Controls.TWinControl.CMCursorChanged | [decompiled](decompiled/004163e8.c) | [assembly](decompiled/004163e8.asm) |
| `0x00416428` | `FUN_00416428` | Controls.TWinControl.CMCtl3DChanged | [decompiled](decompiled/00416428.c) | [assembly](decompiled/00416428.asm) |
| `0x00416468` | `root_00416468` | Controls.TWinControl.CMParentCtl3DChanged | [decompiled](decompiled/00416468.c) | [assembly](decompiled/00416468.asm) |
| `0x00416490` | `root_00416490` |  | [decompiled](decompiled/00416490.c) | [assembly](decompiled/00416490.asm) |
| `0x00416498` | `root_00416498` |  | [decompiled](decompiled/00416498.c) | [assembly](decompiled/00416498.asm) |
| `0x004164a0` | `root_004164a0` |  | [decompiled](decompiled/004164a0.c) | [assembly](decompiled/004164a0.asm) |
| `0x004164a8` | `root_004164a8` |  | [decompiled](decompiled/004164a8.c) | [assembly](decompiled/004164a8.asm) |
| `0x004164b0` | `root_004164b0` | Controls.TWinControl.CMDrag | [decompiled](decompiled/004164b0.c) | [assembly](decompiled/004164b0.asm) |
| `0x00416508` | `root_00416508` |  | [decompiled](decompiled/00416508.c) | [assembly](decompiled/00416508.asm) |
| `0x0041651c` | `FUN_0041651c` |  | [decompiled](decompiled/0041651c.c) | [assembly](decompiled/0041651c.asm) |
| `0x004165a4` | `FUN_004165a4` | Controls.TWinControl.CNKeyDown | [decompiled](decompiled/004165a4.c) | [assembly](decompiled/004165a4.asm) |
| `0x0041667c` | `root_0041667c` | Controls.TWinControl.CNKeyUp | [decompiled](decompiled/0041667c.c) | [assembly](decompiled/0041667c.asm) |
| `0x004166d0` | `root_004166d0` | Controls.TWinControl.CNChar | [decompiled](decompiled/004166d0.c) | [assembly](decompiled/004166d0.asm) |
| `0x0041671c` | `root_0041671c` | Controls.TWinControl.CNSysKeyDown | [decompiled](decompiled/0041671c.c) | [assembly](decompiled/0041671c.asm) |
| `0x00416778` | `root_00416778` | Controls.TWinControl.CNSysChar | [decompiled](decompiled/00416778.c) | [assembly](decompiled/00416778.asm) |
| `0x004167ac` | `root_004167ac` | Controls.TWinControl.SetBounds | [decompiled](decompiled/004167ac.c) | [assembly](decompiled/004167ac.asm) |
| `0x0041687c` | `FUN_0041687c` | Controls.TWinControl.ScaleControls | [decompiled](decompiled/0041687c.c) | [assembly](decompiled/0041687c.asm) |
| `0x004168c4` | `FUN_004168c4` | Controls.TWinControl.ChangeScale | [decompiled](decompiled/004168c4.c) | [assembly](decompiled/004168c4.asm) |
| `0x00416915` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00416915.c) | [assembly](decompiled/00416915.asm) |
| `0x0041691a` | `root_0041691a` |  | [decompiled](decompiled/0041691a.c) | [assembly](decompiled/0041691a.asm) |
| `0x00416924` | `FUN_00416924` | Controls.TWinControl.ScrollBy | [decompiled](decompiled/00416924.c) | [assembly](decompiled/00416924.asm) |
| `0x004169fc` | `root_004169fc` |  | [decompiled](decompiled/004169fc.c) | [assembly](decompiled/004169fc.asm) |
| `0x00416a0c` | `FUN_00416a0c` | Controls.TWinControl.SetZOrderPosition | [decompiled](decompiled/00416a0c.c) | [assembly](decompiled/00416a0c.asm) |
| `0x00416ae4` | `root_00416ae4` | Controls.TWinControl.SetZOrder | [decompiled](decompiled/00416ae4.c) | [assembly](decompiled/00416ae4.asm) |
| `0x00416b44` | `root_00416b44` | Controls.TWinControl.GetDeviceContext | [decompiled](decompiled/00416b44.c) | [assembly](decompiled/00416b44.asm) |
| `0x00416b98` | `root_00416b98` | Controls.TWinControl.Invalidate | [decompiled](decompiled/00416b98.c) | [assembly](decompiled/00416b98.asm) |
| `0x00416bc4` | `FUN_00416bc4` | Controls.TWinControl.Update | [decompiled](decompiled/00416bc4.c) | [assembly](decompiled/00416bc4.asm) |
| `0x00416be0` | `FUN_00416be0` | Controls.TWinControl.Repaint | [decompiled](decompiled/00416be0.c) | [assembly](decompiled/00416be0.asm) |
| `0x00416bf4` | `FUN_00416bf4` | Controls.TWinControl.InvalidateFrame | [decompiled](decompiled/00416bf4.c) | [assembly](decompiled/00416bf4.asm) |
| `0x00416c2c` | `FUN_00416c2c` | Controls.TWinControl.CanFocus | [decompiled](decompiled/00416c2c.c) | [assembly](decompiled/00416c2c.asm) |
| `0x00416c60` | `FUN_00416c60` |  | [decompiled](decompiled/00416c60.c) | [assembly](decompiled/00416c60.asm) |
| `0x00416c74` | `FUN_00416c74` | Controls.TWinControl.Focused | [decompiled](decompiled/00416c74.c) | [assembly](decompiled/00416c74.asm) |
| `0x00416c98` | `FUN_00416c98` | Controls.TWinControl.HandleNeeded | [decompiled](decompiled/00416c98.c) | [assembly](decompiled/00416c98.asm) |
| `0x00416cbc` | `FUN_00416cbc` |  | [decompiled](decompiled/00416cbc.c) | [assembly](decompiled/00416cbc.asm) |
| `0x00416cd0` | `root_00416cd0` | Controls.TWinControl.GetClientOrigin | [decompiled](decompiled/00416cd0.c) | [assembly](decompiled/00416cd0.asm) |
| `0x00416cf0` | `FUN_00416cf0` |  | [decompiled](decompiled/00416cf0.c) | [assembly](decompiled/00416cf0.asm) |
| `0x00416d08` | `FUN_00416d08` | Controls.TWinControl.SetCtl3D | [decompiled](decompiled/00416d08.c) | [assembly](decompiled/00416d08.asm) |
| `0x00416d2c` | `root_00416d2c` |  | [decompiled](decompiled/00416d2c.c) | [assembly](decompiled/00416d2c.asm) |
| `0x00416d38` | `root_00416d38` | Controls.TWinControl.SetParentCtl3D | [decompiled](decompiled/00416d38.c) | [assembly](decompiled/00416d38.asm) |
| `0x00416d5c` | `FUN_00416d5c` | Controls.TWinControl.GetTabOrder | [decompiled](decompiled/00416d5c.c) | [assembly](decompiled/00416d5c.asm) |
| `0x00416d80` | `FUN_00416d80` | Controls.TWinControl.UpdateTabOrder | [decompiled](decompiled/00416d80.c) | [assembly](decompiled/00416d80.asm) |
| `0x00416ddc` | `root_00416ddc` | Controls.TWinControl.SetTabOrder | [decompiled](decompiled/00416ddc.c) | [assembly](decompiled/00416ddc.asm) |
| `0x00416df4` | `FUN_00416df4` | Controls.TWinControl.SetTabStop | [decompiled](decompiled/00416df4.c) | [assembly](decompiled/00416df4.asm) |
| `0x00416e54` | `FUN_00416e54` |  | [decompiled](decompiled/00416e54.c) | [assembly](decompiled/00416e54.asm) |
| `0x00416e60` | `FUN_00416e60` | Controls.TWinControl.UpdateBounds | [decompiled](decompiled/00416e60.c) | [assembly](decompiled/00416e60.asm) |
| `0x00416f10` | `root_00416f10` | Controls.TWinControl.GetTabOrderList | [decompiled](decompiled/00416f10.c) | [assembly](decompiled/00416f10.asm) |
| `0x00416f68` | `root_00416f68` | Controls.TWinControl.FindNextControl | [decompiled](decompiled/00416f68.c) | [assembly](decompiled/00416f68.asm) |
| `0x00417057` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00417057.c) | [assembly](decompiled/00417057.asm) |
| `0x0041705c` | `root_0041705c` |  | [decompiled](decompiled/0041705c.c) | [assembly](decompiled/0041705c.asm) |
| `0x0041706c` | `root_0041706c` |  | [decompiled](decompiled/0041706c.c) | [assembly](decompiled/0041706c.asm) |
| `0x00417098` | `root_00417098` | Controls.TWinControl.GetChildren | [decompiled](decompiled/00417098.c) | [assembly](decompiled/00417098.asm) |
| `0x004170e8` | `FUN_004170e8` | Controls.TWinControl.SetChildOrder | [decompiled](decompiled/004170e8.c) | [assembly](decompiled/004170e8.asm) |
| `0x00417128` | `FUN_00417128` | Controls.TGraphicControl.Create | [decompiled](decompiled/00417128.c) | [assembly](decompiled/00417128.asm) |
| `0x0041717c` | `FUN_0041717c` | Controls.TGraphicControl.Destroy | [decompiled](decompiled/0041717c.c) | [assembly](decompiled/0041717c.asm) |
| `0x004171a8` | `root_004171a8` | Controls.TGraphicControl.WMPaint | [decompiled](decompiled/004171a8.c) | [assembly](decompiled/004171a8.asm) |
| `0x004171fa` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004171fa.c) | [assembly](decompiled/004171fa.asm) |
| `0x004171ff` | `root_004171ff` |  | [decompiled](decompiled/004171ff.c) | [assembly](decompiled/004171ff.asm) |
| `0x00417204` | `root_00417204` |  | [decompiled](decompiled/00417204.c) | [assembly](decompiled/00417204.asm) |
| `0x00417208` | `FUN_00417208` |  | [decompiled](decompiled/00417208.c) | [assembly](decompiled/00417208.asm) |
| `0x004172d0` | `root_004172d0` | Controls.THintWindow.CreateParams | [decompiled](decompiled/004172d0.c) | [assembly](decompiled/004172d0.asm) |
| `0x004172fc` | `root_004172fc` |  | [decompiled](decompiled/004172fc.c) | [assembly](decompiled/004172fc.asm) |
| `0x0041737f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041737f.c) | [assembly](decompiled/0041737f.asm) |
| `0x00417384` | `root_00417384` |  | [decompiled](decompiled/00417384.c) | [assembly](decompiled/00417384.asm) |
| `0x00417390` | `root_00417390` | Controls.THintWindow.IsHintMsg | [decompiled](decompiled/00417390.c) | [assembly](decompiled/00417390.asm) |
| `0x004173f4` | `FUN_004173f4` |  | [decompiled](decompiled/004173f4.c) | [assembly](decompiled/004173f4.asm) |
| `0x004173fc` | `root_004173fc` |  | [decompiled](decompiled/004173fc.c) | [assembly](decompiled/004173fc.asm) |
| `0x00417479` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00417479.c) | [assembly](decompiled/00417479.asm) |
| `0x0041747e` | `root_0041747e` |  | [decompiled](decompiled/0041747e.c) | [assembly](decompiled/0041747e.asm) |
| `0x00417488` | `root_00417488` | Controls.THintWindow.ActivateHint | [decompiled](decompiled/00417488.c) | [assembly](decompiled/00417488.asm) |
| `0x00417538` | `FUN_00417538` |  | [decompiled](decompiled/00417538.c) | [assembly](decompiled/00417538.asm) |
| `0x0041758c` | `FUN_0041758c` |  | [decompiled](decompiled/0041758c.c) | [assembly](decompiled/0041758c.asm) |
| `0x004175b8` | `root_004175b8` |  | [decompiled](decompiled/004175b8.c) | [assembly](decompiled/004175b8.asm) |
| `0x004175c0` | `root_004175c0` |  | [decompiled](decompiled/004175c0.c) | [assembly](decompiled/004175c0.asm) |
| `0x0041760c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041760c.c) | [assembly](decompiled/0041760c.asm) |
| `0x00417611` | `root_00417611` |  | [decompiled](decompiled/00417611.c) | [assembly](decompiled/00417611.asm) |
| `0x00417618` | `root_00417618` |  | [decompiled](decompiled/00417618.c) | [assembly](decompiled/00417618.asm) |
| `0x0041761c` | `FUN_0041761c` | Controls.GetRGBColor | [decompiled](decompiled/0041761c.c) | [assembly](decompiled/0041761c.asm) |
| `0x0041763c` | `FUN_0041763c` | Controls.GetColor | [decompiled](decompiled/0041763c.c) | [assembly](decompiled/0041763c.asm) |
| `0x0041765c` | `FUN_0041765c` | Controls.ClientToWindow | [decompiled](decompiled/0041765c.c) | [assembly](decompiled/0041765c.asm) |
| `0x0041769c` | `FUN_0041769c` | Controls.TCustomImageList.Create | [decompiled](decompiled/0041769c.c) | [assembly](decompiled/0041769c.asm) |
| `0x004176e0` | `FUN_004176e0` | Controls.TCustomImageList.CreateSize | [decompiled](decompiled/004176e0.c) | [assembly](decompiled/004176e0.asm) |
| `0x0041772c` | `FUN_0041772c` | Controls.TCustomImageList.Destroy | [decompiled](decompiled/0041772c.c) | [assembly](decompiled/0041772c.asm) |
| `0x00417780` | `FUN_00417780` | Controls.TCustomImageList.Initialize | [decompiled](decompiled/00417780.c) | [assembly](decompiled/00417780.asm) |
| `0x00417800` | `FUN_00417800` |  | [decompiled](decompiled/00417800.c) | [assembly](decompiled/00417800.asm) |
| `0x00417808` | `FUN_00417808` |  | [decompiled](decompiled/00417808.c) | [assembly](decompiled/00417808.asm) |
| `0x00417814` | `FUN_00417814` | Controls.TCustomImageList.InitBitmap | [decompiled](decompiled/00417814.c) | [assembly](decompiled/00417814.asm) |
| `0x004178ac` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004178ac.c) | [assembly](decompiled/004178ac.asm) |
| `0x004178b1` | `root_004178b1` |  | [decompiled](decompiled/004178b1.c) | [assembly](decompiled/004178b1.asm) |
| `0x004178bc` | `FUN_004178bc` | Controls.TCustomImageList.SetNewDimensions | [decompiled](decompiled/004178bc.c) | [assembly](decompiled/004178bc.asm) |
| `0x004178f4` | `FUN_004178f4` | Controls.TCustomImageList.SetWidth | [decompiled](decompiled/004178f4.c) | [assembly](decompiled/004178f4.asm) |
| `0x0041793c` | `FUN_0041793c` | Controls.TCustomImageList.SetHeight | [decompiled](decompiled/0041793c.c) | [assembly](decompiled/0041793c.asm) |
| `0x00417984` | `FUN_00417984` |  | [decompiled](decompiled/00417984.c) | [assembly](decompiled/00417984.asm) |
| `0x00417994` | `FUN_00417994` | Controls.TCustomImageList.GetImageHandle | [decompiled](decompiled/00417994.c) | [assembly](decompiled/00417994.asm) |
| `0x004179bc` | `FUN_004179bc` | Controls.TCustomImageList.FreeHandle | [decompiled](decompiled/004179bc.c) | [assembly](decompiled/004179bc.asm) |
| `0x004179f0` | `FUN_004179f0` | Controls.TCustomImageList.CreateImageList | [decompiled](decompiled/004179f0.c) | [assembly](decompiled/004179f0.asm) |
| `0x00417a50` | `FUN_00417a50` | Controls.TCustomImageList.GetImageBitmap | [decompiled](decompiled/00417a50.c) | [assembly](decompiled/00417a50.asm) |
| `0x00417a90` | `FUN_00417a90` | Controls.TCustomImageList.GetMaskBitmap | [decompiled](decompiled/00417a90.c) | [assembly](decompiled/00417a90.asm) |
| `0x00417ad0` | `FUN_00417ad0` | Controls.TCustomImageList.Add | [decompiled](decompiled/00417ad0.c) | [assembly](decompiled/00417ad0.asm) |
| `0x00417b00` | `FUN_00417b00` | Controls.TCustomImageList.AddMasked | [decompiled](decompiled/00417b00.c) | [assembly](decompiled/00417b00.asm) |
| `0x00417b3c` | `FUN_00417b3c` | Controls.TCustomImageList.GetCount | [decompiled](decompiled/00417b3c.c) | [assembly](decompiled/00417b3c.asm) |
| `0x00417b60` | `FUN_00417b60` | Controls.TCustomImageList.Replace | [decompiled](decompiled/00417b60.c) | [assembly](decompiled/00417b60.asm) |
| `0x00417bc8` | `FUN_00417bc8` |  | [decompiled](decompiled/00417bc8.c) | [assembly](decompiled/00417bc8.asm) |
| `0x00417d22` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00417d22.c) | [assembly](decompiled/00417d22.asm) |
| `0x00417d27` | `root_00417d27` |  | [decompiled](decompiled/00417d27.c) | [assembly](decompiled/00417d27.asm) |
| `0x00417d36` | `FUN_00417d36` |  | [decompiled](decompiled/00417d36.c) | [assembly](decompiled/00417d36.asm) |
| `0x00417d42` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00417d42.c) | [assembly](decompiled/00417d42.asm) |
| `0x00417d47` | `thunk_FUN_00417d36` |  | [decompiled](decompiled/00417d47.c) | [assembly](decompiled/00417d47.asm) |
| `0x00417d74` | `FUN_00417d74` | Controls.TCustomImageList.Delete | [decompiled](decompiled/00417d74.c) | [assembly](decompiled/00417d74.asm) |
| `0x00417dc4` | `FUN_00417dc4` | Controls.TCustomImageList.Clear | [decompiled](decompiled/00417dc4.c) | [assembly](decompiled/00417dc4.asm) |
| `0x00417de0` | `FUN_00417de0` | Controls.TCustomImageList.SetBkColor | [decompiled](decompiled/00417de0.c) | [assembly](decompiled/00417de0.asm) |
| `0x00417e1c` | `FUN_00417e1c` | Controls.TCustomImageList.GetBkColor | [decompiled](decompiled/00417e1c.c) | [assembly](decompiled/00417e1c.asm) |
| `0x00417e44` | `FUN_00417e44` | Controls.TCustomImageList.Draw | [decompiled](decompiled/00417e44.c) | [assembly](decompiled/00417e44.asm) |
| `0x00417eb4` | `FUN_00417eb4` | Controls.TCustomImageList.CopyImages | [decompiled](decompiled/00417eb4.c) | [assembly](decompiled/00417eb4.asm) |
| `0x00417fcb` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00417fcb.c) | [assembly](decompiled/00417fcb.asm) |
| `0x00417fd0` | `root_00417fd0` |  | [decompiled](decompiled/00417fd0.c) | [assembly](decompiled/00417fd0.asm) |
| `0x00417fdc` | `FUN_00417fdc` | Controls.TCustomImageList.AddImages | [decompiled](decompiled/00417fdc.c) | [assembly](decompiled/00417fdc.asm) |
| `0x00417ffc` | `root_00417ffc` | Controls.TCustomImageList.Assign | [decompiled](decompiled/00417ffc.c) | [assembly](decompiled/00417ffc.asm) |
| `0x004180b4` | `root_004180b4` | Controls.TCustomImageList.AssignTo | [decompiled](decompiled/004180b4.c) | [assembly](decompiled/004180b4.asm) |
| `0x00418160` | `FUN_00418160` | Controls.TCustomImageList.CheckImage | [decompiled](decompiled/00418160.c) | [assembly](decompiled/00418160.asm) |
| `0x0041819c` | `FUN_0041819c` | Controls.TCustomImageList.CombineDragCursor | [decompiled](decompiled/0041819c.c) | [assembly](decompiled/0041819c.asm) |
| `0x00418250` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00418250.c) | [assembly](decompiled/00418250.asm) |
| `0x00418255` | `root_00418255` |  | [decompiled](decompiled/00418255.c) | [assembly](decompiled/00418255.asm) |
| `0x0041825c` | `FUN_0041825c` | Controls.TCustomImageList.SetDragCursor | [decompiled](decompiled/0041825c.c) | [assembly](decompiled/0041825c.asm) |
| `0x00418274` | `FUN_00418274` | Controls.TCustomImageList.SetDragImage | [decompiled](decompiled/00418274.c) | [assembly](decompiled/00418274.asm) |
| `0x004182b0` | `FUN_004182b0` | Controls.TCustomImageList.BeginDrag | [decompiled](decompiled/004182b0.c) | [assembly](decompiled/004182b0.asm) |
| `0x0041830c` | `FUN_0041830c` | Controls.TCustomImageList.DragLock | [decompiled](decompiled/0041830c.c) | [assembly](decompiled/0041830c.asm) |
| `0x00418370` | `FUN_00418370` | Controls.TCustomImageList.DragUnlock | [decompiled](decompiled/00418370.c) | [assembly](decompiled/00418370.asm) |
| `0x00418394` | `FUN_00418394` | Controls.TCustomImageList.DragMove | [decompiled](decompiled/00418394.c) | [assembly](decompiled/00418394.asm) |
| `0x004183d8` | `FUN_004183d8` |  | [decompiled](decompiled/004183d8.c) | [assembly](decompiled/004183d8.asm) |
| `0x004183f0` | `FUN_004183f0` |  | [decompiled](decompiled/004183f0.c) | [assembly](decompiled/004183f0.asm) |
| `0x00418408` | `FUN_00418408` | Controls.TCustomImageList.EndDrag | [decompiled](decompiled/00418408.c) | [assembly](decompiled/00418408.asm) |
| `0x00418450` | `FUN_00418450` | Controls.TCustomImageList.Change | [decompiled](decompiled/00418450.c) | [assembly](decompiled/00418450.asm) |
| `0x00418490` | `FUN_00418490` | Controls.TCustomImageList.UnRegisterChanges | [decompiled](decompiled/00418490.c) | [assembly](decompiled/00418490.asm) |
| `0x004184d0` | `root_004184d0` | Controls.TCustomImageList.DefineProperties | [decompiled](decompiled/004184d0.c) | [assembly](decompiled/004184d0.asm) |
| `0x00418518` | `root_00418518` | Controls.TCustomImageList.ReadData | [decompiled](decompiled/00418518.c) | [assembly](decompiled/00418518.asm) |
| `0x00418718` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00418718.c) | [assembly](decompiled/00418718.asm) |
| `0x0041871d` | `root_0041871d` |  | [decompiled](decompiled/0041871d.c) | [assembly](decompiled/0041871d.asm) |
| `0x0041872c` | `FUN_0041872c` |  | [decompiled](decompiled/0041872c.c) | [assembly](decompiled/0041872c.asm) |
| `0x00418735` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00418735.c) | [assembly](decompiled/00418735.asm) |
| `0x0041873a` | `thunk_FUN_0041872c` |  | [decompiled](decompiled/0041873a.c) | [assembly](decompiled/0041873a.asm) |
| `0x00418749` | `FUN_00418749` |  | [decompiled](decompiled/00418749.c) | [assembly](decompiled/00418749.asm) |
| `0x00418752` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00418752.c) | [assembly](decompiled/00418752.asm) |
| `0x00418757` | `thunk_FUN_00418749` |  | [decompiled](decompiled/00418757.c) | [assembly](decompiled/00418757.asm) |
| `0x00418760` | `root_00418760` | Controls.TCustomImageList.WriteData | [decompiled](decompiled/00418760.c) | [assembly](decompiled/00418760.asm) |
| `0x00418845` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00418845.c) | [assembly](decompiled/00418845.asm) |
| `0x0041884a` | `root_0041884a` |  | [decompiled](decompiled/0041884a.c) | [assembly](decompiled/0041884a.asm) |
| `0x00418884` | `FUN_00418884` | Controls.InitControls | [decompiled](decompiled/00418884.c) | [assembly](decompiled/00418884.asm) |
| `0x0041898c` | `FUN_0041898c` |  | [decompiled](decompiled/0041898c.c) | [assembly](decompiled/0041898c.asm) |
| `0x0041913c` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/0041913c.c) | [assembly](decompiled/0041913c.asm) |
| `0x00419144` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00419144.c) | [assembly](decompiled/00419144.asm) |
| `0x0041914c` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/0041914c.c) | [assembly](decompiled/0041914c.asm) |
| `0x00419154` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00419154.c) | [assembly](decompiled/00419154.asm) |
| `0x0041915c` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/0041915c.c) | [assembly](decompiled/0041915c.asm) |
| `0x00419164` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00419164.c) | [assembly](decompiled/00419164.asm) |
| `0x0041916c` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/0041916c.c) | [assembly](decompiled/0041916c.asm) |
| `0x00419174` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00419174.c) | [assembly](decompiled/00419174.asm) |
| `0x0041917c` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/0041917c.c) | [assembly](decompiled/0041917c.asm) |
| `0x00419184` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00419184.c) | [assembly](decompiled/00419184.asm) |
| `0x00419330` | `thunk_FUN_004028c0` |  | [decompiled](decompiled/00419330.c) | [assembly](decompiled/00419330.asm) |
| `0x004195ac` | `FUN_004195ac` | Graphics.GetHashCode | [decompiled](decompiled/004195ac.c) | [assembly](decompiled/004195ac.asm) |
| `0x004195c0` | `FUN_004195c0` | Graphics.BlockCompare | [decompiled](decompiled/004195c0.c) | [assembly](decompiled/004195c0.asm) |
| `0x004195e4` | `FUN_004195e4` | Graphics.TResourceManager.Create | [decompiled](decompiled/004195e4.c) | [assembly](decompiled/004195e4.asm) |
| `0x00419604` | `FUN_00419604` | Graphics.TResourceManager.AllocResource | [decompiled](decompiled/00419604.c) | [assembly](decompiled/00419604.asm) |
| `0x00419680` | `FUN_00419680` | Graphics.TResourceManager.FreeResource | [decompiled](decompiled/00419680.c) | [assembly](decompiled/00419680.asm) |
| `0x004196d0` | `FUN_004196d0` | Graphics.TResourceManager.ChangeResource | [decompiled](decompiled/004196d0.c) | [assembly](decompiled/004196d0.asm) |
| `0x0041970c` | `FUN_0041970c` | Graphics.TResourceManager.AssignResource | [decompiled](decompiled/0041970c.c) | [assembly](decompiled/0041970c.asm) |
| `0x00419738` | `root_00419738` | Graphics.ClearColor | [decompiled](decompiled/00419738.c) | [assembly](decompiled/00419738.asm) |
| `0x00419764` | `root_00419764` | Graphics.PaletteChanged | [decompiled](decompiled/00419764.c) | [assembly](decompiled/00419764.asm) |
| `0x00419b00` | `FUN_00419b00` |  | [decompiled](decompiled/00419b00.c) | [assembly](decompiled/00419b00.asm) |
| `0x00419b10` | `FUN_00419b10` |  | [decompiled](decompiled/00419b10.c) | [assembly](decompiled/00419b10.asm) |
| `0x00419b40` | `FUN_00419b40` | Graphics.IdentToColor | [decompiled](decompiled/00419b40.c) | [assembly](decompiled/00419b40.asm) |
| `0x00419b78` | `root_00419b78` | Graphics.TGraphicsObject.Changed | [decompiled](decompiled/00419b78.c) | [assembly](decompiled/00419b78.asm) |
| `0x00419b8c` | `FUN_00419b8c` | Graphics.TFont.Create | [decompiled](decompiled/00419b8c.c) | [assembly](decompiled/00419b8c.asm) |
| `0x00419bd4` | `root_00419bd4` | Graphics.TBrush.Destroy, Graphics.TFont.Destroy, Graphics.TPen.Destroy | [decompiled](decompiled/00419bd4.c) | [assembly](decompiled/00419bd4.asm) |
| `0x00419bf8` | `FUN_00419bf8` | Graphics.TFont.Assign | [decompiled](decompiled/00419bf8.c) | [assembly](decompiled/00419bf8.asm) |
| `0x00419c54` | `FUN_00419c54` | Graphics.TFont.GetData | [decompiled](decompiled/00419c54.c) | [assembly](decompiled/00419c54.asm) |
| `0x00419c6c` | `FUN_00419c6c` |  | [decompiled](decompiled/00419c6c.c) | [assembly](decompiled/00419c6c.asm) |
| `0x00419c7c` | `FUN_00419c7c` | Graphics.TFont.SetColor | [decompiled](decompiled/00419c7c.c) | [assembly](decompiled/00419c7c.asm) |
| `0x00419c90` | `FUN_00419c90` | Graphics.TFont.GetHandle | [decompiled](decompiled/00419c90.c) | [assembly](decompiled/00419c90.asm) |
| `0x00419d70` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00419d70.c) | [assembly](decompiled/00419d70.asm) |
| `0x00419d75` | `root_00419d75` |  | [decompiled](decompiled/00419d75.c) | [assembly](decompiled/00419d75.asm) |
| `0x00419d80` | `FUN_00419d80` | Graphics.TFont.SetHandle | [decompiled](decompiled/00419d80.c) | [assembly](decompiled/00419d80.asm) |
| `0x00419da4` | `FUN_00419da4` |  | [decompiled](decompiled/00419da4.c) | [assembly](decompiled/00419da4.asm) |
| `0x00419dac` | `FUN_00419dac` | Graphics.TFont.SetHeight | [decompiled](decompiled/00419dac.c) | [assembly](decompiled/00419dac.asm) |
| `0x00419dd4` | `FUN_00419dd4` | Graphics.TFont.GetName | [decompiled](decompiled/00419dd4.c) | [assembly](decompiled/00419dd4.asm) |
| `0x00419dec` | `FUN_00419dec` | Graphics.TFont.SetName | [decompiled](decompiled/00419dec.c) | [assembly](decompiled/00419dec.asm) |
| `0x00419e30` | `FUN_00419e30` | Graphics.TFont.GetSize | [decompiled](decompiled/00419e30.c) | [assembly](decompiled/00419e30.asm) |
| `0x00419e4c` | `FUN_00419e4c` | Graphics.TFont.SetSize | [decompiled](decompiled/00419e4c.c) | [assembly](decompiled/00419e4c.asm) |
| `0x00419e6c` | `FUN_00419e6c` |  | [decompiled](decompiled/00419e6c.c) | [assembly](decompiled/00419e6c.asm) |
| `0x00419e78` | `FUN_00419e78` | Graphics.TFont.SetStyle | [decompiled](decompiled/00419e78.c) | [assembly](decompiled/00419e78.asm) |
| `0x00419ea4` | `FUN_00419ea4` |  | [decompiled](decompiled/00419ea4.c) | [assembly](decompiled/00419ea4.asm) |
| `0x00419eac` | `FUN_00419eac` | Graphics.TFont.SetPitch | [decompiled](decompiled/00419eac.c) | [assembly](decompiled/00419eac.asm) |
| `0x00419ed4` | `FUN_00419ed4` | Graphics.TPen.Create | [decompiled](decompiled/00419ed4.c) | [assembly](decompiled/00419ed4.asm) |
| `0x00419f10` | `root_00419f10` | Graphics.TBrush.Destroy, Graphics.TFont.Destroy, Graphics.TPen.Destroy | [decompiled](decompiled/00419f10.c) | [assembly](decompiled/00419f10.asm) |
| `0x00419f34` | `FUN_00419f34` | Graphics.TPen.Assign | [decompiled](decompiled/00419f34.c) | [assembly](decompiled/00419f34.asm) |
| `0x00419f78` | `FUN_00419f78` | Graphics.TPen.GetData | [decompiled](decompiled/00419f78.c) | [assembly](decompiled/00419f78.asm) |
| `0x00419f90` | `FUN_00419f90` |  | [decompiled](decompiled/00419f90.c) | [assembly](decompiled/00419f90.asm) |
| `0x00419fa0` | `root_00419fa0` |  | [decompiled](decompiled/00419fa0.c) | [assembly](decompiled/00419fa0.asm) |
| `0x00419fa8` | `FUN_00419fa8` | Graphics.TPen.SetColor, LibMain.TContainer.SetTop | [decompiled](decompiled/00419fa8.c) | [assembly](decompiled/00419fa8.asm) |
| `0x00419fd0` | `FUN_00419fd0` | Graphics.TPen.GetHandle | [decompiled](decompiled/00419fd0.c) | [assembly](decompiled/00419fd0.asm) |
| `0x0041a014` | `FUN_0041a014` | Graphics.TPen.SetMode | [decompiled](decompiled/0041a014.c) | [assembly](decompiled/0041a014.asm) |
| `0x0041a028` | `FUN_0041a028` |  | [decompiled](decompiled/0041a028.c) | [assembly](decompiled/0041a028.asm) |
| `0x0041a030` | `FUN_0041a030` | Graphics.TPen.SetStyle | [decompiled](decompiled/0041a030.c) | [assembly](decompiled/0041a030.asm) |
| `0x0041a058` | `root_0041a058` |  | [decompiled](decompiled/0041a058.c) | [assembly](decompiled/0041a058.asm) |
| `0x0041a060` | `FUN_0041a060` | Graphics.TPen.SetWidth | [decompiled](decompiled/0041a060.c) | [assembly](decompiled/0041a060.asm) |
| `0x0041a08c` | `FUN_0041a08c` | Graphics.TBrush.Create | [decompiled](decompiled/0041a08c.c) | [assembly](decompiled/0041a08c.asm) |
| `0x0041a0c4` | `root_0041a0c4` | Graphics.TBrush.Destroy, Graphics.TFont.Destroy, Graphics.TPen.Destroy | [decompiled](decompiled/0041a0c4.c) | [assembly](decompiled/0041a0c4.asm) |
| `0x0041a0e8` | `root_0041a0e8` | Graphics.TBrush.Assign | [decompiled](decompiled/0041a0e8.c) | [assembly](decompiled/0041a0e8.asm) |
| `0x0041a11c` | `FUN_0041a11c` | Graphics.TBrush.GetData | [decompiled](decompiled/0041a11c.c) | [assembly](decompiled/0041a11c.asm) |
| `0x0041a13c` | `FUN_0041a13c` |  | [decompiled](decompiled/0041a13c.c) | [assembly](decompiled/0041a13c.asm) |
| `0x0041a14c` | `FUN_0041a14c` |  | [decompiled](decompiled/0041a14c.c) | [assembly](decompiled/0041a14c.asm) |
| `0x0041a154` | `FUN_0041a154` | Graphics.TBrush.SetColor | [decompiled](decompiled/0041a154.c) | [assembly](decompiled/0041a154.asm) |
| `0x0041a188` | `FUN_0041a188` | Graphics.TBrush.GetHandle | [decompiled](decompiled/0041a188.c) | [assembly](decompiled/0041a188.asm) |
| `0x0041a204` | `FUN_0041a204` |  | [decompiled](decompiled/0041a204.c) | [assembly](decompiled/0041a204.asm) |
| `0x0041a20c` | `FUN_0041a20c` | Graphics.TBrush.SetStyle | [decompiled](decompiled/0041a20c.c) | [assembly](decompiled/0041a20c.asm) |
| `0x0041a240` | `FUN_0041a240` | Graphics.TCanvas.Create | [decompiled](decompiled/0041a240.c) | [assembly](decompiled/0041a240.asm) |
| `0x0041a2e0` | `FUN_0041a2e0` | Graphics.TCanvas.Destroy | [decompiled](decompiled/0041a2e0.c) | [assembly](decompiled/0041a2e0.asm) |
| `0x0041a32c` | `FUN_0041a32c` | Graphics.TCanvas.BrushCopy | [decompiled](decompiled/0041a32c.c) | [assembly](decompiled/0041a32c.asm) |
| `0x0041a530` | `FUN_0041a530` | Graphics.TCanvas.CopyRect | [decompiled](decompiled/0041a530.c) | [assembly](decompiled/0041a530.asm) |
| `0x0041a5b8` | `FUN_0041a5b8` | Graphics.TCanvas.Draw | [decompiled](decompiled/0041a5b8.c) | [assembly](decompiled/0041a5b8.asm) |
| `0x0041a664` | `FUN_0041a664` | Graphics.TCanvas.FillRect, Graphics.TCanvas.FrameRect | [decompiled](decompiled/0041a664.c) | [assembly](decompiled/0041a664.asm) |
| `0x0041a6a0` | `FUN_0041a6a0` | Graphics.TCanvas.LineTo | [decompiled](decompiled/0041a6a0.c) | [assembly](decompiled/0041a6a0.asm) |
| `0x0041a6d8` | `FUN_0041a6d8` | Graphics.TCanvas.MoveTo | [decompiled](decompiled/0041a6d8.c) | [assembly](decompiled/0041a6d8.asm) |
| `0x0041a704` | `FUN_0041a704` | Graphics.TCanvas.Polygon, Graphics.TCanvas.Polyline | [decompiled](decompiled/0041a704.c) | [assembly](decompiled/0041a704.asm) |
| `0x0041a73c` | `FUN_0041a73c` | Graphics.TCanvas.Ellipse, Graphics.TCanvas.Rectangle | [decompiled](decompiled/0041a73c.c) | [assembly](decompiled/0041a73c.asm) |
| `0x0041a784` | `FUN_0041a784` | Graphics.TCanvas.StretchDraw | [decompiled](decompiled/0041a784.c) | [assembly](decompiled/0041a784.asm) |
| `0x0041a7c0` | `FUN_0041a7c0` | Graphics.TCanvas.TextOut | [decompiled](decompiled/0041a7c0.c) | [assembly](decompiled/0041a7c0.asm) |
| `0x0041a830` | `FUN_0041a830` | Graphics.TCanvas.TextWidth | [decompiled](decompiled/0041a830.c) | [assembly](decompiled/0041a830.asm) |
| `0x0041a874` | `FUN_0041a874` | Graphics.TCanvas.TextHeight | [decompiled](decompiled/0041a874.c) | [assembly](decompiled/0041a874.asm) |
| `0x0041a8bc` | `FUN_0041a8bc` |  | [decompiled](decompiled/0041a8bc.c) | [assembly](decompiled/0041a8bc.asm) |
| `0x0041a8c8` | `root_0041a8c8` |  | [decompiled](decompiled/0041a8c8.c) | [assembly](decompiled/0041a8c8.asm) |
| `0x0041a8d4` | `FUN_0041a8d4` |  | [decompiled](decompiled/0041a8d4.c) | [assembly](decompiled/0041a8d4.asm) |
| `0x0041a8e0` | `FUN_0041a8e0` | Graphics.TCanvas.GetClipRect, Graphics.TCanvas.GetPenPos | [decompiled](decompiled/0041a8e0.c) | [assembly](decompiled/0041a8e0.asm) |
| `0x0041a904` | `FUN_0041a904` | Graphics.TCanvas.SetPenPos | [decompiled](decompiled/0041a904.c) | [assembly](decompiled/0041a904.asm) |
| `0x0041a924` | `FUN_0041a924` | Graphics.TCanvas.GetPixel | [decompiled](decompiled/0041a924.c) | [assembly](decompiled/0041a924.asm) |
| `0x0041a950` | `FUN_0041a950` | Graphics.TCanvas.GetHandle | [decompiled](decompiled/0041a950.c) | [assembly](decompiled/0041a950.asm) |
| `0x0041a970` | `FUN_0041a970` | Graphics.TCanvas.DeselectHandles | [decompiled](decompiled/0041a970.c) | [assembly](decompiled/0041a970.asm) |
| `0x0041a9cc` | `FUN_0041a9cc` |  | [decompiled](decompiled/0041a9cc.c) | [assembly](decompiled/0041a9cc.asm) |
| `0x0041a9d0` | `FUN_0041a9d0` | Graphics.TCanvas.SetHandle | [decompiled](decompiled/0041a9d0.c) | [assembly](decompiled/0041a9d0.asm) |
| `0x0041aa24` | `FUN_0041aa24` |  | [decompiled](decompiled/0041aa24.c) | [assembly](decompiled/0041aa24.asm) |
| `0x0041aaa8` | `root_0041aaa8` | ExtCtrls.TTimer.Timer, Graphics.TCanvas.Changing | [decompiled](decompiled/0041aaa8.c) | [assembly](decompiled/0041aaa8.asm) |
| `0x0041aabc` | `root_0041aabc` | Graphics.TCanvas.Changed | [decompiled](decompiled/0041aabc.c) | [assembly](decompiled/0041aabc.asm) |
| `0x0041aad0` | `FUN_0041aad0` | Graphics.TCanvas.CreateFont | [decompiled](decompiled/0041aad0.c) | [assembly](decompiled/0041aad0.asm) |
| `0x0041aafc` | `FUN_0041aafc` | Graphics.TCanvas.CreatePen | [decompiled](decompiled/0041aafc.c) | [assembly](decompiled/0041aafc.asm) |
| `0x0041ab2c` | `FUN_0041ab2c` | Graphics.TCanvas.CreateBrush | [decompiled](decompiled/0041ab2c.c) | [assembly](decompiled/0041ab2c.asm) |
| `0x0041aba8` | `root_0041aba8` | Graphics.TCanvas.FontChanged | [decompiled](decompiled/0041aba8.c) | [assembly](decompiled/0041aba8.asm) |
| `0x0041abc8` | `root_0041abc8` | Graphics.TCanvas.PenChanged | [decompiled](decompiled/0041abc8.c) | [assembly](decompiled/0041abc8.asm) |
| `0x0041abe8` | `root_0041abe8` | Graphics.TCanvas.BrushChanged | [decompiled](decompiled/0041abe8.c) | [assembly](decompiled/0041abe8.asm) |
| `0x0041ac08` | `FUN_0041ac08` |  | [decompiled](decompiled/0041ac08.c) | [assembly](decompiled/0041ac08.asm) |
| `0x0041ac20` | `FUN_0041ac20` |  | [decompiled](decompiled/0041ac20.c) | [assembly](decompiled/0041ac20.asm) |
| `0x0041ac38` | `FUN_0041ac38` |  | [decompiled](decompiled/0041ac38.c) | [assembly](decompiled/0041ac38.asm) |
| `0x0041ac44` | `FUN_0041ac44` |  | [decompiled](decompiled/0041ac44.c) | [assembly](decompiled/0041ac44.asm) |
| `0x0041ac50` | `FUN_0041ac50` |  | [decompiled](decompiled/0041ac50.c) | [assembly](decompiled/0041ac50.asm) |
| `0x0041ac5c` | `FUN_0041ac5c` |  | [decompiled](decompiled/0041ac5c.c) | [assembly](decompiled/0041ac5c.asm) |
| `0x0041ac74` | `FUN_0041ac74` | Graphics.DupBits | [decompiled](decompiled/0041ac74.c) | [assembly](decompiled/0041ac74.asm) |
| `0x0041ad23` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041ad23.c) | [assembly](decompiled/0041ad23.asm) |
| `0x0041ad28` | `root_0041ad28` |  | [decompiled](decompiled/0041ad28.c) | [assembly](decompiled/0041ad28.asm) |
| `0x0041adb0` | `FUN_0041adb0` | Graphics.GetDInColors | [decompiled](decompiled/0041adb0.c) | [assembly](decompiled/0041adb0.asm) |
| `0x0041add0` | `FUN_0041add0` | Graphics.PaletteFromW3DIB | [decompiled](decompiled/0041add0.c) | [assembly](decompiled/0041add0.asm) |
| `0x0041aef4` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041aef4.c) | [assembly](decompiled/0041aef4.asm) |
| `0x0041aef9` | `root_0041aef9` |  | [decompiled](decompiled/0041aef9.c) | [assembly](decompiled/0041aef9.asm) |
| `0x0041af14` | `FUN_0041af14` |  | [decompiled](decompiled/0041af14.c) | [assembly](decompiled/0041af14.asm) |
| `0x0041af20` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041af20.c) | [assembly](decompiled/0041af20.asm) |
| `0x0041af25` | `thunk_FUN_0041af14` |  | [decompiled](decompiled/0041af25.c) | [assembly](decompiled/0041af25.asm) |
| `0x0041af34` | `FUN_0041af34` | Graphics.ReadWin3DIB | [decompiled](decompiled/0041af34.c) | [assembly](decompiled/0041af34.asm) |
| `0x0041b0c2` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b0c2.c) | [assembly](decompiled/0041b0c2.asm) |
| `0x0041b0c7` | `root_0041b0c7` |  | [decompiled](decompiled/0041b0c7.c) | [assembly](decompiled/0041b0c7.asm) |
| `0x0041b0d6` | `FUN_0041b0d6` |  | [decompiled](decompiled/0041b0d6.c) | [assembly](decompiled/0041b0d6.asm) |
| `0x0041b0e4` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b0e4.c) | [assembly](decompiled/0041b0e4.asm) |
| `0x0041b0e9` | `thunk_FUN_0041b0d6` |  | [decompiled](decompiled/0041b0e9.c) | [assembly](decompiled/0041b0e9.asm) |
| `0x0041b0f8` | `FUN_0041b0f8` |  | [decompiled](decompiled/0041b0f8.c) | [assembly](decompiled/0041b0f8.asm) |
| `0x0041b104` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b104.c) | [assembly](decompiled/0041b104.asm) |
| `0x0041b109` | `thunk_FUN_0041b0f8` |  | [decompiled](decompiled/0041b109.c) | [assembly](decompiled/0041b109.asm) |
| `0x0041b118` | `FUN_0041b118` |  | [decompiled](decompiled/0041b118.c) | [assembly](decompiled/0041b118.asm) |
| `0x0041b128` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b128.c) | [assembly](decompiled/0041b128.asm) |
| `0x0041b12d` | `thunk_FUN_0041b118` |  | [decompiled](decompiled/0041b12d.c) | [assembly](decompiled/0041b12d.asm) |
| `0x0041b138` | `FUN_0041b138` | Graphics.PaletteFromPM1DIB | [decompiled](decompiled/0041b138.c) | [assembly](decompiled/0041b138.asm) |
| `0x0041b1f3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b1f3.c) | [assembly](decompiled/0041b1f3.asm) |
| `0x0041b1f8` | `root_0041b1f8` |  | [decompiled](decompiled/0041b1f8.c) | [assembly](decompiled/0041b1f8.asm) |
| `0x0041b204` | `FUN_0041b204` | Graphics.ReadPM1DIB | [decompiled](decompiled/0041b204.c) | [assembly](decompiled/0041b204.asm) |
| `0x0041b38f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b38f.c) | [assembly](decompiled/0041b38f.asm) |
| `0x0041b394` | `root_0041b394` |  | [decompiled](decompiled/0041b394.c) | [assembly](decompiled/0041b394.asm) |
| `0x0041b3a3` | `FUN_0041b3a3` |  | [decompiled](decompiled/0041b3a3.c) | [assembly](decompiled/0041b3a3.asm) |
| `0x0041b3b1` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b3b1.c) | [assembly](decompiled/0041b3b1.asm) |
| `0x0041b3b6` | `thunk_FUN_0041b3a3` |  | [decompiled](decompiled/0041b3b6.c) | [assembly](decompiled/0041b3b6.asm) |
| `0x0041b3c5` | `FUN_0041b3c5` |  | [decompiled](decompiled/0041b3c5.c) | [assembly](decompiled/0041b3c5.asm) |
| `0x0041b3d1` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b3d1.c) | [assembly](decompiled/0041b3d1.asm) |
| `0x0041b3d6` | `thunk_FUN_0041b3c5` |  | [decompiled](decompiled/0041b3d6.c) | [assembly](decompiled/0041b3d6.asm) |
| `0x0041b3e5` | `FUN_0041b3e5` |  | [decompiled](decompiled/0041b3e5.c) | [assembly](decompiled/0041b3e5.asm) |
| `0x0041b3f5` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b3f5.c) | [assembly](decompiled/0041b3f5.asm) |
| `0x0041b3fa` | `thunk_FUN_0041b3e5` |  | [decompiled](decompiled/0041b3fa.c) | [assembly](decompiled/0041b3fa.asm) |
| `0x0041b408` | `FUN_0041b408` | Graphics.ReadDIB | [decompiled](decompiled/0041b408.c) | [assembly](decompiled/0041b408.asm) |
| `0x0041b46c` | `FUN_0041b46c` | Graphics.WidthBytes | [decompiled](decompiled/0041b46c.c) | [assembly](decompiled/0041b46c.asm) |
| `0x0041b480` | `FUN_0041b480` | Graphics.TwoBitsFromDIB | [decompiled](decompiled/0041b480.c) | [assembly](decompiled/0041b480.asm) |
| `0x0041b568` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b568.c) | [assembly](decompiled/0041b568.asm) |
| `0x0041b56d` | `root_0041b56d` |  | [decompiled](decompiled/0041b56d.c) | [assembly](decompiled/0041b56d.asm) |
| `0x0041b61b` | `FUN_0041b61b` |  | [decompiled](decompiled/0041b61b.c) | [assembly](decompiled/0041b61b.asm) |
| `0x0041b625` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b625.c) | [assembly](decompiled/0041b625.asm) |
| `0x0041b62a` | `thunk_FUN_0041b61b` |  | [decompiled](decompiled/0041b62a.c) | [assembly](decompiled/0041b62a.asm) |
| `0x0041b639` | `FUN_0041b639` |  | [decompiled](decompiled/0041b639.c) | [assembly](decompiled/0041b639.asm) |
| `0x0041b645` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b645.c) | [assembly](decompiled/0041b645.asm) |
| `0x0041b64a` | `thunk_FUN_0041b639` |  | [decompiled](decompiled/0041b64a.c) | [assembly](decompiled/0041b64a.asm) |
| `0x0041b654` | `FUN_0041b654` | Graphics.ReadIcon | [decompiled](decompiled/0041b654.c) | [assembly](decompiled/0041b654.asm) |
| `0x0041b724` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b724.c) | [assembly](decompiled/0041b724.asm) |
| `0x0041b729` | `root_0041b729` |  | [decompiled](decompiled/0041b729.c) | [assembly](decompiled/0041b729.asm) |
| `0x0041b8b1` | `FUN_0041b8b1` |  | [decompiled](decompiled/0041b8b1.c) | [assembly](decompiled/0041b8b1.asm) |
| `0x0041b8bd` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b8bd.c) | [assembly](decompiled/0041b8bd.asm) |
| `0x0041b8c2` | `thunk_FUN_0041b8b1` |  | [decompiled](decompiled/0041b8c2.c) | [assembly](decompiled/0041b8c2.asm) |
| `0x0041b8d1` | `FUN_0041b8d1` |  | [decompiled](decompiled/0041b8d1.c) | [assembly](decompiled/0041b8d1.asm) |
| `0x0041b8e0` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b8e0.c) | [assembly](decompiled/0041b8e0.asm) |
| `0x0041b8e5` | `thunk_FUN_0041b8d1` |  | [decompiled](decompiled/0041b8e5.c) | [assembly](decompiled/0041b8e5.asm) |
| `0x0041b8f4` | `FUN_0041b8f4` |  | [decompiled](decompiled/0041b8f4.c) | [assembly](decompiled/0041b8f4.asm) |
| `0x0041b900` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041b900.c) | [assembly](decompiled/0041b900.asm) |
| `0x0041b905` | `thunk_FUN_0041b8f4` |  | [decompiled](decompiled/0041b905.c) | [assembly](decompiled/0041b905.asm) |
| `0x0041b910` | `FUN_0041b910` | Graphics.ComputeAldusChecksum | [decompiled](decompiled/0041b910.c) | [assembly](decompiled/0041b910.asm) |
| `0x0041b928` | `FUN_0041b928` | Graphics.InitializeBitmapInfoHeader | [decompiled](decompiled/0041b928.c) | [assembly](decompiled/0041b928.asm) |
| `0x0041b9dc` | `FUN_0041b9dc` | Graphics.InternalGetDIBSizes | [decompiled](decompiled/0041b9dc.c) | [assembly](decompiled/0041b9dc.asm) |
| `0x0041ba28` | `FUN_0041ba28` | Graphics.InternalGetDIB | [decompiled](decompiled/0041ba28.c) | [assembly](decompiled/0041ba28.asm) |
| `0x0041bad3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041bad3.c) | [assembly](decompiled/0041bad3.asm) |
| `0x0041bad8` | `root_0041bad8` |  | [decompiled](decompiled/0041bad8.c) | [assembly](decompiled/0041bad8.asm) |
| `0x0041bae8` | `FUN_0041bae8` | Graphics.DIBFromBit | [decompiled](decompiled/0041bae8.c) | [assembly](decompiled/0041bae8.asm) |
| `0x0041bb50` | `FUN_0041bb50` |  | [decompiled](decompiled/0041bb50.c) | [assembly](decompiled/0041bb50.asm) |
| `0x0041bb54` | `FUN_0041bb54` |  | [decompiled](decompiled/0041bb54.c) | [assembly](decompiled/0041bb54.asm) |
| `0x0041bb60` | `FUN_0041bb60` | Graphics.WriteIcon | [decompiled](decompiled/0041bb60.c) | [assembly](decompiled/0041bb60.asm) |
| `0x0041bd27` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041bd27.c) | [assembly](decompiled/0041bd27.asm) |
| `0x0041bd2c` | `root_0041bd2c` |  | [decompiled](decompiled/0041bd2c.c) | [assembly](decompiled/0041bd2c.asm) |
| `0x0041bd3b` | `FUN_0041bd3b` |  | [decompiled](decompiled/0041bd3b.c) | [assembly](decompiled/0041bd3b.asm) |
| `0x0041bd4e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041bd4e.c) | [assembly](decompiled/0041bd4e.asm) |
| `0x0041bd53` | `thunk_FUN_0041bd3b` |  | [decompiled](decompiled/0041bd53.c) | [assembly](decompiled/0041bd53.asm) |
| `0x0041bd5c` | `FUN_0041bd5c` | DBTables.TBinaryField.Create, Graphics.TGraphic.Create, QuickRep.TQRCustomControl.create, QuickRep.TQRDetailLink.Create | [decompiled](decompiled/0041bd5c.c) | [assembly](decompiled/0041bd5c.asm) |
| `0x0041bd8c` | `FUN_0041bd8c` | Graphics.TGraphic.Changed | [decompiled](decompiled/0041bd8c.c) | [assembly](decompiled/0041bd8c.asm) |
| `0x0041bda4` | `FUN_0041bda4` | Graphics.DoWrite | [decompiled](decompiled/0041bda4.c) | [assembly](decompiled/0041bda4.asm) |
| `0x0041bdfc` | `root_0041bdfc` | Graphics.TGraphic.DefineProperties | [decompiled](decompiled/0041bdfc.c) | [assembly](decompiled/0041bdfc.asm) |
| `0x0041be48` | `FUN_0041be48` | Graphics.CompareMem | [decompiled](decompiled/0041be48.c) | [assembly](decompiled/0041be48.asm) |
| `0x0041be68` | `FUN_0041be68` | Classes.StreamsEqual, Graphics.StreamsEqual | [decompiled](decompiled/0041be68.c) | [assembly](decompiled/0041be68.asm) |
| `0x0041bea8` | `root_0041bea8` | Graphics.TGraphic.Equals | [decompiled](decompiled/0041bea8.c) | [assembly](decompiled/0041bea8.asm) |
| `0x0041bf8c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041bf8c.c) | [assembly](decompiled/0041bf8c.asm) |
| `0x0041bf91` | `root_0041bf91` |  | [decompiled](decompiled/0041bf91.c) | [assembly](decompiled/0041bf91.asm) |
| `0x0041bfa0` | `FUN_0041bfa0` |  | [decompiled](decompiled/0041bfa0.c) | [assembly](decompiled/0041bfa0.asm) |
| `0x0041bfa9` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041bfa9.c) | [assembly](decompiled/0041bfa9.asm) |
| `0x0041bfae` | `thunk_FUN_0041bfa0` |  | [decompiled](decompiled/0041bfae.c) | [assembly](decompiled/0041bfae.asm) |
| `0x0041bfbc` | `root_0041bfbc` | Graphics.TGraphic.LoadFromFile | [decompiled](decompiled/0041bfbc.c) | [assembly](decompiled/0041bfbc.asm) |
| `0x0041c004` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041c004.c) | [assembly](decompiled/0041c004.asm) |
| `0x0041c009` | `root_0041c009` |  | [decompiled](decompiled/0041c009.c) | [assembly](decompiled/0041c009.asm) |
| `0x0041c010` | `FUN_0041c010` | Graphics.TGraphic.SaveToFile | [decompiled](decompiled/0041c010.c) | [assembly](decompiled/0041c010.asm) |
| `0x0041c05b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041c05b.c) | [assembly](decompiled/0041c05b.asm) |
| `0x0041c060` | `root_0041c060` |  | [decompiled](decompiled/0041c060.c) | [assembly](decompiled/0041c060.asm) |
| `0x0041c068` | `root_0041c068` |  | [decompiled](decompiled/0041c068.c) | [assembly](decompiled/0041c068.asm) |
| `0x0041c070` | `root_0041c070` |  | [decompiled](decompiled/0041c070.c) | [assembly](decompiled/0041c070.asm) |
| `0x0041c0a8` | `root_0041c0a8` | Buttons.TGlyphCache.Destroy, DsgnIntf.TComponentList.Destroy, Graphics.TPicture.Destroy, IStreams.TVirtualStream.Destroy, VirtFile.TExternalFileSystem.Destroy | [decompiled](decompiled/0041c0a8.c) | [assembly](decompiled/0041c0a8.asm) |
| `0x0041c0d0` | `root_0041c0d0` | Graphics.TPicture.AssignTo | [decompiled](decompiled/0041c0d0.c) | [assembly](decompiled/0041c0d0.asm) |
| `0x0041c104` | `FUN_0041c104` | Graphics.TPicture.ForceType | [decompiled](decompiled/0041c104.c) | [assembly](decompiled/0041c104.asm) |
| `0x0041c14c` | `FUN_0041c14c` |  | [decompiled](decompiled/0041c14c.c) | [assembly](decompiled/0041c14c.asm) |
| `0x0041c160` | `FUN_0041c160` | Graphics.TPicture.SetGraphic | [decompiled](decompiled/0041c160.c) | [assembly](decompiled/0041c160.asm) |
| `0x0041c1c9` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041c1c9.c) | [assembly](decompiled/0041c1c9.asm) |
| `0x0041c1ce` | `root_0041c1ce` |  | [decompiled](decompiled/0041c1ce.c) | [assembly](decompiled/0041c1ce.asm) |
| `0x0041c1e8` | `FUN_0041c1e8` | Graphics.TPicture.LoadFromFile | [decompiled](decompiled/0041c1e8.c) | [assembly](decompiled/0041c1e8.asm) |
| `0x0041c285` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041c285.c) | [assembly](decompiled/0041c285.asm) |
| `0x0041c28a` | `root_0041c28a` |  | [decompiled](decompiled/0041c28a.c) | [assembly](decompiled/0041c28a.asm) |
| `0x0041c30c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041c30c.c) | [assembly](decompiled/0041c30c.asm) |
| `0x0041c311` | `root_0041c311` |  | [decompiled](decompiled/0041c311.c) | [assembly](decompiled/0041c311.asm) |
| `0x0041c31c` | `root_0041c31c` | Graphics.TPicture.Assign | [decompiled](decompiled/0041c31c.c) | [assembly](decompiled/0041c31c.asm) |
| `0x0041c378` | `FUN_0041c378` | Graphics.TPicture.Changed | [decompiled](decompiled/0041c378.c) | [assembly](decompiled/0041c378.asm) |
| `0x0041c38c` | `root_0041c38c` | Graphics.TPicture.ReadData | [decompiled](decompiled/0041c38c.c) | [assembly](decompiled/0041c38c.asm) |
| `0x0041c41e` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041c41e.c) | [assembly](decompiled/0041c41e.asm) |
| `0x0041c423` | `root_0041c423` |  | [decompiled](decompiled/0041c423.c) | [assembly](decompiled/0041c423.asm) |
| `0x0041c468` | `FUN_0041c468` | Graphics.TPicture.WriteData | [decompiled](decompiled/0041c468.c) | [assembly](decompiled/0041c468.asm) |
| `0x0041c4b4` | `FUN_0041c4b4` | Graphics.DoWrite | [decompiled](decompiled/0041c4b4.c) | [assembly](decompiled/0041c4b4.asm) |
| `0x0041c530` | `FUN_0041c530` | Graphics.TPicture.DefineProperties | [decompiled](decompiled/0041c530.c) | [assembly](decompiled/0041c530.asm) |
| `0x0041c57c` | `FUN_0041c57c` | Graphics.TPicture.GetWidth | [decompiled](decompiled/0041c57c.c) | [assembly](decompiled/0041c57c.asm) |
| `0x0041c594` | `FUN_0041c594` | Graphics.TPicture.GetHeight | [decompiled](decompiled/0041c594.c) | [assembly](decompiled/0041c594.asm) |
| `0x0041c5ac` | `FUN_0041c5ac` |  | [decompiled](decompiled/0041c5ac.c) | [assembly](decompiled/0041c5ac.asm) |
| `0x0041c5b0` | `FUN_0041c5b0` | Graphics.TMetafileImage.Release | [decompiled](decompiled/0041c5b0.c) | [assembly](decompiled/0041c5b0.asm) |
| `0x0041c5e4` | `FUN_0041c5e4` | Graphics.TMetafile.Create | [decompiled](decompiled/0041c5e4.c) | [assembly](decompiled/0041c5e4.asm) |
| `0x0041c620` | `root_0041c620` | Graphics.TIcon.Destroy, Graphics.TMetafile.Destroy, LibMain.TComponentIntf.Destroy | [decompiled](decompiled/0041c620.c) | [assembly](decompiled/0041c620.asm) |
| `0x0041c648` | `root_0041c648` | Graphics.TMetafile.Assign | [decompiled](decompiled/0041c648.c) | [assembly](decompiled/0041c648.asm) |
| `0x0041c6b4` | `root_0041c6b4` | Graphics.TMetafile.Draw | [decompiled](decompiled/0041c6b4.c) | [assembly](decompiled/0041c6b4.asm) |
| `0x0041c748` | `root_0041c748` |  | [decompiled](decompiled/0041c748.c) | [assembly](decompiled/0041c748.asm) |
| `0x0041c750` | `root_0041c750` | Graphics.TMetafile.GetHeight | [decompiled](decompiled/0041c750.c) | [assembly](decompiled/0041c750.asm) |
| `0x0041c7b4` | `FUN_0041c7b4` | Graphics.TMetafile.GetPalette | [decompiled](decompiled/0041c7b4.c) | [assembly](decompiled/0041c7b4.asm) |
| `0x0041c88c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041c88c.c) | [assembly](decompiled/0041c88c.asm) |
| `0x0041c891` | `root_0041c891` |  | [decompiled](decompiled/0041c891.c) | [assembly](decompiled/0041c891.asm) |
| `0x0041c8a4` | `root_0041c8a4` | Graphics.TMetafile.GetWidth | [decompiled](decompiled/0041c8a4.c) | [assembly](decompiled/0041c8a4.asm) |
| `0x0041c908` | `root_0041c908` | Graphics.TMetafile.LoadFromStream | [decompiled](decompiled/0041c908.c) | [assembly](decompiled/0041c908.asm) |
| `0x0041c954` | `FUN_0041c954` | Graphics.TMetafile.NewImage | [decompiled](decompiled/0041c954.c) | [assembly](decompiled/0041c954.asm) |
| `0x0041c97c` | `FUN_0041c97c` | Graphics.TMetafile.ReadData | [decompiled](decompiled/0041c97c.c) | [assembly](decompiled/0041c97c.asm) |
| `0x0041c9c4` | `FUN_0041c9c4` | Graphics.TMetafile.ReadEMFStream | [decompiled](decompiled/0041c9c4.c) | [assembly](decompiled/0041c9c4.asm) |
| `0x0041ca84` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041ca84.c) | [assembly](decompiled/0041ca84.asm) |
| `0x0041ca89` | `root_0041ca89` |  | [decompiled](decompiled/0041ca89.c) | [assembly](decompiled/0041ca89.asm) |
| `0x0041ca94` | `FUN_0041ca94` | Graphics.TMetafile.ReadWMFStream | [decompiled](decompiled/0041ca94.c) | [assembly](decompiled/0041ca94.asm) |
| `0x0041cbaa` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041cbaa.c) | [assembly](decompiled/0041cbaa.asm) |
| `0x0041cbaf` | `root_0041cbaf` |  | [decompiled](decompiled/0041cbaf.c) | [assembly](decompiled/0041cbaf.asm) |
| `0x0041cbb8` | `root_0041cbb8` | Graphics.TMetafile.SaveToFile | [decompiled](decompiled/0041cbb8.c) | [assembly](decompiled/0041cbb8.asm) |
| `0x0041cc26` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041cc26.c) | [assembly](decompiled/0041cc26.asm) |
| `0x0041cc2b` | `root_0041cc2b` |  | [decompiled](decompiled/0041cc2b.c) | [assembly](decompiled/0041cc2b.asm) |
| `0x0041cc44` | `root_0041cc44` | Graphics.TMetafile.SaveToStream | [decompiled](decompiled/0041cc44.c) | [assembly](decompiled/0041cc44.asm) |
| `0x0041cc60` | `root_0041cc60` | Graphics.TMetafile.SetHeight | [decompiled](decompiled/0041cc60.c) | [assembly](decompiled/0041cc60.asm) |
| `0x0041ccd4` | `FUN_0041ccd4` | Graphics.TMetafile.SetMMHeight | [decompiled](decompiled/0041ccd4.c) | [assembly](decompiled/0041ccd4.asm) |
| `0x0041cd10` | `FUN_0041cd10` | Graphics.TMetafile.SetMMWidth | [decompiled](decompiled/0041cd10.c) | [assembly](decompiled/0041cd10.asm) |
| `0x0041cd4c` | `root_0041cd4c` | Graphics.TMetafile.SetWidth | [decompiled](decompiled/0041cd4c.c) | [assembly](decompiled/0041cd4c.asm) |
| `0x0041cdc0` | `FUN_0041cdc0` | Graphics.TMetafile.TestEMF | [decompiled](decompiled/0041cdc0.c) | [assembly](decompiled/0041cdc0.asm) |
| `0x0041ce20` | `FUN_0041ce20` | Graphics.TMetafile.UniqueImage | [decompiled](decompiled/0041ce20.c) | [assembly](decompiled/0041ce20.asm) |
| `0x0041cea4` | `FUN_0041cea4` | Graphics.TMetafile.WriteData | [decompiled](decompiled/0041cea4.c) | [assembly](decompiled/0041cea4.asm) |
| `0x0041cf28` | `FUN_0041cf28` | Graphics.TMetafile.WriteEMFStream | [decompiled](decompiled/0041cf28.c) | [assembly](decompiled/0041cf28.asm) |
| `0x0041cf9e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041cf9e.c) | [assembly](decompiled/0041cf9e.asm) |
| `0x0041cfa3` | `root_0041cfa3` |  | [decompiled](decompiled/0041cfa3.c) | [assembly](decompiled/0041cfa3.asm) |
| `0x0041cfac` | `FUN_0041cfac` | Graphics.TMetafile.WriteWMFStream | [decompiled](decompiled/0041cfac.c) | [assembly](decompiled/0041cfac.asm) |
| `0x0041d0b5` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041d0b5.c) | [assembly](decompiled/0041d0b5.asm) |
| `0x0041d0ba` | `root_0041d0ba` |  | [decompiled](decompiled/0041d0ba.c) | [assembly](decompiled/0041d0ba.asm) |
| `0x0041d0c9` | `FUN_0041d0c9` |  | [decompiled](decompiled/0041d0c9.c) | [assembly](decompiled/0041d0c9.asm) |
| `0x0041d0d5` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041d0d5.c) | [assembly](decompiled/0041d0d5.asm) |
| `0x0041d0da` | `thunk_FUN_0041d0c9` |  | [decompiled](decompiled/0041d0da.c) | [assembly](decompiled/0041d0da.asm) |
| `0x0041d0e4` | `root_0041d0e4` | Graphics.TMetafile.LoadFromClipboardFormat | [decompiled](decompiled/0041d0e4.c) | [assembly](decompiled/0041d0e4.asm) |
| `0x0041d158` | `FUN_0041d158` | Graphics.TMetafile.SaveToClipboardFormat | [decompiled](decompiled/0041d158.c) | [assembly](decompiled/0041d158.asm) |
| `0x0041d20c` | `FUN_0041d20c` | Graphics.FreeMemoryContexts | [decompiled](decompiled/0041d20c.c) | [assembly](decompiled/0041d20c.asm) |
| `0x0041d22c` | `FUN_0041d22c` | Graphics.DeselectBitmap | [decompiled](decompiled/0041d22c.c) | [assembly](decompiled/0041d22c.asm) |
| `0x0041d268` | `FUN_0041d268` | Graphics.TBitmapCanvas.Create, Printers.TPrinterCanvas.Create | [decompiled](decompiled/0041d268.c) | [assembly](decompiled/0041d268.asm) |
| `0x0041d2a0` | `root_0041d2a0` | Classes.TMemoryStream.Destroy, Classes.TWriter.Destroy, ComCtrls.TListItems.Destroy, ComCtrls.TTreeNodes.Destroy, Controls.TControlCanvas.Destroy, DBGrids.TGridDataLink.Destroy, DDEMan.TDdeCliItem.Destroy, DsgnWnds.TDesignWindow.Destroy, Graphics.TBitmapCanvas.Destroy, Registry.TRegistry.Destroy | [decompiled](decompiled/0041d2a0.c) | [assembly](decompiled/0041d2a0.asm) |
| `0x0041d2c8` | `FUN_0041d2c8` | Graphics.TBitmapCanvas.FreeContext | [decompiled](decompiled/0041d2c8.c) | [assembly](decompiled/0041d2c8.asm) |
| `0x0041d318` | `root_0041d318` | Graphics.TBitmapCanvas.CreateHandle | [decompiled](decompiled/0041d318.c) | [assembly](decompiled/0041d318.asm) |
| `0x0041d3a0` | `FUN_0041d3a0` |  | [decompiled](decompiled/0041d3a0.c) | [assembly](decompiled/0041d3a0.asm) |
| `0x0041d3a4` | `FUN_0041d3a4` | Graphics.TInternalImage.Release | [decompiled](decompiled/0041d3a4.c) | [assembly](decompiled/0041d3a4.asm) |
| `0x0041d3cc` | `FUN_0041d3cc` | Graphics.TBitmapImage.FreeHandle | [decompiled](decompiled/0041d3cc.c) | [assembly](decompiled/0041d3cc.asm) |
| `0x0041d400` | `FUN_0041d400` | Graphics.CopyBitmap | [decompiled](decompiled/0041d400.c) | [assembly](decompiled/0041d400.asm) |
| `0x0041d5fe` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041d5fe.c) | [assembly](decompiled/0041d5fe.asm) |
| `0x0041d603` | `root_0041d603` |  | [decompiled](decompiled/0041d603.c) | [assembly](decompiled/0041d603.asm) |
| `0x0041d60f` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041d60f.c) | [assembly](decompiled/0041d60f.asm) |
| `0x0041d614` | `root_0041d614` |  | [decompiled](decompiled/0041d614.c) | [assembly](decompiled/0041d614.asm) |
| `0x0041d656` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041d656.c) | [assembly](decompiled/0041d656.asm) |
| `0x0041d65b` | `root_0041d65b` |  | [decompiled](decompiled/0041d65b.c) | [assembly](decompiled/0041d65b.asm) |
| `0x0041d66c` | `FUN_0041d66c` | Graphics.CopyPalette | [decompiled](decompiled/0041d66c.c) | [assembly](decompiled/0041d66c.asm) |
| `0x0041d708` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041d708.c) | [assembly](decompiled/0041d708.asm) |
| `0x0041d70d` | `root_0041d70d` |  | [decompiled](decompiled/0041d70d.c) | [assembly](decompiled/0041d70d.asm) |
| `0x0041d718` | `FUN_0041d718` | Graphics.TBitmap.Create, Graphics.TIcon.Create | [decompiled](decompiled/0041d718.c) | [assembly](decompiled/0041d718.asm) |
| `0x0041d760` | `root_0041d760` | Graphics.TBitmap.Destroy | [decompiled](decompiled/0041d760.c) | [assembly](decompiled/0041d760.asm) |
| `0x0041d790` | `FUN_0041d790` | Graphics.TBitmap.Assign | [decompiled](decompiled/0041d790.c) | [assembly](decompiled/0041d790.asm) |
| `0x0041d7fc` | `FUN_0041d7fc` | Graphics.TBitmap.CopyImage | [decompiled](decompiled/0041d7fc.c) | [assembly](decompiled/0041d7fc.asm) |
| `0x0041d87f` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041d87f.c) | [assembly](decompiled/0041d87f.asm) |
| `0x0041d884` | `root_0041d884` |  | [decompiled](decompiled/0041d884.c) | [assembly](decompiled/0041d884.asm) |
| `0x0041d8a1` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041d8a1.c) | [assembly](decompiled/0041d8a1.asm) |
| `0x0041d8a6` | `root_0041d8a6` |  | [decompiled](decompiled/0041d8a6.c) | [assembly](decompiled/0041d8a6.asm) |
| `0x0041d8c4` | `FUN_0041d8c4` |  | [decompiled](decompiled/0041d8c4.c) | [assembly](decompiled/0041d8c4.asm) |
| `0x0041d8e0` | `FUN_0041d8e0` | Graphics.TBitmap.Draw | [decompiled](decompiled/0041d8e0.c) | [assembly](decompiled/0041d8e0.asm) |
| `0x0041da6d` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041da6d.c) | [assembly](decompiled/0041da6d.asm) |
| `0x0041da72` | `root_0041da72` |  | [decompiled](decompiled/0041da72.c) | [assembly](decompiled/0041da72.asm) |
| `0x0041da80` | `FUN_0041da80` | Graphics.TBitmap.FreeImage | [decompiled](decompiled/0041da80.c) | [assembly](decompiled/0041da80.asm) |
| `0x0041dac0` | `root_0041dac0` | Graphics.TBitmap.GetEmpty, Graphics.TIcon.GetEmpty | [decompiled](decompiled/0041dac0.c) | [assembly](decompiled/0041dac0.asm) |
| `0x0041dad8` | `FUN_0041dad8` | Graphics.TBitmap.GetCanvas | [decompiled](decompiled/0041dad8.c) | [assembly](decompiled/0041dad8.asm) |
| `0x0041db18` | `root_0041db18` | Graphics.TBitmap.GetHandle | [decompiled](decompiled/0041db18.c) | [assembly](decompiled/0041db18.asm) |
| `0x0041db3c` | `root_0041db3c` |  | [decompiled](decompiled/0041db3c.c) | [assembly](decompiled/0041db3c.asm) |
| `0x0041db44` | `FUN_0041db44` |  | [decompiled](decompiled/0041db44.c) | [assembly](decompiled/0041db44.asm) |
| `0x0041db4c` | `FUN_0041db4c` |  | [decompiled](decompiled/0041db4c.c) | [assembly](decompiled/0041db4c.asm) |
| `0x0041db60` | `FUN_0041db60` | Graphics.TBitmap.GetTransparentColor | [decompiled](decompiled/0041db60.c) | [assembly](decompiled/0041db60.asm) |
| `0x0041db94` | `root_0041db94` |  | [decompiled](decompiled/0041db94.c) | [assembly](decompiled/0041db94.asm) |
| `0x0041db9c` | `FUN_0041db9c` |  | [decompiled](decompiled/0041db9c.c) | [assembly](decompiled/0041db9c.asm) |
| `0x0041dbac` | `FUN_0041dbac` | Graphics.TBitmap.HandleNeeded | [decompiled](decompiled/0041dbac.c) | [assembly](decompiled/0041dbac.asm) |
| `0x0041dbe0` | `FUN_0041dbe0` | Graphics.TBitmap.MemoryImageNeeded | [decompiled](decompiled/0041dbe0.c) | [assembly](decompiled/0041dbe0.asm) |
| `0x0041dc45` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041dc45.c) | [assembly](decompiled/0041dc45.asm) |
| `0x0041dc4a` | `root_0041dc4a` |  | [decompiled](decompiled/0041dc4a.c) | [assembly](decompiled/0041dc4a.asm) |
| `0x0041dc94` | `FUN_0041dc94` | Graphics.TBitmap.PaletteNeeded | [decompiled](decompiled/0041dc94.c) | [assembly](decompiled/0041dc94.asm) |
| `0x0041dccc` | `FUN_0041dccc` | Graphics.TBitmap.LoadFromClipboardFormat | [decompiled](decompiled/0041dccc.c) | [assembly](decompiled/0041dccc.asm) |
| `0x0041dd8e` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041dd8e.c) | [assembly](decompiled/0041dd8e.asm) |
| `0x0041dd93` | `root_0041dd93` |  | [decompiled](decompiled/0041dd93.c) | [assembly](decompiled/0041dd93.asm) |
| `0x0041ddb0` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041ddb0.c) | [assembly](decompiled/0041ddb0.asm) |
| `0x0041ddb5` | `root_0041ddb5` |  | [decompiled](decompiled/0041ddb5.c) | [assembly](decompiled/0041ddb5.asm) |
| `0x0041dddc` | `root_0041dddc` | Graphics.TBitmap.LoadFromStream | [decompiled](decompiled/0041dddc.c) | [assembly](decompiled/0041dddc.asm) |
| `0x0041de0c` | `FUN_0041de0c` | Graphics.TBitmap.NewImage | [decompiled](decompiled/0041de0c.c) | [assembly](decompiled/0041de0c.asm) |
| `0x0041de8b` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041de8b.c) | [assembly](decompiled/0041de8b.asm) |
| `0x0041de90` | `root_0041de90` |  | [decompiled](decompiled/0041de90.c) | [assembly](decompiled/0041de90.asm) |
| `0x0041dec0` | `root_0041dec0` | Graphics.TBitmap.ReadData | [decompiled](decompiled/0041dec0.c) | [assembly](decompiled/0041dec0.asm) |
| `0x0041def0` | `FUN_0041def0` | Graphics.TBitmap.ReadStream | [decompiled](decompiled/0041def0.c) | [assembly](decompiled/0041def0.asm) |
| `0x0041df94` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041df94.c) | [assembly](decompiled/0041df94.asm) |
| `0x0041df99` | `root_0041df99` |  | [decompiled](decompiled/0041df99.c) | [assembly](decompiled/0041df99.asm) |
| `0x0041dfb4` | `FUN_0041dfb4` | Graphics.TBitmap.ReadStreamDIB | [decompiled](decompiled/0041dfb4.c) | [assembly](decompiled/0041dfb4.asm) |
| `0x0041e0ec` | `FUN_0041e0ec` | Graphics.TBitmap.SetHandle | [decompiled](decompiled/0041e0ec.c) | [assembly](decompiled/0041e0ec.asm) |
| `0x0041e194` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041e194.c) | [assembly](decompiled/0041e194.asm) |
| `0x0041e199` | `root_0041e199` |  | [decompiled](decompiled/0041e199.c) | [assembly](decompiled/0041e199.asm) |
| `0x0041e1bc` | `FUN_0041e1bc` | Graphics.TBitmap.SetHeight | [decompiled](decompiled/0041e1bc.c) | [assembly](decompiled/0041e1bc.asm) |
| `0x0041e1ec` | `FUN_0041e1ec` | Graphics.TBitmap.SetMonochrome | [decompiled](decompiled/0041e1ec.c) | [assembly](decompiled/0041e1ec.asm) |
| `0x0041e21c` | `root_0041e21c` | Graphics.TBitmap.SetWidth | [decompiled](decompiled/0041e21c.c) | [assembly](decompiled/0041e21c.asm) |
| `0x0041e24c` | `root_0041e24c` |  | [decompiled](decompiled/0041e24c.c) | [assembly](decompiled/0041e24c.asm) |
| `0x0041e254` | `FUN_0041e254` | Graphics.TBitmap.WriteStream | [decompiled](decompiled/0041e254.c) | [assembly](decompiled/0041e254.asm) |
| `0x0041e2f8` | `root_0041e2f8` |  | [decompiled](decompiled/0041e2f8.c) | [assembly](decompiled/0041e2f8.asm) |
| `0x0041e300` | `FUN_0041e300` | Graphics.TBitmap.SaveToClipboardFormat | [decompiled](decompiled/0041e300.c) | [assembly](decompiled/0041e300.asm) |
| `0x0041e362` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041e362.c) | [assembly](decompiled/0041e362.asm) |
| `0x0041e367` | `root_0041e367` |  | [decompiled](decompiled/0041e367.c) | [assembly](decompiled/0041e367.asm) |
| `0x0041e384` | `FUN_0041e384` | Graphics.TIconImage.FreeHandle | [decompiled](decompiled/0041e384.c) | [assembly](decompiled/0041e384.asm) |
| `0x0041e39c` | `FUN_0041e39c` | Graphics.TBitmap.Create, Graphics.TIcon.Create | [decompiled](decompiled/0041e39c.c) | [assembly](decompiled/0041e39c.asm) |
| `0x0041e3e4` | `root_0041e3e4` | Graphics.TIcon.Destroy, Graphics.TMetafile.Destroy, LibMain.TComponentIntf.Destroy | [decompiled](decompiled/0041e3e4.c) | [assembly](decompiled/0041e3e4.asm) |
| `0x0041e40c` | `FUN_0041e40c` | Graphics.TIcon.Assign | [decompiled](decompiled/0041e40c.c) | [assembly](decompiled/0041e40c.asm) |
| `0x0041e468` | `FUN_0041e468` | Graphics.TIcon.Draw | [decompiled](decompiled/0041e468.c) | [assembly](decompiled/0041e468.asm) |
| `0x0041e4a0` | `root_0041e4a0` | Graphics.TBitmap.GetEmpty, Graphics.TIcon.GetEmpty | [decompiled](decompiled/0041e4a0.c) | [assembly](decompiled/0041e4a0.asm) |
| `0x0041e4b8` | `FUN_0041e4b8` |  | [decompiled](decompiled/0041e4b8.c) | [assembly](decompiled/0041e4b8.asm) |
| `0x0041e4cc` | `root_0041e4cc` |  | [decompiled](decompiled/0041e4cc.c) | [assembly](decompiled/0041e4cc.asm) |
| `0x0041e4d4` | `root_0041e4d4` |  | [decompiled](decompiled/0041e4d4.c) | [assembly](decompiled/0041e4d4.asm) |
| `0x0041e4dc` | `FUN_0041e4dc` | Graphics.TIcon.HandleNeeded | [decompiled](decompiled/0041e4dc.c) | [assembly](decompiled/0041e4dc.asm) |
| `0x0041e548` | `FUN_0041e548` | Graphics.TIcon.ImageNeeded | [decompiled](decompiled/0041e548.c) | [assembly](decompiled/0041e548.asm) |
| `0x0041e5d5` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041e5d5.c) | [assembly](decompiled/0041e5d5.asm) |
| `0x0041e5da` | `root_0041e5da` |  | [decompiled](decompiled/0041e5da.c) | [assembly](decompiled/0041e5da.asm) |
| `0x0041e5fc` | `root_0041e5fc` | Graphics.TIcon.LoadFromStream | [decompiled](decompiled/0041e5fc.c) | [assembly](decompiled/0041e5fc.asm) |
| `0x0041e68c` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041e68c.c) | [assembly](decompiled/0041e68c.asm) |
| `0x0041e691` | `root_0041e691` |  | [decompiled](decompiled/0041e691.c) | [assembly](decompiled/0041e691.asm) |
| `0x0041e6b4` | `FUN_0041e6b4` | Graphics.TIcon.NewImage | [decompiled](decompiled/0041e6b4.c) | [assembly](decompiled/0041e6b4.asm) |
| `0x0041e6f4` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041e6f4.c) | [assembly](decompiled/0041e6f4.asm) |
| `0x0041e6f9` | `root_0041e6f9` |  | [decompiled](decompiled/0041e6f9.c) | [assembly](decompiled/0041e6f9.asm) |
| `0x0041e728` | `FUN_0041e728` |  | [decompiled](decompiled/0041e728.c) | [assembly](decompiled/0041e728.asm) |
| `0x0041e740` | `root_0041e740` |  | [decompiled](decompiled/0041e740.c) | [assembly](decompiled/0041e740.asm) |
| `0x0041e74c` | `root_0041e74c` |  | [decompiled](decompiled/0041e74c.c) | [assembly](decompiled/0041e74c.asm) |
| `0x0041e758` | `root_0041e758` | Graphics.TIcon.SaveToStream | [decompiled](decompiled/0041e758.c) | [assembly](decompiled/0041e758.asm) |
| `0x0041e784` | `root_0041e784` |  | [decompiled](decompiled/0041e784.c) | [assembly](decompiled/0041e784.asm) |
| `0x0041e798` | `root_0041e798` |  | [decompiled](decompiled/0041e798.c) | [assembly](decompiled/0041e798.asm) |
| `0x0041e7ac` | `FUN_0041e7ac` |  | [decompiled](decompiled/0041e7ac.c) | [assembly](decompiled/0041e7ac.asm) |
| `0x0041f7d8` | `FUN_0041f7d8` |  | [decompiled](decompiled/0041f7d8.c) | [assembly](decompiled/0041f7d8.asm) |
| `0x0041f7e4` | `root_0041f7e4` | Forms.DoneApplication | [decompiled](decompiled/0041f7e4.c) | [assembly](decompiled/0041f7e4.asm) |
| `0x0041f810` | `root_0041f810` | Forms.DoDisableWindow | [decompiled](decompiled/0041f810.c) | [assembly](decompiled/0041f810.asm) |
| `0x0041f860` | `FUN_0041f860` | Forms.DisableTaskWindows | [decompiled](decompiled/0041f860.c) | [assembly](decompiled/0041f860.asm) |
| `0x0041f8cc` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0041f8cc.c) | [assembly](decompiled/0041f8cc.asm) |
| `0x0041f8d1` | `root_0041f8d1` |  | [decompiled](decompiled/0041f8d1.c) | [assembly](decompiled/0041f8d1.asm) |
| `0x0041f903` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041f903.c) | [assembly](decompiled/0041f903.asm) |
| `0x0041f908` | `root_0041f908` |  | [decompiled](decompiled/0041f908.c) | [assembly](decompiled/0041f908.asm) |
| `0x0041f914` | `FUN_0041f914` | Forms.EnableTaskWindows | [decompiled](decompiled/0041f914.c) | [assembly](decompiled/0041f914.asm) |
| `0x0041f94c` | `FUN_0041f94c` | Forms.DoFindWindow | [decompiled](decompiled/0041f94c.c) | [assembly](decompiled/0041f94c.asm) |
| `0x0041f9b0` | `FUN_0041f9b0` | Forms.FindTopMostWindow | [decompiled](decompiled/0041f9b0.c) | [assembly](decompiled/0041f9b0.asm) |
| `0x0041f9ec` | `FUN_0041f9ec` | Forms.SendFocusMessage | [decompiled](decompiled/0041f9ec.c) | [assembly](decompiled/0041f9ec.asm) |
| `0x0041fa0c` | `FUN_0041fa0c` | Forms.CheckTaskWindow | [decompiled](decompiled/0041fa0c.c) | [assembly](decompiled/0041fa0c.asm) |
| `0x0041fa30` | `FUN_0041fa30` | Forms.ForegroundTask | [decompiled](decompiled/0041fa30.c) | [assembly](decompiled/0041fa30.asm) |
| `0x0041fa5c` | `root_0041fa5c` | Forms.FindGlobalComponent | [decompiled](decompiled/0041fa5c.c) | [assembly](decompiled/0041fa5c.asm) |
| `0x0041fad4` | `FUN_0041fad4` | Forms.InitCtl3D | [decompiled](decompiled/0041fad4.c) | [assembly](decompiled/0041fad4.asm) |
| `0x0041fd00` | `FUN_0041fd00` |  | [decompiled](decompiled/0041fd00.c) | [assembly](decompiled/0041fd00.asm) |
| `0x0041fd24` | `root_0041fd24` | Forms.StdWndProc | [decompiled](decompiled/0041fd24.c) | [assembly](decompiled/0041fd24.asm) |
| `0x0041fd44` | `FUN_0041fd44` |  | [decompiled](decompiled/0041fd44.c) | [assembly](decompiled/0041fd44.asm) |
| `0x0041fd4c` | `FUN_0041fd4c` | Forms.MakeObjectInstance | [decompiled](decompiled/0041fd4c.c) | [assembly](decompiled/0041fd4c.asm) |
| `0x0041fde4` | `FUN_0041fde4` |  | [decompiled](decompiled/0041fde4.c) | [assembly](decompiled/0041fde4.asm) |
| `0x0041fe08` | `FUN_0041fe08` | Forms.AllocateHWnd | [decompiled](decompiled/0041fe08.c) | [assembly](decompiled/0041fe08.asm) |
| `0x0041feac` | `FUN_0041feac` | Forms.DeallocateHWnd | [decompiled](decompiled/0041feac.c) | [assembly](decompiled/0041feac.asm) |
| `0x0041fecc` | `FUN_0041fecc` | Forms.KeysToShiftState | [decompiled](decompiled/0041fecc.c) | [assembly](decompiled/0041fecc.asm) |
| `0x0041ff20` | `FUN_0041ff20` | Forms.KeyDataToShiftState | [decompiled](decompiled/0041ff20.c) | [assembly](decompiled/0041ff20.asm) |
| `0x0041ff5c` | `FUN_0041ff5c` | Forms.IsAccel | [decompiled](decompiled/0041ff5c.c) | [assembly](decompiled/0041ff5c.asm) |
| `0x0041ffde` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0041ffde.c) | [assembly](decompiled/0041ffde.asm) |
| `0x0041ffe3` | `root_0041ffe3` |  | [decompiled](decompiled/0041ffe3.c) | [assembly](decompiled/0041ffe3.asm) |
| `0x0041fffc` | `FUN_0041fffc` | Forms.GetParentForm | [decompiled](decompiled/0041fffc.c) | [assembly](decompiled/0041fffc.asm) |
| `0x00420024` | `FUN_00420024` | Forms.ValidParentForm | [decompiled](decompiled/00420024.c) | [assembly](decompiled/00420024.asm) |
| `0x00420060` | `FUN_00420060` | Forms.TControlScrollBar.Create | [decompiled](decompiled/00420060.c) | [assembly](decompiled/00420060.asm) |
| `0x004200ac` | `FUN_004200ac` | Forms.TControlScrollBar.Assign | [decompiled](decompiled/004200ac.c) | [assembly](decompiled/004200ac.asm) |
| `0x004200fc` | `FUN_004200fc` | Forms.ProcessHorz | [decompiled](decompiled/004200fc.c) | [assembly](decompiled/004200fc.asm) |
| `0x00420144` | `FUN_00420144` | Forms.ProcessVert | [decompiled](decompiled/00420144.c) | [assembly](decompiled/00420144.asm) |
| `0x0042018c` | `FUN_0042018c` |  | [decompiled](decompiled/0042018c.c) | [assembly](decompiled/0042018c.asm) |
| `0x0042021c` | `FUN_0042021c` | Forms.ScrollBarVisible | [decompiled](decompiled/0042021c.c) | [assembly](decompiled/0042021c.asm) |
| `0x00420250` | `FUN_00420250` | Forms.Adjustment | [decompiled](decompiled/00420250.c) | [assembly](decompiled/00420250.asm) |
| `0x004202c4` | `FUN_004202c4` | Forms.TControlScrollBar.ControlSize | [decompiled](decompiled/004202c4.c) | [assembly](decompiled/004202c4.asm) |
| `0x00420344` | `FUN_00420344` | Forms.TControlScrollBar.NeedsScrollBarVisible | [decompiled](decompiled/00420344.c) | [assembly](decompiled/00420344.asm) |
| `0x0042035c` | `root_0042035c` | Forms.TControlScrollBar.ScrollMessage | [decompiled](decompiled/0042035c.c) | [assembly](decompiled/0042035c.asm) |
| `0x00420424` | `FUN_00420424` |  | [decompiled](decompiled/00420424.c) | [assembly](decompiled/00420424.asm) |
| `0x004204e0` | `FUN_004204e0` | Forms.TControlScrollBar.DoSetRange | [decompiled](decompiled/004204e0.c) | [assembly](decompiled/004204e0.asm) |
| `0x004204f8` | `FUN_004204f8` |  | [decompiled](decompiled/004204f8.c) | [assembly](decompiled/004204f8.asm) |
| `0x0042050c` | `root_0042050c` |  | [decompiled](decompiled/0042050c.c) | [assembly](decompiled/0042050c.asm) |
| `0x00420518` | `FUN_00420518` |  | [decompiled](decompiled/00420518.c) | [assembly](decompiled/00420518.asm) |
| `0x00420524` | `FUN_00420524` | Forms.TControlScrollBar.Update | [decompiled](decompiled/00420524.c) | [assembly](decompiled/00420524.asm) |
| `0x004205d8` | `FUN_004205d8` |  | [decompiled](decompiled/004205d8.c) | [assembly](decompiled/004205d8.asm) |
| `0x0042063c` | `FUN_0042063c` |  | [decompiled](decompiled/0042063c.c) | [assembly](decompiled/0042063c.asm) |
| `0x00420674` | `FUN_00420674` |  | [decompiled](decompiled/00420674.c) | [assembly](decompiled/00420674.asm) |
| `0x00420688` | `FUN_00420688` |  | [decompiled](decompiled/00420688.c) | [assembly](decompiled/00420688.asm) |
| `0x0042070c` | `FUN_0042070c` |  | [decompiled](decompiled/0042070c.c) | [assembly](decompiled/0042070c.asm) |
| `0x00420730` | `FUN_00420730` |  | [decompiled](decompiled/00420730.c) | [assembly](decompiled/00420730.asm) |
| `0x0042076c` | `root_0042076c` |  | [decompiled](decompiled/0042076c.c) | [assembly](decompiled/0042076c.asm) |
| `0x00420778` | `root_00420778` |  | [decompiled](decompiled/00420778.c) | [assembly](decompiled/00420778.asm) |
| `0x00420784` | `FUN_00420784` |  | [decompiled](decompiled/00420784.c) | [assembly](decompiled/00420784.asm) |
| `0x0042086f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042086f.c) | [assembly](decompiled/0042086f.asm) |
| `0x00420874` | `root_00420874` |  | [decompiled](decompiled/00420874.c) | [assembly](decompiled/00420874.asm) |
| `0x0042087c` | `FUN_0042087c` | Forms.TScrollingWinControl.AutoScrollInView | [decompiled](decompiled/0042087c.c) | [assembly](decompiled/0042087c.asm) |
| `0x00420894` | `FUN_00420894` |  | [decompiled](decompiled/00420894.c) | [assembly](decompiled/00420894.asm) |
| `0x004209e8` | `FUN_004209e8` |  | [decompiled](decompiled/004209e8.c) | [assembly](decompiled/004209e8.asm) |
| `0x00420a8c` | `FUN_00420a8c` | Forms.TScrollingWinControl.ChangeScale | [decompiled](decompiled/00420a8c.c) | [assembly](decompiled/00420a8c.asm) |
| `0x00420ab0` | `FUN_00420ab0` |  | [decompiled](decompiled/00420ab0.c) | [assembly](decompiled/00420ab0.asm) |
| `0x00420aef` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00420aef.c) | [assembly](decompiled/00420aef.asm) |
| `0x00420af4` | `root_00420af4` |  | [decompiled](decompiled/00420af4.c) | [assembly](decompiled/00420af4.asm) |
| `0x00420b04` | `root_00420b04` | Forms.TScrollingWinControl.WMVScroll | [decompiled](decompiled/00420b04.c) | [assembly](decompiled/00420b04.asm) |
| `0x00420b1c` | `root_00420b1c` |  | [decompiled](decompiled/00420b1c.c) | [assembly](decompiled/00420b1c.asm) |
| `0x00420b34` | `FUN_00420b34` |  | [decompiled](decompiled/00420b34.c) | [assembly](decompiled/00420b34.asm) |
| `0x00420be9` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00420be9.c) | [assembly](decompiled/00420be9.asm) |
| `0x00420bee` | `root_00420bee` |  | [decompiled](decompiled/00420bee.c) | [assembly](decompiled/00420bee.asm) |
| `0x00420c70` | `FUN_00420c70` |  | [decompiled](decompiled/00420c70.c) | [assembly](decompiled/00420c70.asm) |
| `0x00420d7c` | `root_00420d7c` |  | [decompiled](decompiled/00420d7c.c) | [assembly](decompiled/00420d7c.asm) |
| `0x00420df9` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00420df9.c) | [assembly](decompiled/00420df9.asm) |
| `0x00420dfe` | `root_00420dfe` |  | [decompiled](decompiled/00420dfe.c) | [assembly](decompiled/00420dfe.asm) |
| `0x00420e98` | `root_00420e98` |  | [decompiled](decompiled/00420e98.c) | [assembly](decompiled/00420e98.asm) |
| `0x00420f20` | `root_00420f20` |  | [decompiled](decompiled/00420f20.c) | [assembly](decompiled/00420f20.asm) |
| `0x004210f2` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004210f2.c) | [assembly](decompiled/004210f2.asm) |
| `0x004210f7` | `root_004210f7` |  | [decompiled](decompiled/004210f7.c) | [assembly](decompiled/004210f7.asm) |
| `0x00421104` | `root_00421104` | Forms.TForm.DefineProperties | [decompiled](decompiled/00421104.c) | [assembly](decompiled/00421104.asm) |
| `0x00421198` | `root_00421198` | Forms.TForm.WritePixelsPerInch, Forms.TForm.WriteTextHeight | [decompiled](decompiled/00421198.c) | [assembly](decompiled/00421198.asm) |
| `0x004211b4` | `root_004211b4` | Forms.TForm.WritePixelsPerInch, Forms.TForm.WriteTextHeight | [decompiled](decompiled/004211b4.c) | [assembly](decompiled/004211b4.asm) |
| `0x004211d0` | `FUN_004211d0` | Forms.TForm.GetTextHeight | [decompiled](decompiled/004211d0.c) | [assembly](decompiled/004211d0.asm) |
| `0x004211f4` | `root_004211f4` | Forms.TForm.ChangeScale | [decompiled](decompiled/004211f4.c) | [assembly](decompiled/004211f4.asm) |
| `0x00421274` | `FUN_00421274` |  | [decompiled](decompiled/00421274.c) | [assembly](decompiled/00421274.asm) |
| `0x004212cc` | `FUN_004212cc` |  | [decompiled](decompiled/004212cc.c) | [assembly](decompiled/004212cc.asm) |
| `0x004212dc` | `FUN_004212dc` |  | [decompiled](decompiled/004212dc.c) | [assembly](decompiled/004212dc.asm) |
| `0x00421304` | `FUN_00421304` |  | [decompiled](decompiled/00421304.c) | [assembly](decompiled/00421304.asm) |
| `0x00421338` | `root_00421338` |  | [decompiled](decompiled/00421338.c) | [assembly](decompiled/00421338.asm) |
| `0x00421354` | `root_00421354` |  | [decompiled](decompiled/00421354.c) | [assembly](decompiled/00421354.asm) |
| `0x00421370` | `root_00421370` |  | [decompiled](decompiled/00421370.c) | [assembly](decompiled/00421370.asm) |
| `0x004213f8` | `root_004213f8` | Forms.TDataModule.GetChildren, Forms.TForm.GetChildren | [decompiled](decompiled/004213f8.c) | [assembly](decompiled/004213f8.asm) |
| `0x0042145c` | `FUN_0042145c` | Forms.TForm.SetChildOrder | [decompiled](decompiled/0042145c.c) | [assembly](decompiled/0042145c.asm) |
| `0x004214f0` | `FUN_004214f0` |  | [decompiled](decompiled/004214f0.c) | [assembly](decompiled/004214f0.asm) |
| `0x0042151c` | `FUN_0042151c` |  | [decompiled](decompiled/0042151c.c) | [assembly](decompiled/0042151c.asm) |
| `0x00421548` | `FUN_00421548` |  | [decompiled](decompiled/00421548.c) | [assembly](decompiled/00421548.asm) |
| `0x00421574` | `root_00421574` |  | [decompiled](decompiled/00421574.c) | [assembly](decompiled/00421574.asm) |
| `0x0042159c` | `root_0042159c` | Forms.TForm.SetParent | [decompiled](decompiled/0042159c.c) | [assembly](decompiled/0042159c.asm) |
| `0x004215d4` | `root_004215d4` |  | [decompiled](decompiled/004215d4.c) | [assembly](decompiled/004215d4.asm) |
| `0x00421610` | `root_00421610` |  | [decompiled](decompiled/00421610.c) | [assembly](decompiled/00421610.asm) |
| `0x0042181c` | `FUN_0042181c` |  | [decompiled](decompiled/0042181c.c) | [assembly](decompiled/0042181c.asm) |
| `0x00421868` | `root_00421868` | Forms.TForm.ClientWndProc | [decompiled](decompiled/00421868.c) | [assembly](decompiled/00421868.asm) |
| `0x004218e0` | `root_004218e0` |  | [decompiled](decompiled/004218e0.c) | [assembly](decompiled/004218e0.asm) |
| `0x00421920` | `root_00421920` |  | [decompiled](decompiled/00421920.c) | [assembly](decompiled/00421920.asm) |
| `0x0042194c` | `FUN_0042194c` |  | [decompiled](decompiled/0042194c.c) | [assembly](decompiled/0042194c.asm) |
| `0x00421984` | `FUN_00421984` |  | [decompiled](decompiled/00421984.c) | [assembly](decompiled/00421984.asm) |
| `0x004219b8` | `FUN_004219b8` |  | [decompiled](decompiled/004219b8.c) | [assembly](decompiled/004219b8.asm) |
| `0x00421a04` | `FUN_00421a04` |  | [decompiled](decompiled/00421a04.c) | [assembly](decompiled/00421a04.asm) |
| `0x00421a54` | `FUN_00421a54` |  | [decompiled](decompiled/00421a54.c) | [assembly](decompiled/00421a54.asm) |
| `0x00421a5c` | `root_00421a5c` |  | [decompiled](decompiled/00421a5c.c) | [assembly](decompiled/00421a5c.asm) |
| `0x00421a68` | `root_00421a68` | Forms.TForm.IsColorStored | [decompiled](decompiled/00421a68.c) | [assembly](decompiled/00421a68.asm) |
| `0x00421a94` | `FUN_00421a94` |  | [decompiled](decompiled/00421a94.c) | [assembly](decompiled/00421a94.asm) |
| `0x00421a9c` | `root_00421a9c` |  | [decompiled](decompiled/00421a9c.c) | [assembly](decompiled/00421a9c.asm) |
| `0x00421ac4` | `root_00421ac4` |  | [decompiled](decompiled/00421ac4.c) | [assembly](decompiled/00421ac4.asm) |
| `0x00421b44` | `FUN_00421b44` |  | [decompiled](decompiled/00421b44.c) | [assembly](decompiled/00421b44.asm) |
| `0x00421bc0` | `root_00421bc0` |  | [decompiled](decompiled/00421bc0.c) | [assembly](decompiled/00421bc0.asm) |
| `0x00421bd4` | `FUN_00421bd4` |  | [decompiled](decompiled/00421bd4.c) | [assembly](decompiled/00421bd4.asm) |
| `0x00421bfc` | `FUN_00421bfc` |  | [decompiled](decompiled/00421bfc.c) | [assembly](decompiled/00421bfc.asm) |
| `0x00421d7c` | `FUN_00421d7c` |  | [decompiled](decompiled/00421d7c.c) | [assembly](decompiled/00421d7c.asm) |
| `0x00421d90` | `root_00421d90` |  | [decompiled](decompiled/00421d90.c) | [assembly](decompiled/00421d90.asm) |
| `0x00421dc4` | `FUN_00421dc4` |  | [decompiled](decompiled/00421dc4.c) | [assembly](decompiled/00421dc4.asm) |
| `0x00421de0` | `root_00421de0` |  | [decompiled](decompiled/00421de0.c) | [assembly](decompiled/00421de0.asm) |
| `0x00421dec` | `root_00421dec` |  | [decompiled](decompiled/00421dec.c) | [assembly](decompiled/00421dec.asm) |
| `0x00421e1c` | `root_00421e1c` |  | [decompiled](decompiled/00421e1c.c) | [assembly](decompiled/00421e1c.asm) |
| `0x00421e40` | `root_00421e40` |  | [decompiled](decompiled/00421e40.c) | [assembly](decompiled/00421e40.asm) |
| `0x00421e58` | `root_00421e58` | Forms.TForm.CMCtl3DChanged | [decompiled](decompiled/00421e58.c) | [assembly](decompiled/00421e58.asm) |
| `0x00421ea0` | `FUN_00421ea0` |  | [decompiled](decompiled/00421ea0.c) | [assembly](decompiled/00421ea0.asm) |
| `0x00421ec0` | `root_00421ec0` |  | [decompiled](decompiled/00421ec0.c) | [assembly](decompiled/00421ec0.asm) |
| `0x00421edc` | `FUN_00421edc` |  | [decompiled](decompiled/00421edc.c) | [assembly](decompiled/00421edc.asm) |
| `0x00421f1c` | `FUN_00421f1c` |  | [decompiled](decompiled/00421f1c.c) | [assembly](decompiled/00421f1c.asm) |
| `0x004220f8` | `root_004220f8` |  | [decompiled](decompiled/004220f8.c) | [assembly](decompiled/004220f8.asm) |
| `0x00422234` | `root_00422234` |  | [decompiled](decompiled/00422234.c) | [assembly](decompiled/00422234.asm) |
| `0x004222fc` | `FUN_004222fc` |  | [decompiled](decompiled/004222fc.c) | [assembly](decompiled/004222fc.asm) |
| `0x00422340` | `root_00422340` |  | [decompiled](decompiled/00422340.c) | [assembly](decompiled/00422340.asm) |
| `0x004223a4` | `FUN_004223a4` |  | [decompiled](decompiled/004223a4.c) | [assembly](decompiled/004223a4.asm) |
| `0x0042240c` | `FUN_0042240c` |  | [decompiled](decompiled/0042240c.c) | [assembly](decompiled/0042240c.asm) |
| `0x00422454` | `FUN_00422454` |  | [decompiled](decompiled/00422454.c) | [assembly](decompiled/00422454.asm) |
| `0x00422478` | `FUN_00422478` |  | [decompiled](decompiled/00422478.c) | [assembly](decompiled/00422478.asm) |
| `0x00422691` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00422691.c) | [assembly](decompiled/00422691.asm) |
| `0x00422696` | `root_00422696` |  | [decompiled](decompiled/00422696.c) | [assembly](decompiled/00422696.asm) |
| `0x004226b0` | `root_004226b0` |  | [decompiled](decompiled/004226b0.c) | [assembly](decompiled/004226b0.asm) |
| `0x004226b4` | `FUN_004226b4` |  | [decompiled](decompiled/004226b4.c) | [assembly](decompiled/004226b4.asm) |
| `0x00422704` | `root_00422704` |  | [decompiled](decompiled/00422704.c) | [assembly](decompiled/00422704.asm) |
| `0x00422768` | `FUN_00422768` |  | [decompiled](decompiled/00422768.c) | [assembly](decompiled/00422768.asm) |
| `0x004227b8` | `FUN_004227b8` |  | [decompiled](decompiled/004227b8.c) | [assembly](decompiled/004227b8.asm) |
| `0x004228c4` | `root_004228c4` |  | [decompiled](decompiled/004228c4.c) | [assembly](decompiled/004228c4.asm) |
| `0x004228e0` | `root_004228e0` | ColorGrd.TColorGrid.Change | [decompiled](decompiled/004228e0.c) | [assembly](decompiled/004228e0.asm) |
| `0x004228fc` | `root_004228fc` |  | [decompiled](decompiled/004228fc.c) | [assembly](decompiled/004228fc.asm) |
| `0x00422918` | `root_00422918` | Calendar.TCalendar.Change | [decompiled](decompiled/00422918.c) | [assembly](decompiled/00422918.asm) |
| `0x00422934` | `FUN_00422934` |  | [decompiled](decompiled/00422934.c) | [assembly](decompiled/00422934.asm) |
| `0x00422950` | `root_00422950` |  | [decompiled](decompiled/00422950.c) | [assembly](decompiled/00422950.asm) |
| `0x004229b2` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004229b2.c) | [assembly](decompiled/004229b2.asm) |
| `0x004229b7` | `root_004229b7` |  | [decompiled](decompiled/004229b7.c) | [assembly](decompiled/004229b7.asm) |
| `0x004229c0` | `root_004229c0` | Forms.TForm.PaletteChanged | [decompiled](decompiled/004229c0.c) | [assembly](decompiled/004229c0.asm) |
| `0x00422a6c` | `root_00422a6c` | Forms.TForm.WMPaint | [decompiled](decompiled/00422a6c.c) | [assembly](decompiled/00422a6c.asm) |
| `0x00422ac8` | `root_00422ac8` |  | [decompiled](decompiled/00422ac8.c) | [assembly](decompiled/00422ac8.asm) |
| `0x00422b28` | `root_00422b28` |  | [decompiled](decompiled/00422b28.c) | [assembly](decompiled/00422b28.asm) |
| `0x00422b60` | `root_00422b60` |  | [decompiled](decompiled/00422b60.c) | [assembly](decompiled/00422b60.asm) |
| `0x00422b74` | `FUN_00422b74` |  | [decompiled](decompiled/00422b74.c) | [assembly](decompiled/00422b74.asm) |
| `0x00422c70` | `root_00422c70` |  | [decompiled](decompiled/00422c70.c) | [assembly](decompiled/00422c70.asm) |
| `0x00422ca4` | `root_00422ca4` |  | [decompiled](decompiled/00422ca4.c) | [assembly](decompiled/00422ca4.asm) |
| `0x00422d04` | `root_00422d04` |  | [decompiled](decompiled/00422d04.c) | [assembly](decompiled/00422d04.asm) |
| `0x00422d38` | `root_00422d38` |  | [decompiled](decompiled/00422d38.c) | [assembly](decompiled/00422d38.asm) |
| `0x00422d50` | `root_00422d50` |  | [decompiled](decompiled/00422d50.c) | [assembly](decompiled/00422d50.asm) |
| `0x00422dee` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00422dee.c) | [assembly](decompiled/00422dee.asm) |
| `0x00422df3` | `root_00422df3` |  | [decompiled](decompiled/00422df3.c) | [assembly](decompiled/00422df3.asm) |
| `0x00422dfc` | `root_00422dfc` |  | [decompiled](decompiled/00422dfc.c) | [assembly](decompiled/00422dfc.asm) |
| `0x00422e1c` | `root_00422e1c` |  | [decompiled](decompiled/00422e1c.c) | [assembly](decompiled/00422e1c.asm) |
| `0x00422e84` | `root_00422e84` |  | [decompiled](decompiled/00422e84.c) | [assembly](decompiled/00422e84.asm) |
| `0x00422e8c` | `root_00422e8c` | Forms.TForm.WMQueryEndSession | [decompiled](decompiled/00422e8c.c) | [assembly](decompiled/00422e8c.asm) |
| `0x00422ea4` | `root_00422ea4` |  | [decompiled](decompiled/00422ea4.c) | [assembly](decompiled/00422ea4.asm) |
| `0x00422efc` | `root_00422efc` | Forms.TForm.WMSysCommand | [decompiled](decompiled/00422efc.c) | [assembly](decompiled/00422efc.asm) |
| `0x00422f2c` | `root_00422f2c` |  | [decompiled](decompiled/00422f2c.c) | [assembly](decompiled/00422f2c.asm) |
| `0x00422fc4` | `root_00422fc4` |  | [decompiled](decompiled/00422fc4.c) | [assembly](decompiled/00422fc4.asm) |
| `0x0042301c` | `root_0042301c` |  | [decompiled](decompiled/0042301c.c) | [assembly](decompiled/0042301c.asm) |
| `0x00423048` | `root_00423048` | Forms.TForm.WMEnterMenuLoop | [decompiled](decompiled/00423048.c) | [assembly](decompiled/00423048.asm) |
| `0x00423064` | `FUN_00423064` | Forms.GetMenuHelpContext | [decompiled](decompiled/00423064.c) | [assembly](decompiled/00423064.asm) |
| `0x004230a4` | `FUN_004230a4` |  | [decompiled](decompiled/004230a4.c) | [assembly](decompiled/004230a4.asm) |
| `0x0042312c` | `root_0042312c` |  | [decompiled](decompiled/0042312c.c) | [assembly](decompiled/0042312c.asm) |
| `0x00423138` | `FUN_00423138` |  | [decompiled](decompiled/00423138.c) | [assembly](decompiled/00423138.asm) |
| `0x0042314c` | `root_0042314c` |  | [decompiled](decompiled/0042314c.c) | [assembly](decompiled/0042314c.asm) |
| `0x004231e8` | `root_004231e8` |  | [decompiled](decompiled/004231e8.c) | [assembly](decompiled/004231e8.asm) |
| `0x00423276` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00423276.c) | [assembly](decompiled/00423276.asm) |
| `0x0042327b` | `root_0042327b` |  | [decompiled](decompiled/0042327b.c) | [assembly](decompiled/0042327b.asm) |
| `0x00423451` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00423451.c) | [assembly](decompiled/00423451.asm) |
| `0x00423456` | `root_00423456` |  | [decompiled](decompiled/00423456.c) | [assembly](decompiled/00423456.asm) |
| `0x0042354a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042354a.c) | [assembly](decompiled/0042354a.asm) |
| `0x0042354f` | `root_0042354f` |  | [decompiled](decompiled/0042354f.c) | [assembly](decompiled/0042354f.asm) |
| `0x00423558` | `FUN_00423558` |  | [decompiled](decompiled/00423558.c) | [assembly](decompiled/00423558.asm) |
| `0x00423578` | `root_00423578` |  | [decompiled](decompiled/00423578.c) | [assembly](decompiled/00423578.asm) |
| `0x00423580` | `root_00423580` |  | [decompiled](decompiled/00423580.c) | [assembly](decompiled/00423580.asm) |
| `0x004235d0` | `root_004235d0` |  | [decompiled](decompiled/004235d0.c) | [assembly](decompiled/004235d0.asm) |
| `0x004235d8` | `FUN_004235d8` |  | [decompiled](decompiled/004235d8.c) | [assembly](decompiled/004235d8.asm) |
| `0x00423680` | `FUN_00423680` |  | [decompiled](decompiled/00423680.c) | [assembly](decompiled/00423680.asm) |
| `0x004236e0` | `FUN_004236e0` |  | [decompiled](decompiled/004236e0.c) | [assembly](decompiled/004236e0.asm) |
| `0x0042375c` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0042375c.c) | [assembly](decompiled/0042375c.asm) |
| `0x00423761` | `root_00423761` |  | [decompiled](decompiled/00423761.c) | [assembly](decompiled/00423761.asm) |
| `0x00423788` | `FUN_00423788` |  | [decompiled](decompiled/00423788.c) | [assembly](decompiled/00423788.asm) |
| `0x00423790` | `FUN_00423790` |  | [decompiled](decompiled/00423790.c) | [assembly](decompiled/00423790.asm) |
| `0x004237a8` | `root_004237a8` |  | [decompiled](decompiled/004237a8.c) | [assembly](decompiled/004237a8.asm) |
| `0x004237dc` | `FUN_004237dc` |  | [decompiled](decompiled/004237dc.c) | [assembly](decompiled/004237dc.asm) |
| `0x0042396f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042396f.c) | [assembly](decompiled/0042396f.asm) |
| `0x00423974` | `root_00423974` |  | [decompiled](decompiled/00423974.c) | [assembly](decompiled/00423974.asm) |
| `0x00423983` | `FUN_00423983` |  | [decompiled](decompiled/00423983.c) | [assembly](decompiled/00423983.asm) |
| `0x004239c6` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004239c6.c) | [assembly](decompiled/004239c6.asm) |
| `0x004239cb` | `thunk_FUN_00423983` |  | [decompiled](decompiled/004239cb.c) | [assembly](decompiled/004239cb.asm) |
| `0x004239d8` | `FUN_004239d8` | Forms.TForm.Release | [decompiled](decompiled/004239d8.c) | [assembly](decompiled/004239d8.asm) |
| `0x004239f4` | `FUN_004239f4` | Forms.EnumFontsProc, Printers.EnumFontsProc | [decompiled](decompiled/004239f4.c) | [assembly](decompiled/004239f4.asm) |
| `0x00423a43` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00423a43.c) | [assembly](decompiled/00423a43.asm) |
| `0x00423a48` | `root_00423a48` |  | [decompiled](decompiled/00423a48.c) | [assembly](decompiled/00423a48.asm) |
| `0x00423a54` | `FUN_00423a54` |  | [decompiled](decompiled/00423a54.c) | [assembly](decompiled/00423a54.asm) |
| `0x00423b60` | `root_00423b60` | Forms.TScreen.Destroy | [decompiled](decompiled/00423b60.c) | [assembly](decompiled/00423b60.asm) |
| `0x00423ba0` | `FUN_00423ba0` |  | [decompiled](decompiled/00423ba0.c) | [assembly](decompiled/00423ba0.asm) |
| `0x00423ba8` | `FUN_00423ba8` |  | [decompiled](decompiled/00423ba8.c) | [assembly](decompiled/00423ba8.asm) |
| `0x00423bb0` | `FUN_00423bb0` |  | [decompiled](decompiled/00423bb0.c) | [assembly](decompiled/00423bb0.asm) |
| `0x00423bbc` | `FUN_00423bbc` |  | [decompiled](decompiled/00423bbc.c) | [assembly](decompiled/00423bbc.asm) |
| `0x00423bc4` | `FUN_00423bc4` | Forms.TScreen.UpdateLastActive | [decompiled](decompiled/00423bc4.c) | [assembly](decompiled/00423bc4.asm) |
| `0x00423c00` | `FUN_00423c00` |  | [decompiled](decompiled/00423c00.c) | [assembly](decompiled/00423c00.asm) |
| `0x00423c0c` | `FUN_00423c0c` | Forms.TScreen.RemoveForm | [decompiled](decompiled/00423c0c.c) | [assembly](decompiled/00423c0c.asm) |
| `0x00423c3c` | `FUN_00423c3c` | Forms.TScreen.CreateCursors | [decompiled](decompiled/00423c3c.c) | [assembly](decompiled/00423c3c.asm) |
| `0x00423c94` | `FUN_00423c94` | Forms.TScreen.DestroyCursors | [decompiled](decompiled/00423c94.c) | [assembly](decompiled/00423c94.asm) |
| `0x00423ce8` | `FUN_00423ce8` | Forms.TScreen.InsertCursor | [decompiled](decompiled/00423ce8.c) | [assembly](decompiled/00423ce8.asm) |
| `0x00423d10` | `FUN_00423d10` |  | [decompiled](decompiled/00423d10.c) | [assembly](decompiled/00423d10.asm) |
| `0x00423d1c` | `FUN_00423d1c` |  | [decompiled](decompiled/00423d1c.c) | [assembly](decompiled/00423d1c.asm) |
| `0x00423d24` | `FUN_00423d24` | Forms.TScreen.GetCursors | [decompiled](decompiled/00423d24.c) | [assembly](decompiled/00423d24.asm) |
| `0x00423d4c` | `FUN_00423d4c` | Forms.TScreen.SetCursor | [decompiled](decompiled/00423d4c.c) | [assembly](decompiled/00423d4c.asm) |
| `0x00423dd8` | `FUN_00423dd8` | Forms.GetHint | [decompiled](decompiled/00423dd8.c) | [assembly](decompiled/00423dd8.asm) |
| `0x00423e08` | `thunk_FUN_00423e0d` | Forms.GetHintControl | [decompiled](decompiled/00423e08.c) | [assembly](decompiled/00423e08.asm) |
| `0x00423e0d` | `FUN_00423e0d` |  | [decompiled](decompiled/00423e0d.c) | [assembly](decompiled/00423e0d.asm) |
| `0x00423e24` | `FUN_00423e24` |  | [decompiled](decompiled/00423e24.c) | [assembly](decompiled/00423e24.asm) |
| `0x00423e40` | `root_00423e40` | Forms.HintMouseThread | [decompiled](decompiled/00423e40.c) | [assembly](decompiled/00423e40.asm) |
| `0x00423e90` | `root_00423e90` | Forms.HintGetMsgHook | [decompiled](decompiled/00423e90.c) | [assembly](decompiled/00423e90.asm) |
| `0x00423ed4` | `FUN_00423ed4` | Forms.HookHintHooks | [decompiled](decompiled/00423ed4.c) | [assembly](decompiled/00423ed4.asm) |
| `0x00423f2c` | `FUN_00423f2c` | Forms.UnhookHintHooks | [decompiled](decompiled/00423f2c.c) | [assembly](decompiled/00423f2c.asm) |
| `0x00423f68` | `FUN_00423f68` | Forms.GetAnimation | [decompiled](decompiled/00423f68.c) | [assembly](decompiled/00423f68.asm) |
| `0x00423f98` | `FUN_00423f98` | Forms.SetAnimation | [decompiled](decompiled/00423f98.c) | [assembly](decompiled/00423f98.asm) |
| `0x00423fbc` | `FUN_00423fbc` | Forms.ShowWinNoAnimate | [decompiled](decompiled/00423fbc.c) | [assembly](decompiled/00423fbc.asm) |
| `0x00423ffc` | `FUN_00423ffc` | Forms.TApplication.Create | [decompiled](decompiled/00423ffc.c) | [assembly](decompiled/00423ffc.asm) |
| `0x00424160` | `root_00424160` | Forms.TApplication.Destroy | [decompiled](decompiled/00424160.c) | [assembly](decompiled/00424160.asm) |
| `0x004241e4` | `FUN_004241e4` | Forms.TApplication.CreateHandle | [decompiled](decompiled/004241e4.c) | [assembly](decompiled/004241e4.asm) |
| `0x0042431c` | `FUN_0042431c` | Forms.TApplication.ControlDestroyed | [decompiled](decompiled/0042431c.c) | [assembly](decompiled/0042431c.asm) |
| `0x0042438c` | `root_0042438c` | Forms.GetTopMostWindows | [decompiled](decompiled/0042438c.c) | [assembly](decompiled/0042438c.asm) |
| `0x004243f4` | `FUN_004243f4` | Forms.TApplication.NormalizeTopMosts | [decompiled](decompiled/004243f4.c) | [assembly](decompiled/004243f4.asm) |
| `0x00424484` | `FUN_00424484` | Forms.TApplication.RestoreTopMosts | [decompiled](decompiled/00424484.c) | [assembly](decompiled/00424484.asm) |
| `0x004244d8` | `FUN_004244d8` | Forms.TApplication.CheckIniChange | [decompiled](decompiled/004244d8.c) | [assembly](decompiled/004244d8.asm) |
| `0x004244f4` | `FUN_004244f4` | Forms.Default | [decompiled](decompiled/004244f4.c) | [assembly](decompiled/004244f4.asm) |
| `0x00424530` | `FUN_00424530` | Forms.DrawAppIcon | [decompiled](decompiled/00424530.c) | [assembly](decompiled/00424530.asm) |
| `0x00424acc` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00424acc.c) | [assembly](decompiled/00424acc.asm) |
| `0x00424ad1` | `root_00424ad1` |  | [decompiled](decompiled/00424ad1.c) | [assembly](decompiled/00424ad1.asm) |
| `0x00424ae8` | `FUN_00424ae8` | Forms.TApplication.GetIconHandle | [decompiled](decompiled/00424ae8.c) | [assembly](decompiled/00424ae8.asm) |
| `0x00424b04` | `FUN_00424b04` | Forms.TApplication.Minimize | [decompiled](decompiled/00424b04.c) | [assembly](decompiled/00424b04.asm) |
| `0x00424b4c` | `FUN_00424b4c` | Forms.TApplication.Restore | [decompiled](decompiled/00424b4c.c) | [assembly](decompiled/00424b4c.asm) |
| `0x00424bb0` | `FUN_00424bb0` | Forms.TApplication.BringToFront | [decompiled](decompiled/00424bb0.c) | [assembly](decompiled/00424bb0.asm) |
| `0x00424bec` | `FUN_00424bec` | Forms.TApplication.GetTitle | [decompiled](decompiled/00424bec.c) | [assembly](decompiled/00424bec.asm) |
| `0x00424c34` | `FUN_00424c34` | Forms.TApplication.SetTitle | [decompiled](decompiled/00424c34.c) | [assembly](decompiled/00424c34.asm) |
| `0x00424c64` | `FUN_00424c64` | Forms.TApplication.IsDlgMsg | [decompiled](decompiled/00424c64.c) | [assembly](decompiled/00424c64.asm) |
| `0x00424c88` | `FUN_00424c88` |  | [decompiled](decompiled/00424c88.c) | [assembly](decompiled/00424c88.asm) |
| `0x00424cd8` | `FUN_00424cd8` |  | [decompiled](decompiled/00424cd8.c) | [assembly](decompiled/00424cd8.asm) |
| `0x00424d3c` | `FUN_00424d3c` |  | [decompiled](decompiled/00424d3c.c) | [assembly](decompiled/00424d3c.asm) |
| `0x00424d6c` | `FUN_00424d6c` | Forms.TApplication.ProcessMessage | [decompiled](decompiled/00424d6c.c) | [assembly](decompiled/00424d6c.asm) |
| `0x00424e1c` | `FUN_00424e1c` |  | [decompiled](decompiled/00424e1c.c) | [assembly](decompiled/00424e1c.asm) |
| `0x00424e34` | `FUN_00424e34` | Forms.TApplication.HookMainWindow | [decompiled](decompiled/00424e34.c) | [assembly](decompiled/00424e34.asm) |
| `0x00424e8c` | `FUN_00424e8c` | Forms.TApplication.UnhookMainWindow | [decompiled](decompiled/00424e8c.c) | [assembly](decompiled/00424e8c.asm) |
| `0x00424f08` | `FUN_00424f08` |  | [decompiled](decompiled/00424f08.c) | [assembly](decompiled/00424f08.asm) |
| `0x00424f18` | `FUN_00424f18` | Forms.TApplication.CreateForm | [decompiled](decompiled/00424f18.c) | [assembly](decompiled/00424f18.asm) |
| `0x00424f5c` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00424f5c.c) | [assembly](decompiled/00424f5c.asm) |
| `0x00424f61` | `root_00424f61` |  | [decompiled](decompiled/00424f61.c) | [assembly](decompiled/00424f61.asm) |
| `0x00424fa8` | `FUN_00424fa8` | Forms.TApplication.Run | [decompiled](decompiled/00424fa8.c) | [assembly](decompiled/00424fa8.asm) |
| `0x0042500e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042500e.c) | [assembly](decompiled/0042500e.asm) |
| `0x00425013` | `root_00425013` |  | [decompiled](decompiled/00425013.c) | [assembly](decompiled/00425013.asm) |
| `0x00425018` | `FUN_00425018` |  | [decompiled](decompiled/00425018.c) | [assembly](decompiled/00425018.asm) |
| `0x00425020` | `root_00425020` | Forms.TApplication.HandleException | [decompiled](decompiled/00425020.c) | [assembly](decompiled/00425020.asm) |
| `0x004250ac` | `FUN_004250ac` | Forms.TApplication.MessageBox | [decompiled](decompiled/004250ac.c) | [assembly](decompiled/004250ac.asm) |
| `0x0042510d` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042510d.c) | [assembly](decompiled/0042510d.asm) |
| `0x00425112` | `root_00425112` |  | [decompiled](decompiled/00425112.c) | [assembly](decompiled/00425112.asm) |
| `0x00425120` | `FUN_00425120` | Forms.TApplication.ShowException | [decompiled](decompiled/00425120.c) | [assembly](decompiled/00425120.asm) |
| `0x00425196` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00425196.c) | [assembly](decompiled/00425196.asm) |
| `0x0042519b` | `root_0042519b` |  | [decompiled](decompiled/0042519b.c) | [assembly](decompiled/0042519b.asm) |
| `0x004251b0` | `FUN_004251b0` | Forms.TApplication.InvokeHelp | [decompiled](decompiled/004251b0.c) | [assembly](decompiled/004251b0.asm) |
| `0x0042524c` | `FUN_0042524c` |  | [decompiled](decompiled/0042524c.c) | [assembly](decompiled/0042524c.asm) |
| `0x00425258` | `FUN_00425258` |  | [decompiled](decompiled/00425258.c) | [assembly](decompiled/00425258.asm) |
| `0x00425260` | `FUN_00425260` | Forms.TApplication.SetShowHint | [decompiled](decompiled/00425260.c) | [assembly](decompiled/00425260.asm) |
| `0x004252a0` | `FUN_004252a0` | Forms.TApplication.Idle | [decompiled](decompiled/004252a0.c) | [assembly](decompiled/004252a0.asm) |
| `0x004253b9` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004253b9.c) | [assembly](decompiled/004253b9.asm) |
| `0x004253be` | `root_004253be` |  | [decompiled](decompiled/004253be.c) | [assembly](decompiled/004253be.asm) |
| `0x004253c8` | `FUN_004253c8` | Forms.TApplication.NotifyForms | [decompiled](decompiled/004253c8.c) | [assembly](decompiled/004253c8.asm) |
| `0x00425404` | `root_00425404` | Forms.TApplication.IconChanged | [decompiled](decompiled/00425404.c) | [assembly](decompiled/00425404.asm) |
| `0x00425454` | `FUN_00425454` | Forms.TApplication.SetHint | [decompiled](decompiled/00425454.c) | [assembly](decompiled/00425454.asm) |
| `0x0042548c` | `FUN_0042548c` | Forms.TApplication.StartHintTimer | [decompiled](decompiled/0042548c.c) | [assembly](decompiled/0042548c.asm) |
| `0x004254d0` | `FUN_004254d0` | Forms.TApplication.StopHintTimer | [decompiled](decompiled/004254d0.c) | [assembly](decompiled/004254d0.asm) |
| `0x004254ec` | `FUN_004254ec` | Forms.TApplication.HintMouseMessage | [decompiled](decompiled/004254ec.c) | [assembly](decompiled/004254ec.asm) |
| `0x004255a8` | `FUN_004255a8` | Forms.TApplication.HintTimerExpired | [decompiled](decompiled/004255a8.c) | [assembly](decompiled/004255a8.asm) |
| `0x004255dc` | `FUN_004255dc` | Forms.TApplication.HideHint | [decompiled](decompiled/004255dc.c) | [assembly](decompiled/004255dc.asm) |
| `0x00425618` | `FUN_00425618` | Forms.TApplication.CancelHint | [decompiled](decompiled/00425618.c) | [assembly](decompiled/00425618.asm) |
| `0x00425640` | `FUN_00425640` |  | [decompiled](decompiled/00425640.c) | [assembly](decompiled/00425640.asm) |
| `0x00425892` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00425892.c) | [assembly](decompiled/00425892.asm) |
| `0x00425897` | `root_00425897` |  | [decompiled](decompiled/00425897.c) | [assembly](decompiled/00425897.asm) |
| `0x004258a0` | `FUN_004258a0` |  | [decompiled](decompiled/004258a0.c) | [assembly](decompiled/004258a0.asm) |
| `0x00427ee0` | `FUN_00427ee0` | StdCtrls.HasPopup | [decompiled](decompiled/00427ee0.c) | [assembly](decompiled/00427ee0.asm) |
| `0x00428174` | `FUN_00428174` | StdCtrls.TCustomLabel.Create | [decompiled](decompiled/00428174.c) | [assembly](decompiled/00428174.asm) |
| `0x004281dc` | `root_004281dc` |  | [decompiled](decompiled/004281dc.c) | [assembly](decompiled/004281dc.asm) |
| `0x004281f0` | `FUN_004281f0` | StdCtrls.TCustomLabel.DoDrawText | [decompiled](decompiled/004281f0.c) | [assembly](decompiled/004281f0.asm) |
| `0x004282bd` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004282bd.c) | [assembly](decompiled/004282bd.asm) |
| `0x004282c2` | `root_004282c2` |  | [decompiled](decompiled/004282c2.c) | [assembly](decompiled/004282c2.asm) |
| `0x004282d8` | `root_004282d8` |  | [decompiled](decompiled/004282d8.c) | [assembly](decompiled/004282d8.asm) |
| `0x00428364` | `FUN_00428364` |  | [decompiled](decompiled/00428364.c) | [assembly](decompiled/00428364.asm) |
| `0x00428404` | `root_00428404` | StdCtrls.TCustomLabel.SetAlignment | [decompiled](decompiled/00428404.c) | [assembly](decompiled/00428404.asm) |
| `0x00428418` | `root_00428418` | StdCtrls.TCustomLabel.SetAutoSize | [decompiled](decompiled/00428418.c) | [assembly](decompiled/00428418.asm) |
| `0x0042842c` | `FUN_0042842c` |  | [decompiled](decompiled/0042842c.c) | [assembly](decompiled/0042842c.asm) |
| `0x00428438` | `root_00428438` |  | [decompiled](decompiled/00428438.c) | [assembly](decompiled/00428438.asm) |
| `0x0042844c` | `root_0042844c` | StdCtrls.TCustomLabel.SetShowAccelChar | [decompiled](decompiled/0042844c.c) | [assembly](decompiled/0042844c.asm) |
| `0x00428460` | `root_00428460` | StdCtrls.TCustomLabel.SetTransparent | [decompiled](decompiled/00428460.c) | [assembly](decompiled/00428460.asm) |
| `0x004284a4` | `FUN_004284a4` | StdCtrls.TCustomLabel.SetWordWrap | [decompiled](decompiled/004284a4.c) | [assembly](decompiled/004284a4.asm) |
| `0x004284b8` | `FUN_004284b8` | StdCtrls.TCustomLabel.Notification | [decompiled](decompiled/004284b8.c) | [assembly](decompiled/004284b8.asm) |
| `0x004284e8` | `root_004284e8` |  | [decompiled](decompiled/004284e8.c) | [assembly](decompiled/004284e8.asm) |
| `0x004284fc` | `FUN_004284fc` |  | [decompiled](decompiled/004284fc.c) | [assembly](decompiled/004284fc.asm) |
| `0x00428510` | `FUN_00428510` |  | [decompiled](decompiled/00428510.c) | [assembly](decompiled/00428510.asm) |
| `0x00428594` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00428594.c) | [assembly](decompiled/00428594.asm) |
| `0x00428599` | `root_00428599` |  | [decompiled](decompiled/00428599.c) | [assembly](decompiled/00428599.asm) |
| `0x004285a4` | `FUN_004285a4` |  | [decompiled](decompiled/004285a4.c) | [assembly](decompiled/004285a4.asm) |
| `0x00428648` | `FUN_00428648` | StdCtrls.TCustomEdit.SetCharCase | [decompiled](decompiled/00428648.c) | [assembly](decompiled/00428648.asm) |
| `0x0042865c` | `FUN_0042865c` |  | [decompiled](decompiled/0042865c.c) | [assembly](decompiled/0042865c.asm) |
| `0x00428680` | `root_00428680` |  | [decompiled](decompiled/00428680.c) | [assembly](decompiled/00428680.asm) |
| `0x00428694` | `root_00428694` | ComCtrls.TStatusBar.SetSizeGrip | [decompiled](decompiled/00428694.c) | [assembly](decompiled/00428694.asm) |
| `0x004286a8` | `FUN_004286a8` |  | [decompiled](decompiled/004286a8.c) | [assembly](decompiled/004286a8.asm) |
| `0x004286e0` | `root_004286e0` |  | [decompiled](decompiled/004286e0.c) | [assembly](decompiled/004286e0.asm) |
| `0x004286f4` | `FUN_004286f4` |  | [decompiled](decompiled/004286f4.c) | [assembly](decompiled/004286f4.asm) |
| `0x0042872c` | `FUN_0042872c` |  | [decompiled](decompiled/0042872c.c) | [assembly](decompiled/0042872c.asm) |
| `0x00428764` | `root_00428764` |  | [decompiled](decompiled/00428764.c) | [assembly](decompiled/00428764.asm) |
| `0x004287e3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004287e3.c) | [assembly](decompiled/004287e3.asm) |
| `0x004287e8` | `root_004287e8` |  | [decompiled](decompiled/004287e8.c) | [assembly](decompiled/004287e8.asm) |
| `0x004287f0` | `root_004287f0` |  | [decompiled](decompiled/004287f0.c) | [assembly](decompiled/004287f0.asm) |
| `0x0042882c` | `FUN_0042882c` | StdCtrls.TCustomEdit.GetSelStart | [decompiled](decompiled/0042882c.c) | [assembly](decompiled/0042882c.asm) |
| `0x00428850` | `FUN_00428850` | StdCtrls.TCustomEdit.Clear | [decompiled](decompiled/00428850.c) | [assembly](decompiled/00428850.asm) |
| `0x0042886c` | `FUN_0042886c` | StdCtrls.TCustomEdit.SelectAll | [decompiled](decompiled/0042886c.c) | [assembly](decompiled/0042886c.asm) |
| `0x00428888` | `FUN_00428888` |  | [decompiled](decompiled/00428888.c) | [assembly](decompiled/00428888.asm) |
| `0x00428944` | `FUN_00428944` |  | [decompiled](decompiled/00428944.c) | [assembly](decompiled/00428944.asm) |
| `0x00428983` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00428983.c) | [assembly](decompiled/00428983.asm) |
| `0x00428988` | `root_00428988` |  | [decompiled](decompiled/00428988.c) | [assembly](decompiled/00428988.asm) |
| `0x004289f4` | `FUN_004289f4` |  | [decompiled](decompiled/004289f4.c) | [assembly](decompiled/004289f4.asm) |
| `0x00428a10` | `FUN_00428a10` |  | [decompiled](decompiled/00428a10.c) | [assembly](decompiled/00428a10.asm) |
| `0x00428a54` | `FUN_00428a54` | ComCtrls.TCustomHotKey.AdjustHeight, StdCtrls.TCustomEdit.AdjustHeight | [decompiled](decompiled/00428a54.c) | [assembly](decompiled/00428a54.asm) |
| `0x00428afc` | `root_00428afc` | ComCtrls.TCustomTabControl.Change, StdCtrls.TScrollBar.Change | [decompiled](decompiled/00428afc.c) | [assembly](decompiled/00428afc.asm) |
| `0x00428b18` | `root_00428b18` | StdCtrls.TCustomEdit.DefaultHandler | [decompiled](decompiled/00428b18.c) | [assembly](decompiled/00428b18.asm) |
| `0x00428b60` | `root_00428b60` |  | [decompiled](decompiled/00428b60.c) | [assembly](decompiled/00428b60.asm) |
| `0x00428ba0` | `root_00428ba0` |  | [decompiled](decompiled/00428ba0.c) | [assembly](decompiled/00428ba0.asm) |
| `0x00428bd4` | `root_00428bd4` | StdCtrls.TCustomEdit.CMFontChanged | [decompiled](decompiled/00428bd4.c) | [assembly](decompiled/00428bd4.asm) |
| `0x00428bfc` | `root_00428bfc` |  | [decompiled](decompiled/00428bfc.c) | [assembly](decompiled/00428bfc.asm) |
| `0x00428c1c` | `root_00428c1c` |  | [decompiled](decompiled/00428c1c.c) | [assembly](decompiled/00428c1c.asm) |
| `0x00428c58` | `FUN_00428c58` |  | [decompiled](decompiled/00428c58.c) | [assembly](decompiled/00428c58.asm) |
| `0x00428c90` | `FUN_00428c90` | ComCtrls.TRichEditStrings.GetCount, StdCtrls.TMemoStrings.GetCount | [decompiled](decompiled/00428c90.c) | [assembly](decompiled/00428c90.asm) |
| `0x00428ce8` | `root_00428ce8` | StdCtrls.TMemoStrings.Get | [decompiled](decompiled/00428ce8.c) | [assembly](decompiled/00428ce8.asm) |
| `0x00428d2c` | `FUN_00428d2c` | StdCtrls.TMemoStrings.Put | [decompiled](decompiled/00428d2c.c) | [assembly](decompiled/00428d2c.asm) |
| `0x00428da0` | `FUN_00428da0` | StdCtrls.TMemoStrings.Insert | [decompiled](decompiled/00428da0.c) | [assembly](decompiled/00428da0.asm) |
| `0x00428e8b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00428e8b.c) | [assembly](decompiled/00428e8b.asm) |
| `0x00428e90` | `root_00428e90` |  | [decompiled](decompiled/00428e90.c) | [assembly](decompiled/00428e90.asm) |
| `0x00428eac` | `root_00428eac` | StdCtrls.TMemoStrings.Delete | [decompiled](decompiled/00428eac.c) | [assembly](decompiled/00428eac.asm) |
| `0x00428f3c` | `root_00428f3c` |  | [decompiled](decompiled/00428f3c.c) | [assembly](decompiled/00428f3c.asm) |
| `0x00428f48` | `root_00428f48` |  | [decompiled](decompiled/00428f48.c) | [assembly](decompiled/00428f48.asm) |
| `0x00428f84` | `root_00428f84` |  | [decompiled](decompiled/00428f84.c) | [assembly](decompiled/00428f84.asm) |
| `0x00428f98` | `FUN_00428f98` | StdCtrls.TMemoStrings.SetTextStr | [decompiled](decompiled/00428f98.c) | [assembly](decompiled/00428f98.asm) |
| `0x0042904b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042904b.c) | [assembly](decompiled/0042904b.asm) |
| `0x00429050` | `root_00429050` |  | [decompiled](decompiled/00429050.c) | [assembly](decompiled/00429050.asm) |
| `0x0042905c` | `FUN_0042905c` |  | [decompiled](decompiled/0042905c.c) | [assembly](decompiled/0042905c.asm) |
| `0x004290dc` | `FUN_004290dc` | Tabs.TScroller.Destroy | [decompiled](decompiled/004290dc.c) | [assembly](decompiled/004290dc.asm) |
| `0x00429108` | `FUN_00429108` |  | [decompiled](decompiled/00429108.c) | [assembly](decompiled/00429108.asm) |
| `0x00429154` | `FUN_00429154` | StdCtrls.TCustomMemo.CreateWindowHandle | [decompiled](decompiled/00429154.c) | [assembly](decompiled/00429154.asm) |
| `0x004291b0` | `root_004291b0` |  | [decompiled](decompiled/004291b0.c) | [assembly](decompiled/004291b0.asm) |
| `0x004291c8` | `FUN_004291c8` | Buttons.TBitBtn.SetButtonStyle | [decompiled](decompiled/004291c8.c) | [assembly](decompiled/004291c8.asm) |
| `0x004291dc` | `root_004291dc` |  | [decompiled](decompiled/004291dc.c) | [assembly](decompiled/004291dc.asm) |
| `0x004291e8` | `root_004291e8` |  | [decompiled](decompiled/004291e8.c) | [assembly](decompiled/004291e8.asm) |
| `0x004291fc` | `root_004291fc` |  | [decompiled](decompiled/004291fc.c) | [assembly](decompiled/004291fc.asm) |
| `0x00429210` | `root_00429210` |  | [decompiled](decompiled/00429210.c) | [assembly](decompiled/00429210.asm) |
| `0x00429244` | `root_00429244` |  | [decompiled](decompiled/00429244.c) | [assembly](decompiled/00429244.asm) |
| `0x0042924c` | `root_0042924c` |  | [decompiled](decompiled/0042924c.c) | [assembly](decompiled/0042924c.asm) |
| `0x00429270` | `FUN_00429270` | StdCtrls.TComboBoxStrings.GetCount | [decompiled](decompiled/00429270.c) | [assembly](decompiled/00429270.asm) |
| `0x0042928c` | `FUN_0042928c` | StdCtrls.TComboBoxStrings.Get | [decompiled](decompiled/0042928c.c) | [assembly](decompiled/0042928c.asm) |
| `0x004292d0` | `root_004292d0` | StdCtrls.TComboBoxStrings.GetObject | [decompiled](decompiled/004292d0.c) | [assembly](decompiled/004292d0.asm) |
| `0x004292f0` | `FUN_004292f0` | StdCtrls.TComboBoxStrings.PutObject | [decompiled](decompiled/004292f0.c) | [assembly](decompiled/004292f0.asm) |
| `0x00429314` | `root_00429314` | StdCtrls.TComboBoxStrings.Add | [decompiled](decompiled/00429314.c) | [assembly](decompiled/00429314.asm) |
| `0x00429354` | `FUN_00429354` | StdCtrls.TComboBoxStrings.Insert | [decompiled](decompiled/00429354.c) | [assembly](decompiled/00429354.asm) |
| `0x00429398` | `root_00429398` | StdCtrls.TComboBoxStrings.Delete | [decompiled](decompiled/00429398.c) | [assembly](decompiled/00429398.asm) |
| `0x004293b8` | `FUN_004293b8` | StdCtrls.TComboBoxStrings.Clear | [decompiled](decompiled/004293b8.c) | [assembly](decompiled/004293b8.asm) |
| `0x0042941b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042941b.c) | [assembly](decompiled/0042941b.asm) |
| `0x00429420` | `root_00429420` |  | [decompiled](decompiled/00429420.c) | [assembly](decompiled/00429420.asm) |
| `0x00429428` | `root_00429428` | ComCtrls.TRichEditStrings.SetUpdateState, StdCtrls.TComboBoxStrings.SetUpdateState, StdCtrls.TListBoxStrings.SetUpdateState, StdCtrls.TMemoStrings.SetUpdateState | [decompiled](decompiled/00429428.c) | [assembly](decompiled/00429428.asm) |
| `0x0042945c` | `FUN_0042945c` |  | [decompiled](decompiled/0042945c.c) | [assembly](decompiled/0042945c.asm) |
| `0x0042954c` | `FUN_0042954c` |  | [decompiled](decompiled/0042954c.c) | [assembly](decompiled/0042954c.asm) |
| `0x004295b4` | `FUN_004295b4` |  | [decompiled](decompiled/004295b4.c) | [assembly](decompiled/004295b4.asm) |
| `0x004295d4` | `FUN_004295d4` | StdCtrls.TCustomComboBox.GetDroppedDown | [decompiled](decompiled/004295d4.c) | [assembly](decompiled/004295d4.asm) |
| `0x004295f8` | `FUN_004295f8` | StdCtrls.TCustomComboBox.SetDroppedDown | [decompiled](decompiled/004295f8.c) | [assembly](decompiled/004295f8.asm) |
| `0x0042961c` | `FUN_0042961c` | StdCtrls.TCustomComboBox.GetItemIndex | [decompiled](decompiled/0042961c.c) | [assembly](decompiled/0042961c.asm) |
| `0x00429638` | `FUN_00429638` | StdCtrls.TCustomComboBox.SetItemIndex | [decompiled](decompiled/00429638.c) | [assembly](decompiled/00429638.asm) |
| `0x00429658` | `root_00429658` |  | [decompiled](decompiled/00429658.c) | [assembly](decompiled/00429658.asm) |
| `0x0042969c` | `FUN_0042969c` |  | [decompiled](decompiled/0042969c.c) | [assembly](decompiled/0042969c.asm) |
| `0x004296c0` | `FUN_004296c0` |  | [decompiled](decompiled/004296c0.c) | [assembly](decompiled/004296c0.asm) |
| `0x004296cc` | `root_004296cc` |  | [decompiled](decompiled/004296cc.c) | [assembly](decompiled/004296cc.asm) |
| `0x0042973c` | `FUN_0042973c` |  | [decompiled](decompiled/0042973c.c) | [assembly](decompiled/0042973c.asm) |
| `0x00429864` | `root_00429864` |  | [decompiled](decompiled/00429864.c) | [assembly](decompiled/00429864.asm) |
| `0x004298a4` | `root_004298a4` |  | [decompiled](decompiled/004298a4.c) | [assembly](decompiled/004298a4.asm) |
| `0x004298c4` | `root_004298c4` |  | [decompiled](decompiled/004298c4.c) | [assembly](decompiled/004298c4.asm) |
| `0x0042990c` | `root_0042990c` |  | [decompiled](decompiled/0042990c.c) | [assembly](decompiled/0042990c.asm) |
| `0x00429918` | `root_00429918` |  | [decompiled](decompiled/00429918.c) | [assembly](decompiled/00429918.asm) |
| `0x00429924` | `root_00429924` |  | [decompiled](decompiled/00429924.c) | [assembly](decompiled/00429924.asm) |
| `0x00429930` | `root_00429930` | StdCtrls.TCustomComboBox.WMGetDlgCode | [decompiled](decompiled/00429930.c) | [assembly](decompiled/00429930.asm) |
| `0x00429954` | `root_00429954` | StdCtrls.TCustomComboBox.CMCancelMode | [decompiled](decompiled/00429954.c) | [assembly](decompiled/00429954.asm) |
| `0x00429968` | `root_00429968` | StdCtrls.TCustomComboBox.CMCtl3DChanged | [decompiled](decompiled/00429968.c) | [assembly](decompiled/00429968.asm) |
| `0x0042998c` | `root_0042998c` |  | [decompiled](decompiled/0042998c.c) | [assembly](decompiled/0042998c.asm) |
| `0x00429a74` | `FUN_00429a74` |  | [decompiled](decompiled/00429a74.c) | [assembly](decompiled/00429a74.asm) |
| `0x00429a94` | `root_00429a94` |  | [decompiled](decompiled/00429a94.c) | [assembly](decompiled/00429a94.asm) |
| `0x00429d3a` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00429d3a.c) | [assembly](decompiled/00429d3a.asm) |
| `0x00429d3f` | `root_00429d3f` |  | [decompiled](decompiled/00429d3f.c) | [assembly](decompiled/00429d3f.asm) |
| `0x00429d5c` | `root_00429d5c` |  | [decompiled](decompiled/00429d5c.c) | [assembly](decompiled/00429d5c.asm) |
| `0x00429e80` | `FUN_00429e80` |  | [decompiled](decompiled/00429e80.c) | [assembly](decompiled/00429e80.asm) |
| `0x00429ef0` | `FUN_00429ef0` |  | [decompiled](decompiled/00429ef0.c) | [assembly](decompiled/00429ef0.asm) |
| `0x0042a031` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042a031.c) | [assembly](decompiled/0042a031.asm) |
| `0x0042a036` | `root_0042a036` |  | [decompiled](decompiled/0042a036.c) | [assembly](decompiled/0042a036.asm) |
| `0x0042a040` | `root_0042a040` |  | [decompiled](decompiled/0042a040.c) | [assembly](decompiled/0042a040.asm) |
| `0x0042a05c` | `FUN_0042a05c` |  | [decompiled](decompiled/0042a05c.c) | [assembly](decompiled/0042a05c.asm) |
| `0x0042a0f8` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042a0f8.c) | [assembly](decompiled/0042a0f8.asm) |
| `0x0042a0fd` | `root_0042a0fd` |  | [decompiled](decompiled/0042a0fd.c) | [assembly](decompiled/0042a0fd.asm) |
| `0x0042a108` | `root_0042a108` |  | [decompiled](decompiled/0042a108.c) | [assembly](decompiled/0042a108.asm) |
| `0x0042a124` | `root_0042a124` |  | [decompiled](decompiled/0042a124.c) | [assembly](decompiled/0042a124.asm) |
| `0x0042a144` | `FUN_0042a144` |  | [decompiled](decompiled/0042a144.c) | [assembly](decompiled/0042a144.asm) |
| `0x0042a204` | `FUN_0042a204` |  | [decompiled](decompiled/0042a204.c) | [assembly](decompiled/0042a204.asm) |
| `0x0042a234` | `root_0042a234` |  | [decompiled](decompiled/0042a234.c) | [assembly](decompiled/0042a234.asm) |
| `0x0042a2a4` | `root_0042a2a4` |  | [decompiled](decompiled/0042a2a4.c) | [assembly](decompiled/0042a2a4.asm) |
| `0x0042a310` | `FUN_0042a310` | StdCtrls.TButton.Create | [decompiled](decompiled/0042a310.c) | [assembly](decompiled/0042a310.asm) |
| `0x0042a370` | `FUN_0042a370` |  | [decompiled](decompiled/0042a370.c) | [assembly](decompiled/0042a370.asm) |
| `0x0042a394` | `FUN_0042a394` | StdCtrls.TButton.SetButtonStyle | [decompiled](decompiled/0042a394.c) | [assembly](decompiled/0042a394.asm) |
| `0x0042a3e8` | `FUN_0042a3e8` |  | [decompiled](decompiled/0042a3e8.c) | [assembly](decompiled/0042a3e8.asm) |
| `0x0042a418` | `FUN_0042a418` |  | [decompiled](decompiled/0042a418.c) | [assembly](decompiled/0042a418.asm) |
| `0x0042a454` | `root_0042a454` |  | [decompiled](decompiled/0042a454.c) | [assembly](decompiled/0042a454.asm) |
| `0x0042a46c` | `root_0042a46c` |  | [decompiled](decompiled/0042a46c.c) | [assembly](decompiled/0042a46c.asm) |
| `0x0042a480` | `root_0042a480` |  | [decompiled](decompiled/0042a480.c) | [assembly](decompiled/0042a480.asm) |
| `0x0042a4e8` | `root_0042a4e8` | StdCtrls.TButton.CMDialogChar | [decompiled](decompiled/0042a4e8.c) | [assembly](decompiled/0042a4e8.asm) |
| `0x0042a55a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042a55a.c) | [assembly](decompiled/0042a55a.asm) |
| `0x0042a55f` | `root_0042a55f` |  | [decompiled](decompiled/0042a55f.c) | [assembly](decompiled/0042a55f.asm) |
| `0x0042a568` | `FUN_0042a568` |  | [decompiled](decompiled/0042a568.c) | [assembly](decompiled/0042a568.asm) |
| `0x0042a5b8` | `FUN_0042a5b8` | StdCtrls.TListBoxStrings.GetCount | [decompiled](decompiled/0042a5b8.c) | [assembly](decompiled/0042a5b8.asm) |
| `0x0042a5d4` | `FUN_0042a5d4` | StdCtrls.TListBoxStrings.Get | [decompiled](decompiled/0042a5d4.c) | [assembly](decompiled/0042a5d4.asm) |
| `0x0042a62c` | `root_0042a62c` | StdCtrls.TListBoxStrings.GetObject | [decompiled](decompiled/0042a62c.c) | [assembly](decompiled/0042a62c.asm) |
| `0x0042a668` | `root_0042a668` | StdCtrls.TListBoxStrings.PutObject | [decompiled](decompiled/0042a668.c) | [assembly](decompiled/0042a668.asm) |
| `0x0042a68c` | `root_0042a68c` | StdCtrls.TListBoxStrings.Add | [decompiled](decompiled/0042a68c.c) | [assembly](decompiled/0042a68c.asm) |
| `0x0042a6cc` | `FUN_0042a6cc` | StdCtrls.TListBoxStrings.Insert | [decompiled](decompiled/0042a6cc.c) | [assembly](decompiled/0042a6cc.asm) |
| `0x0042a710` | `root_0042a710` | StdCtrls.TListBoxStrings.Delete | [decompiled](decompiled/0042a710.c) | [assembly](decompiled/0042a710.asm) |
| `0x0042a730` | `FUN_0042a730` | StdCtrls.TListBoxStrings.Clear | [decompiled](decompiled/0042a730.c) | [assembly](decompiled/0042a730.asm) |
| `0x0042a74c` | `root_0042a74c` | ComCtrls.TRichEditStrings.SetUpdateState, StdCtrls.TComboBoxStrings.SetUpdateState, StdCtrls.TListBoxStrings.SetUpdateState, StdCtrls.TMemoStrings.SetUpdateState | [decompiled](decompiled/0042a74c.c) | [assembly](decompiled/0042a74c.asm) |
| `0x0042a780` | `FUN_0042a780` |  | [decompiled](decompiled/0042a780.c) | [assembly](decompiled/0042a780.asm) |
| `0x0042a854` | `FUN_0042a854` |  | [decompiled](decompiled/0042a854.c) | [assembly](decompiled/0042a854.asm) |
| `0x0042a894` | `FUN_0042a894` |  | [decompiled](decompiled/0042a894.c) | [assembly](decompiled/0042a894.asm) |
| `0x0042a8a0` | `FUN_0042a8a0` |  | [decompiled](decompiled/0042a8a0.c) | [assembly](decompiled/0042a8a0.asm) |
| `0x0042a8d8` | `root_0042a8d8` |  | [decompiled](decompiled/0042a8d8.c) | [assembly](decompiled/0042a8d8.asm) |
| `0x0042a91c` | `FUN_0042a91c` | StdCtrls.TCustomListBox.GetItemIndex | [decompiled](decompiled/0042a91c.c) | [assembly](decompiled/0042a91c.asm) |
| `0x0042a938` | `FUN_0042a938` | StdCtrls.TCustomListBox.SetItemIndex | [decompiled](decompiled/0042a938.c) | [assembly](decompiled/0042a938.asm) |
| `0x0042a964` | `root_0042a964` | ExtCtrls.THeader.SetBorderStyle, StdCtrls.TCustomMemo.SetAlignment | [decompiled](decompiled/0042a964.c) | [assembly](decompiled/0042a964.asm) |
| `0x0042a978` | `root_0042a978` |  | [decompiled](decompiled/0042a978.c) | [assembly](decompiled/0042a978.asm) |
| `0x0042a98c` | `root_0042a98c` |  | [decompiled](decompiled/0042a98c.c) | [assembly](decompiled/0042a98c.asm) |
| `0x0042a9d0` | `FUN_0042a9d0` |  | [decompiled](decompiled/0042a9d0.c) | [assembly](decompiled/0042a9d0.asm) |
| `0x0042a9e8` | `root_0042a9e8` |  | [decompiled](decompiled/0042a9e8.c) | [assembly](decompiled/0042a9e8.asm) |
| `0x0042aa04` | `FUN_0042aa04` |  | [decompiled](decompiled/0042aa04.c) | [assembly](decompiled/0042aa04.asm) |
| `0x0042aa18` | `FUN_0042aa18` | StdCtrls.TCustomListBox.GetSelected | [decompiled](decompiled/0042aa18.c) | [assembly](decompiled/0042aa18.asm) |
| `0x0042aa58` | `FUN_0042aa58` |  | [decompiled](decompiled/0042aa58.c) | [assembly](decompiled/0042aa58.asm) |
| `0x0042aa6c` | `FUN_0042aa6c` | ComCtrls.TCustomListView.SetColumnHeaders, StdCtrls.TCustomListBox.SetExtendedSelect | [decompiled](decompiled/0042aa6c.c) | [assembly](decompiled/0042aa6c.asm) |
| `0x0042aa80` | `FUN_0042aa80` | PropExpl.TPropExplBox.TopIndex, StdCtrls.TCustomListBox.GetTopIndex | [decompiled](decompiled/0042aa80.c) | [assembly](decompiled/0042aa80.asm) |
| `0x0042aa9c` | `root_0042aa9c` | StdCtrls.TCustomComboBox.SetSorted | [decompiled](decompiled/0042aa9c.c) | [assembly](decompiled/0042aa9c.asm) |
| `0x0042aab0` | `FUN_0042aab0` | StdCtrls.TCustomListBox.SetTopIndex | [decompiled](decompiled/0042aab0.c) | [assembly](decompiled/0042aab0.asm) |
| `0x0042aadc` | `root_0042aadc` |  | [decompiled](decompiled/0042aadc.c) | [assembly](decompiled/0042aadc.asm) |
| `0x0042aae8` | `root_0042aae8` |  | [decompiled](decompiled/0042aae8.c) | [assembly](decompiled/0042aae8.asm) |
| `0x0042ab74` | `root_0042ab74` |  | [decompiled](decompiled/0042ab74.c) | [assembly](decompiled/0042ab74.asm) |
| `0x0042ac54` | `FUN_0042ac54` |  | [decompiled](decompiled/0042ac54.c) | [assembly](decompiled/0042ac54.asm) |
| `0x0042acf4` | `FUN_0042acf4` |  | [decompiled](decompiled/0042acf4.c) | [assembly](decompiled/0042acf4.asm) |
| `0x0042ad4c` | `FUN_0042ad4c` | ComCtrls.TCustomTreeView.WndProc, StdCtrls.TCustomListBox.WndProc | [decompiled](decompiled/0042ad4c.c) | [assembly](decompiled/0042ad4c.asm) |
| `0x0042adb0` | `root_0042adb0` |  | [decompiled](decompiled/0042adb0.c) | [assembly](decompiled/0042adb0.asm) |
| `0x0042ae44` | `root_0042ae44` | StdCtrls.TCustomListBox.CNCommand | [decompiled](decompiled/0042ae44.c) | [assembly](decompiled/0042ae44.asm) |
| `0x0042ae6c` | `FUN_0042ae6c` |  | [decompiled](decompiled/0042ae6c.c) | [assembly](decompiled/0042ae6c.asm) |
| `0x0042afd0` | `root_0042afd0` | StdCtrls.TCustomListBox.WMPaint | [decompiled](decompiled/0042afd0.c) | [assembly](decompiled/0042afd0.asm) |
| `0x0042b000` | `root_0042b000` |  | [decompiled](decompiled/0042b000.c) | [assembly](decompiled/0042b000.asm) |
| `0x0042b014` | `root_0042b014` | StdCtrls.TCustomListBox.DragCanceled | [decompiled](decompiled/0042b014.c) | [assembly](decompiled/0042b014.asm) |
| `0x0042b074` | `root_0042b074` |  | [decompiled](decompiled/0042b074.c) | [assembly](decompiled/0042b074.asm) |
| `0x0042b11f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042b11f.c) | [assembly](decompiled/0042b11f.asm) |
| `0x0042b124` | `root_0042b124` |  | [decompiled](decompiled/0042b124.c) | [assembly](decompiled/0042b124.asm) |
| `0x0042b130` | `root_0042b130` |  | [decompiled](decompiled/0042b130.c) | [assembly](decompiled/0042b130.asm) |
| `0x0042b150` | `FUN_0042b150` |  | [decompiled](decompiled/0042b150.c) | [assembly](decompiled/0042b150.asm) |
| `0x0042b210` | `FUN_0042b210` |  | [decompiled](decompiled/0042b210.c) | [assembly](decompiled/0042b210.asm) |
| `0x0042b23c` | `root_0042b23c` |  | [decompiled](decompiled/0042b23c.c) | [assembly](decompiled/0042b23c.asm) |
| `0x0042be5c` | `FUN_0042be5c` | ExtCtrls.DoRect | [decompiled](decompiled/0042be5c.c) | [assembly](decompiled/0042be5c.asm) |
| `0x0042bf20` | `FUN_0042bf20` | ExtCtrls.Frame3D | [decompiled](decompiled/0042bf20.c) | [assembly](decompiled/0042bf20.asm) |
| `0x0042bf80` | `FUN_0042bf80` | ExtCtrls.TImage.Create | [decompiled](decompiled/0042bf80.c) | [assembly](decompiled/0042bf80.asm) |
| `0x0042c000` | `root_0042c000` | ExtCtrls.TImage.Destroy | [decompiled](decompiled/0042c000.c) | [assembly](decompiled/0042c000.asm) |
| `0x0042c02c` | `root_0042c02c` | ExtCtrls.TImage.GetPalette | [decompiled](decompiled/0042c02c.c) | [assembly](decompiled/0042c02c.asm) |
| `0x0042c05c` | `root_0042c05c` | ExtCtrls.TImage.Paint | [decompiled](decompiled/0042c05c.c) | [assembly](decompiled/0042c05c.asm) |
| `0x0042c150` | `FUN_0042c150` | ExtCtrls.TImage.GetCanvas | [decompiled](decompiled/0042c150.c) | [assembly](decompiled/0042c150.asm) |
| `0x0042c1c9` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042c1c9.c) | [assembly](decompiled/0042c1c9.asm) |
| `0x0042c1ce` | `root_0042c1ce` |  | [decompiled](decompiled/0042c1ce.c) | [assembly](decompiled/0042c1ce.asm) |
| `0x0042c210` | `root_0042c210` |  | [decompiled](decompiled/0042c210.c) | [assembly](decompiled/0042c210.asm) |
| `0x0042c220` | `root_0042c220` | ExtCtrls.TImage.SetCenter | [decompiled](decompiled/0042c220.c) | [assembly](decompiled/0042c220.asm) |
| `0x0042c238` | `root_0042c238` |  | [decompiled](decompiled/0042c238.c) | [assembly](decompiled/0042c238.asm) |
| `0x0042c248` | `root_0042c248` | ExtCtrls.TImage.SetStretch | [decompiled](decompiled/0042c248.c) | [assembly](decompiled/0042c248.asm) |
| `0x0042c260` | `root_0042c260` | ExtCtrls.TImage.PictureChanged | [decompiled](decompiled/0042c260.c) | [assembly](decompiled/0042c260.asm) |
| `0x0042c314` | `root_0042c314` | ExtCtrls.TTimer.Create | [decompiled](decompiled/0042c314.c) | [assembly](decompiled/0042c314.asm) |
| `0x0042c35c` | `root_0042c35c` | ExtCtrls.TTimer.Destroy | [decompiled](decompiled/0042c35c.c) | [assembly](decompiled/0042c35c.asm) |
| `0x0042c390` | `root_0042c390` | ExtCtrls.TTimer.WndProc | [decompiled](decompiled/0042c390.c) | [assembly](decompiled/0042c390.asm) |
| `0x0042c3ca` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0042c3ca.c) | [assembly](decompiled/0042c3ca.asm) |
| `0x0042c3cf` | `root_0042c3cf` |  | [decompiled](decompiled/0042c3cf.c) | [assembly](decompiled/0042c3cf.asm) |
| `0x0042c404` | `FUN_0042c404` | ExtCtrls.TTimer.UpdateTimer | [decompiled](decompiled/0042c404.c) | [assembly](decompiled/0042c404.asm) |
| `0x0042c454` | `FUN_0042c454` |  | [decompiled](decompiled/0042c454.c) | [assembly](decompiled/0042c454.asm) |
| `0x0042c464` | `FUN_0042c464` |  | [decompiled](decompiled/0042c464.c) | [assembly](decompiled/0042c464.asm) |
| `0x0042c474` | `root_0042c474` | ExtCtrls.TTimer.SetOnTimer | [decompiled](decompiled/0042c474.c) | [assembly](decompiled/0042c474.asm) |
| `0x0042c48c` | `root_0042c48c` | ExtCtrls.TTimer.Timer, Graphics.TCanvas.Changing | [decompiled](decompiled/0042c48c.c) | [assembly](decompiled/0042c48c.asm) |
| `0x0042c4a0` | `root_0042c4a0` |  | [decompiled](decompiled/0042c4a0.c) | [assembly](decompiled/0042c4a0.asm) |
| `0x0042c52c` | `root_0042c52c` |  | [decompiled](decompiled/0042c52c.c) | [assembly](decompiled/0042c52c.asm) |
| `0x0042c57c` | `root_0042c57c` |  | [decompiled](decompiled/0042c57c.c) | [assembly](decompiled/0042c57c.asm) |
| `0x0042c584` | `root_0042c584` |  | [decompiled](decompiled/0042c584.c) | [assembly](decompiled/0042c584.asm) |
| `0x0042c5b0` | `root_0042c5b0` |  | [decompiled](decompiled/0042c5b0.c) | [assembly](decompiled/0042c5b0.asm) |
| `0x0042c5c4` | `root_0042c5c4` |  | [decompiled](decompiled/0042c5c4.c) | [assembly](decompiled/0042c5c4.asm) |
| `0x0042c5f4` | `root_0042c5f4` |  | [decompiled](decompiled/0042c5f4.c) | [assembly](decompiled/0042c5f4.asm) |
| `0x0042c614` | `FUN_0042c614` |  | [decompiled](decompiled/0042c614.c) | [assembly](decompiled/0042c614.asm) |
| `0x0042c660` | `FUN_0042c660` | ExtCtrls.AdjustColors | [decompiled](decompiled/0042c660.c) | [assembly](decompiled/0042c660.asm) |
| `0x0042c698` | `root_0042c698` |  | [decompiled](decompiled/0042c698.c) | [assembly](decompiled/0042c698.asm) |
| `0x0042c7db` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042c7db.c) | [assembly](decompiled/0042c7db.asm) |
| `0x0042c7e0` | `root_0042c7e0` |  | [decompiled](decompiled/0042c7e0.c) | [assembly](decompiled/0042c7e0.asm) |
| `0x0042c7f8` | `root_0042c7f8` |  | [decompiled](decompiled/0042c7f8.c) | [assembly](decompiled/0042c7f8.asm) |
| `0x0042c80c` | `root_0042c80c` |  | [decompiled](decompiled/0042c80c.c) | [assembly](decompiled/0042c80c.asm) |
| `0x0042c828` | `FUN_0042c828` |  | [decompiled](decompiled/0042c828.c) | [assembly](decompiled/0042c828.asm) |
| `0x0042c844` | `FUN_0042c844` |  | [decompiled](decompiled/0042c844.c) | [assembly](decompiled/0042c844.asm) |
| `0x0042c860` | `root_0042c860` |  | [decompiled](decompiled/0042c860.c) | [assembly](decompiled/0042c860.asm) |
| `0x0042c87c` | `root_0042c87c` | StdCtrls.TCustomListBox.SetStyle | [decompiled](decompiled/0042c87c.c) | [assembly](decompiled/0042c87c.asm) |
| `0x0042c890` | `FUN_0042c890` |  | [decompiled](decompiled/0042c890.c) | [assembly](decompiled/0042c890.asm) |
| `0x0042c898` | `FUN_0042c898` | Dialogs.GetAveCharSize | [decompiled](decompiled/0042c898.c) | [assembly](decompiled/0042c898.asm) |
| `0x0042ca6c` | `FUN_0042ca6c` |  | [decompiled](decompiled/0042ca6c.c) | [assembly](decompiled/0042ca6c.asm) |
| `0x0042ce95` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042ce95.c) | [assembly](decompiled/0042ce95.asm) |
| `0x0042ce9a` | `root_0042ce9a` |  | [decompiled](decompiled/0042ce9a.c) | [assembly](decompiled/0042ce9a.asm) |
| `0x0042cec8` | `FUN_0042cec8` | Dialogs.MessageDlg | [decompiled](decompiled/0042cec8.c) | [assembly](decompiled/0042cec8.asm) |
| `0x0042cee8` | `FUN_0042cee8` | Dialogs.MessageDlgPos | [decompiled](decompiled/0042cee8.c) | [assembly](decompiled/0042cee8.asm) |
| `0x0042cf63` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042cf63.c) | [assembly](decompiled/0042cf63.asm) |
| `0x0042cf68` | `root_0042cf68` |  | [decompiled](decompiled/0042cf68.c) | [assembly](decompiled/0042cf68.asm) |
| `0x0042cf78` | `FUN_0042cf78` |  | [decompiled](decompiled/0042cf78.c) | [assembly](decompiled/0042cf78.asm) |
| `0x0042cf84` | `FUN_0042cf84` | Dialogs.ShowMessagePos | [decompiled](decompiled/0042cf84.c) | [assembly](decompiled/0042cf84.asm) |
| `0x0042cf9c` | `FUN_0042cf9c` |  | [decompiled](decompiled/0042cf9c.c) | [assembly](decompiled/0042cf9c.asm) |
| `0x0042d24e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042d24e.c) | [assembly](decompiled/0042d24e.asm) |
| `0x0042d253` | `root_0042d253` |  | [decompiled](decompiled/0042d253.c) | [assembly](decompiled/0042d253.asm) |
| `0x0042d262` | `FUN_0042d262` |  | [decompiled](decompiled/0042d262.c) | [assembly](decompiled/0042d262.asm) |
| `0x0042d273` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042d273.c) | [assembly](decompiled/0042d273.asm) |
| `0x0042d278` | `thunk_FUN_0042d262` |  | [decompiled](decompiled/0042d278.c) | [assembly](decompiled/0042d278.asm) |
| `0x0042d284` | `FUN_0042d284` | Dialogs.InitGlobals | [decompiled](decompiled/0042d284.c) | [assembly](decompiled/0042d284.asm) |
| `0x0042d338` | `FUN_0042d338` |  | [decompiled](decompiled/0042d338.c) | [assembly](decompiled/0042d338.asm) |
| `0x0042d348` | `FUN_0042d348` |  | [decompiled](decompiled/0042d348.c) | [assembly](decompiled/0042d348.asm) |
| `0x0042d360` | `FUN_0042d360` |  | [decompiled](decompiled/0042d360.c) | [assembly](decompiled/0042d360.asm) |
| `0x0042de28` | `FUN_0042de28` | ComCtrls.TTextAttributes.Create | [decompiled](decompiled/0042de28.c) | [assembly](decompiled/0042de28.asm) |
| `0x0042de6c` | `FUN_0042de6c` | ComCtrls.TTextAttributes.InitFormat | [decompiled](decompiled/0042de6c.c) | [assembly](decompiled/0042de6c.asm) |
| `0x0042de88` | `FUN_0042de88` | ComCtrls.TTextAttributes.GetAttributes | [decompiled](decompiled/0042de88.c) | [assembly](decompiled/0042de88.asm) |
| `0x0042dec8` | `FUN_0042dec8` | ComCtrls.TTextAttributes.SetAttributes | [decompiled](decompiled/0042dec8.c) | [assembly](decompiled/0042dec8.asm) |
| `0x0042df04` | `FUN_0042df04` | ComCtrls.TTextAttributes.GetColor | [decompiled](decompiled/0042df04.c) | [assembly](decompiled/0042df04.asm) |
| `0x0042df24` | `FUN_0042df24` |  | [decompiled](decompiled/0042df24.c) | [assembly](decompiled/0042df24.asm) |
| `0x0042df6c` | `FUN_0042df6c` | ComCtrls.TTextAttributes.GetName | [decompiled](decompiled/0042df6c.c) | [assembly](decompiled/0042df6c.asm) |
| `0x0042dfa0` | `FUN_0042dfa0` |  | [decompiled](decompiled/0042dfa0.c) | [assembly](decompiled/0042dfa0.asm) |
| `0x0042e03b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042e03b.c) | [assembly](decompiled/0042e03b.asm) |
| `0x0042e040` | `root_0042e040` |  | [decompiled](decompiled/0042e040.c) | [assembly](decompiled/0042e040.asm) |
| `0x0042e04c` | `FUN_0042e04c` | ComCtrls.TTextAttributes.GetStyle | [decompiled](decompiled/0042e04c.c) | [assembly](decompiled/0042e04c.asm) |
| `0x0042e09c` | `FUN_0042e09c` | ComCtrls.TTextAttributes.SetStyle | [decompiled](decompiled/0042e09c.c) | [assembly](decompiled/0042e09c.asm) |
| `0x0042e0f4` | `FUN_0042e0f4` | ComCtrls.TTextAttributes.GetSize | [decompiled](decompiled/0042e0f4.c) | [assembly](decompiled/0042e0f4.asm) |
| `0x0042e110` | `FUN_0042e110` | ComCtrls.TTextAttributes.SetSize | [decompiled](decompiled/0042e110.c) | [assembly](decompiled/0042e110.asm) |
| `0x0042e148` | `FUN_0042e148` | ComCtrls.TTextAttributes.GetPitch | [decompiled](decompiled/0042e148.c) | [assembly](decompiled/0042e148.asm) |
| `0x0042e178` | `FUN_0042e178` | ComCtrls.TTextAttributes.SetPitch | [decompiled](decompiled/0042e178.c) | [assembly](decompiled/0042e178.asm) |
| `0x0042e1b8` | `root_0042e1b8` | ComCtrls.TTextAttributes.Assign | [decompiled](decompiled/0042e1b8.c) | [assembly](decompiled/0042e1b8.asm) |
| `0x0042e288` | `FUN_0042e288` | ComCtrls.TTextAttributes.AssignTo | [decompiled](decompiled/0042e288.c) | [assembly](decompiled/0042e288.asm) |
| `0x0042e360` | `FUN_0042e360` | ComCtrls.TListItems.Create, ComCtrls.TParaAttributes.Create, ComCtrls.TTreeNodes.Create, IStreams.TVirtualStream.Create, LibMain.TDragTarget.Create, VirtFile.TExternalFileSystem.Create | [decompiled](decompiled/0042e360.c) | [assembly](decompiled/0042e360.asm) |
| `0x0042e398` | `FUN_0042e398` | ComCtrls.TParaAttributes.InitPara | [decompiled](decompiled/0042e398.c) | [assembly](decompiled/0042e398.asm) |
| `0x0042e3b4` | `FUN_0042e3b4` | ComCtrls.TParaAttributes.GetAttributes | [decompiled](decompiled/0042e3b4.c) | [assembly](decompiled/0042e3b4.asm) |
| `0x0042e3e8` | `FUN_0042e3e8` | ComCtrls.TParaAttributes.SetAttributes | [decompiled](decompiled/0042e3e8.c) | [assembly](decompiled/0042e3e8.asm) |
| `0x0042e414` | `FUN_0042e414` | ComCtrls.TParaAttributes.GetAlignment | [decompiled](decompiled/0042e414.c) | [assembly](decompiled/0042e414.asm) |
| `0x0042e430` | `FUN_0042e430` | ComCtrls.TParaAttributes.SetAlignment | [decompiled](decompiled/0042e430.c) | [assembly](decompiled/0042e430.asm) |
| `0x0042e46c` | `FUN_0042e46c` | ComCtrls.TParaAttributes.GetNumbering | [decompiled](decompiled/0042e46c.c) | [assembly](decompiled/0042e46c.asm) |
| `0x0042e484` | `FUN_0042e484` | ComCtrls.TParaAttributes.SetNumbering | [decompiled](decompiled/0042e484.c) | [assembly](decompiled/0042e484.asm) |
| `0x0042e4e8` | `FUN_0042e4e8` | ComCtrls.TParaAttributes.GetFirstIndent | [decompiled](decompiled/0042e4e8.c) | [assembly](decompiled/0042e4e8.asm) |
| `0x0042e508` | `FUN_0042e508` | ComCtrls.TParaAttributes.SetFirstIndent | [decompiled](decompiled/0042e508.c) | [assembly](decompiled/0042e508.asm) |
| `0x0042e544` | `FUN_0042e544` | ComCtrls.TParaAttributes.GetLeftIndent | [decompiled](decompiled/0042e544.c) | [assembly](decompiled/0042e544.asm) |
| `0x0042e564` | `FUN_0042e564` | ComCtrls.TParaAttributes.SetLeftIndent | [decompiled](decompiled/0042e564.c) | [assembly](decompiled/0042e564.asm) |
| `0x0042e5a0` | `FUN_0042e5a0` | ComCtrls.TParaAttributes.GetRightIndent | [decompiled](decompiled/0042e5a0.c) | [assembly](decompiled/0042e5a0.asm) |
| `0x0042e5c0` | `FUN_0042e5c0` | ComCtrls.TParaAttributes.SetRightIndent | [decompiled](decompiled/0042e5c0.c) | [assembly](decompiled/0042e5c0.asm) |
| `0x0042e5fc` | `FUN_0042e5fc` | ComCtrls.TParaAttributes.GetTab | [decompiled](decompiled/0042e5fc.c) | [assembly](decompiled/0042e5fc.asm) |
| `0x0042e624` | `FUN_0042e624` | ComCtrls.TParaAttributes.SetTab | [decompiled](decompiled/0042e624.c) | [assembly](decompiled/0042e624.asm) |
| `0x0042e678` | `FUN_0042e678` | ComCtrls.TParaAttributes.Assign | [decompiled](decompiled/0042e678.c) | [assembly](decompiled/0042e678.asm) |
| `0x0042e710` | `FUN_0042e710` | ComCtrls.TConversion.ConvertReadStream | [decompiled](decompiled/0042e710.c) | [assembly](decompiled/0042e710.asm) |
| `0x0042e724` | `FUN_0042e724` | ComCtrls.TConversion.ConvertWriteStream | [decompiled](decompiled/0042e724.c) | [assembly](decompiled/0042e724.asm) |
| `0x0042e810` | `root_0042e810` |  | [decompiled](decompiled/0042e810.c) | [assembly](decompiled/0042e810.asm) |
| `0x0042e87b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042e87b.c) | [assembly](decompiled/0042e87b.asm) |
| `0x0042e880` | `root_0042e880` |  | [decompiled](decompiled/0042e880.c) | [assembly](decompiled/0042e880.asm) |
| `0x0042e888` | `root_0042e888` | ComCtrls.TRichEditStrings.GetCount, StdCtrls.TMemoStrings.GetCount | [decompiled](decompiled/0042e888.c) | [assembly](decompiled/0042e888.asm) |
| `0x0042e8e0` | `root_0042e8e0` | ComCtrls.TRichEditStrings.Get | [decompiled](decompiled/0042e8e0.c) | [assembly](decompiled/0042e8e0.asm) |
| `0x0042e934` | `FUN_0042e934` | ComCtrls.TRichEditStrings.Put | [decompiled](decompiled/0042e934.c) | [assembly](decompiled/0042e934.asm) |
| `0x0042e9c4` | `root_0042e9c4` | ComCtrls.TRichEditStrings.Insert | [decompiled](decompiled/0042e9c4.c) | [assembly](decompiled/0042e9c4.asm) |
| `0x0042eb12` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042eb12.c) | [assembly](decompiled/0042eb12.asm) |
| `0x0042eb17` | `root_0042eb17` |  | [decompiled](decompiled/0042eb17.c) | [assembly](decompiled/0042eb17.asm) |
| `0x0042eb34` | `root_0042eb34` | ComCtrls.TRichEditStrings.Delete | [decompiled](decompiled/0042eb34.c) | [assembly](decompiled/0042eb34.asm) |
| `0x0042ebe4` | `root_0042ebe4` |  | [decompiled](decompiled/0042ebe4.c) | [assembly](decompiled/0042ebe4.asm) |
| `0x0042ebf0` | `root_0042ebf0` | ComCtrls.TRichEditStrings.SetUpdateState, StdCtrls.TComboBoxStrings.SetUpdateState, StdCtrls.TListBoxStrings.SetUpdateState, StdCtrls.TMemoStrings.SetUpdateState | [decompiled](decompiled/0042ebf0.c) | [assembly](decompiled/0042ebf0.asm) |
| `0x0042ec24` | `FUN_0042ec24` | ComCtrls.AdjustLineBreaks | [decompiled](decompiled/0042ec24.c) | [assembly](decompiled/0042ec24.asm) |
| `0x0042ec5c` | `root_0042ec5c` | ComCtrls.StreamSave | [decompiled](decompiled/0042ec5c.c) | [assembly](decompiled/0042ec5c.asm) |
| `0x0042eca1` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0042eca1.c) | [assembly](decompiled/0042eca1.asm) |
| `0x0042eca6` | `root_0042eca6` |  | [decompiled](decompiled/0042eca6.c) | [assembly](decompiled/0042eca6.asm) |
| `0x0042ecbc` | `root_0042ecbc` | ComCtrls.StreamLoad | [decompiled](decompiled/0042ecbc.c) | [assembly](decompiled/0042ecbc.asm) |
| `0x0042ed75` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0042ed75.c) | [assembly](decompiled/0042ed75.asm) |
| `0x0042ed7a` | `root_0042ed7a` |  | [decompiled](decompiled/0042ed7a.c) | [assembly](decompiled/0042ed7a.asm) |
| `0x0042ed9c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042ed9c.c) | [assembly](decompiled/0042ed9c.asm) |
| `0x0042eda1` | `root_0042eda1` |  | [decompiled](decompiled/0042eda1.c) | [assembly](decompiled/0042eda1.asm) |
| `0x0042edb0` | `root_0042edb0` |  | [decompiled](decompiled/0042edb0.c) | [assembly](decompiled/0042edb0.asm) |
| `0x0042eec5` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042eec5.c) | [assembly](decompiled/0042eec5.asm) |
| `0x0042eeca` | `root_0042eeca` |  | [decompiled](decompiled/0042eeca.c) | [assembly](decompiled/0042eeca.asm) |
| `0x0042eed4` | `FUN_0042eed4` |  | [decompiled](decompiled/0042eed4.c) | [assembly](decompiled/0042eed4.asm) |
| `0x0042ef9a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042ef9a.c) | [assembly](decompiled/0042ef9a.asm) |
| `0x0042ef9f` | `root_0042ef9f` |  | [decompiled](decompiled/0042ef9f.c) | [assembly](decompiled/0042ef9f.asm) |
| `0x0042efa8` | `root_0042efa8` | ComCtrls.TRichEditStrings.LoadFromFile, ComCtrls.TRichEditStrings.SaveToFile | [decompiled](decompiled/0042efa8.c) | [assembly](decompiled/0042efa8.asm) |
| `0x0042f04c` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0042f04c.c) | [assembly](decompiled/0042f04c.asm) |
| `0x0042f051` | `root_0042f051` |  | [decompiled](decompiled/0042f051.c) | [assembly](decompiled/0042f051.asm) |
| `0x0042f089` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042f089.c) | [assembly](decompiled/0042f089.asm) |
| `0x0042f08e` | `root_0042f08e` |  | [decompiled](decompiled/0042f08e.c) | [assembly](decompiled/0042f08e.asm) |
| `0x0042f098` | `FUN_0042f098` | ComCtrls.TRichEditStrings.LoadFromFile, ComCtrls.TRichEditStrings.SaveToFile | [decompiled](decompiled/0042f098.c) | [assembly](decompiled/0042f098.asm) |
| `0x0042f13c` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0042f13c.c) | [assembly](decompiled/0042f13c.asm) |
| `0x0042f141` | `root_0042f141` |  | [decompiled](decompiled/0042f141.c) | [assembly](decompiled/0042f141.asm) |
| `0x0042f179` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042f179.c) | [assembly](decompiled/0042f179.asm) |
| `0x0042f17e` | `root_0042f17e` |  | [decompiled](decompiled/0042f17e.c) | [assembly](decompiled/0042f17e.asm) |
| `0x0042f188` | `FUN_0042f188` |  | [decompiled](decompiled/0042f188.c) | [assembly](decompiled/0042f188.asm) |
| `0x0042f27c` | `root_0042f27c` |  | [decompiled](decompiled/0042f27c.c) | [assembly](decompiled/0042f27c.asm) |
| `0x0042f2d4` | `root_0042f2d4` |  | [decompiled](decompiled/0042f2d4.c) | [assembly](decompiled/0042f2d4.asm) |
| `0x0042f36c` | `root_0042f36c` |  | [decompiled](decompiled/0042f36c.c) | [assembly](decompiled/0042f36c.asm) |
| `0x0042f430` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042f430.c) | [assembly](decompiled/0042f430.asm) |
| `0x0042f435` | `root_0042f435` |  | [decompiled](decompiled/0042f435.c) | [assembly](decompiled/0042f435.asm) |
| `0x0042f44c` | `root_0042f44c` |  | [decompiled](decompiled/0042f44c.c) | [assembly](decompiled/0042f44c.asm) |
| `0x0042f4de` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042f4de.c) | [assembly](decompiled/0042f4de.asm) |
| `0x0042f4e3` | `root_0042f4e3` |  | [decompiled](decompiled/0042f4e3.c) | [assembly](decompiled/0042f4e3.asm) |
| `0x0042f4f4` | `root_0042f4f4` |  | [decompiled](decompiled/0042f4f4.c) | [assembly](decompiled/0042f4f4.asm) |
| `0x0042f510` | `root_0042f510` |  | [decompiled](decompiled/0042f510.c) | [assembly](decompiled/0042f510.asm) |
| `0x0042f520` | `root_0042f520` |  | [decompiled](decompiled/0042f520.c) | [assembly](decompiled/0042f520.asm) |
| `0x0042f530` | `FUN_0042f530` |  | [decompiled](decompiled/0042f530.c) | [assembly](decompiled/0042f530.asm) |
| `0x0042f544` | `FUN_0042f544` |  | [decompiled](decompiled/0042f544.c) | [assembly](decompiled/0042f544.asm) |
| `0x0042f574` | `FUN_0042f574` |  | [decompiled](decompiled/0042f574.c) | [assembly](decompiled/0042f574.asm) |
| `0x0042f580` | `FUN_0042f580` |  | [decompiled](decompiled/0042f580.c) | [assembly](decompiled/0042f580.asm) |
| `0x0042f58c` | `root_0042f58c` | ComCtrls.TCustomRichEdit.CMColorChanged | [decompiled](decompiled/0042f58c.c) | [assembly](decompiled/0042f58c.asm) |
| `0x0042f5b8` | `root_0042f5b8` |  | [decompiled](decompiled/0042f5b8.c) | [assembly](decompiled/0042f5b8.asm) |
| `0x0042f5c4` | `root_0042f5c4` | ComCtrls.TCustomRichEdit.WMPaint | [decompiled](decompiled/0042f5c4.c) | [assembly](decompiled/0042f5c4.asm) |
| `0x0042f679` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0042f679.c) | [assembly](decompiled/0042f679.asm) |
| `0x0042f67e` | `root_0042f67e` |  | [decompiled](decompiled/0042f67e.c) | [assembly](decompiled/0042f67e.asm) |
| `0x0042f688` | `root_0042f688` | ComCtrls.TCustomRichEdit.WMSetCursor | [decompiled](decompiled/0042f688.c) | [assembly](decompiled/0042f688.asm) |
| `0x0042f714` | `FUN_0042f714` |  | [decompiled](decompiled/0042f714.c) | [assembly](decompiled/0042f714.asm) |
| `0x0042f794` | `FUN_0042f794` |  | [decompiled](decompiled/0042f794.c) | [assembly](decompiled/0042f794.asm) |
| `0x0042f7c4` | `FUN_0042f7c4` |  | [decompiled](decompiled/0042f7c4.c) | [assembly](decompiled/0042f7c4.asm) |
| `0x0042f7f4` | `root_0042f7f4` |  | [decompiled](decompiled/0042f7f4.c) | [assembly](decompiled/0042f7f4.asm) |
| `0x0042f810` | `root_0042f810` |  | [decompiled](decompiled/0042f810.c) | [assembly](decompiled/0042f810.asm) |
| `0x0042f830` | `mciGetErrorStringA` |  | [decompiled](decompiled/0042f830.c) | [assembly](decompiled/0042f830.asm) |
| `0x0042f838` | `mciSendCommandA` |  | [decompiled](decompiled/0042f838.c) | [assembly](decompiled/0042f838.asm) |
| `0x0042f840` | `FUN_0042f840` |  | [decompiled](decompiled/0042f840.c) | [assembly](decompiled/0042f840.asm) |
| `0x0042f844` | `root_0042f844` |  | [decompiled](decompiled/0042f844.c) | [assembly](decompiled/0042f844.asm) |
| `0x0042f84c` | `root_0042f84c` |  | [decompiled](decompiled/0042f84c.c) | [assembly](decompiled/0042f84c.asm) |
| `0x0042fef8` | `root_0042fef8` |  | [decompiled](decompiled/0042fef8.c) | [assembly](decompiled/0042fef8.asm) |
| `0x0042ffdc` | `root_0042ffdc` |  | [decompiled](decompiled/0042ffdc.c) | [assembly](decompiled/0042ffdc.asm) |
| `0x00430024` | `FUN_00430024` |  | [decompiled](decompiled/00430024.c) | [assembly](decompiled/00430024.asm) |
| `0x00430048` | `FUN_00430048` |  | [decompiled](decompiled/00430048.c) | [assembly](decompiled/00430048.asm) |
| `0x004301b8` | `FUN_004301b8` |  | [decompiled](decompiled/004301b8.c) | [assembly](decompiled/004301b8.asm) |
| `0x004301f0` | `root_004301f0` |  | [decompiled](decompiled/004301f0.c) | [assembly](decompiled/004301f0.asm) |
| `0x00430218` | `root_00430218` |  | [decompiled](decompiled/00430218.c) | [assembly](decompiled/00430218.asm) |
| `0x0043025c` | `FUN_0043025c` |  | [decompiled](decompiled/0043025c.c) | [assembly](decompiled/0043025c.asm) |
| `0x00430290` | `root_00430290` |  | [decompiled](decompiled/00430290.c) | [assembly](decompiled/00430290.asm) |
| `0x004302d4` | `root_004302d4` |  | [decompiled](decompiled/004302d4.c) | [assembly](decompiled/004302d4.asm) |
| `0x00430344` | `FUN_00430344` |  | [decompiled](decompiled/00430344.c) | [assembly](decompiled/00430344.asm) |
| `0x0043036c` | `FUN_0043036c` |  | [decompiled](decompiled/0043036c.c) | [assembly](decompiled/0043036c.asm) |
| `0x00430394` | `root_00430394` |  | [decompiled](decompiled/00430394.c) | [assembly](decompiled/00430394.asm) |
| `0x00430420` | `FUN_00430420` |  | [decompiled](decompiled/00430420.c) | [assembly](decompiled/00430420.asm) |
| `0x00430718` | `root_00430718` |  | [decompiled](decompiled/00430718.c) | [assembly](decompiled/00430718.asm) |
| `0x0043078c` | `FUN_0043078c` |  | [decompiled](decompiled/0043078c.c) | [assembly](decompiled/0043078c.asm) |
| `0x004309b4` | `root_004309b4` |  | [decompiled](decompiled/004309b4.c) | [assembly](decompiled/004309b4.asm) |
| `0x00430a9c` | `root_00430a9c` |  | [decompiled](decompiled/00430a9c.c) | [assembly](decompiled/00430a9c.asm) |
| `0x00430aac` | `root_00430aac` |  | [decompiled](decompiled/00430aac.c) | [assembly](decompiled/00430aac.asm) |
| `0x00430abc` | `root_00430abc` |  | [decompiled](decompiled/00430abc.c) | [assembly](decompiled/00430abc.asm) |
| `0x00430b24` | `root_00430b24` |  | [decompiled](decompiled/00430b24.c) | [assembly](decompiled/00430b24.asm) |
| `0x00430be4` | `root_00430be4` |  | [decompiled](decompiled/00430be4.c) | [assembly](decompiled/00430be4.asm) |
| `0x00430bf8` | `root_00430bf8` |  | [decompiled](decompiled/00430bf8.c) | [assembly](decompiled/00430bf8.asm) |
| `0x00430c7c` | `root_00430c7c` |  | [decompiled](decompiled/00430c7c.c) | [assembly](decompiled/00430c7c.asm) |
| `0x00430c88` | `root_00430c88` |  | [decompiled](decompiled/00430c88.c) | [assembly](decompiled/00430c88.asm) |
| `0x00430c94` | `root_00430c94` |  | [decompiled](decompiled/00430c94.c) | [assembly](decompiled/00430c94.asm) |
| `0x00430c9c` | `root_00430c9c` |  | [decompiled](decompiled/00430c9c.c) | [assembly](decompiled/00430c9c.asm) |
| `0x00430d78` | `root_00430d78` |  | [decompiled](decompiled/00430d78.c) | [assembly](decompiled/00430d78.asm) |
| `0x00430e1c` | `FUN_00430e1c` |  | [decompiled](decompiled/00430e1c.c) | [assembly](decompiled/00430e1c.asm) |
| `0x00430e3c` | `root_00430e3c` |  | [decompiled](decompiled/00430e3c.c) | [assembly](decompiled/00430e3c.asm) |
| `0x00430e5c` | `root_00430e5c` | Outline.TCustomOutline.Collapse | [decompiled](decompiled/00430e5c.c) | [assembly](decompiled/00430e5c.asm) |
| `0x00430e7c` | `root_00430e7c` | DBGrids.TCustomDBGrid.EditButtonClick | [decompiled](decompiled/00430e7c.c) | [assembly](decompiled/00430e7c.asm) |
| `0x00430e98` | `FUN_00430e98` |  | [decompiled](decompiled/00430e98.c) | [assembly](decompiled/00430e98.asm) |
| `0x00430f20` | `FUN_00430f20` |  | [decompiled](decompiled/00430f20.c) | [assembly](decompiled/00430f20.asm) |
| `0x00431172` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00431172.c) | [assembly](decompiled/00431172.asm) |
| `0x00431177` | `root_00431177` |  | [decompiled](decompiled/00431177.c) | [assembly](decompiled/00431177.asm) |
| `0x00431188` | `FUN_00431188` |  | [decompiled](decompiled/00431188.c) | [assembly](decompiled/00431188.asm) |
| `0x00431250` | `FUN_00431250` |  | [decompiled](decompiled/00431250.c) | [assembly](decompiled/00431250.asm) |
| `0x00431360` | `root_00431360` |  | [decompiled](decompiled/00431360.c) | [assembly](decompiled/00431360.asm) |
| `0x00431438` | `root_00431438` |  | [decompiled](decompiled/00431438.c) | [assembly](decompiled/00431438.asm) |
| `0x004314cc` | `root_004314cc` |  | [decompiled](decompiled/004314cc.c) | [assembly](decompiled/004314cc.asm) |
| `0x00431518` | `root_00431518` |  | [decompiled](decompiled/00431518.c) | [assembly](decompiled/00431518.asm) |
| `0x004315ac` | `root_004315ac` |  | [decompiled](decompiled/004315ac.c) | [assembly](decompiled/004315ac.asm) |
| `0x00431660` | `FUN_00431660` |  | [decompiled](decompiled/00431660.c) | [assembly](decompiled/00431660.asm) |
| `0x004317f0` | `root_004317f0` |  | [decompiled](decompiled/004317f0.c) | [assembly](decompiled/004317f0.asm) |
| `0x004319ac` | `root_004319ac` |  | [decompiled](decompiled/004319ac.c) | [assembly](decompiled/004319ac.asm) |
| `0x00431a88` | `root_00431a88` |  | [decompiled](decompiled/00431a88.c) | [assembly](decompiled/00431a88.asm) |
| `0x00431b4c` | `root_00431b4c` |  | [decompiled](decompiled/00431b4c.c) | [assembly](decompiled/00431b4c.asm) |
| `0x00431bf8` | `FUN_00431bf8` |  | [decompiled](decompiled/00431bf8.c) | [assembly](decompiled/00431bf8.asm) |
| `0x00431c24` | `FUN_00431c24` |  | [decompiled](decompiled/00431c24.c) | [assembly](decompiled/00431c24.asm) |
| `0x00431c5c` | `FUN_00431c5c` |  | [decompiled](decompiled/00431c5c.c) | [assembly](decompiled/00431c5c.asm) |
| `0x00431c74` | `FUN_00431c74` |  | [decompiled](decompiled/00431c74.c) | [assembly](decompiled/00431c74.asm) |
| `0x00431c8c` | `FUN_00431c8c` |  | [decompiled](decompiled/00431c8c.c) | [assembly](decompiled/00431c8c.asm) |
| `0x00431c9c` | `FUN_00431c9c` |  | [decompiled](decompiled/00431c9c.c) | [assembly](decompiled/00431c9c.asm) |
| `0x00431cd8` | `FUN_00431cd8` |  | [decompiled](decompiled/00431cd8.c) | [assembly](decompiled/00431cd8.asm) |
| `0x00431d60` | `root_00431d60` |  | [decompiled](decompiled/00431d60.c) | [assembly](decompiled/00431d60.asm) |
| `0x00431da0` | `FUN_00431da0` |  | [decompiled](decompiled/00431da0.c) | [assembly](decompiled/00431da0.asm) |
| `0x00431dec` | `FUN_00431dec` |  | [decompiled](decompiled/00431dec.c) | [assembly](decompiled/00431dec.asm) |
| `0x00431e44` | `FUN_00431e44` |  | [decompiled](decompiled/00431e44.c) | [assembly](decompiled/00431e44.asm) |
| `0x00431fdc` | `FUN_00431fdc` |  | [decompiled](decompiled/00431fdc.c) | [assembly](decompiled/00431fdc.asm) |
| `0x00432024` | `FUN_00432024` |  | [decompiled](decompiled/00432024.c) | [assembly](decompiled/00432024.asm) |
| `0x0043206c` | `FUN_0043206c` |  | [decompiled](decompiled/0043206c.c) | [assembly](decompiled/0043206c.asm) |
| `0x004320b0` | `FUN_004320b0` |  | [decompiled](decompiled/004320b0.c) | [assembly](decompiled/004320b0.asm) |
| `0x004320f0` | `FUN_004320f0` |  | [decompiled](decompiled/004320f0.c) | [assembly](decompiled/004320f0.asm) |
| `0x00432138` | `FUN_00432138` |  | [decompiled](decompiled/00432138.c) | [assembly](decompiled/00432138.asm) |
| `0x00432188` | `ShellExecuteA` |  | [decompiled](decompiled/00432188.c) | [assembly](decompiled/00432188.asm) |
| `0x0043268c` | `FUN_0043268c` | Buttons.GetBitBtnGlyph | [decompiled](decompiled/0043268c.c) | [assembly](decompiled/0043268c.asm) |
| `0x004327f0` | `FUN_004327f0` | Buttons.TGlyphList.Create | [decompiled](decompiled/004327f0.c) | [assembly](decompiled/004327f0.asm) |
| `0x00432838` | `root_00432838` | Buttons.TGlyphList.Destroy | [decompiled](decompiled/00432838.c) | [assembly](decompiled/00432838.asm) |
| `0x00432860` | `FUN_00432860` | Buttons.TGlyphList.AllocateIndex | [decompiled](decompiled/00432860.c) | [assembly](decompiled/00432860.asm) |
| `0x004328a0` | `FUN_004328a0` | Buttons.TGlyphList.Add, Buttons.TGlyphList.AddMasked | [decompiled](decompiled/004328a0.c) | [assembly](decompiled/004328a0.asm) |
| `0x004328cc` | `FUN_004328cc` |  | [decompiled](decompiled/004328cc.c) | [assembly](decompiled/004328cc.asm) |
| `0x00432932` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00432932.c) | [assembly](decompiled/00432932.asm) |
| `0x00432937` | `root_00432937` |  | [decompiled](decompiled/00432937.c) | [assembly](decompiled/00432937.asm) |
| `0x00432948` | `FUN_00432948` | Buttons.TGlyphList.Delete | [decompiled](decompiled/00432948.c) | [assembly](decompiled/00432948.asm) |
| `0x00432970` | `FUN_00432970` | Buttons.TGlyphCache.Create, DRIntf.TNameMap.Create, DRIntf.TValueList.Create, DsgnIntf.TComponentList.Create | [decompiled](decompiled/00432970.c) | [assembly](decompiled/00432970.asm) |
| `0x004329b0` | `root_004329b0` | Buttons.TGlyphCache.Destroy, DsgnIntf.TComponentList.Destroy, Graphics.TPicture.Destroy, IStreams.TVirtualStream.Destroy, VirtFile.TExternalFileSystem.Destroy | [decompiled](decompiled/004329b0.c) | [assembly](decompiled/004329b0.asm) |
| `0x004329d8` | `FUN_004329d8` | Buttons.TGlyphCache.GetList | [decompiled](decompiled/004329d8.c) | [assembly](decompiled/004329d8.asm) |
| `0x00432a38` | `FUN_00432a38` | Buttons.TGlyphCache.ReturnList | [decompiled](decompiled/00432a38.c) | [assembly](decompiled/00432a38.asm) |
| `0x00432a58` | `FUN_00432a58` |  | [decompiled](decompiled/00432a58.c) | [assembly](decompiled/00432a58.asm) |
| `0x00432a64` | `FUN_00432a64` | Buttons.TButtonGlyph.Create | [decompiled](decompiled/00432a64.c) | [assembly](decompiled/00432a64.asm) |
| `0x00432af0` | `root_00432af0` | Buttons.TButtonGlyph.Destroy | [decompiled](decompiled/00432af0.c) | [assembly](decompiled/00432af0.asm) |
| `0x00432b48` | `FUN_00432b48` | Buttons.TButtonGlyph.Invalidate | [decompiled](decompiled/00432b48.c) | [assembly](decompiled/00432b48.asm) |
| `0x00432b90` | `FUN_00432b90` | Buttons.TButtonGlyph.GlyphChanged | [decompiled](decompiled/00432b90.c) | [assembly](decompiled/00432b90.asm) |
| `0x00432bc0` | `FUN_00432bc0` | Buttons.TButtonGlyph.SetGlyph | [decompiled](decompiled/00432bc0.c) | [assembly](decompiled/00432bc0.asm) |
| `0x00432c38` | `FUN_00432c38` | Buttons.TButtonGlyph.SetNumGlyphs | [decompiled](decompiled/00432c38.c) | [assembly](decompiled/00432c38.asm) |
| `0x00432c54` | `FUN_00432c54` | Buttons.TButtonGlyph.CreateButtonGlyph | [decompiled](decompiled/00432c54.c) | [assembly](decompiled/00432c54.asm) |
| `0x004331b5` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004331b5.c) | [assembly](decompiled/004331b5.asm) |
| `0x004331ba` | `root_004331ba` |  | [decompiled](decompiled/004331ba.c) | [assembly](decompiled/004331ba.asm) |
| `0x004331d2` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004331d2.c) | [assembly](decompiled/004331d2.asm) |
| `0x004331d7` | `root_004331d7` |  | [decompiled](decompiled/004331d7.c) | [assembly](decompiled/004331d7.asm) |
| `0x004331fc` | `FUN_004331fc` | Buttons.TButtonGlyph.DrawButtonGlyph | [decompiled](decompiled/004331fc.c) | [assembly](decompiled/004331fc.asm) |
| `0x004332b8` | `FUN_004332b8` | Buttons.TButtonGlyph.DrawButtonText | [decompiled](decompiled/004332b8.c) | [assembly](decompiled/004332b8.asm) |
| `0x00433388` | `FUN_00433388` | Buttons.TButtonGlyph.CalcButtonLayout | [decompiled](decompiled/00433388.c) | [assembly](decompiled/00433388.asm) |
| `0x0043365c` | `FUN_0043365c` | Buttons.TButtonGlyph.Draw | [decompiled](decompiled/0043365c.c) | [assembly](decompiled/0043365c.asm) |
| `0x004336c0` | `FUN_004336c0` |  | [decompiled](decompiled/004336c0.c) | [assembly](decompiled/004336c0.asm) |
| `0x0043374c` | `root_0043374c` |  | [decompiled](decompiled/0043374c.c) | [assembly](decompiled/0043374c.asm) |
| `0x00433784` | `root_00433784` |  | [decompiled](decompiled/00433784.c) | [assembly](decompiled/00433784.asm) |
| `0x004337ac` | `root_004337ac` |  | [decompiled](decompiled/004337ac.c) | [assembly](decompiled/004337ac.asm) |
| `0x004337bc` | `root_004337bc` |  | [decompiled](decompiled/004337bc.c) | [assembly](decompiled/004337bc.asm) |
| `0x004337d0` | `FUN_004337d0` |  | [decompiled](decompiled/004337d0.c) | [assembly](decompiled/004337d0.asm) |
| `0x00433838` | `root_00433838` | Buttons.TBitBtn.CNMeasureItem | [decompiled](decompiled/00433838.c) | [assembly](decompiled/00433838.asm) |
| `0x00433848` | `root_00433848` |  | [decompiled](decompiled/00433848.c) | [assembly](decompiled/00433848.asm) |
| `0x00433854` | `FUN_00433854` |  | [decompiled](decompiled/00433854.c) | [assembly](decompiled/00433854.asm) |
| `0x00433aa8` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00433aa8.c) | [assembly](decompiled/00433aa8.asm) |
| `0x00433aad` | `root_00433aad` |  | [decompiled](decompiled/00433aad.c) | [assembly](decompiled/00433aad.asm) |
| `0x00433ab8` | `root_00433ab8` |  | [decompiled](decompiled/00433ab8.c) | [assembly](decompiled/00433ab8.asm) |
| `0x00433acc` | `root_00433acc` |  | [decompiled](decompiled/00433acc.c) | [assembly](decompiled/00433acc.asm) |
| `0x00433ae0` | `root_00433ae0` |  | [decompiled](decompiled/00433ae0.c) | [assembly](decompiled/00433ae0.asm) |
| `0x00433af4` | `root_00433af4` |  | [decompiled](decompiled/00433af4.c) | [assembly](decompiled/00433af4.asm) |
| `0x00433b08` | `root_00433b08` |  | [decompiled](decompiled/00433b08.c) | [assembly](decompiled/00433b08.asm) |
| `0x00433b28` | `FUN_00433b28` |  | [decompiled](decompiled/00433b28.c) | [assembly](decompiled/00433b28.asm) |
| `0x00433b3c` | `root_00433b3c` |  | [decompiled](decompiled/00433b3c.c) | [assembly](decompiled/00433b3c.asm) |
| `0x00433b50` | `root_00433b50` |  | [decompiled](decompiled/00433b50.c) | [assembly](decompiled/00433b50.asm) |
| `0x00433b6c` | `root_00433b6c` |  | [decompiled](decompiled/00433b6c.c) | [assembly](decompiled/00433b6c.asm) |
| `0x00433c6f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00433c6f.c) | [assembly](decompiled/00433c6f.asm) |
| `0x00433c74` | `root_00433c74` |  | [decompiled](decompiled/00433c74.c) | [assembly](decompiled/00433c74.asm) |
| `0x00433c80` | `root_00433c80` |  | [decompiled](decompiled/00433c80.c) | [assembly](decompiled/00433c80.asm) |
| `0x00433cee` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00433cee.c) | [assembly](decompiled/00433cee.asm) |
| `0x00433cf3` | `root_00433cf3` |  | [decompiled](decompiled/00433cf3.c) | [assembly](decompiled/00433cf3.asm) |
| `0x00433d00` | `FUN_00433d00` |  | [decompiled](decompiled/00433d00.c) | [assembly](decompiled/00433d00.asm) |
| `0x00433d6c` | `root_00433d6c` |  | [decompiled](decompiled/00433d6c.c) | [assembly](decompiled/00433d6c.asm) |
| `0x00433d88` | `root_00433d88` |  | [decompiled](decompiled/00433d88.c) | [assembly](decompiled/00433d88.asm) |
| `0x00433d94` | `FUN_00433d94` |  | [decompiled](decompiled/00433d94.c) | [assembly](decompiled/00433d94.asm) |
| `0x00433dc0` | `root_00433dc0` |  | [decompiled](decompiled/00433dc0.c) | [assembly](decompiled/00433dc0.asm) |
| `0x00433ddc` | `root_00433ddc` |  | [decompiled](decompiled/00433ddc.c) | [assembly](decompiled/00433ddc.asm) |
| `0x00433e20` | `FUN_00433e20` |  | [decompiled](decompiled/00433e20.c) | [assembly](decompiled/00433e20.asm) |
| `0x00434084` | `TAboutBox_OKButtonClick` |  | [decompiled](decompiled/00434084.c) | [assembly](decompiled/00434084.asm) |
| `0x00434094` | `TAboutBox_image1onclick` |  | [decompiled](decompiled/00434094.c) | [assembly](decompiled/00434094.asm) |
| `0x004340b4` | `FUN_004340b4` |  | [decompiled](decompiled/004340b4.c) | [assembly](decompiled/004340b4.asm) |
| `0x004340e0` | `FUN_004340e0` |  | [decompiled](decompiled/004340e0.c) | [assembly](decompiled/004340e0.asm) |
| `0x00434130` | `TAboutBox_programicononclick` |  | [decompiled](decompiled/00434130.c) | [assembly](decompiled/00434130.asm) |
| `0x0043415c` | `TAboutBox_AboutBoxonclose` |  | [decompiled](decompiled/0043415c.c) | [assembly](decompiled/0043415c.asm) |
| `0x0043416c` | `TAboutBox_formactivate` |  | [decompiled](decompiled/0043416c.c) | [assembly](decompiled/0043416c.asm) |
| `0x004345a4` | `TAboutBox_copyrightonclick` |  | [decompiled](decompiled/004345a4.c) | [assembly](decompiled/004345a4.asm) |
| `0x00434bc4` | `TForm2_formactivate` |  | [decompiled](decompiled/00434bc4.c) | [assembly](decompiled/00434bc4.asm) |
| `0x00436bf0` | `TForm2_Button6Click` |  | [decompiled](decompiled/00436bf0.c) | [assembly](decompiled/00436bf0.asm) |
| `0x00436c14` | `FUN_00436c14` |  | [decompiled](decompiled/00436c14.c) | [assembly](decompiled/00436c14.asm) |
| `0x00437589` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00437589.c) | [assembly](decompiled/00437589.asm) |
| `0x0043758e` | `root_0043758e` |  | [decompiled](decompiled/0043758e.c) | [assembly](decompiled/0043758e.asm) |
| `0x004375d8` | `FUN_004375d8` |  | [decompiled](decompiled/004375d8.c) | [assembly](decompiled/004375d8.asm) |
| `0x00437f08` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00437f08.c) | [assembly](decompiled/00437f08.asm) |
| `0x00437f0d` | `root_00437f0d` |  | [decompiled](decompiled/00437f0d.c) | [assembly](decompiled/00437f0d.asm) |
| `0x00437f2c` | `FUN_00437f2c` |  | [decompiled](decompiled/00437f2c.c) | [assembly](decompiled/00437f2c.asm) |
| `0x00438c60` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00438c60.c) | [assembly](decompiled/00438c60.asm) |
| `0x00438c65` | `root_00438c65` |  | [decompiled](decompiled/00438c65.c) | [assembly](decompiled/00438c65.asm) |
| `0x00439b19` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00439b19.c) | [assembly](decompiled/00439b19.asm) |
| `0x00439b1e` | `root_00439b1e` |  | [decompiled](decompiled/00439b1e.c) | [assembly](decompiled/00439b1e.asm) |
| `0x00439ce0` | `FUN_00439ce0` |  | [decompiled](decompiled/00439ce0.c) | [assembly](decompiled/00439ce0.asm) |
| `0x0043a2ea` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043a2ea.c) | [assembly](decompiled/0043a2ea.asm) |
| `0x0043a2ef` | `root_0043a2ef` |  | [decompiled](decompiled/0043a2ef.c) | [assembly](decompiled/0043a2ef.asm) |
| `0x0043a3fc` | `FUN_0043a3fc` |  | [decompiled](decompiled/0043a3fc.c) | [assembly](decompiled/0043a3fc.asm) |
| `0x0043a4c0` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0043a4c0.c) | [assembly](decompiled/0043a4c0.asm) |
| `0x0043a4c5` | `root_0043a4c5` |  | [decompiled](decompiled/0043a4c5.c) | [assembly](decompiled/0043a4c5.asm) |
| `0x0043a4e0` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043a4e0.c) | [assembly](decompiled/0043a4e0.asm) |
| `0x0043a4e5` | `root_0043a4e5` |  | [decompiled](decompiled/0043a4e5.c) | [assembly](decompiled/0043a4e5.asm) |
| `0x0043a504` | `TForm2_form2onclose` |  | [decompiled](decompiled/0043a504.c) | [assembly](decompiled/0043a504.asm) |
| `0x0043a528` | `TForm2_BitBtn1Click` |  | [decompiled](decompiled/0043a528.c) | [assembly](decompiled/0043a528.asm) |
| `0x0043a550` | `TForm2_BitBtn2Click` |  | [decompiled](decompiled/0043a550.c) | [assembly](decompiled/0043a550.asm) |
| `0x0043a578` | `TForm2_BitBtn3Click` |  | [decompiled](decompiled/0043a578.c) | [assembly](decompiled/0043a578.asm) |
| `0x0043a5a0` | `TForm2_BitBtn4Click` |  | [decompiled](decompiled/0043a5a0.c) | [assembly](decompiled/0043a5a0.asm) |
| `0x0043a5c8` | `TForm2_BitBtn5Click` |  | [decompiled](decompiled/0043a5c8.c) | [assembly](decompiled/0043a5c8.asm) |
| `0x0043a5f0` | `TForm2_Button1Click` |  | [decompiled](decompiled/0043a5f0.c) | [assembly](decompiled/0043a5f0.asm) |
| `0x0043bbba` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043bbba.c) | [assembly](decompiled/0043bbba.asm) |
| `0x0043bbbf` | `root_0043bbbf` |  | [decompiled](decompiled/0043bbbf.c) | [assembly](decompiled/0043bbbf.asm) |
| `0x0043c0c8` | `FUN_0043c0c8` |  | [decompiled](decompiled/0043c0c8.c) | [assembly](decompiled/0043c0c8.asm) |
| `0x0043c124` | `FUN_0043c124` |  | [decompiled](decompiled/0043c124.c) | [assembly](decompiled/0043c124.asm) |
| `0x0043c180` | `FUN_0043c180` |  | [decompiled](decompiled/0043c180.c) | [assembly](decompiled/0043c180.asm) |
| `0x0043c1da` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043c1da.c) | [assembly](decompiled/0043c1da.asm) |
| `0x0043c1df` | `root_0043c1df` |  | [decompiled](decompiled/0043c1df.c) | [assembly](decompiled/0043c1df.asm) |
| `0x0043d5cc` | `FUN_0043d5cc` |  | [decompiled](decompiled/0043d5cc.c) | [assembly](decompiled/0043d5cc.asm) |
| `0x0043d634` | `FUN_0043d634` | FileCtrl.CutFirstDirectory | [decompiled](decompiled/0043d634.c) | [assembly](decompiled/0043d634.asm) |
| `0x0043d6f0` | `FUN_0043d6f0` |  | [decompiled](decompiled/0043d6f0.c) | [assembly](decompiled/0043d6f0.asm) |
| `0x0043d805` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043d805.c) | [assembly](decompiled/0043d805.asm) |
| `0x0043d80a` | `root_0043d80a` |  | [decompiled](decompiled/0043d80a.c) | [assembly](decompiled/0043d80a.asm) |
| `0x0043d838` | `FUN_0043d838` | FileCtrl.VolumeID | [decompiled](decompiled/0043d838.c) | [assembly](decompiled/0043d838.asm) |
| `0x0043d95f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043d95f.c) | [assembly](decompiled/0043d95f.asm) |
| `0x0043d964` | `root_0043d964` |  | [decompiled](decompiled/0043d964.c) | [assembly](decompiled/0043d964.asm) |
| `0x0043d973` | `FUN_0043d973` |  | [decompiled](decompiled/0043d973.c) | [assembly](decompiled/0043d973.asm) |
| `0x0043d97f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043d97f.c) | [assembly](decompiled/0043d97f.asm) |
| `0x0043d984` | `thunk_FUN_0043d973` |  | [decompiled](decompiled/0043d984.c) | [assembly](decompiled/0043d984.asm) |
| `0x0043d9ac` | `FUN_0043d9ac` |  | [decompiled](decompiled/0043d9ac.c) | [assembly](decompiled/0043d9ac.asm) |
| `0x0043da72` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043da72.c) | [assembly](decompiled/0043da72.asm) |
| `0x0043da77` | `root_0043da77` |  | [decompiled](decompiled/0043da77.c) | [assembly](decompiled/0043da77.asm) |
| `0x0043da80` | `FUN_0043da80` |  | [decompiled](decompiled/0043da80.c) | [assembly](decompiled/0043da80.asm) |
| `0x0043dcc6` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043dcc6.c) | [assembly](decompiled/0043dcc6.asm) |
| `0x0043dccb` | `root_0043dccb` |  | [decompiled](decompiled/0043dccb.c) | [assembly](decompiled/0043dccb.asm) |
| `0x0043dcda` | `FUN_0043dcda` |  | [decompiled](decompiled/0043dcda.c) | [assembly](decompiled/0043dcda.asm) |
| `0x0043dce8` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043dce8.c) | [assembly](decompiled/0043dce8.asm) |
| `0x0043dced` | `thunk_FUN_0043dcda` |  | [decompiled](decompiled/0043dced.c) | [assembly](decompiled/0043dced.asm) |
| `0x0043dd1c` | `FUN_0043dd1c` | FileCtrl.GetItemHeight | [decompiled](decompiled/0043dd1c.c) | [assembly](decompiled/0043dd1c.asm) |
| `0x0043dd5c` | `FUN_0043dd5c` |  | [decompiled](decompiled/0043dd5c.c) | [assembly](decompiled/0043dd5c.asm) |
| `0x0043dddc` | `root_0043dddc` |  | [decompiled](decompiled/0043dddc.c) | [assembly](decompiled/0043dddc.asm) |
| `0x0043de34` | `FUN_0043de34` |  | [decompiled](decompiled/0043de34.c) | [assembly](decompiled/0043de34.asm) |
| `0x0043deaa` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043deaa.c) | [assembly](decompiled/0043deaa.asm) |
| `0x0043deaf` | `root_0043deaf` |  | [decompiled](decompiled/0043deaf.c) | [assembly](decompiled/0043deaf.asm) |
| `0x0043dec8` | `root_0043dec8` |  | [decompiled](decompiled/0043dec8.c) | [assembly](decompiled/0043dec8.asm) |
| `0x0043e06b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043e06b.c) | [assembly](decompiled/0043e06b.asm) |
| `0x0043e070` | `root_0043e070` |  | [decompiled](decompiled/0043e070.c) | [assembly](decompiled/0043e070.asm) |
| `0x0043e08c` | `FUN_0043e08c` |  | [decompiled](decompiled/0043e08c.c) | [assembly](decompiled/0043e08c.asm) |
| `0x0043e1b3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043e1b3.c) | [assembly](decompiled/0043e1b3.asm) |
| `0x0043e1b8` | `root_0043e1b8` |  | [decompiled](decompiled/0043e1b8.c) | [assembly](decompiled/0043e1b8.asm) |
| `0x0043e1c4` | `root_0043e1c4` |  | [decompiled](decompiled/0043e1c4.c) | [assembly](decompiled/0043e1c4.asm) |
| `0x0043e1ec` | `root_0043e1ec` |  | [decompiled](decompiled/0043e1ec.c) | [assembly](decompiled/0043e1ec.asm) |
| `0x0043e21c` | `FUN_0043e21c` |  | [decompiled](decompiled/0043e21c.c) | [assembly](decompiled/0043e21c.asm) |
| `0x0043e240` | `FUN_0043e240` |  | [decompiled](decompiled/0043e240.c) | [assembly](decompiled/0043e240.asm) |
| `0x0043e37a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043e37a.c) | [assembly](decompiled/0043e37a.asm) |
| `0x0043e37f` | `root_0043e37f` |  | [decompiled](decompiled/0043e37f.c) | [assembly](decompiled/0043e37f.asm) |
| `0x0043e38c` | `root_0043e38c` |  | [decompiled](decompiled/0043e38c.c) | [assembly](decompiled/0043e38c.asm) |
| `0x0043e3ef` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043e3ef.c) | [assembly](decompiled/0043e3ef.asm) |
| `0x0043e3f4` | `root_0043e3f4` |  | [decompiled](decompiled/0043e3f4.c) | [assembly](decompiled/0043e3f4.asm) |
| `0x0043e3fc` | `root_0043e3fc` |  | [decompiled](decompiled/0043e3fc.c) | [assembly](decompiled/0043e3fc.asm) |
| `0x0043e418` | `FUN_0043e418` |  | [decompiled](decompiled/0043e418.c) | [assembly](decompiled/0043e418.asm) |
| `0x0043e450` | `FUN_0043e450` |  | [decompiled](decompiled/0043e450.c) | [assembly](decompiled/0043e450.asm) |
| `0x0043e55c` | `root_0043e55c` | FileCtrl.TFilterComboBox.Notification | [decompiled](decompiled/0043e55c.c) | [assembly](decompiled/0043e55c.asm) |
| `0x0043e58c` | `root_0043e58c` | DB.TDataSet.DoAfterDelete, Forms.TForm.Deactivate | [decompiled](decompiled/0043e58c.c) | [assembly](decompiled/0043e58c.asm) |
| `0x0043e5a8` | `FUN_0043e5a8` |  | [decompiled](decompiled/0043e5a8.c) | [assembly](decompiled/0043e5a8.asm) |
| `0x0043e5e0` | `FUN_0043e5e0` | FileCtrl.TFolderBitmap.Create | [decompiled](decompiled/0043e5e0.c) | [assembly](decompiled/0043e5e0.asm) |
| `0x0043e628` | `root_0043e628` |  | [decompiled](decompiled/0043e628.c) | [assembly](decompiled/0043e628.asm) |
| `0x0043e694` | `root_0043e694` |  | [decompiled](decompiled/0043e694.c) | [assembly](decompiled/0043e694.asm) |
| `0x0043e6d4` | `FUN_0043e6d4` |  | [decompiled](decompiled/0043e6d4.c) | [assembly](decompiled/0043e6d4.asm) |
| `0x0043e78e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043e78e.c) | [assembly](decompiled/0043e78e.asm) |
| `0x0043e793` | `root_0043e793` |  | [decompiled](decompiled/0043e793.c) | [assembly](decompiled/0043e793.asm) |
| `0x0043e7a0` | `root_0043e7a0` |  | [decompiled](decompiled/0043e7a0.c) | [assembly](decompiled/0043e7a0.asm) |
| `0x0043e7d0` | `FUN_0043e7d0` |  | [decompiled](decompiled/0043e7d0.c) | [assembly](decompiled/0043e7d0.asm) |
| `0x0043e838` | `FUN_0043e838` |  | [decompiled](decompiled/0043e838.c) | [assembly](decompiled/0043e838.asm) |
| `0x0043e886` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043e886.c) | [assembly](decompiled/0043e886.asm) |
| `0x0043e88b` | `root_0043e88b` |  | [decompiled](decompiled/0043e88b.c) | [assembly](decompiled/0043e88b.asm) |
| `0x0043e894` | `FUN_0043e894` |  | [decompiled](decompiled/0043e894.c) | [assembly](decompiled/0043e894.asm) |
| `0x0043e8c4` | `FUN_0043e8c4` |  | [decompiled](decompiled/0043e8c4.c) | [assembly](decompiled/0043e8c4.asm) |
| `0x0043e8e4` | `FUN_0043e8e4` | FileCtrl.TDirectoryListBox.ReadDirectoryNames | [decompiled](decompiled/0043e8e4.c) | [assembly](decompiled/0043e8e4.asm) |
| `0x0043e9c3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043e9c3.c) | [assembly](decompiled/0043e9c3.asm) |
| `0x0043e9c8` | `root_0043e9c8` |  | [decompiled](decompiled/0043e9c8.c) | [assembly](decompiled/0043e9c8.asm) |
| `0x0043e9d7` | `FUN_0043e9d7` |  | [decompiled](decompiled/0043e9d7.c) | [assembly](decompiled/0043e9d7.asm) |
| `0x0043e9f3` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043e9f3.c) | [assembly](decompiled/0043e9f3.asm) |
| `0x0043e9f8` | `thunk_FUN_0043e9d7` |  | [decompiled](decompiled/0043e9f8.c) | [assembly](decompiled/0043e9f8.asm) |
| `0x0043ea28` | `root_0043ea28` |  | [decompiled](decompiled/0043ea28.c) | [assembly](decompiled/0043ea28.asm) |
| `0x0043eca1` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043eca1.c) | [assembly](decompiled/0043eca1.asm) |
| `0x0043eca6` | `root_0043eca6` |  | [decompiled](decompiled/0043eca6.c) | [assembly](decompiled/0043eca6.asm) |
| `0x0043ecb5` | `FUN_0043ecb5` |  | [decompiled](decompiled/0043ecb5.c) | [assembly](decompiled/0043ecb5.asm) |
| `0x0043ecc4` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043ecc4.c) | [assembly](decompiled/0043ecc4.asm) |
| `0x0043ecc9` | `thunk_FUN_0043ecb5` |  | [decompiled](decompiled/0043ecc9.c) | [assembly](decompiled/0043ecc9.asm) |
| `0x0043ecef` | `FUN_0043ecef` |  | [decompiled](decompiled/0043ecef.c) | [assembly](decompiled/0043ecef.asm) |
| `0x0043ed0a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043ed0a.c) | [assembly](decompiled/0043ed0a.asm) |
| `0x0043ed0f` | `thunk_FUN_0043ecef` |  | [decompiled](decompiled/0043ed0f.c) | [assembly](decompiled/0043ed0f.asm) |
| `0x0043ed24` | `root_0043ed24` |  | [decompiled](decompiled/0043ed24.c) | [assembly](decompiled/0043ed24.asm) |
| `0x0043ede0` | `root_0043ede0` |  | [decompiled](decompiled/0043ede0.c) | [assembly](decompiled/0043ede0.asm) |
| `0x0043edf4` | `FUN_0043edf4` |  | [decompiled](decompiled/0043edf4.c) | [assembly](decompiled/0043edf4.asm) |
| `0x0043ee30` | `root_0043ee30` |  | [decompiled](decompiled/0043ee30.c) | [assembly](decompiled/0043ee30.asm) |
| `0x0043ef98` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043ef98.c) | [assembly](decompiled/0043ef98.asm) |
| `0x0043ef9d` | `root_0043ef9d` |  | [decompiled](decompiled/0043ef9d.c) | [assembly](decompiled/0043ef9d.asm) |
| `0x0043efa8` | `FUN_0043efa8` |  | [decompiled](decompiled/0043efa8.c) | [assembly](decompiled/0043efa8.asm) |
| `0x0043f11f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043f11f.c) | [assembly](decompiled/0043f11f.asm) |
| `0x0043f124` | `root_0043f124` |  | [decompiled](decompiled/0043f124.c) | [assembly](decompiled/0043f124.asm) |
| `0x0043f13c` | `root_0043f13c` |  | [decompiled](decompiled/0043f13c.c) | [assembly](decompiled/0043f13c.asm) |
| `0x0043f168` | `root_0043f168` |  | [decompiled](decompiled/0043f168.c) | [assembly](decompiled/0043f168.asm) |
| `0x0043f17c` | `FUN_0043f17c` |  | [decompiled](decompiled/0043f17c.c) | [assembly](decompiled/0043f17c.asm) |
| `0x0043f1b4` | `FUN_0043f1b4` |  | [decompiled](decompiled/0043f1b4.c) | [assembly](decompiled/0043f1b4.asm) |
| `0x0043f1c0` | `helper_43f1c0` |  | [decompiled](decompiled/0043f1c0.c) | [assembly](decompiled/0043f1c0.asm) |
| `0x0043f236` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043f236.c) | [assembly](decompiled/0043f236.asm) |
| `0x0043f23b` | `root_0043f23b` |  | [decompiled](decompiled/0043f23b.c) | [assembly](decompiled/0043f23b.asm) |
| `0x0043f250` | `root_0043f250` |  | [decompiled](decompiled/0043f250.c) | [assembly](decompiled/0043f250.asm) |
| `0x0043f30e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043f30e.c) | [assembly](decompiled/0043f30e.asm) |
| `0x0043f313` | `root_0043f313` |  | [decompiled](decompiled/0043f313.c) | [assembly](decompiled/0043f313.asm) |
| `0x0043f33b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043f33b.c) | [assembly](decompiled/0043f33b.asm) |
| `0x0043f340` | `root_0043f340` |  | [decompiled](decompiled/0043f340.c) | [assembly](decompiled/0043f340.asm) |
| `0x0043f34c` | `root_0043f34c` | FileCtrl.TDirectoryListBox.KeyPress | [decompiled](decompiled/0043f34c.c) | [assembly](decompiled/0043f34c.asm) |
| `0x0043f370` | `FUN_0043f370` |  | [decompiled](decompiled/0043f370.c) | [assembly](decompiled/0043f370.asm) |
| `0x0043f3c4` | `FUN_0043f3c4` |  | [decompiled](decompiled/0043f3c4.c) | [assembly](decompiled/0043f3c4.asm) |
| `0x0043f42c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043f42c.c) | [assembly](decompiled/0043f42c.asm) |
| `0x0043f431` | `root_0043f431` |  | [decompiled](decompiled/0043f431.c) | [assembly](decompiled/0043f431.asm) |
| `0x0043f43c` | `root_0043f43c` |  | [decompiled](decompiled/0043f43c.c) | [assembly](decompiled/0043f43c.asm) |
| `0x0043f4e4` | `root_0043f4e4` |  | [decompiled](decompiled/0043f4e4.c) | [assembly](decompiled/0043f4e4.asm) |
| `0x0043f524` | `FUN_0043f524` |  | [decompiled](decompiled/0043f524.c) | [assembly](decompiled/0043f524.asm) |
| `0x0043f53c` | `root_0043f53c` |  | [decompiled](decompiled/0043f53c.c) | [assembly](decompiled/0043f53c.asm) |
| `0x0043f560` | `root_0043f560` |  | [decompiled](decompiled/0043f560.c) | [assembly](decompiled/0043f560.asm) |
| `0x0043f618` | `root_0043f618` |  | [decompiled](decompiled/0043f618.c) | [assembly](decompiled/0043f618.asm) |
| `0x0043f89e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043f89e.c) | [assembly](decompiled/0043f89e.asm) |
| `0x0043f8a3` | `root_0043f8a3` |  | [decompiled](decompiled/0043f8a3.c) | [assembly](decompiled/0043f8a3.asm) |
| `0x0043f8e1` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043f8e1.c) | [assembly](decompiled/0043f8e1.asm) |
| `0x0043f8e6` | `root_0043f8e6` |  | [decompiled](decompiled/0043f8e6.c) | [assembly](decompiled/0043f8e6.asm) |
| `0x0043f940` | `root_0043f940` |  | [decompiled](decompiled/0043f940.c) | [assembly](decompiled/0043f940.asm) |
| `0x0043f968` | `root_0043f968` |  | [decompiled](decompiled/0043f968.c) | [assembly](decompiled/0043f968.asm) |
| `0x0043fa10` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043fa10.c) | [assembly](decompiled/0043fa10.asm) |
| `0x0043fa15` | `root_0043fa15` |  | [decompiled](decompiled/0043fa15.c) | [assembly](decompiled/0043fa15.asm) |
| `0x0043fa20` | `root_0043fa20` |  | [decompiled](decompiled/0043fa20.c) | [assembly](decompiled/0043fa20.asm) |
| `0x0043fa68` | `FUN_0043fa68` |  | [decompiled](decompiled/0043fa68.c) | [assembly](decompiled/0043fa68.asm) |
| `0x0043fab4` | `FUN_0043fab4` |  | [decompiled](decompiled/0043fab4.c) | [assembly](decompiled/0043fab4.asm) |
| `0x0043fb2b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043fb2b.c) | [assembly](decompiled/0043fb2b.asm) |
| `0x0043fb30` | `root_0043fb30` |  | [decompiled](decompiled/0043fb30.c) | [assembly](decompiled/0043fb30.asm) |
| `0x0043fb38` | `root_0043fb38` |  | [decompiled](decompiled/0043fb38.c) | [assembly](decompiled/0043fb38.asm) |
| `0x0043fbb4` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043fbb4.c) | [assembly](decompiled/0043fbb4.asm) |
| `0x0043fbb9` | `root_0043fbb9` |  | [decompiled](decompiled/0043fbb9.c) | [assembly](decompiled/0043fbb9.asm) |
| `0x0043fbc4` | `root_0043fbc4` |  | [decompiled](decompiled/0043fbc4.c) | [assembly](decompiled/0043fbc4.asm) |
| `0x0043fcf8` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043fcf8.c) | [assembly](decompiled/0043fcf8.asm) |
| `0x0043fcfd` | `root_0043fcfd` |  | [decompiled](decompiled/0043fcfd.c) | [assembly](decompiled/0043fcfd.asm) |
| `0x0043fd08` | `FUN_0043fd08` |  | [decompiled](decompiled/0043fd08.c) | [assembly](decompiled/0043fd08.asm) |
| `0x0043fd58` | `root_0043fd58` |  | [decompiled](decompiled/0043fd58.c) | [assembly](decompiled/0043fd58.asm) |
| `0x0043fd80` | `FUN_0043fd80` |  | [decompiled](decompiled/0043fd80.c) | [assembly](decompiled/0043fd80.asm) |
| `0x0043fdb0` | `FUN_0043fdb0` |  | [decompiled](decompiled/0043fdb0.c) | [assembly](decompiled/0043fdb0.asm) |
| `0x0043fdc4` | `FUN_0043fdc4` |  | [decompiled](decompiled/0043fdc4.c) | [assembly](decompiled/0043fdc4.asm) |
| `0x0043fe08` | `root_0043fe08` |  | [decompiled](decompiled/0043fe08.c) | [assembly](decompiled/0043fe08.asm) |
| `0x0043ff73` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0043ff73.c) | [assembly](decompiled/0043ff73.asm) |
| `0x0043ff78` | `root_0043ff78` |  | [decompiled](decompiled/0043ff78.c) | [assembly](decompiled/0043ff78.asm) |
| `0x0043ffac` | `root_0043ffac` |  | [decompiled](decompiled/0043ffac.c) | [assembly](decompiled/0043ffac.asm) |
| `0x0044000d` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0044000d.c) | [assembly](decompiled/0044000d.asm) |
| `0x00440012` | `root_00440012` |  | [decompiled](decompiled/00440012.c) | [assembly](decompiled/00440012.asm) |
| `0x0044001c` | `root_0044001c` |  | [decompiled](decompiled/0044001c.c) | [assembly](decompiled/0044001c.asm) |
| `0x00440298` | `TForm4_DriveComboBox1Change` |  | [decompiled](decompiled/00440298.c) | [assembly](decompiled/00440298.asm) |
| `0x004402b0` | `FUN_004402b0` |  | [decompiled](decompiled/004402b0.c) | [assembly](decompiled/004402b0.asm) |
| `0x004402e8` | `TForm4_Button1Click` |  | [decompiled](decompiled/004402e8.c) | [assembly](decompiled/004402e8.asm) |
| `0x0044084d` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0044084d.c) | [assembly](decompiled/0044084d.asm) |
| `0x00440852` | `root_00440852` |  | [decompiled](decompiled/00440852.c) | [assembly](decompiled/00440852.asm) |
| `0x00440974` | `TForm4_Button2Click` |  | [decompiled](decompiled/00440974.c) | [assembly](decompiled/00440974.asm) |
| `0x00440984` | `TForm4_Button3Click` |  | [decompiled](decompiled/00440984.c) | [assembly](decompiled/00440984.asm) |
| `0x00440a2b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00440a2b.c) | [assembly](decompiled/00440a2b.asm) |
| `0x00440a30` | `root_00440a30` |  | [decompiled](decompiled/00440a30.c) | [assembly](decompiled/00440a30.asm) |
| `0x00440a88` | `TForm4_form4onclose` |  | [decompiled](decompiled/00440a88.c) | [assembly](decompiled/00440a88.asm) |
| `0x00440a98` | `TForm4_form4activate` |  | [decompiled](decompiled/00440a98.c) | [assembly](decompiled/00440a98.asm) |
| `0x0044280c` | `TTSW10_formactivate` |  | [decompiled](decompiled/0044280c.c) | [assembly](decompiled/0044280c.asm) |
| `0x004429e1` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/004429e1.c) | [assembly](decompiled/004429e1.asm) |
| `0x004429e6` | `root_004429e6` |  | [decompiled](decompiled/004429e6.c) | [assembly](decompiled/004429e6.asm) |
| `0x00442ba8` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00442ba8.c) | [assembly](decompiled/00442ba8.asm) |
| `0x00442bad` | `root_00442bad` |  | [decompiled](decompiled/00442bad.c) | [assembly](decompiled/00442bad.asm) |
| `0x00442c38` | `FUN_00442c38` |  | [decompiled](decompiled/00442c38.c) | [assembly](decompiled/00442c38.asm) |
| `0x00442d50` | `TTSW10_buttonfocus` |  | [decompiled](decompiled/00442d50.c) | [assembly](decompiled/00442d50.asm) |
| `0x00442dc8` | `kaidanwork` |  | [decompiled](decompiled/00442dc8.c) | [assembly](decompiled/00442dc8.asm) |
| `0x00442f80` | `FUN_00442f80` |  | [decompiled](decompiled/00442f80.c) | [assembly](decompiled/00442f80.asm) |
| `0x00443050` | `FUN_00443050` |  | [decompiled](decompiled/00443050.c) | [assembly](decompiled/00443050.asm) |
| `0x00443120` | `FUN_00443120` |  | [decompiled](decompiled/00443120.c) | [assembly](decompiled/00443120.asm) |
| `0x004433a4` | `FUN_004433a4` |  | [decompiled](decompiled/004433a4.c) | [assembly](decompiled/004433a4.asm) |
| `0x00443648` | `FUN_00443648` |  | [decompiled](decompiled/00443648.c) | [assembly](decompiled/00443648.asm) |
| `0x00443808` | `FUN_00443808` |  | [decompiled](decompiled/00443808.c) | [assembly](decompiled/00443808.asm) |
| `0x00443a34` | `FUN_00443a34` |  | [decompiled](decompiled/00443a34.c) | [assembly](decompiled/00443a34.asm) |
| `0x00443c08` | `FUN_00443c08` |  | [decompiled](decompiled/00443c08.c) | [assembly](decompiled/00443c08.asm) |
| `0x00443de8` | `FUN_00443de8` |  | [decompiled](decompiled/00443de8.c) | [assembly](decompiled/00443de8.asm) |
| `0x004440e8` | `FUN_004440e8` |  | [decompiled](decompiled/004440e8.c) | [assembly](decompiled/004440e8.asm) |
| `0x0044439c` | `FUN_0044439c` |  | [decompiled](decompiled/0044439c.c) | [assembly](decompiled/0044439c.asm) |
| `0x00444490` | `handan` |  | [decompiled](decompiled/00444490.c) | [assembly](decompiled/00444490.asm) |
| `0x00448fd7` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00448fd7.c) | [assembly](decompiled/00448fd7.asm) |
| `0x00448fdc` | `root_00448fdc` |  | [decompiled](decompiled/00448fdc.c) | [assembly](decompiled/00448fdc.asm) |
| `0x00449014` | `syounin` |  | [decompiled](decompiled/00449014.c) | [assembly](decompiled/00449014.asm) |
| `0x004496ed` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004496ed.c) | [assembly](decompiled/004496ed.asm) |
| `0x004496f2` | `root_004496f2` |  | [decompiled](decompiled/004496f2.c) | [assembly](decompiled/004496f2.asm) |
| `0x00449708` | `roujin` |  | [decompiled](decompiled/00449708.c) | [assembly](decompiled/00449708.asm) |
| `0x00449e18` | `FUN_00449e18` |  | [decompiled](decompiled/00449e18.c) | [assembly](decompiled/00449e18.asm) |
| `0x0044a437` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0044a437.c) | [assembly](decompiled/0044a437.asm) |
| `0x0044a43c` | `root_0044a43c` |  | [decompiled](decompiled/0044a43c.c) | [assembly](decompiled/0044a43c.asm) |
| `0x0044a480` | `taisen` |  | [decompiled](decompiled/0044a480.c) | [assembly](decompiled/0044a480.asm) |
| `0x0044b6cd` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0044b6cd.c) | [assembly](decompiled/0044b6cd.asm) |
| `0x0044b6d2` | `root_0044b6d2` |  | [decompiled](decompiled/0044b6d2.c) | [assembly](decompiled/0044b6d2.asm) |
| `0x0044b6f4` | `FUN_0044b6f4` |  | [decompiled](decompiled/0044b6f4.c) | [assembly](decompiled/0044b6f4.asm) |
| `0x0044b77c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0044b77c.c) | [assembly](decompiled/0044b77c.asm) |
| `0x0044b781` | `root_0044b781` |  | [decompiled](decompiled/0044b781.c) | [assembly](decompiled/0044b781.asm) |
| `0x0044b78c` | `FUN_0044b78c` |  | [decompiled](decompiled/0044b78c.c) | [assembly](decompiled/0044b78c.asm) |
| `0x0044bbfd` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0044bbfd.c) | [assembly](decompiled/0044bbfd.asm) |
| `0x0044bc02` | `root_0044bc02` |  | [decompiled](decompiled/0044bc02.c) | [assembly](decompiled/0044bc02.asm) |
| `0x0044bc0c` | `start_event_timer` |  | [decompiled](decompiled/0044bc0c.c) | [assembly](decompiled/0044bc0c.asm) |
| `0x0044bc34` | `toroad2` |  | [decompiled](decompiled/0044bc34.c) | [assembly](decompiled/0044bc34.asm) |
| `0x0044bed8` | `FUN_0044bed8` |  | [decompiled](decompiled/0044bed8.c) | [assembly](decompiled/0044bed8.asm) |
| `0x0044c04c` | `FUN_0044c04c` |  | [decompiled](decompiled/0044c04c.c) | [assembly](decompiled/0044c04c.asm) |
| `0x0044c464` | `FUN_0044c464` |  | [decompiled](decompiled/0044c464.c) | [assembly](decompiled/0044c464.asm) |
| `0x0044c5c4` | `mazyutu1` |  | [decompiled](decompiled/0044c5c4.c) | [assembly](decompiled/0044c5c4.asm) |
| `0x0044c9f0` | `FUN_0044c9f0` |  | [decompiled](decompiled/0044c9f0.c) | [assembly](decompiled/0044c9f0.asm) |
| `0x0044cb34` | `FUN_0044cb34` |  | [decompiled](decompiled/0044cb34.c) | [assembly](decompiled/0044cb34.asm) |
| `0x0044ccb1` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0044ccb1.c) | [assembly](decompiled/0044ccb1.asm) |
| `0x0044ccb6` | `root_0044ccb6` |  | [decompiled](decompiled/0044ccb6.c) | [assembly](decompiled/0044ccb6.asm) |
| `0x0044ccd8` | `FUN_0044ccd8` |  | [decompiled](decompiled/0044ccd8.c) | [assembly](decompiled/0044ccd8.asm) |
| `0x0044da10` | `dialogue_continue` |  | [decompiled](decompiled/0044da10.c) | [assembly](decompiled/0044da10.asm) |
| `0x0044e1cc` | `accept_merchant_or_altar` |  | [decompiled](decompiled/0044e1cc.c) | [assembly](decompiled/0044e1cc.asm) |
| `0x0044ea74` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0044ea74.c) | [assembly](decompiled/0044ea74.asm) |
| `0x0044ea79` | `root_0044ea79` |  | [decompiled](decompiled/0044ea79.c) | [assembly](decompiled/0044ea79.asm) |
| `0x0044ea90` | `TTSW10_Button7Click` |  | [decompiled](decompiled/0044ea90.c) | [assembly](decompiled/0044ea90.asm) |
| `0x0044eaec` | `TTSW10_Image4Click` |  | [decompiled](decompiled/0044eaec.c) | [assembly](decompiled/0044eaec.asm) |
| `0x0044eaf4` | `confirm_flight` |  | [decompiled](decompiled/0044eaf4.c) | [assembly](decompiled/0044eaf4.asm) |
| `0x0044ed1c` | `preview_flight_down` |  | [decompiled](decompiled/0044ed1c.c) | [assembly](decompiled/0044ed1c.asm) |
| `0x0044ed94` | `preview_flight_up` |  | [decompiled](decompiled/0044ed94.c) | [assembly](decompiled/0044ed94.asm) |
| `0x0044ee44` | `TTSW10_Image5Click` |  | [decompiled](decompiled/0044ee44.c) | [assembly](decompiled/0044ee44.asm) |
| `0x0044ee4c` | `TTSW10_Button11Click` |  | [decompiled](decompiled/0044ee4c.c) | [assembly](decompiled/0044ee4c.asm) |
| `0x0044ee64` | `TTSW10_Button12Click` |  | [decompiled](decompiled/0044ee64.c) | [assembly](decompiled/0044ee64.asm) |
| `0x0044ee80` | `TTSW10_Button13Click` |  | [decompiled](decompiled/0044ee80.c) | [assembly](decompiled/0044ee80.asm) |
| `0x0044ee9c` | `TTSW10_Button14Click` |  | [decompiled](decompiled/0044ee9c.c) | [assembly](decompiled/0044ee9c.asm) |
| `0x0044eeb8` | `TTSW10_Button15Click` |  | [decompiled](decompiled/0044eeb8.c) | [assembly](decompiled/0044eeb8.asm) |
| `0x0044eed4` | `TTSW10_Button16Click` |  | [decompiled](decompiled/0044eed4.c) | [assembly](decompiled/0044eed4.asm) |
| `0x0044eef0` | `TTSW10_Button17Click` |  | [decompiled](decompiled/0044eef0.c) | [assembly](decompiled/0044eef0.asm) |
| `0x0044ef0c` | `TTSW10_Button18Click` |  | [decompiled](decompiled/0044ef0c.c) | [assembly](decompiled/0044ef0c.asm) |
| `0x0044ef28` | `TTSW10_Button19Click` |  | [decompiled](decompiled/0044ef28.c) | [assembly](decompiled/0044ef28.asm) |
| `0x0044ef44` | `TTSW10_Button20Click` |  | [decompiled](decompiled/0044ef44.c) | [assembly](decompiled/0044ef44.asm) |
| `0x0044ef60` | `TTSW10_Button21Click` |  | [decompiled](decompiled/0044ef60.c) | [assembly](decompiled/0044ef60.asm) |
| `0x0044ef7c` | `TTSW10_Button22Click` |  | [decompiled](decompiled/0044ef7c.c) | [assembly](decompiled/0044ef7c.asm) |
| `0x0044ef98` | `TTSW10_Button23Click` |  | [decompiled](decompiled/0044ef98.c) | [assembly](decompiled/0044ef98.asm) |
| `0x0044efb4` | `TTSW10_Button24Click` |  | [decompiled](decompiled/0044efb4.c) | [assembly](decompiled/0044efb4.asm) |
| `0x0044efd0` | `TTSW10_Button25Click` |  | [decompiled](decompiled/0044efd0.c) | [assembly](decompiled/0044efd0.asm) |
| `0x0044efec` | `TTSW10_Button26Click` |  | [decompiled](decompiled/0044efec.c) | [assembly](decompiled/0044efec.asm) |
| `0x0044f008` | `TTSW10_Button27Click` |  | [decompiled](decompiled/0044f008.c) | [assembly](decompiled/0044f008.asm) |
| `0x0044f024` | `TTSW10_Button28Click` |  | [decompiled](decompiled/0044f024.c) | [assembly](decompiled/0044f024.asm) |
| `0x0044f040` | `TTSW10_Button29Click` |  | [decompiled](decompiled/0044f040.c) | [assembly](decompiled/0044f040.asm) |
| `0x0044f05c` | `TTSW10_Button30Click` |  | [decompiled](decompiled/0044f05c.c) | [assembly](decompiled/0044f05c.asm) |
| `0x0044f078` | `TTSW10_Button31Click` |  | [decompiled](decompiled/0044f078.c) | [assembly](decompiled/0044f078.asm) |
| `0x0044f094` | `TTSW10_Button32Click` |  | [decompiled](decompiled/0044f094.c) | [assembly](decompiled/0044f094.asm) |
| `0x0044f0b0` | `TTSW10_Button33Click` |  | [decompiled](decompiled/0044f0b0.c) | [assembly](decompiled/0044f0b0.asm) |
| `0x0044f0cc` | `TTSW10_Button34Click` |  | [decompiled](decompiled/0044f0cc.c) | [assembly](decompiled/0044f0cc.asm) |
| `0x0044f0e8` | `close_wisdom` |  | [decompiled](decompiled/0044f0e8.c) | [assembly](decompiled/0044f0e8.asm) |
| `0x0044f264` | `TTSW10_Image6Click` |  | [decompiled](decompiled/0044f264.c) | [assembly](decompiled/0044f264.asm) |
| `0x0044f26c` | `FUN_0044f26c` |  | [decompiled](decompiled/0044f26c.c) | [assembly](decompiled/0044f26c.asm) |
| `0x0044fef1` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0044fef1.c) | [assembly](decompiled/0044fef1.asm) |
| `0x0044fef6` | `root_0044fef6` |  | [decompiled](decompiled/0044fef6.c) | [assembly](decompiled/0044fef6.asm) |
| `0x0044ff0c` | `FUN_0044ff0c` |  | [decompiled](decompiled/0044ff0c.c) | [assembly](decompiled/0044ff0c.asm) |
| `0x0045004a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0045004a.c) | [assembly](decompiled/0045004a.asm) |
| `0x0045004f` | `root_0045004f` |  | [decompiled](decompiled/0045004f.c) | [assembly](decompiled/0045004f.asm) |
| `0x00450064` | `FUN_00450064` |  | [decompiled](decompiled/00450064.c) | [assembly](decompiled/00450064.asm) |
| `0x0045026d` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0045026d.c) | [assembly](decompiled/0045026d.asm) |
| `0x00450272` | `root_00450272` |  | [decompiled](decompiled/00450272.c) | [assembly](decompiled/00450272.asm) |
| `0x00450288` | `FUN_00450288` |  | [decompiled](decompiled/00450288.c) | [assembly](decompiled/00450288.asm) |
| `0x004502d0` | `FUN_004502d0` |  | [decompiled](decompiled/004502d0.c) | [assembly](decompiled/004502d0.asm) |
| `0x0045031c` | `FUN_0045031c` |  | [decompiled](decompiled/0045031c.c) | [assembly](decompiled/0045031c.asm) |
| `0x00450360` | `FUN_00450360` |  | [decompiled](decompiled/00450360.c) | [assembly](decompiled/00450360.asm) |
| `0x004503a8` | `FUN_004503a8` |  | [decompiled](decompiled/004503a8.c) | [assembly](decompiled/004503a8.asm) |
| `0x004503ec` | `TTSW10_Button36Click` |  | [decompiled](decompiled/004503ec.c) | [assembly](decompiled/004503ec.asm) |
| `0x00450758` | `FUN_00450758` |  | [decompiled](decompiled/00450758.c) | [assembly](decompiled/00450758.asm) |
| `0x00450878` | `TTSW10_Image8Click` |  | [decompiled](decompiled/00450878.c) | [assembly](decompiled/00450878.asm) |
| `0x00450880` | `FUN_00450880` |  | [decompiled](decompiled/00450880.c) | [assembly](decompiled/00450880.asm) |
| `0x00450b78` | `TTSW10_Button37Click` |  | [decompiled](decompiled/00450b78.c) | [assembly](decompiled/00450b78.asm) |
| `0x00450ba0` | `TTSW10_Button38Click` |  | [decompiled](decompiled/00450ba0.c) | [assembly](decompiled/00450ba0.asm) |
| `0x00451b5d` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00451b5d.c) | [assembly](decompiled/00451b5d.asm) |
| `0x00451b62` | `root_00451b62` |  | [decompiled](decompiled/00451b62.c) | [assembly](decompiled/00451b62.asm) |
| `0x00451b78` | `TTSW10_Image9Click` |  | [decompiled](decompiled/00451b78.c) | [assembly](decompiled/00451b78.asm) |
| `0x00451b80` | `TTSW10_Image10Click` |  | [decompiled](decompiled/00451b80.c) | [assembly](decompiled/00451b80.asm) |
| `0x00451b88` | `TTSW10_Image12Click` |  | [decompiled](decompiled/00451b88.c) | [assembly](decompiled/00451b88.asm) |
| `0x00451b90` | `TTSW10_Image13Click` |  | [decompiled](decompiled/00451b90.c) | [assembly](decompiled/00451b90.asm) |
| `0x00451b98` | `mattock_wall` |  | [decompiled](decompiled/00451b98.c) | [assembly](decompiled/00451b98.asm) |
| `0x00451c20` | `classify_neighbor` |  | [decompiled](decompiled/00451c20.c) | [assembly](decompiled/00451c20.asm) |
| `0x00451d3c` | `crystal_lava` |  | [decompiled](decompiled/00451d3c.c) | [assembly](decompiled/00451d3c.asm) |
| `0x00451dfc` | `TTSW10_Image15Click` |  | [decompiled](decompiled/00451dfc.c) | [assembly](decompiled/00451dfc.asm) |
| `0x00451e04` | `TTSW10_Image16Click` |  | [decompiled](decompiled/00451e04.c) | [assembly](decompiled/00451e04.asm) |
| `0x00451e0c` | `TTSW10_Image17Click` |  | [decompiled](decompiled/00451e0c.c) | [assembly](decompiled/00451e0c.asm) |
| `0x00451e14` | `TTSW10_Image11Click` |  | [decompiled](decompiled/00451e14.c) | [assembly](decompiled/00451e14.asm) |
| `0x00451e1c` | `altar_health` |  | [decompiled](decompiled/00451e1c.c) | [assembly](decompiled/00451e1c.asm) |
| `0x00452098` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00452098.c) | [assembly](decompiled/00452098.asm) |
| `0x0045209d` | `root_0045209d` |  | [decompiled](decompiled/0045209d.c) | [assembly](decompiled/0045209d.asm) |
| `0x004520b4` | `altar_attack` |  | [decompiled](decompiled/004520b4.c) | [assembly](decompiled/004520b4.asm) |
| `0x00452336` | `FUN_00452336` |  | [decompiled](decompiled/00452336.c) | [assembly](decompiled/00452336.asm) |
| `0x00452344` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00452344.c) | [assembly](decompiled/00452344.asm) |
| `0x00452349` | `thunk_FUN_00452336` |  | [decompiled](decompiled/00452349.c) | [assembly](decompiled/00452349.asm) |
| `0x00452360` | `altar_defense` |  | [decompiled](decompiled/00452360.c) | [assembly](decompiled/00452360.asm) |
| `0x004525e4` | `FUN_004525e4` |  | [decompiled](decompiled/004525e4.c) | [assembly](decompiled/004525e4.asm) |
| `0x004525f2` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004525f2.c) | [assembly](decompiled/004525f2.asm) |
| `0x004525f7` | `thunk_FUN_004525e4` |  | [decompiled](decompiled/004525f7.c) | [assembly](decompiled/004525f7.asm) |
| `0x0045260c` | `TTSW10_Button42Click` |  | [decompiled](decompiled/0045260c.c) | [assembly](decompiled/0045260c.asm) |
| `0x0045265c` | `TTSW10_timer2timer` |  | [decompiled](decompiled/0045265c.c) | [assembly](decompiled/0045265c.asm) |
| `0x004526c0` | `FUN_004526c0` |  | [decompiled](decompiled/004526c0.c) | [assembly](decompiled/004526c0.asm) |
| `0x00454804` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00454804.c) | [assembly](decompiled/00454804.asm) |
| `0x00454809` | `root_00454809` |  | [decompiled](decompiled/00454809.c) | [assembly](decompiled/00454809.asm) |
| `0x004548a0` | `FUN_004548a0` |  | [decompiled](decompiled/004548a0.c) | [assembly](decompiled/004548a0.asm) |
| `0x00454a58` | `FUN_00454a58` |  | [decompiled](decompiled/00454a58.c) | [assembly](decompiled/00454a58.asm) |
| `0x00454c10` | `FUN_00454c10` |  | [decompiled](decompiled/00454c10.c) | [assembly](decompiled/00454c10.asm) |
| `0x00454da0` | `FUN_00454da0` |  | [decompiled](decompiled/00454da0.c) | [assembly](decompiled/00454da0.asm) |
| `0x00454de8` | `FUN_00454de8` |  | [decompiled](decompiled/00454de8.c) | [assembly](decompiled/00454de8.asm) |
| `0x00455bb5` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00455bb5.c) | [assembly](decompiled/00455bb5.asm) |
| `0x00455bba` | `root_00455bba` |  | [decompiled](decompiled/00455bba.c) | [assembly](decompiled/00455bba.asm) |
| `0x00455cb8` | `initialize_cycle` |  | [decompiled](decompiled/00455cb8.c) | [assembly](decompiled/00455cb8.asm) |
| `0x00460bd8` | `FUN_00460bd8` |  | [decompiled](decompiled/00460bd8.c) | [assembly](decompiled/00460bd8.asm) |
| `0x004610c4` | `FUN_004610c4` |  | [decompiled](decompiled/004610c4.c) | [assembly](decompiled/004610c4.asm) |
| `0x0046171c` | `FUN_0046171c` |  | [decompiled](decompiled/0046171c.c) | [assembly](decompiled/0046171c.asm) |
| `0x00461760` | `TTSW10_timer3ontimer` |  | [decompiled](decompiled/00461760.c) | [assembly](decompiled/00461760.asm) |
| `0x004618fc` | `TTSW10_button8onmousedown` |  | [decompiled](decompiled/004618fc.c) | [assembly](decompiled/004618fc.asm) |
| `0x00461944` | `FUN_00461944` |  | [decompiled](decompiled/00461944.c) | [assembly](decompiled/00461944.asm) |
| `0x00461984` | `TTSW10_button9onmousedown` |  | [decompiled](decompiled/00461984.c) | [assembly](decompiled/00461984.asm) |
| `0x004619cc` | `FUN_004619cc` |  | [decompiled](decompiled/004619cc.c) | [assembly](decompiled/004619cc.asm) |
| `0x00461a0c` | `FUN_00461a0c` |  | [decompiled](decompiled/00461a0c.c) | [assembly](decompiled/00461a0c.asm) |
| `0x00461ef4` | `FUN_00461ef4` |  | [decompiled](decompiled/00461ef4.c) | [assembly](decompiled/00461ef4.asm) |
| `0x00462560` | `FUN_00462560` |  | [decompiled](decompiled/00462560.c) | [assembly](decompiled/00462560.asm) |
| `0x004637e8` | `TTSW10_GameStart1Click` |  | [decompiled](decompiled/004637e8.c) | [assembly](decompiled/004637e8.asm) |
| `0x00463874` | `TTSW10_GameQuit1Click` |  | [decompiled](decompiled/00463874.c) | [assembly](decompiled/00463874.asm) |
| `0x0046391c` | `TTSW10_Exit1Click` |  | [decompiled](decompiled/0046391c.c) | [assembly](decompiled/0046391c.asm) |
| `0x0046397c` | `mevent` |  | [decompiled](decompiled/0046397c.c) | [assembly](decompiled/0046397c.asm) |
| `0x0046403a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0046403a.c) | [assembly](decompiled/0046403a.asm) |
| `0x0046403f` | `root_0046403f` |  | [decompiled](decompiled/0046403f.c) | [assembly](decompiled/0046403f.asm) |
| `0x00464048` | `opening_capture` |  | [decompiled](decompiled/00464048.c) | [assembly](decompiled/00464048.asm) |
| `0x004653a7` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004653a7.c) | [assembly](decompiled/004653a7.asm) |
| `0x004653ac` | `root_004653ac` |  | [decompiled](decompiled/004653ac.c) | [assembly](decompiled/004653ac.asm) |
| `0x004653b8` | `FUN_004653b8` |  | [decompiled](decompiled/004653b8.c) | [assembly](decompiled/004653b8.asm) |
| `0x00465882` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00465882.c) | [assembly](decompiled/00465882.asm) |
| `0x00465887` | `root_00465887` |  | [decompiled](decompiled/00465887.c) | [assembly](decompiled/00465887.asm) |
| `0x00465900` | `touzoku` |  | [decompiled](decompiled/00465900.c) | [assembly](decompiled/00465900.asm) |
| `0x004660b6` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004660b6.c) | [assembly](decompiled/004660b6.asm) |
| `0x004660bb` | `root_004660bb` |  | [decompiled](decompiled/004660bb.c) | [assembly](decompiled/004660bb.asm) |
| `0x004660d0` | `doorstackin` |  | [decompiled](decompiled/004660d0.c) | [assembly](decompiled/004660d0.asm) |
| `0x004664e4` | `moncheck` |  | [decompiled](decompiled/004664e4.c) | [assembly](decompiled/004664e4.asm) |
| `0x0046cb1c` | `ichicheck` |  | [decompiled](decompiled/0046cb1c.c) | [assembly](decompiled/0046cb1c.asm) |
| `0x004770c4` | `thunk_FUN_00403140` |  | [decompiled](decompiled/004770c4.c) | [assembly](decompiled/004770c4.asm) |
| `0x004770c9` | `root_004770c9` |  | [decompiled](decompiled/004770c9.c) | [assembly](decompiled/004770c9.asm) |
| `0x004770e0` | `FUN_004770e0` |  | [decompiled](decompiled/004770e0.c) | [assembly](decompiled/004770e0.asm) |
| `0x00478f0c` | `FUN_00478f0c` |  | [decompiled](decompiled/00478f0c.c) | [assembly](decompiled/00478f0c.asm) |
| `0x00479ea9` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/00479ea9.c) | [assembly](decompiled/00479ea9.asm) |
| `0x00479eae` | `root_00479eae` |  | [decompiled](decompiled/00479eae.c) | [assembly](decompiled/00479eae.asm) |
| `0x0047bd30` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047bd30.c) | [assembly](decompiled/0047bd30.asm) |
| `0x0047bd35` | `root_0047bd35` |  | [decompiled](decompiled/0047bd35.c) | [assembly](decompiled/0047bd35.asm) |
| `0x0047beac` | `doorcheck` |  | [decompiled](decompiled/0047beac.c) | [assembly](decompiled/0047beac.asm) |
| `0x0047c20c` | `TTSW10_wavon1Click` |  | [decompiled](decompiled/0047c20c.c) | [assembly](decompiled/0047c20c.asm) |
| `0x0047c258` | `FUN_0047c258` |  | [decompiled](decompiled/0047c258.c) | [assembly](decompiled/0047c258.asm) |
| `0x0047c2bc` | `FUN_0047c2bc` |  | [decompiled](decompiled/0047c2bc.c) | [assembly](decompiled/0047c2bc.asm) |
| `0x0047c70c` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047c70c.c) | [assembly](decompiled/0047c70c.asm) |
| `0x0047c711` | `root_0047c711` |  | [decompiled](decompiled/0047c711.c) | [assembly](decompiled/0047c711.asm) |
| `0x0047c8f8` | `FUN_0047c8f8` |  | [decompiled](decompiled/0047c8f8.c) | [assembly](decompiled/0047c8f8.asm) |
| `0x0047c978` | `FUN_0047c978` |  | [decompiled](decompiled/0047c978.c) | [assembly](decompiled/0047c978.asm) |
| `0x0047d2d8` | `FUN_0047d2d8` |  | [decompiled](decompiled/0047d2d8.c) | [assembly](decompiled/0047d2d8.asm) |
| `0x0047d318` | `TTSW10_About1Click` |  | [decompiled](decompiled/0047d318.c) | [assembly](decompiled/0047d318.asm) |
| `0x0047d324` | `FUN_0047d324` |  | [decompiled](decompiled/0047d324.c) | [assembly](decompiled/0047d324.asm) |
| `0x0047d44a` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047d44a.c) | [assembly](decompiled/0047d44a.asm) |
| `0x0047d44f` | `root_0047d44f` |  | [decompiled](decompiled/0047d44f.c) | [assembly](decompiled/0047d44f.asm) |
| `0x0047d4a4` | `FUN_0047d4a4` |  | [decompiled](decompiled/0047d4a4.c) | [assembly](decompiled/0047d4a4.asm) |
| `0x0047d9d4` | `FUN_0047d9d4` |  | [decompiled](decompiled/0047d9d4.c) | [assembly](decompiled/0047d9d4.asm) |
| `0x0047db5e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047db5e.c) | [assembly](decompiled/0047db5e.asm) |
| `0x0047db63` | `root_0047db63` |  | [decompiled](decompiled/0047db63.c) | [assembly](decompiled/0047db63.asm) |
| `0x0047db94` | `load_slot_2` |  | [decompiled](decompiled/0047db94.c) | [assembly](decompiled/0047db94.asm) |
| `0x0047dd1e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047dd1e.c) | [assembly](decompiled/0047dd1e.asm) |
| `0x0047dd23` | `root_0047dd23` |  | [decompiled](decompiled/0047dd23.c) | [assembly](decompiled/0047dd23.asm) |
| `0x0047dd54` | `load_slot_3` |  | [decompiled](decompiled/0047dd54.c) | [assembly](decompiled/0047dd54.asm) |
| `0x0047dede` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047dede.c) | [assembly](decompiled/0047dede.asm) |
| `0x0047dee3` | `root_0047dee3` |  | [decompiled](decompiled/0047dee3.c) | [assembly](decompiled/0047dee3.asm) |
| `0x0047df14` | `load_slot_4` |  | [decompiled](decompiled/0047df14.c) | [assembly](decompiled/0047df14.asm) |
| `0x0047e09e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047e09e.c) | [assembly](decompiled/0047e09e.asm) |
| `0x0047e0a3` | `root_0047e0a3` |  | [decompiled](decompiled/0047e0a3.c) | [assembly](decompiled/0047e0a3.asm) |
| `0x0047e0d4` | `load_slot_5` |  | [decompiled](decompiled/0047e0d4.c) | [assembly](decompiled/0047e0d4.asm) |
| `0x0047e25e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047e25e.c) | [assembly](decompiled/0047e25e.asm) |
| `0x0047e263` | `root_0047e263` |  | [decompiled](decompiled/0047e263.c) | [assembly](decompiled/0047e263.asm) |
| `0x0047e294` | `load_slot_6` |  | [decompiled](decompiled/0047e294.c) | [assembly](decompiled/0047e294.asm) |
| `0x0047e41e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047e41e.c) | [assembly](decompiled/0047e41e.asm) |
| `0x0047e423` | `root_0047e423` |  | [decompiled](decompiled/0047e423.c) | [assembly](decompiled/0047e423.asm) |
| `0x0047e454` | `load_slot_7` |  | [decompiled](decompiled/0047e454.c) | [assembly](decompiled/0047e454.asm) |
| `0x0047e5de` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047e5de.c) | [assembly](decompiled/0047e5de.asm) |
| `0x0047e5e3` | `root_0047e5e3` |  | [decompiled](decompiled/0047e5e3.c) | [assembly](decompiled/0047e5e3.asm) |
| `0x0047e614` | `load_slot_8` |  | [decompiled](decompiled/0047e614.c) | [assembly](decompiled/0047e614.asm) |
| `0x0047e79e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047e79e.c) | [assembly](decompiled/0047e79e.asm) |
| `0x0047e7a3` | `root_0047e7a3` |  | [decompiled](decompiled/0047e7a3.c) | [assembly](decompiled/0047e7a3.asm) |
| `0x0047e7d4` | `FUN_0047e7d4` |  | [decompiled](decompiled/0047e7d4.c) | [assembly](decompiled/0047e7d4.asm) |
| `0x0047ea42` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0047ea42.c) | [assembly](decompiled/0047ea42.asm) |
| `0x0047ea47` | `root_0047ea47` |  | [decompiled](decompiled/0047ea47.c) | [assembly](decompiled/0047ea47.asm) |
| `0x0047ea93` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047ea93.c) | [assembly](decompiled/0047ea93.asm) |
| `0x0047ea98` | `root_0047ea98` |  | [decompiled](decompiled/0047ea98.c) | [assembly](decompiled/0047ea98.asm) |
| `0x0047eadc` | `write_original_save` |  | [decompiled](decompiled/0047eadc.c) | [assembly](decompiled/0047eadc.asm) |
| `0x0047ec11` | `thunk_FUN_00402f4c` |  | [decompiled](decompiled/0047ec11.c) | [assembly](decompiled/0047ec11.asm) |
| `0x0047ec16` | `root_0047ec16` |  | [decompiled](decompiled/0047ec16.c) | [assembly](decompiled/0047ec16.asm) |
| `0x0047ecc4` | `save_slot_1` |  | [decompiled](decompiled/0047ecc4.c) | [assembly](decompiled/0047ecc4.asm) |
| `0x0047ed97` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047ed97.c) | [assembly](decompiled/0047ed97.asm) |
| `0x0047ed9c` | `root_0047ed9c` |  | [decompiled](decompiled/0047ed9c.c) | [assembly](decompiled/0047ed9c.asm) |
| `0x0047edb8` | `save_slot_2` |  | [decompiled](decompiled/0047edb8.c) | [assembly](decompiled/0047edb8.asm) |
| `0x0047ee8b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047ee8b.c) | [assembly](decompiled/0047ee8b.asm) |
| `0x0047ee90` | `root_0047ee90` |  | [decompiled](decompiled/0047ee90.c) | [assembly](decompiled/0047ee90.asm) |
| `0x0047eeac` | `save_slot_3` |  | [decompiled](decompiled/0047eeac.c) | [assembly](decompiled/0047eeac.asm) |
| `0x0047ef7f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047ef7f.c) | [assembly](decompiled/0047ef7f.asm) |
| `0x0047ef84` | `root_0047ef84` |  | [decompiled](decompiled/0047ef84.c) | [assembly](decompiled/0047ef84.asm) |
| `0x0047efa0` | `save_slot_4` |  | [decompiled](decompiled/0047efa0.c) | [assembly](decompiled/0047efa0.asm) |
| `0x0047f073` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047f073.c) | [assembly](decompiled/0047f073.asm) |
| `0x0047f078` | `root_0047f078` |  | [decompiled](decompiled/0047f078.c) | [assembly](decompiled/0047f078.asm) |
| `0x0047f094` | `save_slot_5` |  | [decompiled](decompiled/0047f094.c) | [assembly](decompiled/0047f094.asm) |
| `0x0047f167` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047f167.c) | [assembly](decompiled/0047f167.asm) |
| `0x0047f16c` | `root_0047f16c` |  | [decompiled](decompiled/0047f16c.c) | [assembly](decompiled/0047f16c.asm) |
| `0x0047f188` | `save_slot_6` |  | [decompiled](decompiled/0047f188.c) | [assembly](decompiled/0047f188.asm) |
| `0x0047f25b` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047f25b.c) | [assembly](decompiled/0047f25b.asm) |
| `0x0047f260` | `root_0047f260` |  | [decompiled](decompiled/0047f260.c) | [assembly](decompiled/0047f260.asm) |
| `0x0047f27c` | `save_slot_7` |  | [decompiled](decompiled/0047f27c.c) | [assembly](decompiled/0047f27c.asm) |
| `0x0047f34f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047f34f.c) | [assembly](decompiled/0047f34f.asm) |
| `0x0047f354` | `root_0047f354` |  | [decompiled](decompiled/0047f354.c) | [assembly](decompiled/0047f354.asm) |
| `0x0047f370` | `save_slot_8` |  | [decompiled](decompiled/0047f370.c) | [assembly](decompiled/0047f370.asm) |
| `0x0047f443` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0047f443.c) | [assembly](decompiled/0047f443.asm) |
| `0x0047f448` | `root_0047f448` |  | [decompiled](decompiled/0047f448.c) | [assembly](decompiled/0047f448.asm) |
| `0x0047f464` | `TTSW10_High1Click` |  | [decompiled](decompiled/0047f464.c) | [assembly](decompiled/0047f464.asm) |
| `0x0047f46c` | `TTSW10_Middle1Click` |  | [decompiled](decompiled/0047f46c.c) | [assembly](decompiled/0047f46c.asm) |
| `0x0047f474` | `TTSW10_Low1Click` |  | [decompiled](decompiled/0047f474.c) | [assembly](decompiled/0047f474.asm) |
| `0x0047f47c` | `FUN_0047f47c` |  | [decompiled](decompiled/0047f47c.c) | [assembly](decompiled/0047f47c.asm) |
| `0x0047f4e0` | `FUN_0047f4e0` |  | [decompiled](decompiled/0047f4e0.c) | [assembly](decompiled/0047f4e0.asm) |
| `0x0047f544` | `FUN_0047f544` |  | [decompiled](decompiled/0047f544.c) | [assembly](decompiled/0047f544.asm) |
| `0x0047f5a8` | `FUN_0047f5a8` |  | [decompiled](decompiled/0047f5a8.c) | [assembly](decompiled/0047f5a8.asm) |
| `0x0047f5e8` | `TTSW10_NormalOption1Click` |  | [decompiled](decompiled/0047f5e8.c) | [assembly](decompiled/0047f5e8.asm) |
| `0x0047f6cc` | `TTSW10_Large1Click` |  | [decompiled](decompiled/0047f6cc.c) | [assembly](decompiled/0047f6cc.asm) |
| `0x0047f724` | `TTSW10_Small1Click` |  | [decompiled](decompiled/0047f724.c) | [assembly](decompiled/0047f724.asm) |
| `0x0047f77c` | `TTSW10_Normal1Click` |  | [decompiled](decompiled/0047f77c.c) | [assembly](decompiled/0047f77c.asm) |
| `0x0047f7d4` | `FUN_0047f7d4` |  | [decompiled](decompiled/0047f7d4.c) | [assembly](decompiled/0047f7d4.asm) |
| `0x00480264` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00480264.c) | [assembly](decompiled/00480264.asm) |
| `0x00480269` | `root_00480269` |  | [decompiled](decompiled/00480269.c) | [assembly](decompiled/00480269.asm) |
| `0x0048028c` | `FUN_0048028c` |  | [decompiled](decompiled/0048028c.c) | [assembly](decompiled/0048028c.asm) |
| `0x004802fc` | `FUN_004802fc` |  | [decompiled](decompiled/004802fc.c) | [assembly](decompiled/004802fc.asm) |
| `0x00480340` | `FUN_00480340` |  | [decompiled](decompiled/00480340.c) | [assembly](decompiled/00480340.asm) |
| `0x00480384` | `FUN_00480384` |  | [decompiled](decompiled/00480384.c) | [assembly](decompiled/00480384.asm) |
| `0x00480a90` | `FUN_00480a90` |  | [decompiled](decompiled/00480a90.c) | [assembly](decompiled/00480a90.asm) |
| `0x00480e0c` | `TTSW10_tiny1Click` |  | [decompiled](decompiled/00480e0c.c) | [assembly](decompiled/00480e0c.asm) |
| `0x00480e64` | `TTSW10_KeyboardControl1Click` |  | [decompiled](decompiled/00480e64.c) | [assembly](decompiled/00480e64.asm) |
| `0x00480ee0` | `FUN_00480ee0` |  | [decompiled](decompiled/00480ee0.c) | [assembly](decompiled/00480ee0.asm) |
| `0x00480f60` | `FUN_00480f60` |  | [decompiled](decompiled/00480f60.c) | [assembly](decompiled/00480f60.asm) |
| `0x0048197f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0048197f.c) | [assembly](decompiled/0048197f.asm) |
| `0x00481984` | `root_00481984` |  | [decompiled](decompiled/00481984.c) | [assembly](decompiled/00481984.asm) |
| `0x0048198c` | `FUN_0048198c` |  | [decompiled](decompiled/0048198c.c) | [assembly](decompiled/0048198c.asm) |
| `0x00481e80` | `FUN_00481e80` |  | [decompiled](decompiled/00481e80.c) | [assembly](decompiled/00481e80.asm) |
| `0x0048201c` | `FUN_0048201c` |  | [decompiled](decompiled/0048201c.c) | [assembly](decompiled/0048201c.asm) |
| `0x00482128` | `FUN_00482128` |  | [decompiled](decompiled/00482128.c) | [assembly](decompiled/00482128.asm) |
| `0x00482234` | `FUN_00482234` |  | [decompiled](decompiled/00482234.c) | [assembly](decompiled/00482234.asm) |
| `0x00482340` | `FUN_00482340` |  | [decompiled](decompiled/00482340.c) | [assembly](decompiled/00482340.asm) |
| `0x0048244c` | `FUN_0048244c` |  | [decompiled](decompiled/0048244c.c) | [assembly](decompiled/0048244c.asm) |
| `0x00482558` | `FUN_00482558` |  | [decompiled](decompiled/00482558.c) | [assembly](decompiled/00482558.asm) |
| `0x00482664` | `FUN_00482664` |  | [decompiled](decompiled/00482664.c) | [assembly](decompiled/00482664.asm) |
| `0x00482770` | `FUN_00482770` |  | [decompiled](decompiled/00482770.c) | [assembly](decompiled/00482770.asm) |
| `0x0048287c` | `FUN_0048287c` |  | [decompiled](decompiled/0048287c.c) | [assembly](decompiled/0048287c.asm) |
| `0x00482988` | `FUN_00482988` |  | [decompiled](decompiled/00482988.c) | [assembly](decompiled/00482988.asm) |
| `0x00482a5f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00482a5f.c) | [assembly](decompiled/00482a5f.asm) |
| `0x00482a64` | `root_00482a64` |  | [decompiled](decompiled/00482a64.c) | [assembly](decompiled/00482a64.asm) |
| `0x00482a80` | `TTSW10_mediaplayer5onnotify` |  | [decompiled](decompiled/00482a80.c) | [assembly](decompiled/00482a80.asm) |
| `0x00482a98` | `TTSW10_timer4ontimer` |  | [decompiled](decompiled/00482a98.c) | [assembly](decompiled/00482a98.asm) |
| `0x00482e3e` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00482e3e.c) | [assembly](decompiled/00482e3e.asm) |
| `0x00482e43` | `root_00482e43` |  | [decompiled](decompiled/00482e43.c) | [assembly](decompiled/00482e43.asm) |
| `0x00482e60` | `FUN_00482e60` |  | [decompiled](decompiled/00482e60.c) | [assembly](decompiled/00482e60.asm) |
| `0x0048473f` | `thunk_FUN_00403140` |  | [decompiled](decompiled/0048473f.c) | [assembly](decompiled/0048473f.asm) |
| `0x00484744` | `root_00484744` |  | [decompiled](decompiled/00484744.c) | [assembly](decompiled/00484744.asm) |
| `0x00484a20` | `TTSW10_K5Click` |  | [decompiled](decompiled/00484a20.c) | [assembly](decompiled/00484a20.asm) |
| `0x00484a50` | `TTSW10_K6Click` |  | [decompiled](decompiled/00484a50.c) | [assembly](decompiled/00484a50.asm) |
| `0x00484b04` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00484b04.c) | [assembly](decompiled/00484b04.asm) |
| `0x00484b09` | `root_00484b09` |  | [decompiled](decompiled/00484b09.c) | [assembly](decompiled/00484b09.asm) |
| `0x00484b14` | `TTSW10_TSW10close` |  | [decompiled](decompiled/00484b14.c) | [assembly](decompiled/00484b14.asm) |
| `0x00484b5c` | `TTSW10_BitBtn1Click` |  | [decompiled](decompiled/00484b5c.c) | [assembly](decompiled/00484b5c.asm) |
| `0x00484bb0` | `TTSW10_BitBtn2Click` |  | [decompiled](decompiled/00484bb0.c) | [assembly](decompiled/00484bb0.asm) |
| `0x00484c04` | `TTSW10_BitBtn3Click` |  | [decompiled](decompiled/00484c04.c) | [assembly](decompiled/00484c04.asm) |
| `0x00484c58` | `TTSW10_BitBtn4Click` |  | [decompiled](decompiled/00484c58.c) | [assembly](decompiled/00484c58.asm) |
| `0x00484cac` | `FUN_00484cac` |  | [decompiled](decompiled/00484cac.c) | [assembly](decompiled/00484cac.asm) |
| `0x00484d74` | `TTSW10_N640x4001Click` |  | [decompiled](decompiled/00484d74.c) | [assembly](decompiled/00484d74.asm) |
| `0x00484de0` | `TTSW10_image34click` |  | [decompiled](decompiled/00484de0.c) | [assembly](decompiled/00484de0.asm) |
| `0x00484de8` | `FUN_00484de8` |  | [decompiled](decompiled/00484de8.c) | [assembly](decompiled/00484de8.asm) |
| `0x00484f48` | `FUN_00484f48` |  | [decompiled](decompiled/00484f48.c) | [assembly](decompiled/00484f48.asm) |
| `0x00488842` | `thunk_FUN_00403140` |  | [decompiled](decompiled/00488842.c) | [assembly](decompiled/00488842.asm) |
| `0x00488847` | `root_00488847` |  | [decompiled](decompiled/00488847.c) | [assembly](decompiled/00488847.asm) |
| `0x00488d50` | `entry` |  | [decompiled](decompiled/00488d50.c) | [assembly](decompiled/00488d50.asm) |
