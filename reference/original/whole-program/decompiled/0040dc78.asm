; FUN_0040dc78 at 0x0040dc78
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040dc78  55  PUSH EBP
0040dc79  8bec  MOV EBP,ESP
0040dc7b  83c4f8  ADD ESP,-0x8
0040dc7e  53  PUSH EBX
0040dc7f  56  PUSH ESI
0040dc80  57  PUSH EDI
0040dc81  33c0  XOR EAX,EAX
0040dc83  8945f8  MOV dword ptr [EBP + -0x8],EAX
0040dc86  33c0  XOR EAX,EAX
0040dc88  55  PUSH EBP
0040dc89  6842dd4000  PUSH 0x40dd42
0040dc8e  64ff30  PUSH dword ptr FS:[EAX]
0040dc91  648920  MOV dword ptr FS:[EAX],ESP
0040dc94  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dc97  8b50f4  MOV EDX,dword ptr [EAX + -0xc]
0040dc9a  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dc9d  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0040dca0  e877a6ffff  CALL 0x0040831c
0040dca5  8945fc  MOV dword ptr [EBP + -0x4],EAX
0040dca8  55  PUSH EBP
0040dca9  e87affffff  CALL 0x0040dc28
0040dcae  59  POP ECX
0040dcaf  84c0  TEST AL,AL
0040dcb1  7579  JNZ 0x0040dd2c
0040dcb3  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dcb6  50  PUSH EAX
0040dcb7  e83cfdffff  CALL 0x0040d9f8
0040dcbc  59  POP ECX
0040dcbd  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dcc0  8b40f0  MOV EAX,dword ptr [EAX + -0x10]
0040dcc3  8a00  MOV AL,byte ptr [EAX]
0040dcc5  fec8  DEC AL
0040dcc7  740e  JZ 0x0040dcd7
0040dcc9  fec8  DEC AL
0040dccb  7421  JZ 0x0040dcee
0040dccd  fec8  DEC AL
0040dccf  743c  JZ 0x0040dd0d
0040dcd1  2c03  SUB AL,0x3
0040dcd3  7429  JZ 0x0040dcfe
0040dcd5  eb55  JMP 0x0040dd2c
0040dcd7  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dcda  50  PUSH EAX
0040dcdb  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dcde  8b40f4  MOV EAX,dword ptr [EAX + -0xc]
0040dce1  8b00  MOV EAX,dword ptr [EAX]
0040dce3  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040dce6  e8f9fdffff  CALL 0x0040dae4
0040dceb  59  POP ECX
0040dcec  eb3e  JMP 0x0040dd2c
0040dcee  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040dcf1  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dcf4  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040dcf7  e864f6ffff  CALL 0x0040d360
0040dcfc  eb2e  JMP 0x0040dd2c
0040dcfe  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dd01  50  PUSH EAX
0040dd02  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040dd05  e846fdffff  CALL 0x0040da50
0040dd0a  59  POP ECX
0040dd0b  eb1f  JMP 0x0040dd2c
0040dd0d  8d4df8  LEA ECX,[EBP + -0x8]
0040dd10  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dd13  8b40f0  MOV EAX,dword ptr [EAX + -0x10]
0040dd16  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040dd19  e88ea4ffff  CALL 0x004081ac
0040dd1e  8b55f8  MOV EDX,dword ptr [EBP + -0x8]
0040dd21  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dd24  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040dd27  e858faffff  CALL 0x0040d784
0040dd2c  33c0  XOR EAX,EAX
0040dd2e  5a  POP EDX
0040dd2f  59  POP ECX
0040dd30  59  POP ECX
0040dd31  648910  MOV dword ptr FS:[EAX],EDX
0040dd34  6849dd4000  PUSH 0x40dd49
0040dd39  8d45f8  LEA EAX,[EBP + -0x8]
0040dd3c  e89b57ffff  CALL 0x004034dc
0040dd41  c3  RET
