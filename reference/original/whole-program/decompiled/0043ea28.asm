; root_0043ea28 at 0x0043ea28
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0043ea28  55  PUSH EBP
0043ea29  8bec  MOV EBP,ESP
0043ea2b  83c4dc  ADD ESP,-0x24
0043ea2e  53  PUSH EBX
0043ea2f  56  PUSH ESI
0043ea30  57  PUSH EDI
0043ea31  33d2  XOR EDX,EDX
0043ea33  8955dc  MOV dword ptr [EBP + -0x24],EDX
0043ea36  8955f8  MOV dword ptr [EBP + -0x8],EDX
0043ea39  8955f4  MOV dword ptr [EBP + -0xc],EDX
0043ea3c  8955e0  MOV dword ptr [EBP + -0x20],EDX
0043ea3f  8945fc  MOV dword ptr [EBP + -0x4],EAX
0043ea42  33c0  XOR EAX,EAX
0043ea44  55  PUSH EBP
0043ea45  680aed4300  PUSH 0x43ed0a
0043ea4a  64ff30  PUSH dword ptr FS:[EAX]
0043ea4d  648920  MOV dword ptr FS:[EAX],ESP
0043ea50  33c0  XOR EAX,EAX
0043ea52  55  PUSH EBP
0043ea53  68c4ec4300  PUSH 0x43ecc4
0043ea58  64ff30  PUSH dword ptr FS:[EAX]
0043ea5b  648920  MOV dword ptr FS:[EAX],ESP
0043ea5e  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ea61  8b8000010000  MOV EAX,dword ptr [EAX + 0x100]
0043ea67  e8e0b6fcff  CALL 0x0040a14c
0043ea6c  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ea6f  8b8000010000  MOV EAX,dword ptr [EAX + 0x100]
0043ea75  8b10  MOV EDX,dword ptr [EAX]
0043ea77  ff5238  CALL dword ptr [EDX + 0x38]
0043ea7a  33db  XOR EBX,EBX
0043ea7c  8d55dc  LEA EDX,[EBP + -0x24]
0043ea7f  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ea82  8b8058010000  MOV EAX,dword ptr [EAX + 0x158]
0043ea88  e87774fcff  CALL 0x00405f04
0043ea8d  8b55dc  MOV EDX,dword ptr [EBP + -0x24]
0043ea90  8d45e0  LEA EAX,[EBP + -0x20]
0043ea93  b920ed4300  MOV ECX,0x43ed20
0043ea98  e8ff4bfcff  CALL 0x0040369c
0043ea9d  6a00  PUSH 0x0
0043ea9f  6a00  PUSH 0x0
0043eaa1  8d45ec  LEA EAX,[EBP + -0x14]
0043eaa4  50  PUSH EAX
0043eaa5  8d45f0  LEA EAX,[EBP + -0x10]
0043eaa8  50  PUSH EAX
0043eaa9  6a00  PUSH 0x0
0043eaab  6a00  PUSH 0x0
0043eaad  6a00  PUSH 0x0
0043eaaf  8b45e0  MOV EAX,dword ptr [EBP + -0x20]
0043eab2  e85d4dfcff  CALL 0x00403814
0043eab7  50  PUSH EAX
0043eab8  e8e760fcff  CALL 0x00404ba4
0043eabd  f645ec03  TEST byte ptr [EBP + -0x14],0x3
0043eac1  0f95c0  SETNZ AL
0043eac4  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0043eac7  888249010000  MOV byte ptr [EDX + 0x149],AL
0043eacd  f645ec01  TEST byte ptr [EBP + -0x14],0x1
0043ead1  0f95c0  SETNZ AL
0043ead4  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0043ead7  88824a010000  MOV byte ptr [EDX + 0x14a],AL
0043eadd  8b45e0  MOV EAX,dword ptr [EBP + -0x20]
0043eae0  e86b4bfcff  CALL 0x00403650
0043eae5  83f802  CMP EAX,0x2
0043eae8  7c53  JL 0x0043eb3d
0043eaea  8b45e0  MOV EAX,dword ptr [EBP + -0x20]
0043eaed  8078015c  CMP byte ptr [EAX + 0x1],0x5c
0043eaf1  754a  JNZ 0x0043eb3d
0043eaf3  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043eaf6  8b8850010000  MOV ECX,dword ptr [EAX + 0x150]
0043eafc  8b55e0  MOV EDX,dword ptr [EBP + -0x20]
0043eaff  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043eb02  8b8000010000  MOV EAX,dword ptr [EAX + 0x100]
0043eb08  8b30  MOV ESI,dword ptr [EAX]
0043eb0a  ff5630  CALL dword ptr [ESI + 0x30]
0043eb0d  43  INC EBX
0043eb0e  8d45f8  LEA EAX,[EBP + -0x8]
0043eb11  50  PUSH EAX
0043eb12  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043eb15  8b8058010000  MOV EAX,dword ptr [EAX + 0x158]
0043eb1b  e8304bfcff  CALL 0x00403650
0043eb20  50  PUSH EAX
0043eb21  8b45e0  MOV EAX,dword ptr [EBP + -0x20]
0043eb24  e8274bfcff  CALL 0x00403650
0043eb29  8bd0  MOV EDX,EAX
0043eb2b  42  INC EDX
0043eb2c  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043eb2f  8b8058010000  MOV EAX,dword ptr [EAX + 0x158]
0043eb35  59  POP ECX
0043eb36  e8194dfcff  CALL 0x00403854
0043eb3b  eb11  JMP 0x0043eb4e
0043eb3d  8d45f8  LEA EAX,[EBP + -0x8]
0043eb40  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0043eb43  8b9258010000  MOV EDX,dword ptr [EDX + 0x158]
0043eb49  e8224afcff  CALL 0x00403570
0043eb4e  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0043eb51  e8fa4afcff  CALL 0x00403650
0043eb56  85c0  TEST EAX,EAX
0043eb58  0f8e9b000000  JLE 0x0043ebf9
0043eb5e  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0043eb61  e8fe01fdff  CALL 0x0040ed64
0043eb66  3c5c  CMP AL,0x5c
0043eb68  7475  JZ 0x0043ebdf
0043eb6a  8b55f8  MOV EDX,dword ptr [EBP + -0x8]
0043eb6d  b820ed4300  MOV EAX,0x43ed20
0043eb72  e85502fdff  CALL 0x0040edcc
0043eb77  8bf0  MOV ESI,EAX
0043eb79  85f6  TEST ESI,ESI
0043eb7b  7462  JZ 0x0043ebdf
0043eb7d  8d45f4  LEA EAX,[EBP + -0xc]
0043eb80  50  PUSH EAX
0043eb81  8bce  MOV ECX,ESI
0043eb83  49  DEC ECX
0043eb84  ba01000000  MOV EDX,0x1
0043eb89  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0043eb8c  e8c34cfcff  CALL 0x00403854
0043eb91  85db  TEST EBX,EBX
0043eb93  750d  JNZ 0x0043eba2
0043eb95  8d45f4  LEA EAX,[EBP + -0xc]
0043eb98  ba20ed4300  MOV EDX,0x43ed20
0043eb9d  e8b64afcff  CALL 0x00403658
0043eba2  8d45f8  LEA EAX,[EBP + -0x8]
0043eba5  8bce  MOV ECX,ESI
0043eba7  ba01000000  MOV EDX,0x1
0043ebac  e8e34cfcff  CALL 0x00403894
0043ebb1  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ebb4  8b8850010000  MOV ECX,dword ptr [EAX + 0x150]
0043ebba  8b55f4  MOV EDX,dword ptr [EBP + -0xc]
0043ebbd  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ebc0  8b8000010000  MOV EAX,dword ptr [EAX + 0x100]
0043ebc6  8b30  MOV ESI,dword ptr [EAX]
0043ebc8  ff5630  CALL dword ptr [ESI + 0x30]
0043ebcb  43  INC EBX
0043ebcc  8b55f8  MOV EDX,dword ptr [EBP + -0x8]
0043ebcf  b820ed4300  MOV EAX,0x43ed20
0043ebd4  e8f301fdff  CALL 0x0040edcc
0043ebd9  8bf0  MOV ESI,EAX
0043ebdb  85f6  TEST ESI,ESI
0043ebdd  759e  JNZ 0x0043eb7d
0043ebdf  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ebe2  8b8854010000  MOV ECX,dword ptr [EAX + 0x154]
0043ebe8  8b55f8  MOV EDX,dword ptr [EBP + -0x8]
0043ebeb  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ebee  8b8000010000  MOV EAX,dword ptr [EAX + 0x100]
0043ebf4  8b18  MOV EBX,dword ptr [EAX]
0043ebf6  ff5330  CALL dword ptr [EBX + 0x30]
0043ebf9  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ebfc  8b8000010000  MOV EAX,dword ptr [EAX + 0x100]
0043ec02  8b10  MOV EDX,dword ptr [EAX]
0043ec04  ff5210  CALL dword ptr [EDX + 0x10]
0043ec07  48  DEC EAX
0043ec08  8945e4  MOV dword ptr [EBP + -0x1c],EAX
0043ec0b  b201  MOV DL,0x1
0043ec0d  b83c8d4000  MOV EAX,0x408d3c
0043ec12  e8f53ffcff  CALL 0x00402c0c
0043ec17  8945e8  MOV dword ptr [EBP + -0x18],EAX
0043ec1a  33c0  XOR EAX,EAX
0043ec1c  55  PUSH EBP
0043ec1d  68a1ec4300  PUSH 0x43eca1
0043ec22  64ff30  PUSH dword ptr FS:[EAX]
0043ec25  648920  MOV dword ptr FS:[EAX],ESP
0043ec28  b201  MOV DL,0x1
0043ec2a  8b45e8  MOV EAX,dword ptr [EBP + -0x18]
0043ec2d  e876c2fcff  CALL 0x0040aea8
0043ec32  8b4de8  MOV ECX,dword ptr [EBP + -0x18]
0043ec35  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ec38  8b9058010000  MOV EDX,dword ptr [EAX + 0x158]
0043ec3e  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ec41  e89efcffff  CALL 0x0043e8e4
0043ec46  8b45e8  MOV EAX,dword ptr [EBP + -0x18]
0043ec49  8b10  MOV EDX,dword ptr [EAX]
0043ec4b  ff5210  CALL dword ptr [EDX + 0x10]
0043ec4e  8bd8  MOV EBX,EAX
0043ec50  4b  DEC EBX
0043ec51  85db  TEST EBX,EBX
0043ec53  7c36  JL 0x0043ec8b
0043ec55  43  INC EBX
0043ec56  c745f000000000  MOV dword ptr [EBP + -0x10],0x0
0043ec5d  8d4ddc  LEA ECX,[EBP + -0x24]
0043ec60  8b55f0  MOV EDX,dword ptr [EBP + -0x10]
0043ec63  8b45e8  MOV EAX,dword ptr [EBP + -0x18]
0043ec66  8b30  MOV ESI,dword ptr [EAX]
0043ec68  ff560c  CALL dword ptr [ESI + 0xc]
0043ec6b  8b55dc  MOV EDX,dword ptr [EBP + -0x24]
0043ec6e  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ec71  8b884c010000  MOV ECX,dword ptr [EAX + 0x14c]
0043ec77  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0043ec7a  8b8000010000  MOV EAX,dword ptr [EAX + 0x100]
0043ec80  8b30  MOV ESI,dword ptr [EAX]
0043ec82  ff5630  CALL dword ptr [ESI + 0x30]
0043ec85  ff45f0  INC dword ptr [EBP + -0x10]
0043ec88  4b  DEC EBX
0043ec89  75d2  JNZ 0x0043ec5d
0043ec8b  33c0  XOR EAX,EAX
0043ec8d  5a  POP EDX
0043ec8e  59  POP ECX
0043ec8f  59  POP ECX
0043ec90  648910  MOV dword ptr FS:[EAX],EDX
0043ec93  68a8ec4300  PUSH 0x43eca8
0043ec98  8b45e8  MOV EAX,dword ptr [EBP + -0x18]
0043ec9b  e8943ffcff  CALL 0x00402c34
0043eca0  c3  RET
