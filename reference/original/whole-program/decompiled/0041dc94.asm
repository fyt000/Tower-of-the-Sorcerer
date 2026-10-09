; FUN_0041dc94 at 0x0041dc94
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041dc94  53  PUSH EBX
0041dc95  80781800  CMP byte ptr [EAX + 0x18],0x0
0041dc99  752e  JNZ 0x0041dcc9
0041dc9b  8b5810  MOV EBX,dword ptr [EAX + 0x10]
0041dc9e  837b1000  CMP dword ptr [EBX + 0x10],0x0
0041dca2  7525  JNZ 0x0041dcc9
0041dca4  8a4325  MOV AL,byte ptr [EBX + 0x25]
0041dca7  fec8  DEC AL
0041dca9  7406  JZ 0x0041dcb1
0041dcab  fec8  DEC AL
0041dcad  740f  JZ 0x0041dcbe
0041dcaf  eb18  JMP 0x0041dcc9
0041dcb1  8b431c  MOV EAX,dword ptr [EBX + 0x1c]
0041dcb4  e817d1ffff  CALL 0x0041add0
0041dcb9  894310  MOV dword ptr [EBX + 0x10],EAX
0041dcbc  eb0b  JMP 0x0041dcc9
0041dcbe  8b431c  MOV EAX,dword ptr [EBX + 0x1c]
0041dcc1  e872d4ffff  CALL 0x0041b138
0041dcc6  894310  MOV dword ptr [EBX + 0x10],EAX
0041dcc9  5b  POP EBX
0041dcca  c3  RET
