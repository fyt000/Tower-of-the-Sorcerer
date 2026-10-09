; root_0041aabc at 0x0041aabc
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041aabc  6683782600  CMP word ptr [EAX + 0x26],0x0
0041aac1  740a  JZ 0x0041aacd
0041aac3  8bc8  MOV ECX,EAX
0041aac5  8bd0  MOV EDX,EAX
0041aac7  8b4128  MOV EAX,dword ptr [ECX + 0x28]
0041aaca  ff5124  CALL dword ptr [ECX + 0x24]
0041aacd  c3  RET
