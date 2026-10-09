; FUN_0040e7a8 at 0x0040e7a8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040e7a8  55  PUSH EBP
0040e7a9  8bec  MOV EBP,ESP
0040e7ab  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040e7ae  8378fc00  CMP dword ptr [EAX + -0x4],0x0
0040e7b2  7419  JZ 0x0040e7cd
0040e7b4  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040e7b7  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0040e7ba  668b4018  MOV AX,word ptr [EAX + 0x18]
0040e7be  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0040e7c1  8b52fc  MOV EDX,dword ptr [EDX + -0x4]
0040e7c4  663b4218  CMP AX,word ptr [EDX + 0x18]
0040e7c8  0f95c0  SETNZ AL
0040e7cb  5d  POP EBP
0040e7cc  c3  RET
0040e7cd  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040e7d0  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0040e7d3  6683781800  CMP word ptr [EAX + 0x18],0x0
0040e7d8  0f95c0  SETNZ AL
0040e7db  5d  POP EBP
0040e7dc  c3  RET
