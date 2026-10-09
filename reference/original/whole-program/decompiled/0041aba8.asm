; root_0041aba8 at 0x0041aba8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041aba8  53  PUSH EBX
0041aba9  8bd8  MOV EBX,EAX
0041abab  f6430802  TEST byte ptr [EBX + 0x8],0x2
0041abaf  7413  JZ 0x0041abc4
0041abb1  806308fd  AND byte ptr [EBX + 0x8],0xfd
0041abb5  a1e0a64800  MOV EAX,[0x0048a6e0]
0041abba  50  PUSH EAX
0041abbb  8b4304  MOV EAX,dword ptr [EBX + 0x4]
0041abbe  50  PUSH EAX
0041abbf  e808a2feff  CALL 0x00404dcc
0041abc4  5b  POP EBX
0041abc5  c3  RET
