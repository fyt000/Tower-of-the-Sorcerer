; FUN_0040dc28 at 0x0040dc28
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040dc28  55  PUSH EBP
0040dc29  8bec  MOV EBP,ESP
0040dc2b  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dc2e  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040dc31  50  PUSH EAX
0040dc32  e875fdffff  CALL 0x0040d9ac
0040dc37  59  POP ECX
0040dc38  84c0  TEST AL,AL
0040dc3a  7425  JZ 0x0040dc61
0040dc3c  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dc3f  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040dc42  8b50f4  MOV EDX,dword ptr [EAX + -0xc]
0040dc45  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dc48  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040dc4b  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040dc4e  8b401c  MOV EAX,dword ptr [EAX + 0x1c]
0040dc51  e8c6a6ffff  CALL 0x0040831c
0040dc56  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0040dc59  3b42fc  CMP EAX,dword ptr [EDX + -0x4]
0040dc5c  0f94c0  SETZ AL
0040dc5f  5d  POP EBP
0040dc60  c3  RET
0040dc61  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dc64  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040dc67  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0040dc6a  8b5208  MOV EDX,dword ptr [EDX + 0x8]
0040dc6d  8b52f4  MOV EDX,dword ptr [EDX + -0xc]
0040dc70  3b4214  CMP EAX,dword ptr [EDX + 0x14]
0040dc73  0f94c0  SETZ AL
0040dc76  5d  POP EBP
0040dc77  c3  RET
