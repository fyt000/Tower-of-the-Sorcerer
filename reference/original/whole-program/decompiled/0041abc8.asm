; root_0041abc8 at 0x0041abc8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041abc8  53  PUSH EBX
0041abc9  8bd8  MOV EBX,EAX
0041abcb  f6430804  TEST byte ptr [EBX + 0x8],0x4
0041abcf  7413  JZ 0x0041abe4
0041abd1  806308fb  AND byte ptr [EBX + 0x8],0xfb
0041abd5  a1d8a64800  MOV EAX,[0x0048a6d8]
0041abda  50  PUSH EAX
0041abdb  8b4304  MOV EAX,dword ptr [EBX + 0x4]
0041abde  50  PUSH EAX
0041abdf  e8e8a1feff  CALL 0x00404dcc
0041abe4  5b  POP EBX
0041abe5  c3  RET
