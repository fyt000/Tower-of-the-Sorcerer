; vcl_413cb8 at 00413cb8
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
00413cb8  55  PUSH EBP
00413cb9  8bec  MOV EBP,ESP
00413cbb  83c4f0  ADD ESP,-0x10
00413cbe  8955f0  MOV dword ptr [EBP + -0x10],EDX
00413cc1  894df4  MOV dword ptr [EBP + -0xc],ECX
00413cc4  8b5508  MOV EDX,dword ptr [EBP + 0x8]
00413cc7  8955f8  MOV dword ptr [EBP + -0x8],EDX
00413cca  33d2  XOR EDX,EDX
00413ccc  8955fc  MOV dword ptr [EBP + -0x4],EDX
00413ccf  85c0  TEST EAX,EAX
00413cd1  7408  JZ 0x00413cdb
00413cd3  8d55f0  LEA EDX,[EBP + -0x10]
00413cd6  8b08  MOV ECX,dword ptr [EAX]
00413cd8  ff5140  CALL dword ptr [ECX + 0x40]
00413cdb  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
00413cde  8be5  MOV ESP,EBP
00413ce0  5d  POP EBP
00413ce1  c20400  RET 0x4
