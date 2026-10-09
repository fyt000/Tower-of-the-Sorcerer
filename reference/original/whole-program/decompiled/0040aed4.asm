; root_0040aed4 at 0x0040aed4
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040aed4  53  PUSH EBX
0040aed5  8bd8  MOV EBX,EAX
0040aed7  807b1400  CMP byte ptr [EBX + 0x14],0x0
0040aedb  7521  JNZ 0x0040aefe
0040aedd  837b0c01  CMP dword ptr [EBX + 0xc],0x1
0040aee1  7e1b  JLE 0x0040aefe
0040aee3  8bc3  MOV EAX,EBX
0040aee5  8b10  MOV EDX,dword ptr [EAX]
0040aee7  ff526c  CALL dword ptr [EDX + 0x6c]
0040aeea  8b4b0c  MOV ECX,dword ptr [EBX + 0xc]
0040aeed  49  DEC ECX
0040aeee  33d2  XOR EDX,EDX
0040aef0  8bc3  MOV EAX,EBX
0040aef2  e8d9feffff  CALL 0x0040add0
0040aef7  8bc3  MOV EAX,EBX
0040aef9  8b10  MOV EDX,dword ptr [EAX]
0040aefb  ff5268  CALL dword ptr [EDX + 0x68]
0040aefe  5b  POP EBX
0040aeff  c3  RET
