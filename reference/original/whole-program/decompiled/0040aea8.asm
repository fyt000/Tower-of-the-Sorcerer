; FUN_0040aea8 at 0x0040aea8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040aea8  53  PUSH EBX
0040aea9  56  PUSH ESI
0040aeaa  8bda  MOV EBX,EDX
0040aeac  8bf0  MOV ESI,EAX
0040aeae  3a5e14  CMP BL,byte ptr [ESI + 0x14]
0040aeb1  740e  JZ 0x0040aec1
0040aeb3  84db  TEST BL,BL
0040aeb5  7407  JZ 0x0040aebe
0040aeb7  8bc6  MOV EAX,ESI
0040aeb9  8b10  MOV EDX,dword ptr [EAX]
0040aebb  ff5274  CALL dword ptr [EDX + 0x74]
0040aebe  885e14  MOV byte ptr [ESI + 0x14],BL
0040aec1  5e  POP ESI
0040aec2  5b  POP EBX
0040aec3  c3  RET
