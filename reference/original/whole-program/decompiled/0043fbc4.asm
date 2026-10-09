; root_0043fbc4 at 0x0043fbc4
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0043fbc4  55  PUSH EBP
0043fbc5  8bec  MOV EBP,ESP
0043fbc7  83c4c0  ADD ESP,-0x40
0043fbca  53  PUSH EBX
0043fbcb  56  PUSH ESI
0043fbcc  57  PUSH EDI
0043fbcd  33db  XOR EBX,EBX
0043fbcf  895dc0  MOV dword ptr [EBP + -0x40],EBX
0043fbd2  8bf1  MOV ESI,ECX
0043fbd4  8d7de4  LEA EDI,[EBP + -0x1c]
0043fbd7  b904000000  MOV ECX,0x4
0043fbdc  f3a5  MOVSD.REP ES:EDI,ESI
0043fbde  8955fc  MOV dword ptr [EBP + -0x4],EDX
0043fbe1  8bd8  MOV EBX,EAX
0043fbe3  33c0  XOR EAX,EAX
0043fbe5  55  PUSH EBP
0043fbe6  68f8fc4300  PUSH 0x43fcf8
0043fbeb  64ff30  PUSH dword ptr FS:[EAX]
0043fbee  648920  MOV dword ptr FS:[EAX],ESP
0043fbf1  8b8308010000  MOV EAX,dword ptr [EBX + 0x108]
0043fbf7  8945f4  MOV dword ptr [EBP + -0xc],EAX
0043fbfa  8d55e4  LEA EDX,[EBP + -0x1c]
0043fbfd  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0043fc00  e85faafdff  CALL 0x0041a664
0043fc05  c745f802000000  MOV dword ptr [EBP + -0x8],0x2
0043fc0c  80bb6c01000000  CMP byte ptr [EBX + 0x16c],0x0
0043fc13  0f84a3000000  JZ 0x0043fcbc
0043fc19  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0043fc1c  8b8300010000  MOV EAX,dword ptr [EBX + 0x100]
0043fc22  8b08  MOV ECX,dword ptr [EAX]
0043fc24  ff5114  CALL dword ptr [ECX + 0x14]
0043fc27  8bf0  MOV ESI,EAX
0043fc29  85f6  TEST ESI,ESI
0043fc2b  0f848b000000  JZ 0x0043fcbc
0043fc31  8bc6  MOV EAX,ESI
0043fc33  8b10  MOV EDX,dword ptr [EAX]
0043fc35  ff521c  CALL dword ptr [EDX + 0x1c]
0043fc38  50  PUSH EAX
0043fc39  8d45d4  LEA EAX,[EBP + -0x2c]
0043fc3c  50  PUSH EAX
0043fc3d  8bc6  MOV EAX,ESI
0043fc3f  8b10  MOV EDX,dword ptr [EAX]
0043fc41  ff5220  CALL dword ptr [EDX + 0x20]
0043fc44  8bc8  MOV ECX,EAX
0043fc46  33d2  XOR EDX,EDX
0043fc48  33c0  XOR EAX,EAX
0043fc4a  e80996fcff  CALL 0x00409258
0043fc4f  8d45d4  LEA EAX,[EBP + -0x2c]
0043fc52  50  PUSH EAX
0043fc53  8bc6  MOV EAX,ESI
0043fc55  8b10  MOV EDX,dword ptr [EAX]
0043fc57  ff521c  CALL dword ptr [EDX + 0x1c]
0043fc5a  48  DEC EAX
0043fc5b  50  PUSH EAX
0043fc5c  8bc6  MOV EAX,ESI
0043fc5e  e875defdff  CALL 0x0041dad8
0043fc63  33d2  XOR EDX,EDX
0043fc65  59  POP ECX
0043fc66  e8b9acfdff  CALL 0x0041a924
0043fc6b  50  PUSH EAX
0043fc6c  8bc6  MOV EAX,ESI
0043fc6e  8b10  MOV EDX,dword ptr [EAX]
0043fc70  ff521c  CALL dword ptr [EDX + 0x1c]
0043fc73  50  PUSH EAX
0043fc74  8d45c4  LEA EAX,[EBP + -0x3c]
0043fc77  50  PUSH EAX
0043fc78  8bc6  MOV EAX,ESI
0043fc7a  8b10  MOV EDX,dword ptr [EAX]
0043fc7c  ff5220  CALL dword ptr [EDX + 0x20]
0043fc7f  50  PUSH EAX
0043fc80  8bc6  MOV EAX,ESI
0043fc82  8b10  MOV EDX,dword ptr [EAX]
0043fc84  ff521c  CALL dword ptr [EDX + 0x1c]
0043fc87  8b55e8  MOV EDX,dword ptr [EBP + -0x18]
0043fc8a  0355f0  ADD EDX,dword ptr [EBP + -0x10]
0043fc8d  2bd0  SUB EDX,EAX
0043fc8f  d1fa  SAR EDX,0x1
0043fc91  7903  JNS 0x0043fc96
0043fc93  83d200  ADC EDX,0x0
0043fc96  8b45e4  MOV EAX,dword ptr [EBP + -0x1c]
0043fc99  83c002  ADD EAX,0x2
0043fc9c  59  POP ECX
0043fc9d  e8b695fcff  CALL 0x00409258
0043fca2  8d55c4  LEA EDX,[EBP + -0x3c]
0043fca5  8bce  MOV ECX,ESI
0043fca7  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0043fcaa  e87da6fdff  CALL 0x0041a32c
0043fcaf  8bc6  MOV EAX,ESI
0043fcb1  8b10  MOV EDX,dword ptr [EAX]
0043fcb3  ff5220  CALL dword ptr [EDX + 0x20]
0043fcb6  83c006  ADD EAX,0x6
0043fcb9  8945f8  MOV dword ptr [EBP + -0x8],EAX
0043fcbc  8d4dc0  LEA ECX,[EBP + -0x40]
0043fcbf  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0043fcc2  8b8300010000  MOV EAX,dword ptr [EBX + 0x100]
0043fcc8  8b18  MOV EBX,dword ptr [EAX]
0043fcca  ff530c  CALL dword ptr [EBX + 0xc]
0043fccd  8b45c0  MOV EAX,dword ptr [EBP + -0x40]
0043fcd0  50  PUSH EAX
0043fcd1  8b55e4  MOV EDX,dword ptr [EBP + -0x1c]
0043fcd4  0355f8  ADD EDX,dword ptr [EBP + -0x8]
0043fcd7  8b4de8  MOV ECX,dword ptr [EBP + -0x18]
0043fcda  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0043fcdd  e8deaafdff  CALL 0x0041a7c0
0043fce2  33c0  XOR EAX,EAX
0043fce4  5a  POP EDX
0043fce5  59  POP ECX
0043fce6  59  POP ECX
0043fce7  648910  MOV dword ptr FS:[EAX],EDX
0043fcea  68fffc4300  PUSH 0x43fcff
0043fcef  8d45c0  LEA EAX,[EBP + -0x40]
0043fcf2  e8e537fcff  CALL 0x004034dc
0043fcf7  c3  RET
