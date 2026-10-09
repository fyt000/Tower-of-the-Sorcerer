; FUN_0041bd8c at 0x0041bd8c
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041bd8c  c6400c01  MOV byte ptr [EAX + 0xc],0x1
0041bd90  6683780600  CMP word ptr [EAX + 0x6],0x0
0041bd95  740a  JZ 0x0041bda1
0041bd97  8bc8  MOV ECX,EAX
0041bd99  8bd0  MOV EDX,EAX
0041bd9b  8b4108  MOV EAX,dword ptr [ECX + 0x8]
0041bd9e  ff5104  CALL dword ptr [ECX + 0x4]
0041bda1  c3  RET
