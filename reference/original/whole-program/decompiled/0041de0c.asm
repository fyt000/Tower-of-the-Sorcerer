; FUN_0041de0c at 0x0041de0c
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041de0c  55  PUSH EBP
0041de0d  8bec  MOV EBP,ESP
0041de0f  51  PUSH ECX
0041de10  53  PUSH EBX
0041de11  56  PUSH ESI
0041de12  57  PUSH EDI
0041de13  8bf9  MOV EDI,ECX
0041de15  8bf2  MOV ESI,EDX
0041de17  8bd8  MOV EBX,EAX
0041de19  b201  MOV DL,0x1
0041de1b  b86c934100  MOV EAX,0x41936c
0041de20  e8e74dfeff  CALL 0x00402c0c
0041de25  8945fc  MOV dword ptr [EBP + -0x4],EAX
0041de28  33c0  XOR EAX,EAX
0041de2a  55  PUSH EBP
0041de2b  688bde4100  PUSH 0x41de8b
0041de30  64ff30  PUSH dword ptr FS:[EAX]
0041de33  648920  MOV dword ptr FS:[EAX],ESP
0041de36  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0041de39  89700c  MOV dword ptr [EAX + 0xc],ESI
0041de3c  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0041de3f  897810  MOV dword ptr [EAX + 0x10],EDI
0041de42  8b4520  MOV EAX,dword ptr [EBP + 0x20]
0041de45  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0041de48  894214  MOV dword ptr [EDX + 0x14],EAX
0041de4b  8b451c  MOV EAX,dword ptr [EBP + 0x1c]
0041de4e  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0041de51  894218  MOV dword ptr [EDX + 0x18],EAX
0041de54  8a4518  MOV AL,byte ptr [EBP + 0x18]
0041de57  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0041de5a  884224  MOV byte ptr [EDX + 0x24],AL
0041de5d  8b4514  MOV EAX,dword ptr [EBP + 0x14]
0041de60  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0041de63  894208  MOV dword ptr [EDX + 0x8],EAX
0041de66  8a4510  MOV AL,byte ptr [EBP + 0x10]
0041de69  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0041de6c  884225  MOV byte ptr [EDX + 0x25],AL
0041de6f  8b450c  MOV EAX,dword ptr [EBP + 0xc]
0041de72  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0041de75  89421c  MOV dword ptr [EDX + 0x1c],EAX
0041de78  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0041de7b  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0041de7e  894220  MOV dword ptr [EDX + 0x20],EAX
0041de81  33c0  XOR EAX,EAX
0041de83  5a  POP EDX
0041de84  59  POP ECX
0041de85  59  POP ECX
0041de86  648910  MOV dword ptr FS:[EAX],EDX
0041de89  eb17  JMP 0x0041dea2
