; FUN_0041ca94 at 0x0041ca94
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041ca94  55  PUSH EBP
0041ca95  8bec  MOV EBP,ESP
0041ca97  83c4cc  ADD ESP,-0x34
0041ca9a  53  PUSH EBX
0041ca9b  56  PUSH ESI
0041ca9c  57  PUSH EDI
0041ca9d  894df8  MOV dword ptr [EBP + -0x8],ECX
0041caa0  8955fc  MOV dword ptr [EBP + -0x4],EDX
0041caa3  8bd8  MOV EBX,EAX
0041caa5  8bc3  MOV EAX,EBX
0041caa7  e8a8feffff  CALL 0x0041c954
0041caac  8d55dc  LEA EDX,[EBP + -0x24]
0041caaf  b916000000  MOV ECX,0x16
0041cab4  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0041cab7  8b30  MOV ESI,dword ptr [EAX]
0041cab9  ff16  CALL dword ptr [ESI]
0041cabb  817ddcd7cdc69a  CMP dword ptr [EBP + -0x24],0x9ac6cdd7
0041cac2  750e  JNZ 0x0041cad2
0041cac4  8d45dc  LEA EAX,[EBP + -0x24]
0041cac7  e844eeffff  CALL 0x0041b910
0041cacc  663b45f0  CMP AX,word ptr [EBP + -0x10]
0041cad0  7405  JZ 0x0041cad7
0041cad2  e879e1ffff  CALL 0x0041ac50
0041cad7  836df816  SUB dword ptr [EBP + -0x8],0x16
0041cadb  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0041cade  e86d5bfeff  CALL 0x00402650
0041cae3  8945f4  MOV dword ptr [EBP + -0xc],EAX
0041cae6  8b7310  MOV ESI,dword ptr [EBX + 0x10]
0041cae9  33c0  XOR EAX,EAX
0041caeb  55  PUSH EBP
0041caec  68aacb4100  PUSH 0x41cbaa
0041caf1  64ff30  PUSH dword ptr FS:[EAX]
0041caf4  648920  MOV dword ptr FS:[EAX],ESP
0041caf7  8b55f4  MOV EDX,dword ptr [EBP + -0xc]
0041cafa  8b4df8  MOV ECX,dword ptr [EBP + -0x8]
0041cafd  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0041cb00  8b38  MOV EDI,dword ptr [EAX]
0041cb02  ff17  CALL dword ptr [EDI]
0041cb04  8b4310  MOV EAX,dword ptr [EBX + 0x10]
0041cb07  668b55ea  MOV DX,word ptr [EBP + -0x16]
0041cb0b  66895018  MOV word ptr [EAX + 0x18],DX
0041cb0f  66837dea00  CMP word ptr [EBP + -0x16],0x0
0041cb14  7506  JNZ 0x0041cb1c
0041cb16  66c745ea6000  MOV word ptr [EBP + -0x16],0x60
0041cb1c  0fb745ea  MOVZX EAX,word ptr [EBP + -0x16]
0041cb20  50  PUSH EAX
0041cb21  6838630000  PUSH 0x6338
0041cb26  0fbf45e6  MOVSX EAX,word ptr [EBP + -0x1a]
0041cb2a  0fbf55e2  MOVSX EDX,word ptr [EBP + -0x1e]
0041cb2e  2bc2  SUB EAX,EDX
0041cb30  50  PUSH EAX
0041cb31  e8de80feff  CALL 0x00404c14
0041cb36  89460c  MOV dword ptr [ESI + 0xc],EAX
0041cb39  0fb745ea  MOVZX EAX,word ptr [EBP + -0x16]
0041cb3d  50  PUSH EAX
0041cb3e  6838630000  PUSH 0x6338
0041cb43  0fbf45e8  MOVSX EAX,word ptr [EBP + -0x18]
0041cb47  0fbf55e4  MOVSX EDX,word ptr [EBP + -0x1c]
0041cb4b  2bc2  SUB EAX,EDX
0041cb4d  50  PUSH EAX
0041cb4e  e8c180feff  CALL 0x00404c14
0041cb53  894610  MOV dword ptr [ESI + 0x10],EAX
0041cb56  c745cc08000000  MOV dword ptr [EBP + -0x34],0x8
0041cb5d  33c0  XOR EAX,EAX
0041cb5f  8945d0  MOV dword ptr [EBP + -0x30],EAX
0041cb62  33c0  XOR EAX,EAX
0041cb64  8945d4  MOV dword ptr [EBP + -0x2c],EAX
0041cb67  33c0  XOR EAX,EAX
0041cb69  8945d8  MOV dword ptr [EBP + -0x28],EAX
0041cb6c  8d45cc  LEA EAX,[EBP + -0x34]
0041cb6f  50  PUSH EAX
0041cb70  6a00  PUSH 0x0
0041cb72  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0041cb75  50  PUSH EAX
0041cb76  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0041cb79  50  PUSH EAX
0041cb7a  e89582feff  CALL 0x00404e14
0041cb7f  8bf8  MOV EDI,EAX
0041cb81  897e08  MOV dword ptr [ESI + 0x8],EDI
0041cb84  85ff  TEST EDI,EDI
0041cb86  7505  JNZ 0x0041cb8d
0041cb88  e8c3e0ffff  CALL 0x0041ac50
0041cb8d  c6431400  MOV byte ptr [EBX + 0x14],0x0
0041cb91  33c0  XOR EAX,EAX
0041cb93  5a  POP EDX
0041cb94  59  POP ECX
0041cb95  59  POP ECX
0041cb96  648910  MOV dword ptr FS:[EAX],EDX
0041cb99  68b1cb4100  PUSH 0x41cbb1
0041cb9e  8b55f8  MOV EDX,dword ptr [EBP + -0x8]
0041cba1  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0041cba4  e8bf5afeff  CALL 0x00402668
0041cba9  c3  RET
