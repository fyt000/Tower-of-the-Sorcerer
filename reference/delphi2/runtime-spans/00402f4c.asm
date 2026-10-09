; @HandleAnyException; compiler-assisted focused span, not a new Ghidra ownership claim
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
00402f4c  8b442404  MOV eax, dword ptr [esp + 4]
00402f50  f7400406000000  TEST dword ptr [eax + 4], 6
00402f57  0f85ac000000  JNE 0x403009
00402f5d  8138cefaed0e  CMP dword ptr [eax], 0xeedface
00402f63  8b5018  MOV edx, dword ptr [eax + 0x18]
00402f66  8b4814  MOV ecx, dword ptr [eax + 0x14]
00402f69  742f  JE 0x402f9a
00402f6b  e8fcfbffff  CALL 0x402b6c
00402f70  8b150ca04800  MOV edx, dword ptr [0x48a00c]
00402f76  85d2  TEST edx, edx
00402f78  0f848b000000  JE 0x403009
00402f7e  ffd2  CALL edx
00402f80  85c0  TEST eax, eax
00402f82  0f8481000000  JE 0x403009
00402f88  8b54240c  MOV edx, dword ptr [esp + 0xc]
00402f8c  e8dbfeffff  CALL 0x402e6c
00402f91  89c2  MOV edx, eax
00402f93  8b442404  MOV eax, dword ptr [esp + 4]
00402f97  8b480c  MOV ecx, dword ptr [eax + 0xc]
00402f9a  83480402  OR dword ptr [eax + 4], 2
00402f9e  53  PUSH ebx
00402f9f  31db  XOR ebx, ebx
00402fa1  56  PUSH esi
00402fa2  57  PUSH edi
00402fa3  55  PUSH ebp
00402fa4  648b1b  MOV ebx, dword ptr fs:[ebx]
00402fa7  53  PUSH ebx
00402fa8  50  PUSH eax
00402fa9  52  PUSH edx
00402faa  51  PUSH ecx
00402fab  8b542428  MOV edx, dword ptr [esp + 0x28]
00402faf  6a00  PUSH 0
00402fb1  50  PUSH eax
00402fb2  68bd2f4000  PUSH 0x402fbd
00402fb7  52  PUSH edx
00402fb8  e8bbe2ffff  CALL 0x401278
00402fbd  8b7c2428  MOV edi, dword ptr [esp + 0x28]
00402fc1  e8d2040000  CALL 0x403498
00402fc6  ffb000000000  PUSH dword ptr [eax]
00402fcc  89a000000000  MOV dword ptr [eax], esp
00402fd2  8b6f08  MOV ebp, dword ptr [edi + 8]
00402fd5  8b5f04  MOV ebx, dword ptr [edi + 4]
00402fd8  c74704e92f4000  MOV dword ptr [edi + 4], 0x402fe9
00402fdf  83c305  ADD ebx, 5
00402fe2  e8cdfeffff  CALL 0x402eb4
00402fe7  ffe3  JMP ebx
00402fe9  e952010000  JMP 0x403140
00402fee  e8a5040000  CALL 0x403498
00402ff3  8b8800000000  MOV ecx, dword ptr [eax]
00402ff9  8b11  MOV edx, dword ptr [ecx]
00402ffb  899000000000  MOV dword ptr [eax], edx
00403001  8b4108  MOV eax, dword ptr [ecx + 8]
00403004  e92bfcffff  JMP 0x402c34
00403009  b801000000  MOV eax, 1
0040300e  c3  RET
