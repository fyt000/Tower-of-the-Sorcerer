; TButton.CMDialogKey; compiler-assisted focused span, not a new Ghidra ownership claim
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0042a480  53  PUSH ebx
0042a481  56  PUSH esi
0042a482  8bf2  MOV esi, edx
0042a484  8bd8  MOV ebx, eax
0042a486  66837e040d  CMP word ptr [esi + 4], 0xd
0042a48b  7509  JNE 0x42a496
0042a48d  80bb0601000000  CMP byte ptr [ebx + 0x106], 0
0042a494  7510  JNE 0x42a4a6
0042a496  66837e041b  CMP word ptr [esi + 4], 0x1b
0042a49b  753b  JNE 0x42a4d8
0042a49d  80bb0501000000  CMP byte ptr [ebx + 0x105], 0
0042a4a4  7432  JE 0x42a4d8
0042a4a6  8b4608  MOV eax, dword ptr [esi + 8]
0042a4a9  e8725affff  CALL 0x41ff20
0042a4ae  8a15e4a44200  MOV dl, byte ptr [0x42a4e4]
0042a4b4  3ad0  CMP dl, al
0042a4b6  7520  JNE 0x42a4d8
0042a4b8  8bc3  MOV eax, ebx
0042a4ba  e86dc7feff  CALL 0x416c2c
0042a4bf  84c0  TEST al, al
0042a4c1  7415  JE 0x42a4d8
0042a4c3  8bc3  MOV eax, ebx
0042a4c5  66bbf5ff  MOV bx, 0xfff5
0042a4c9  e80e88fdff  CALL 0x402cdc
0042a4ce  c7460c01000000  MOV dword ptr [esi + 0xc], 1
0042a4d5  5e  POP esi
0042a4d6  5b  POP ebx
0042a4d7  c3  RET
0042a4d8  8bd6  MOV edx, esi
0042a4da  8bc3  MOV eax, ebx
0042a4dc  e8f3bdfeff  CALL 0x4162d4
0042a4e1  5e  POP esi
0042a4e2  5b  POP ebx
0042a4e3  c3  RET
