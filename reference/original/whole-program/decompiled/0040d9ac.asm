; FUN_0040d9ac at 0x0040d9ac
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040d9ac  55  PUSH EBP
0040d9ad  8bec  MOV EBP,ESP
0040d9af  53  PUSH EBX
0040d9b0  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040d9b3  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040d9b6  83781c00  CMP dword ptr [EAX + 0x1c],0x0
0040d9ba  7430  JZ 0x0040d9ec
0040d9bc  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040d9bf  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0040d9c2  e8b151ffff  CALL 0x00402b78
0040d9c7  8bd8  MOV EBX,EAX
0040d9c9  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040d9cc  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040d9cf  8b401c  MOV EAX,dword ptr [EAX + 0x1c]
0040d9d2  e8a151ffff  CALL 0x00402b78
0040d9d7  3bd8  CMP EBX,EAX
0040d9d9  7416  JZ 0x0040d9f1
0040d9db  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040d9de  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0040d9e1  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0040d9e4  8b52fc  MOV EDX,dword ptr [EDX + -0x4]
0040d9e7  3b4218  CMP EAX,dword ptr [EDX + 0x18]
0040d9ea  7405  JZ 0x0040d9f1
0040d9ec  33c0  XOR EAX,EAX
0040d9ee  5b  POP EBX
0040d9ef  5d  POP EBP
0040d9f0  c3  RET
0040d9f1  b001  MOV AL,0x1
0040d9f3  5b  POP EBX
0040d9f4  5d  POP EBP
0040d9f5  c3  RET
