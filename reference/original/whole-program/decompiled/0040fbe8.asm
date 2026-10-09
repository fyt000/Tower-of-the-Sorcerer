; FUN_0040fbe8 at 0x0040fbe8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040fbe8  55  PUSH EBP
0040fbe9  8bec  MOV EBP,ESP
0040fbeb  83c4f4  ADD ESP,-0xc
0040fbee  53  PUSH EBX
0040fbef  56  PUSH ESI
0040fbf0  894df8  MOV dword ptr [EBP + -0x8],ECX
0040fbf3  8bf2  MOV ESI,EDX
0040fbf5  8bd8  MOV EBX,EAX
0040fbf7  85f6  TEST ESI,ESI
0040fbf9  7444  JZ 0x0040fc3f
0040fbfb  c645f700  MOV byte ptr [EBP + -0x9],0x0
0040fbff  eb2d  JMP 0x0040fc2e
0040fc01  8b13  MOV EDX,dword ptr [EBX]
0040fc03  8bc6  MOV EAX,ESI
0040fc05  e812080000  CALL 0x0041041c
0040fc0a  8945fc  MOV dword ptr [EBP + -0x4],EAX
0040fc0d  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040fc10  8a402d  MOV AL,byte ptr [EAX + 0x2d]
0040fc13  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0040fc16  3a42ff  CMP AL,byte ptr [EDX + -0x1]
0040fc19  7724  JA 0x0040fc3f
0040fc1b  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040fc1e  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0040fc21  ff32  PUSH dword ptr [EDX]
0040fc23  ff55f8  CALL dword ptr [EBP + -0x8]
0040fc26  83c404  ADD ESP,0x4
0040fc29  8845f7  MOV byte ptr [EBP + -0x9],AL
0040fc2c  ff03  INC dword ptr [EBX]
0040fc2e  807df700  CMP byte ptr [EBP + -0x9],0x0
0040fc32  750b  JNZ 0x0040fc3f
0040fc34  8bc6  MOV EAX,ESI
0040fc36  e8d1070000  CALL 0x0041040c
0040fc3b  3b03  CMP EAX,dword ptr [EBX]
0040fc3d  7fc2  JG 0x0040fc01
0040fc3f  8a45f7  MOV AL,byte ptr [EBP + -0x9]
0040fc42  5e  POP ESI
0040fc43  5b  POP EBX
0040fc44  8be5  MOV ESP,EBP
0040fc46  5d  POP EBP
0040fc47  c3  RET
