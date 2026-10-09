; root_0040aab0 at 0x0040aab0
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040aab0  53  PUSH EBX
0040aab1  8bd8  MOV EBX,EAX
0040aab3  837b0c00  CMP dword ptr [EBX + 0xc],0x0
0040aab7  742c  JZ 0x0040aae5
0040aab9  8bc3  MOV EAX,EBX
0040aabb  8b10  MOV EDX,dword ptr [EAX]
0040aabd  ff526c  CALL dword ptr [EDX + 0x6c]
0040aac0  8b4308  MOV EAX,dword ptr [EBX + 0x8]
0040aac3  8b4b0c  MOV ECX,dword ptr [EBX + 0xc]
0040aac6  bae88c4000  MOV EDX,0x408ce8
0040aacb  e8bc8fffff  CALL 0x00403a8c
0040aad0  33c0  XOR EAX,EAX
0040aad2  89430c  MOV dword ptr [EBX + 0xc],EAX
0040aad5  33d2  XOR EDX,EDX
0040aad7  8bc3  MOV EAX,EBX
0040aad9  e8ae030000  CALL 0x0040ae8c
0040aade  8bc3  MOV EAX,EBX
0040aae0  8b10  MOV EDX,dword ptr [EAX]
0040aae2  ff5268  CALL dword ptr [EDX + 0x68]
0040aae5  5b  POP EBX
0040aae6  c3  RET
