; Runtime boundary 0042cec8; original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0042cec8  55  PUSH EBP
0042cec9  8bec  MOV EBP,ESP
0042cecb  51  PUSH ECX
0042cecc  66894dfe  MOV word ptr [EBP + -0x2],CX
0042ced0  8b4d08  MOV ECX,dword ptr [EBP + 0x8]
0042ced3  51  PUSH ECX
0042ced4  6aff  PUSH -0x1
0042ced6  6aff  PUSH -0x1
0042ced8  668b4dfe  MOV CX,word ptr [EBP + -0x2]
0042cedc  e807000000  CALL 0x0042cee8
0042cee1  59  POP ECX
0042cee2  5d  POP EBP
0042cee3  c20400  RET 0x4
