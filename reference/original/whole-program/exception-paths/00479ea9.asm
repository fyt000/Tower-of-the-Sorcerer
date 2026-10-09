; Exception continuation for TTSW10.yousei; handler 0x00479ea9
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
; Bounded direct CFG; calls are retained, not inlined; unresolved exits are in inventory.json.
00479eae  b850be4700  MOV eax, 0x47be50
00479eb3  e8c030fbff  CALL 0x42cf78
00479eb8  8b45f0  MOV eax, dword ptr [ebp - 0x10]
00479ebb  83f805  CMP eax, 5
00479ebe  0f871e090000  JA 0x47a7e2
00479ec4  ff2485cb9e4700  JMP dword ptr [eax*4 + 0x479ecb]
0047a7e2  e8818af8ff  CALL 0x403268
