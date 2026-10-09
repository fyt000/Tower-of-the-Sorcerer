; FUN_0042cee8 at 0x0042cee8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0042cee8  55  PUSH EBP
0042cee9  8bec  MOV EBP,ESP
0042ceeb  83c4f4  ADD ESP,-0xc
0042ceee  53  PUSH EBX
0042ceef  56  PUSH ESI
0042cef0  66894dfd  MOV word ptr [EBP + -0x3],CX
0042cef4  8855ff  MOV byte ptr [EBP + -0x1],DL
0042cef7  8b7508  MOV ESI,dword ptr [EBP + 0x8]
0042cefa  8b5d0c  MOV EBX,dword ptr [EBP + 0xc]
0042cefd  668b4dfd  MOV CX,word ptr [EBP + -0x3]
0042cf01  8a55ff  MOV DL,byte ptr [EBP + -0x1]
0042cf04  e863fbffff  CALL 0x0042ca6c
0042cf09  8945f4  MOV dword ptr [EBP + -0xc],EAX
0042cf0c  33c0  XOR EAX,EAX
0042cf0e  55  PUSH EBP
0042cf0f  6863cf4200  PUSH 0x42cf63
0042cf14  64ff30  PUSH dword ptr FS:[EAX]
0042cf17  648920  MOV dword ptr FS:[EAX],ESP
0042cf1a  8b4510  MOV EAX,dword ptr [EBP + 0x10]
0042cf1d  8b55f4  MOV EDX,dword ptr [EBP + -0xc]
0042cf20  8982d0000000  MOV dword ptr [EDX + 0xd0],EAX
0042cf26  85db  TEST EBX,EBX
0042cf28  7c0a  JL 0x0042cf34
0042cf2a  8bd3  MOV EDX,EBX
0042cf2c  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0042cf2f  e86461feff  CALL 0x00413098
0042cf34  85f6  TEST ESI,ESI
0042cf36  7c0a  JL 0x0042cf42
0042cf38  8bd6  MOV EDX,ESI
0042cf3a  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0042cf3d  e87661feff  CALL 0x004130b8
0042cf42  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0042cf45  e89268ffff  CALL 0x004237dc
0042cf4a  8945f8  MOV dword ptr [EBP + -0x8],EAX
0042cf4d  33c0  XOR EAX,EAX
0042cf4f  5a  POP EDX
0042cf50  59  POP ECX
0042cf51  59  POP ECX
0042cf52  648910  MOV dword ptr FS:[EAX],EDX
0042cf55  686acf4200  PUSH 0x42cf6a
0042cf5a  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0042cf5d  e8d25cfdff  CALL 0x00402c34
0042cf62  c3  RET
