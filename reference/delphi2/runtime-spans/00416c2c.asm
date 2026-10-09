; TWinControl.CanFocus; compiler-assisted focused span, not a new Ghidra ownership claim
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
00416c2c  53  PUSH ebx
00416c2d  56  PUSH esi
00416c2e  8bf0  MOV esi, eax
00416c30  33db  XOR ebx, ebx
00416c32  8bc6  MOV eax, esi
00416c34  e8c3930000  CALL 0x41fffc
00416c39  8bd0  MOV edx, eax
00416c3b  85d2  TEST edx, edx
00416c3d  741b  JE 0x416c5a
00416c3f  8bc6  MOV eax, esi
00416c41  3bd0  CMP edx, eax
00416c43  7413  JE 0x416c58
00416c45  80783700  CMP byte ptr [eax + 0x37], 0
00416c49  740f  JE 0x416c5a
00416c4b  80783800  CMP byte ptr [eax + 0x38], 0
00416c4f  7409  JE 0x416c5a
00416c51  8b4020  MOV eax, dword ptr [eax + 0x20]
00416c54  3bd0  CMP edx, eax
00416c56  75ed  JNE 0x416c45
00416c58  b301  MOV bl, 1
00416c5a  8bc3  MOV eax, ebx
00416c5c  5e  POP esi
00416c5d  5b  POP ebx
00416c5e  c3  RET
