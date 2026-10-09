; root_0042afd0 at 0x0042afd0
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0042afd0  55  PUSH EBP
0042afd1  8bec  MOV EBP,ESP
0042afd3  83c4f8  ADD ESP,-0x8
0042afd6  8955f8  MOV dword ptr [EBP + -0x8],EDX
0042afd9  8945fc  MOV dword ptr [EBP + -0x4],EAX
0042afdc  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0042afdf  83780400  CMP dword ptr [EAX + 0x4],0x0
0042afe3  7409  JZ 0x0042afee
0042afe5  55  PUSH EBP
0042afe6  e881feffff  CALL 0x0042ae6c
0042afeb  59  POP ECX
0042afec  eb0b  JMP 0x0042aff9
0042afee  8b55f8  MOV EDX,dword ptr [EBP + -0x8]
0042aff1  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0042aff4  e80faafeff  CALL 0x00415a08
0042aff9  59  POP ECX
0042affa  59  POP ECX
0042affb  5d  POP EBP
0042affc  c3  RET
