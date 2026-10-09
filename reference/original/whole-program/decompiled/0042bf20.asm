; FUN_0042bf20 at 0x0042bf20
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0042bf20  55  PUSH EBP
0042bf21  8bec  MOV EBP,ESP
0042bf23  83c4f4  ADD ESP,-0xc
0042bf26  53  PUSH EBX
0042bf27  894df4  MOV dword ptr [EBP + -0xc],ECX
0042bf2a  8955fc  MOV dword ptr [EBP + -0x4],EDX
0042bf2d  8945f8  MOV dword ptr [EBP + -0x8],EAX
0042bf30  8b5d08  MOV EBX,dword ptr [EBP + 0x8]
0042bf33  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0042bf36  8b4010  MOV EAX,dword ptr [EAX + 0x10]
0042bf39  ba01000000  MOV EDX,0x1
0042bf3e  e81de1feff  CALL 0x0041a060
0042bf43  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0042bf46  ff480c  DEC dword ptr [EAX + 0xc]
0042bf49  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0042bf4c  ff4808  DEC dword ptr [EAX + 0x8]
0042bf4f  85db  TEST EBX,EBX
0042bf51  7e19  JLE 0x0042bf6c
0042bf53  4b  DEC EBX
0042bf54  55  PUSH EBP
0042bf55  e802ffffff  CALL 0x0042be5c
0042bf5a  59  POP ECX
0042bf5b  6aff  PUSH -0x1
0042bf5d  6aff  PUSH -0x1
0042bf5f  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0042bf62  50  PUSH EAX
0042bf63  e80c91fdff  CALL 0x00405074
0042bf68  85db  TEST EBX,EBX
0042bf6a  7fe7  JG 0x0042bf53
0042bf6c  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0042bf6f  ff400c  INC dword ptr [EAX + 0xc]
0042bf72  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0042bf75  ff4008  INC dword ptr [EAX + 0x8]
0042bf78  5b  POP EBX
0042bf79  8be5  MOV ESP,EBP
0042bf7b  5d  POP EBP
0042bf7c  c20800  RET 0x8
