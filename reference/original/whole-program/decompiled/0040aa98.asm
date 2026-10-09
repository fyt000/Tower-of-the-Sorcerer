; root_0040aa98 at 0x0040aa98
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040aa98  83780400  CMP dword ptr [EAX + 0x4],0x0
0040aa9c  7511  JNZ 0x0040aaaf
0040aa9e  6683782200  CMP word ptr [EAX + 0x22],0x0
0040aaa3  740a  JZ 0x0040aaaf
0040aaa5  8bc8  MOV ECX,EAX
0040aaa7  8bd0  MOV EDX,EAX
0040aaa9  8b4124  MOV EAX,dword ptr [ECX + 0x24]
0040aaac  ff5120  CALL dword ptr [ECX + 0x20]
0040aaaf  c3  RET
