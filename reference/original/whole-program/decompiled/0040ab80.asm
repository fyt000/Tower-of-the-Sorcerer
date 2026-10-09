; FUN_0040ab80 at 0x0040ab80
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040ab80  53  PUSH EBX
0040ab81  8b5808  MOV EBX,dword ptr [EAX + 0x8]
0040ab84  8d14d3  LEA EDX,[EBX + EDX*0x8]
0040ab87  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040ab8a  8d04c8  LEA EAX,[EAX + ECX*0x8]
0040ab8d  8b0a  MOV ECX,dword ptr [EDX]
0040ab8f  8b18  MOV EBX,dword ptr [EAX]
0040ab91  891a  MOV dword ptr [EDX],EBX
0040ab93  8908  MOV dword ptr [EAX],ECX
0040ab95  8b4a04  MOV ECX,dword ptr [EDX + 0x4]
0040ab98  8b5804  MOV EBX,dword ptr [EAX + 0x4]
0040ab9b  895a04  MOV dword ptr [EDX + 0x4],EBX
0040ab9e  894804  MOV dword ptr [EAX + 0x4],ECX
0040aba1  5b  POP EBX
0040aba2  c3  RET
