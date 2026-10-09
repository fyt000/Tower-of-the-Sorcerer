; FUN_0041dbac at 0x0041dbac
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041dbac  53  PUSH EBX
0041dbad  56  PUSH ESI
0041dbae  8b5810  MOV EBX,dword ptr [EAX + 0x10]
0041dbb1  837b0c00  CMP dword ptr [EBX + 0xc],0x0
0041dbb5  7526  JNZ 0x0041dbdd
0041dbb7  8b4308  MOV EAX,dword ptr [EBX + 0x8]
0041dbba  85c0  TEST EAX,EAX
0041dbbc  741f  JZ 0x0041dbdd
0041dbbe  33d2  XOR EDX,EDX
0041dbc0  e84bd3feff  CALL 0x0040af10
0041dbc5  8b7308  MOV ESI,dword ptr [EBX + 0x8]
0041dbc8  8bc6  MOV EAX,ESI
0041dbca  e84dd3feff  CALL 0x0040af1c
0041dbcf  50  PUSH EAX
0041dbd0  8d4b10  LEA ECX,[EBX + 0x10]
0041dbd3  8d530c  LEA EDX,[EBX + 0xc]
0041dbd6  8bc6  MOV EAX,ESI
0041dbd8  e82bd8ffff  CALL 0x0041b408
0041dbdd  5e  POP ESI
0041dbde  5b  POP EBX
0041dbdf  c3  RET
