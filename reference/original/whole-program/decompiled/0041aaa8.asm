; root_0041aaa8 at 0x0041aaa8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041aaa8  6683782e00  CMP word ptr [EAX + 0x2e],0x0
0041aaad  740a  JZ 0x0041aab9
0041aaaf  8bc8  MOV ECX,EAX
0041aab1  8bd0  MOV EDX,EAX
0041aab3  8b4130  MOV EAX,dword ptr [ECX + 0x30]
0041aab6  ff512c  CALL dword ptr [ECX + 0x2c]
0041aab9  c3  RET
