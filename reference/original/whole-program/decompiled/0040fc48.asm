; FUN_0040fc48 at 0x0040fc48
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040fc48  55  PUSH EBP
0040fc49  8bec  MOV EBP,ESP
0040fc4b  83c4e8  ADD ESP,-0x18
0040fc4e  53  PUSH EBX
0040fc4f  56  PUSH ESI
0040fc50  57  PUSH EDI
0040fc51  894df4  MOV dword ptr [EBP + -0xc],ECX
0040fc54  8bfa  MOV EDI,EDX
0040fc56  8945f8  MOV dword ptr [EBP + -0x8],EAX
0040fc59  33c0  XOR EAX,EAX
0040fc5b  8945f0  MOV dword ptr [EBP + -0x10],EAX
0040fc5e  33c0  XOR EAX,EAX
0040fc60  8945ec  MOV dword ptr [EBP + -0x14],EAX
0040fc63  33db  XOR EBX,EBX
0040fc65  33f6  XOR ESI,ESI
0040fc67  85ff  TEST EDI,EDI
0040fc69  7409  JZ 0x0040fc74
0040fc6b  8bc7  MOV EAX,EDI
0040fc6d  e89a070000  CALL 0x0041040c
0040fc72  8bd8  MOV EBX,EAX
0040fc74  837df400  CMP dword ptr [EBP + -0xc],0x0
0040fc78  740a  JZ 0x0040fc84
0040fc7a  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0040fc7d  e88a070000  CALL 0x0041040c
0040fc82  8bf0  MOV ESI,EAX
0040fc84  c645ea00  MOV byte ptr [EBP + -0x16],0x0
0040fc88  e9a1000000  JMP 0x0040fd2e
0040fc8d  c645ffff  MOV byte ptr [EBP + -0x1],0xff
0040fc91  c645ebff  MOV byte ptr [EBP + -0x15],0xff
0040fc95  3b5df0  CMP EBX,dword ptr [EBP + -0x10]
0040fc98  7e10  JLE 0x0040fcaa
0040fc9a  8b55f0  MOV EDX,dword ptr [EBP + -0x10]
0040fc9d  8bc7  MOV EAX,EDI
0040fc9f  e878070000  CALL 0x0041041c
0040fca4  8a402d  MOV AL,byte ptr [EAX + 0x2d]
0040fca7  8845ff  MOV byte ptr [EBP + -0x1],AL
0040fcaa  3b75ec  CMP ESI,dword ptr [EBP + -0x14]
0040fcad  7e11  JLE 0x0040fcc0
0040fcaf  8b55ec  MOV EDX,dword ptr [EBP + -0x14]
0040fcb2  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0040fcb5  e862070000  CALL 0x0041041c
0040fcba  8a402d  MOV AL,byte ptr [EAX + 0x2d]
0040fcbd  8845eb  MOV byte ptr [EBP + -0x15],AL
0040fcc0  8a45ff  MOV AL,byte ptr [EBP + -0x1]
0040fcc3  3a45eb  CMP AL,byte ptr [EBP + -0x15]
0040fcc6  7714  JA 0x0040fcdc
0040fcc8  55  PUSH EBP
0040fcc9  8d45f0  LEA EAX,[EBP + -0x10]
0040fccc  8b4df8  MOV ECX,dword ptr [EBP + -0x8]
0040fccf  8bd7  MOV EDX,EDI
0040fcd1  e812ffffff  CALL 0x0040fbe8
0040fcd6  59  POP ECX
0040fcd7  8845ea  MOV byte ptr [EBP + -0x16],AL
0040fcda  eb1e  JMP 0x0040fcfa
0040fcdc  8a45eb  MOV AL,byte ptr [EBP + -0x15]
0040fcdf  8845ff  MOV byte ptr [EBP + -0x1],AL
0040fce2  55  PUSH EBP
0040fce3  8d45ec  LEA EAX,[EBP + -0x14]
0040fce6  8b4df8  MOV ECX,dword ptr [EBP + -0x8]
0040fce9  8b55f4  MOV EDX,dword ptr [EBP + -0xc]
0040fcec  e8f7feffff  CALL 0x0040fbe8
0040fcf1  59  POP ECX
0040fcf2  8845ea  MOV byte ptr [EBP + -0x16],AL
0040fcf5  eb03  JMP 0x0040fcfa
0040fcf7  ff45f0  INC dword ptr [EBP + -0x10]
0040fcfa  3b5df0  CMP EBX,dword ptr [EBP + -0x10]
0040fcfd  7e17  JLE 0x0040fd16
0040fcff  8b55f0  MOV EDX,dword ptr [EBP + -0x10]
0040fd02  8bc7  MOV EAX,EDI
0040fd04  e813070000  CALL 0x0041041c
0040fd09  8a402d  MOV AL,byte ptr [EAX + 0x2d]
0040fd0c  3a45ff  CMP AL,byte ptr [EBP + -0x1]
0040fd0f  76e6  JBE 0x0040fcf7
0040fd11  eb03  JMP 0x0040fd16
0040fd13  ff45ec  INC dword ptr [EBP + -0x14]
0040fd16  3b75ec  CMP ESI,dword ptr [EBP + -0x14]
0040fd19  7e13  JLE 0x0040fd2e
0040fd1b  8b55ec  MOV EDX,dword ptr [EBP + -0x14]
0040fd1e  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0040fd21  e8f6060000  CALL 0x0041041c
0040fd26  8a402d  MOV AL,byte ptr [EAX + 0x2d]
0040fd29  3a45ff  CMP AL,byte ptr [EBP + -0x1]
0040fd2c  76e5  JBE 0x0040fd13
0040fd2e  807dea00  CMP byte ptr [EBP + -0x16],0x0
0040fd32  7512  JNZ 0x0040fd46
0040fd34  3b5df0  CMP EBX,dword ptr [EBP + -0x10]
0040fd37  0f8f50ffffff  JG 0x0040fc8d
0040fd3d  3b75ec  CMP ESI,dword ptr [EBP + -0x14]
0040fd40  0f8f47ffffff  JG 0x0040fc8d
0040fd46  5f  POP EDI
0040fd47  5e  POP ESI
0040fd48  5b  POP EBX
0040fd49  8be5  MOV ESP,EBP
0040fd4b  5d  POP EBP
0040fd4c  c3  RET
