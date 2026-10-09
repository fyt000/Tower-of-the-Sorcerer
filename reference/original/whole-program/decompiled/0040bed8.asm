; FUN_0040bed8 at 0x0040bed8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040bed8  55  PUSH EBP
0040bed9  8bec  MOV EBP,ESP
0040bedb  53  PUSH EBX
0040bedc  56  PUSH ESI
0040bedd  57  PUSH EDI
0040bede  33c0  XOR EAX,EAX
0040bee0  55  PUSH EBP
0040bee1  6825bf4000  PUSH 0x40bf25
0040bee6  64ff30  PUSH dword ptr FS:[EAX]
0040bee9  648920  MOV dword ptr FS:[EAX],ESP
0040beec  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040beef  8b40f4  MOV EAX,dword ptr [EAX + -0xc]
0040bef2  8b5028  MOV EDX,dword ptr [EAX + 0x28]
0040bef5  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040bef8  8b40f0  MOV EAX,dword ptr [EAX + -0x10]
0040befb  66bbfbff  MOV BX,0xfffb
0040beff  e8d86dffff  CALL 0x00402cdc
0040bf04  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040bf07  8d48e8  LEA ECX,[EAX + -0x18]
0040bf0a  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040bf0d  8b50f0  MOV EDX,dword ptr [EAX + -0x10]
0040bf10  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040bf13  8b40f4  MOV EAX,dword ptr [EAX + -0xc]
0040bf16  8b18  MOV EBX,dword ptr [EAX]
0040bf18  ff5314  CALL dword ptr [EBX + 0x14]
0040bf1b  33c0  XOR EAX,EAX
0040bf1d  5a  POP EDX
0040bf1e  59  POP ECX
0040bf1f  59  POP ECX
0040bf20  648910  MOV dword ptr FS:[EAX],EDX
0040bf23  eb23  JMP 0x0040bf48
