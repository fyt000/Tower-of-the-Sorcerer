; @HandleFinally; compiler-assisted focused span, not a new Ghidra ownership claim
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
00403140  8b442404  MOV eax, dword ptr [esp + 4]
00403144  8b542408  MOV edx, dword ptr [esp + 8]
00403148  f7400406000000  TEST dword ptr [eax + 4], 6
0040314f  741f  JE 0x403170
00403151  8b4a04  MOV ecx, dword ptr [edx + 4]
00403154  c7420470314000  MOV dword ptr [edx + 4], 0x403170
0040315b  53  PUSH ebx
0040315c  56  PUSH esi
0040315d  57  PUSH edi
0040315e  55  PUSH ebp
0040315f  8b6a08  MOV ebp, dword ptr [edx + 8]
00403162  83c105  ADD ecx, 5
00403165  e87efdffff  CALL 0x402ee8
0040316a  ffd1  CALL ecx
0040316c  5d  POP ebp
0040316d  5f  POP edi
0040316e  5e  POP esi
0040316f  5b  POP ebx
00403170  b801000000  MOV eax, 1
00403175  c3  RET
