; FUN_0041bae8 at 0x0041bae8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041bae8  55  PUSH EBP
0041bae9  8bec  MOV EBP,ESP
0041baeb  83c4f4  ADD ESP,-0xc
0041baee  53  PUSH EBX
0041baef  56  PUSH ESI
0041baf0  57  PUSH EDI
0041baf1  894dfc  MOV dword ptr [EBP + -0x4],ECX
0041baf4  8bda  MOV EBX,EDX
0041baf6  8bf8  MOV EDI,EAX
0041baf8  8b750c  MOV ESI,dword ptr [EBP + 0xc]
0041bafb  85db  TEST EBX,EBX
0041bafd  7505  JNZ 0x0041bb04
0041baff  e834f1ffff  CALL 0x0041ac38
0041bb04  8b4510  MOV EAX,dword ptr [EBP + 0x10]
0041bb07  50  PUSH EAX
0041bb08  8d4df4  LEA ECX,[EBP + -0xc]
0041bb0b  8d55f8  LEA EDX,[EBP + -0x8]
0041bb0e  8bc3  MOV EAX,EBX
0041bb10  e8c7feffff  CALL 0x0041b9dc
0041bb15  8b55f8  MOV EDX,dword ptr [EBP + -0x8]
0041bb18  0355f4  ADD EDX,dword ptr [EBP + -0xc]
0041bb1b  8bc7  MOV EAX,EDI
0041bb1d  e8c6f7feff  CALL 0x0040b2e8
0041bb22  8b4704  MOV EAX,dword ptr [EDI + 0x4]
0041bb25  8906  MOV dword ptr [ESI],EAX
0041bb27  8b06  MOV EAX,dword ptr [ESI]
0041bb29  0345f8  ADD EAX,dword ptr [EBP + -0x8]
0041bb2c  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0041bb2f  8902  MOV dword ptr [EDX],EAX
0041bb31  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0041bb34  8b00  MOV EAX,dword ptr [EAX]
0041bb36  50  PUSH EAX
0041bb37  8b4510  MOV EAX,dword ptr [EBP + 0x10]
0041bb3a  50  PUSH EAX
0041bb3b  8b0e  MOV ECX,dword ptr [ESI]
0041bb3d  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0041bb40  8bc3  MOV EAX,EBX
0041bb42  e8e1feffff  CALL 0x0041ba28
0041bb47  5f  POP EDI
0041bb48  5e  POP ESI
0041bb49  5b  POP EBX
0041bb4a  8be5  MOV ESP,EBP
0041bb4c  5d  POP EBP
0041bb4d  c20c00  RET 0xc
