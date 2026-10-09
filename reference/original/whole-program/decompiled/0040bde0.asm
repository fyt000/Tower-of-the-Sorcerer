; root_0040bde0 at 0x0040bde0
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040bde0  55  PUSH EBP
0040bde1  8bec  MOV EBP,ESP
0040bde3  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040bde6  f640ff01  TEST byte ptr [EAX + -0x1],0x1
0040bdea  7509  JNZ 0x0040bdf5
0040bdec  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040bdef  8378f800  CMP dword ptr [EAX + -0x8],0x0
0040bdf3  7404  JZ 0x0040bdf9
0040bdf5  33c0  XOR EAX,EAX
0040bdf7  5d  POP EBP
0040bdf8  c3  RET
0040bdf9  b001  MOV AL,0x1
0040bdfb  5d  POP EBP
0040bdfc  c3  RET
