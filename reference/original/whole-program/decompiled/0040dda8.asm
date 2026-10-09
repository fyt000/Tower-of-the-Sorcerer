; FUN_0040dda8 at 0x0040dda8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040dda8  55  PUSH EBP
0040dda9  8bec  MOV EBP,ESP
0040ddab  83c4f4  ADD ESP,-0xc
0040ddae  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040ddb1  8b50f4  MOV EDX,dword ptr [EAX + -0xc]
0040ddb4  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040ddb7  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0040ddba  e8d1a7ffff  CALL 0x00408590
0040ddbf  db7df6  FSTP tword ptr [EBP + -0xa]
0040ddc2  9b  WAIT
0040ddc3  55  PUSH EBP
0040ddc4  e887ffffff  CALL 0x0040dd50
0040ddc9  59  POP ECX
0040ddca  84c0  TEST AL,AL
0040ddcc  7520  JNZ 0x0040ddee
0040ddce  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040ddd1  50  PUSH EAX
0040ddd2  e821fcffff  CALL 0x0040d9f8
0040ddd7  59  POP ECX
0040ddd8  668b45fe  MOV AX,word ptr [EBP + -0x2]
0040dddc  50  PUSH EAX
0040dddd  ff75fa  PUSH dword ptr [EBP + -0x6]
0040dde0  ff75f6  PUSH dword ptr [EBP + -0xa]
0040dde3  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040dde6  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040dde9  e872f9ffff  CALL 0x0040d760
0040ddee  8be5  MOV ESP,EBP
0040ddf0  5d  POP EBP
0040ddf1  c3  RET
