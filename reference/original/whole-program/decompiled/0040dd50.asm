; FUN_0040dd50 at 0x0040dd50
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040dd50  55  PUSH EBP
0040dd51  8bec  MOV EBP,ESP
0040dd53  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dd56  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040dd59  50  PUSH EAX
0040dd5a  e84dfcffff  CALL 0x0040d9ac
0040dd5f  59  POP ECX
0040dd60  84c0  TEST AL,AL
0040dd62  742a  JZ 0x0040dd8e
0040dd64  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dd67  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040dd6a  8b50f4  MOV EDX,dword ptr [EAX + -0xc]
0040dd6d  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dd70  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040dd73  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040dd76  8b401c  MOV EAX,dword ptr [EAX + 0x1c]
0040dd79  e812a8ffff  CALL 0x00408590
0040dd7e  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dd81  db68f6  FLD tword ptr [EAX + -0xa]
0040dd84  ded9  FCOMPP
0040dd86  dfe0  FNSTSW AX
0040dd88  9e  SAHF
0040dd89  0f94c0  SETZ AL
0040dd8c  5d  POP EBP
0040dd8d  c3  RET
0040dd8e  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dd91  db68f6  FLD tword ptr [EAX + -0xa]
0040dd94  d81da4dd4000  FCOMP dword ptr [0x0040dda4]
0040dd9a  dfe0  FNSTSW AX
0040dd9c  9e  SAHF
0040dd9d  0f94c0  SETZ AL
0040dda0  5d  POP EBP
0040dda1  c3  RET
