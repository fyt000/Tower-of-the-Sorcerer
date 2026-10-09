; FUN_0041da80 at 0x0041da80
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041da80  53  PUSH EBX
0041da81  8b5810  MOV EBX,dword ptr [EAX + 0x10]
0041da84  837b0401  CMP dword ptr [EBX + 0x4],0x1
0041da88  7e19  JLE 0x0041daa3
0041da8a  8b5314  MOV EDX,dword ptr [EBX + 0x14]
0041da8d  52  PUSH EDX
0041da8e  8b5318  MOV EDX,dword ptr [EBX + 0x18]
0041da91  52  PUSH EDX
0041da92  8a5324  MOV DL,byte ptr [EBX + 0x24]
0041da95  52  PUSH EDX
0041da96  8b4b10  MOV ECX,dword ptr [EBX + 0x10]
0041da99  8b530c  MOV EDX,dword ptr [EBX + 0xc]
0041da9c  e85bfdffff  CALL 0x0041d7fc
0041daa1  5b  POP EBX
0041daa2  c3  RET
0041daa3  8b4308  MOV EAX,dword ptr [EBX + 0x8]
0041daa6  e88951feff  CALL 0x00402c34
0041daab  33c0  XOR EAX,EAX
0041daad  894308  MOV dword ptr [EBX + 0x8],EAX
0041dab0  33c0  XOR EAX,EAX
0041dab2  89431c  MOV dword ptr [EBX + 0x1c],EAX
0041dab5  33c0  XOR EAX,EAX
0041dab7  894320  MOV dword ptr [EBX + 0x20],EAX
0041daba  c6432500  MOV byte ptr [EBX + 0x25],0x0
0041dabe  5b  POP EBX
0041dabf  c3  RET
