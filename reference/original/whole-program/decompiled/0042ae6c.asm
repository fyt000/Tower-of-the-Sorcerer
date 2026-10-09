; FUN_0042ae6c at 0x0042ae6c
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0042ae6c  55  PUSH EBP
0042ae6d  8bec  MOV EBP,ESP
0042ae6f  81c470ffffff  ADD ESP,0xffffff70
0042ae75  53  PUSH EBX
0042ae76  56  PUSH ESI
0042ae77  57  PUSH EDI
0042ae78  8b7d08  MOV EDI,dword ptr [EBP + 0x8]
0042ae7b  83c7fc  ADD EDI,-0x4
0042ae7e  c745e82bbc0000  MOV dword ptr [EBP + -0x18],0xbc2b
0042ae85  8d45a8  LEA EAX,[EBP + -0x58]
0042ae88  8945f0  MOV dword ptr [EBP + -0x10],EAX
0042ae8b  8b07  MOV EAX,dword ptr [EDI]
0042ae8d  e82abefeff  CALL 0x00416cbc
0042ae92  8945ec  MOV dword ptr [EBP + -0x14],EAX
0042ae95  c745a802000000  MOV dword ptr [EBP + -0x58],0x2
0042ae9c  c745b401000000  MOV dword ptr [EBP + -0x4c],0x1
0042aea3  33c0  XOR EAX,EAX
0042aea5  8945b8  MOV dword ptr [EBP + -0x48],EAX
0042aea8  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0042aeab  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0042aeae  8b4004  MOV EAX,dword ptr [EAX + 0x4]
0042aeb1  8945c0  MOV dword ptr [EBP + -0x40],EAX
0042aeb4  8b07  MOV EAX,dword ptr [EDI]
0042aeb6  e801befeff  CALL 0x00416cbc
0042aebb  8945ac  MOV dword ptr [EBP + -0x54],EAX
0042aebe  8b07  MOV EAX,dword ptr [EDI]
0042aec0  e8f7bdfeff  CALL 0x00416cbc
0042aec5  8945bc  MOV dword ptr [EBP + -0x44],EAX
0042aec8  c745d82cbc0000  MOV dword ptr [EBP + -0x28],0xbc2c
0042aecf  8b07  MOV EAX,dword ptr [EDI]
0042aed1  e8e6bdfeff  CALL 0x00416cbc
0042aed6  8945dc  MOV dword ptr [EBP + -0x24],EAX
0042aed9  8d4590  LEA EAX,[EBP + -0x70]
0042aedc  8945e0  MOV dword ptr [EBP + -0x20],EAX
0042aedf  c7459002000000  MOV dword ptr [EBP + -0x70],0x2
0042aee6  8b07  MOV EAX,dword ptr [EDI]
0042aee8  e8cfbdfeff  CALL 0x00416cbc
0042aeed  894594  MOV dword ptr [EBP + -0x6c],EAX
0042aef0  33f6  XOR ESI,ESI
0042aef2  8b07  MOV EAX,dword ptr [EDI]
0042aef4  e887fbffff  CALL 0x0042aa80
0042aef9  8bd8  MOV EBX,EAX
0042aefb  8d4580  LEA EAX,[EBP + -0x80]
0042aefe  50  PUSH EAX
0042aeff  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0042af02  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0042af05  8b4004  MOV EAX,dword ptr [EAX + 0x4]
0042af08  50  PUSH EAX
0042af09  e8e69dfdff  CALL 0x00404cf4
0042af0e  8b07  MOV EAX,dword ptr [EDI]
0042af10  8b4030  MOV EAX,dword ptr [EAX + 0x30]
0042af13  8945fc  MOV dword ptr [EBP + -0x4],EAX
0042af16  8b07  MOV EAX,dword ptr [EDI]
0042af18  8b402c  MOV EAX,dword ptr [EAX + 0x2c]
0042af1b  8945f8  MOV dword ptr [EBP + -0x8],EAX
0042af1e  3b75fc  CMP ESI,dword ptr [EBP + -0x4]
0042af21  0f8d9f000000  JGE 0x0042afc6
0042af27  895d98  MOV dword ptr [EBP + -0x68],EBX
0042af2a  8b07  MOV EAX,dword ptr [EDI]
0042af2c  8b8000010000  MOV EAX,dword ptr [EAX + 0x100]
0042af32  8b10  MOV EDX,dword ptr [EAX]
0042af34  ff5210  CALL dword ptr [EDX + 0x10]
0042af37  3bd8  CMP EBX,EAX
0042af39  7d12  JGE 0x0042af4d
0042af3b  8b07  MOV EAX,dword ptr [EDI]
0042af3d  8b8000010000  MOV EAX,dword ptr [EAX + 0x100]
0042af43  8bd3  MOV EDX,EBX
0042af45  8b08  MOV ECX,dword ptr [EAX]
0042af47  ff5114  CALL dword ptr [ECX + 0x14]
0042af4a  8945a4  MOV dword ptr [EBP + -0x5c],EAX
0042af4d  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0042af50  89459c  MOV dword ptr [EBP + -0x64],EAX
0042af53  8b07  MOV EAX,dword ptr [EDI]
0042af55  8b8010010000  MOV EAX,dword ptr [EAX + 0x110]
0042af5b  8945a0  MOV dword ptr [EBP + -0x60],EAX
0042af5e  8b45a4  MOV EAX,dword ptr [EBP + -0x5c]
0042af61  8945d4  MOV dword ptr [EBP + -0x2c],EAX
0042af64  895db0  MOV dword ptr [EBP + -0x50],EBX
0042af67  8d55d8  LEA EDX,[EBP + -0x28]
0042af6a  8b07  MOV EAX,dword ptr [EDI]
0042af6c  e89b7dfdff  CALL 0x00402d0c
0042af71  8b45a0  MOV EAX,dword ptr [EBP + -0x60]
0042af74  03c6  ADD EAX,ESI
0042af76  50  PUSH EAX
0042af77  8d8570ffffff  LEA EAX,[EBP + 0xffffff70]
0042af7d  50  PUSH EAX
0042af7e  8b4d9c  MOV ECX,dword ptr [EBP + -0x64]
0042af81  8bd6  MOV EDX,ESI
0042af83  33c0  XOR EAX,EAX
0042af85  e8b2e2fdff  CALL 0x0040923c
0042af8a  56  PUSH ESI
0042af8b  57  PUSH EDI
0042af8c  8db570ffffff  LEA ESI,[EBP + 0xffffff70]
0042af92  8d7dc4  LEA EDI,[EBP + -0x3c]
0042af95  b904000000  MOV ECX,0x4
0042af9a  f3a5  MOVSD.REP ES:EDI,ESI
0042af9c  5f  POP EDI
0042af9d  5e  POP ESI
0042af9e  8d55e8  LEA EDX,[EBP + -0x18]
0042afa1  8b07  MOV EAX,dword ptr [EDI]
0042afa3  e8647dfdff  CALL 0x00402d0c
0042afa8  0375a0  ADD ESI,dword ptr [EBP + -0x60]
0042afab  43  INC EBX
0042afac  8b07  MOV EAX,dword ptr [EDI]
0042afae  8b8000010000  MOV EAX,dword ptr [EAX + 0x100]
0042afb4  8b10  MOV EDX,dword ptr [EAX]
0042afb6  ff5210  CALL dword ptr [EDX + 0x10]
0042afb9  3bd8  CMP EBX,EAX
0042afbb  7d09  JGE 0x0042afc6
0042afbd  3b75fc  CMP ESI,dword ptr [EBP + -0x4]
0042afc0  0f8c61ffffff  JL 0x0042af27
0042afc6  5f  POP EDI
0042afc7  5e  POP ESI
0042afc8  5b  POP EBX
0042afc9  8be5  MOV ESP,EBP
0042afcb  5d  POP EBP
0042afcc  c3  RET
