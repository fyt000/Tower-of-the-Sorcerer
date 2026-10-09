; root_0041dac0 at 0x0041dac0
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041dac0  8b4010  MOV EAX,dword ptr [EAX + 0x10]
0041dac3  83780c00  CMP dword ptr [EAX + 0xc],0x0
0041dac7  7506  JNZ 0x0041dacf
0041dac9  83780800  CMP dword ptr [EAX + 0x8],0x0
0041dacd  7403  JZ 0x0041dad2
0041dacf  33c0  XOR EAX,EAX
0041dad1  c3  RET
0041dad2  b001  MOV AL,0x1
0041dad4  c3  RET
