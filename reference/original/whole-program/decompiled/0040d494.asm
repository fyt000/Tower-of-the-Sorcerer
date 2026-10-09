; root_0040d494 at 0x0040d494
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040d494  55  PUSH EBP
0040d495  8bec  MOV EBP,ESP
0040d497  81c4dcfeffff  ADD ESP,0xfffffedc
0040d49d  53  PUSH EBX
0040d49e  56  PUSH ESI
0040d49f  57  PUSH EDI
0040d4a0  33c9  XOR ECX,ECX
0040d4a2  898ddcfeffff  MOV dword ptr [EBP + 0xfffffedc],ECX
0040d4a8  8955f8  MOV dword ptr [EBP + -0x8],EDX
0040d4ab  8945fc  MOV dword ptr [EBP + -0x4],EAX
0040d4ae  33c0  XOR EAX,EAX
0040d4b0  55  PUSH EBP
0040d4b1  6849d74000  PUSH 0x40d749
0040d4b6  64ff30  PUSH dword ptr FS:[EAX]
0040d4b9  648920  MOV dword ptr FS:[EAX],ESP
0040d4bc  8d95e0feffff  LEA EDX,[EBP + 0xfffffee0]
0040d4c2  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0040d4c5  8b00  MOV EAX,dword ptr [EAX]
0040d4c7  e8b056ffff  CALL 0x00402b7c
0040d4cc  33db  XOR EBX,EBX
0040d4ce  8a9de0feffff  MOV BL,byte ptr [EBP + 0xfffffee0]
0040d4d4  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0040d4d7  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040d4da  e87161ffff  CALL 0x00403650
0040d4df  03d8  ADD EBX,EAX
0040d4e1  43  INC EBX
0040d4e2  83c305  ADD EBX,0x5
0040d4e5  83c303  ADD EBX,0x3
0040d4e8  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d4eb  8b400c  MOV EAX,dword ptr [EAX + 0xc]
0040d4ee  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040d4f1  2b4210  SUB EAX,dword ptr [EDX + 0x10]
0040d4f4  3bd8  CMP EBX,EAX
0040d4f6  7e08  JLE 0x0040d500
0040d4f8  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d4fb  e834feffff  CALL 0x0040d334
0040d500  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d503  e808fdffff  CALL 0x0040d210
0040d508  8945f4  MOV dword ptr [EBP + -0xc],EAX
0040d50b  a058d74000  MOV AL,[0x0040d758]
0040d510  8845e3  MOV byte ptr [EBP + -0x1d],AL
0040d513  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d516  83781c00  CMP dword ptr [EAX + 0x1c],0x0
0040d51a  7404  JZ 0x0040d520
0040d51c  804de301  OR byte ptr [EBP + -0x1d],0x1
0040d520  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d523  8b582c  MOV EBX,dword ptr [EAX + 0x2c]
0040d526  85db  TEST EBX,EBX
0040d528  7431  JZ 0x0040d55b
0040d52a  8b4308  MOV EAX,dword ptr [EBX + 0x8]
0040d52d  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040d530  3b4230  CMP EAX,dword ptr [EDX + 0x30]
0040d533  7e26  JLE 0x0040d55b
0040d535  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d538  83781c00  CMP dword ptr [EAX + 0x1c],0x0
0040d53c  7419  JZ 0x0040d557
0040d53e  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d541  8b5030  MOV EDX,dword ptr [EAX + 0x30]
0040d544  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d547  8b402c  MOV EAX,dword ptr [EAX + 0x2c]
0040d54a  e8f1c4ffff  CALL 0x00409a40
0040d54f  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040d552  3b421c  CMP EAX,dword ptr [EDX + 0x1c]
0040d555  7404  JZ 0x0040d55b
0040d557  804de302  OR byte ptr [EBP + -0x1d],0x2
0040d55b  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d55e  8b4834  MOV ECX,dword ptr [EAX + 0x34]
0040d561  8a55e3  MOV DL,byte ptr [EBP + -0x1d]
0040d564  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d567  e838030000  CALL 0x0040d8a4
0040d56c  8d95e0feffff  LEA EDX,[EBP + 0xfffffee0]
0040d572  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0040d575  8b00  MOV EAX,dword ptr [EAX]
0040d577  e80056ffff  CALL 0x00402b7c
0040d57c  8d95e0feffff  LEA EDX,[EBP + 0xfffffee0]
0040d582  8d85dcfeffff  LEA EAX,[EBP + 0xfffffedc]
0040d588  e86f60ffff  CALL 0x004035fc
0040d58d  8b95dcfeffff  MOV EDX,dword ptr [EBP + 0xfffffedc]
0040d593  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d596  e8650e0000  CALL 0x0040e400
0040d59b  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0040d59e  8b5008  MOV EDX,dword ptr [EAX + 0x8]
0040d5a1  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d5a4  e8570e0000  CALL 0x0040e400
0040d5a9  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d5ac  e85ffcffff  CALL 0x0040d210
0040d5b1  8945f0  MOV dword ptr [EBP + -0x10],EAX
0040d5b4  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d5b7  8b402c  MOV EAX,dword ptr [EAX + 0x2c]
0040d5ba  85c0  TEST EAX,EAX
0040d5bc  7420  JZ 0x0040d5de
0040d5be  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040d5c1  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040d5c4  3b4230  CMP EAX,dword ptr [EDX + 0x30]
0040d5c7  7e15  JLE 0x0040d5de
0040d5c9  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d5cc  83781c00  CMP dword ptr [EAX + 0x1c],0x0
0040d5d0  7406  JZ 0x0040d5d8
0040d5d2  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d5d5  ff4030  INC dword ptr [EAX + 0x30]
0040d5d8  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d5db  ff4034  INC dword ptr [EAX + 0x34]
0040d5de  8b55f8  MOV EDX,dword ptr [EBP + -0x8]
0040d5e1  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d5e4  e8ff020000  CALL 0x0040d8e8
0040d5e9  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d5ec  e8ab020000  CALL 0x0040d89c
0040d5f1  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d5f4  8b402c  MOV EAX,dword ptr [EAX + 0x2c]
0040d5f7  8945ec  MOV dword ptr [EBP + -0x14],EAX
0040d5fa  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d5fd  8b4030  MOV EAX,dword ptr [EAX + 0x30]
0040d600  8945e8  MOV dword ptr [EBP + -0x18],EAX
0040d603  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d606  8b4034  MOV EAX,dword ptr [EAX + 0x34]
0040d609  8945e4  MOV dword ptr [EBP + -0x1c],EAX
0040d60c  33c0  XOR EAX,EAX
0040d60e  55  PUSH EBP
0040d60f  68efd64000  PUSH 0x40d6ef
0040d614  64ff30  PUSH dword ptr FS:[EAX]
0040d617  648920  MOV dword ptr FS:[EAX],ESP
0040d61a  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d61d  33d2  XOR EDX,EDX
0040d61f  89502c  MOV dword ptr [EAX + 0x2c],EDX
0040d622  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d625  33d2  XOR EDX,EDX
0040d627  895030  MOV dword ptr [EAX + 0x30],EDX
0040d62a  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d62d  33d2  XOR EDX,EDX
0040d62f  895034  MOV dword ptr [EAX + 0x34],EDX
0040d632  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d635  80782000  CMP byte ptr [EAX + 0x20],0x0
0040d639  0f8587000000  JNZ 0x0040d6c6
0040d63f  33c0  XOR EAX,EAX
0040d641  55  PUSH EBP
0040d642  68bfd64000  PUSH 0x40d6bf
0040d647  64ff30  PUSH dword ptr FS:[EAX]
0040d64a  648920  MOV dword ptr FS:[EAX],ESP
0040d64d  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d650  8b581c  MOV EBX,dword ptr [EAX + 0x1c]
0040d653  85db  TEST EBX,EBX
0040d655  743a  JZ 0x0040d691
0040d657  8bc3  MOV EAX,EBX
0040d659  ba44914000  MOV EDX,0x409144
0040d65e  e81956ffff  CALL 0x00402c7c
0040d663  84c0  TEST AL,AL
0040d665  742a  JZ 0x0040d691
0040d667  b201  MOV DL,0x1
0040d669  b8c88a4000  MOV EAX,0x408ac8
0040d66e  e89955ffff  CALL 0x00402c0c
0040d673  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040d676  89422c  MOV dword ptr [EDX + 0x2c],EAX
0040d679  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d67c  50  PUSH EAX
0040d67d  68c0d14000  PUSH 0x40d1c0
0040d682  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d685  8b401c  MOV EAX,dword ptr [EAX + 0x1c]
0040d688  66bbffff  MOV BX,0xffff
0040d68c  e84b56ffff  CALL 0x00402cdc
0040d691  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d694  50  PUSH EAX
0040d695  6858d44000  PUSH 0x40d458
0040d69a  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0040d69d  66bbffff  MOV BX,0xffff
0040d6a1  e83656ffff  CALL 0x00402cdc
0040d6a6  33c0  XOR EAX,EAX
0040d6a8  5a  POP EDX
0040d6a9  59  POP ECX
0040d6aa  59  POP ECX
0040d6ab  648910  MOV dword ptr FS:[EAX],EDX
0040d6ae  68c6d64000  PUSH 0x40d6c6
0040d6b3  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040d6b6  8b402c  MOV EAX,dword ptr [EAX + 0x2c]
0040d6b9  e87655ffff  CALL 0x00402c34
0040d6be  c3  RET
0040d6c6  33c0  XOR EAX,EAX
0040d6c8  5a  POP EDX
0040d6c9  59  POP ECX
0040d6ca  59  POP ECX
0040d6cb  648910  MOV dword ptr FS:[EAX],EDX
0040d6ce  68f6d64000  PUSH 0x40d6f6
0040d6d3  8b45ec  MOV EAX,dword ptr [EBP + -0x14]
0040d6d6  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040d6d9  89422c  MOV dword ptr [EDX + 0x2c],EAX
0040d6dc  8b45e8  MOV EAX,dword ptr [EBP + -0x18]
0040d6df  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040d6e2  894230  MOV dword ptr [EDX + 0x30],EAX
0040d6e5  8b45e4  MOV EAX,dword ptr [EBP + -0x1c]
0040d6e8  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040d6eb  894234  MOV dword ptr [EDX + 0x34],EAX
0040d6ee  c3  RET
