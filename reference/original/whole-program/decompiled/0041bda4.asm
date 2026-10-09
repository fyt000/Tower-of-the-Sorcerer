; FUN_0041bda4 at 0x0041bda4
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041bda4  55  PUSH EBP
0041bda5  8bec  MOV EBP,ESP
0041bda7  53  PUSH EBX
0041bda8  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0041bdab  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0041bdae  83781c00  CMP dword ptr [EAX + 0x1c],0x0
0041bdb2  7436  JZ 0x0041bdea
0041bdb4  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0041bdb7  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0041bdba  8b581c  MOV EBX,dword ptr [EAX + 0x1c]
0041bdbd  8bc3  MOV EAX,EBX
0041bdbf  bac4904100  MOV EDX,0x4190c4
0041bdc4  e8b36efeff  CALL 0x00402c7c
0041bdc9  84c0  TEST AL,AL
0041bdcb  7418  JZ 0x0041bde5
0041bdcd  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0041bdd0  8bd3  MOV EDX,EBX
0041bdd2  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0041bdd5  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0041bdd8  8b08  MOV ECX,dword ptr [EAX]
0041bdda  ff5114  CALL dword ptr [ECX + 0x14]
0041bddd  84c0  TEST AL,AL
0041bddf  7404  JZ 0x0041bde5
0041bde1  33c0  XOR EAX,EAX
0041bde3  eb12  JMP 0x0041bdf7
0041bde5  b001  MOV AL,0x1
0041bde7  5b  POP EBX
0041bde8  5d  POP EBP
0041bde9  c3  RET
0041bdea  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0041bded  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0041bdf0  8b10  MOV EDX,dword ptr [EAX]
0041bdf2  ff5218  CALL dword ptr [EDX + 0x18]
0041bdf5  3401  XOR AL,0x1
0041bdf7  5b  POP EBX
0041bdf8  5d  POP EBP
0041bdf9  c3  RET
