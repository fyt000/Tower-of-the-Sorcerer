; root_0041dc4a at 0x0041dc4a
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041dc4a  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0041dc4d  e8e24ffeff  CALL 0x00402c34
0041dc52  e8bd55feff  CALL 0x00403214
0041dc57  e80c56feff  CALL 0x00403268
0041dc5c  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0041dc5f  894308  MOV dword ptr [EBX + 0x8],EAX
0041dc62  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0041dc65  89431c  MOV dword ptr [EBX + 0x1c],EAX
0041dc68  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0041dc6b  894320  MOV dword ptr [EBX + 0x20],EAX
0041dc6e  8b431c  MOV EAX,dword ptr [EBX + 0x1c]
0041dc71  8b00  MOV EAX,dword ptr [EAX]
0041dc73  83e80c  SUB EAX,0xc
0041dc76  740b  JZ 0x0041dc83
0041dc78  83e81c  SUB EAX,0x1c
0041dc7b  750c  JNZ 0x0041dc89
0041dc7d  c6432501  MOV byte ptr [EBX + 0x25],0x1
0041dc81  eb0a  JMP 0x0041dc8d
0041dc83  c6432502  MOV byte ptr [EBX + 0x25],0x2
0041dc87  eb04  JMP 0x0041dc8d
0041dc89  c6432500  MOV byte ptr [EBX + 0x25],0x0
0041dc8d  5f  POP EDI
0041dc8e  5e  POP ESI
0041dc8f  5b  POP EBX
0041dc90  8be5  MOV ESP,EBP
0041dc92  5d  POP EBP
0041dc93  c3  RET
