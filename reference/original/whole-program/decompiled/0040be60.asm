; FUN_0040be60 at 0x0040be60
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040be60  55  PUSH EBP
0040be61  8bec  MOV EBP,ESP
0040be63  53  PUSH EBX
0040be64  56  PUSH ESI
0040be65  57  PUSH EDI
0040be66  33c0  XOR EAX,EAX
0040be68  55  PUSH EBP
0040be69  68b0be4000  PUSH 0x40beb0
0040be6e  64ff30  PUSH dword ptr FS:[EAX]
0040be71  648920  MOV dword ptr FS:[EAX],ESP
0040be74  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040be77  8b50ec  MOV EDX,dword ptr [EAX + -0x14]
0040be7a  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040be7d  8b40f4  MOV EAX,dword ptr [EAX + -0xc]
0040be80  8b4018  MOV EAX,dword ptr [EAX + 0x18]
0040be83  e8e8d4ffff  CALL 0x00409370
0040be88  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0040be8b  8b52f4  MOV EDX,dword ptr [EDX + -0xc]
0040be8e  8b4a24  MOV ECX,dword ptr [EDX + 0x24]
0040be91  b201  MOV DL,0x1
0040be93  ff5024  CALL dword ptr [EAX + 0x24]
0040be96  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0040be99  8942f0  MOV dword ptr [EDX + -0x10],EAX
0040be9c  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040be9f  8b40f0  MOV EAX,dword ptr [EAX + -0x10]
0040bea2  80481c01  OR byte ptr [EAX + 0x1c],0x1
0040bea6  33c0  XOR EAX,EAX
0040bea8  5a  POP EDX
0040bea9  59  POP ECX
0040beaa  59  POP ECX
0040beab  648910  MOV dword ptr FS:[EAX],EDX
0040beae  eb23  JMP 0x0040bed3
