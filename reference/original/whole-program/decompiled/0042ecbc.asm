; root_0042ecbc at 0x0042ecbc
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0042ecbc  55  PUSH EBP
0042ecbd  8bec  MOV EBP,ESP
0042ecbf  83c4f0  ADD ESP,-0x10
0042ecc2  53  PUSH EBX
0042ecc3  56  PUSH ESI
0042ecc4  57  PUSH EDI
0042ecc5  8b5d14  MOV EBX,dword ptr [EBP + 0x14]
0042ecc8  8b7510  MOV ESI,dword ptr [EBP + 0x10]
0042eccb  33c0  XOR EAX,EAX
0042eccd  8945fc  MOV dword ptr [EBP + -0x4],EAX
0042ecd0  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0042ecd3  8945f0  MOV dword ptr [EBP + -0x10],EAX
0042ecd6  8d4601  LEA EAX,[ESI + 0x1]
0042ecd9  e84275fdff  CALL 0x00406220
0042ecde  8945f8  MOV dword ptr [EBP + -0x8],EAX
0042ece1  33c0  XOR EAX,EAX
0042ece3  55  PUSH EBP
0042ece4  689ced4200  PUSH 0x42ed9c
0042ece9  64ff30  PUSH dword ptr FS:[EAX]
0042ecec  648920  MOV dword ptr FS:[EAX],ESP
0042ecef  d1fe  SAR ESI,0x1
0042ecf1  7903  JNS 0x0042ecf6
0042ecf3  83d600  ADC ESI,0x0
0042ecf6  33c0  XOR EAX,EAX
0042ecf8  8903  MOV dword ptr [EBX],EAX
0042ecfa  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0042ecfd  03c6  ADD EAX,ESI
0042ecff  8945f4  MOV dword ptr [EBP + -0xc],EAX
0042ed02  33c0  XOR EAX,EAX
0042ed04  55  PUSH EBP
0042ed05  6875ed4200  PUSH 0x42ed75
0042ed0a  64ff30  PUSH dword ptr FS:[EAX]
0042ed0d  648920  MOV dword ptr FS:[EAX],ESP
0042ed10  8b45f0  MOV EAX,dword ptr [EBP + -0x10]
0042ed13  833800  CMP dword ptr [EAX],0x0
0042ed16  7415  JZ 0x0042ed2d
0042ed18  56  PUSH ESI
0042ed19  8b45f0  MOV EAX,dword ptr [EBP + -0x10]
0042ed1c  8b5004  MOV EDX,dword ptr [EAX + 0x4]
0042ed1f  8b45f0  MOV EAX,dword ptr [EBP + -0x10]
0042ed22  8b00  MOV EAX,dword ptr [EAX]
0042ed24  8b4df4  MOV ECX,dword ptr [EBP + -0xc]
0042ed27  8b30  MOV ESI,dword ptr [EAX]
0042ed29  ff16  CALL dword ptr [ESI]
0042ed2b  8903  MOV dword ptr [EBX],EAX
0042ed2d  833b00  CMP dword ptr [EBX],0x0
0042ed30  7e39  JLE 0x0042ed6b
0042ed32  8b03  MOV EAX,dword ptr [EBX]
0042ed34  8b55f4  MOV EDX,dword ptr [EBP + -0xc]
0042ed37  c6040200  MOV byte ptr [EDX + EAX*0x1],0x0
0042ed3b  8b03  MOV EAX,dword ptr [EBX]
0042ed3d  8b55f4  MOV EDX,dword ptr [EBP + -0xc]
0042ed40  807c02ff0d  CMP byte ptr [EDX + EAX*0x1 + -0x1],0xd
0042ed45  750a  JNZ 0x0042ed51
0042ed47  8b03  MOV EAX,dword ptr [EBX]
0042ed49  8b55f4  MOV EDX,dword ptr [EBP + -0xc]
0042ed4c  c64402ff00  MOV byte ptr [EDX + EAX*0x1 + -0x1],0x0
0042ed51  8b55f4  MOV EDX,dword ptr [EBP + -0xc]
0042ed54  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0042ed57  e8c8feffff  CALL 0x0042ec24
0042ed5c  8903  MOV dword ptr [EBX],EAX
0042ed5e  8b0b  MOV ECX,dword ptr [EBX]
0042ed60  8b550c  MOV EDX,dword ptr [EBP + 0xc]
0042ed63  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0042ed66  e8053bfdff  CALL 0x00402870
0042ed6b  33c0  XOR EAX,EAX
0042ed6d  5a  POP EDX
0042ed6e  59  POP ECX
0042ed6f  59  POP ECX
0042ed70  648910  MOV dword ptr FS:[EAX],EDX
0042ed73  eb11  JMP 0x0042ed86
