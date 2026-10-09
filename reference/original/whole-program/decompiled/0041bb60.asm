; FUN_0041bb60 at 0x0041bb60
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041bb60  55  PUSH EBP
0041bb61  8bec  MOV EBP,ESP
0041bb63  83c4ac  ADD ESP,-0x54
0041bb66  53  PUSH EBX
0041bb67  56  PUSH ESI
0041bb68  57  PUSH EDI
0041bb69  884dff  MOV byte ptr [EBP + -0x1],CL
0041bb6c  8bf2  MOV ESI,EDX
0041bb6e  8bd8  MOV EBX,EAX
0041bb70  8d45d6  LEA EAX,[EBP + -0x2a]
0041bb73  33c9  XOR ECX,ECX
0041bb75  ba06000000  MOV EDX,0x6
0041bb7a  e8396efeff  CALL 0x004029b8
0041bb7f  8d45ac  LEA EAX,[EBP + -0x54]
0041bb82  33c9  XOR ECX,ECX
0041bb84  ba10000000  MOV EDX,0x10
0041bb89  e82a6efeff  CALL 0x004029b8
0041bb8e  8d45bc  LEA EAX,[EBP + -0x44]
0041bb91  50  PUSH EAX
0041bb92  56  PUSH ESI
0041bb93  e82494feff  CALL 0x00404fbc
0041bb98  e8b7ffffff  CALL 0x0041bb54
0041bb9d  33d2  XOR EDX,EDX
0041bb9f  55  PUSH EBP
0041bba0  684ebd4100  PUSH 0x41bd4e
0041bba5  64ff32  PUSH dword ptr FS:[EDX]
0041bba8  648922  MOV dword ptr FS:[EDX],ESP
0041bbab  6a02  PUSH 0x2
0041bbad  8d4df0  LEA ECX,[EBP + -0x10]
0041bbb0  8d55f8  LEA EDX,[EBP + -0x8]
0041bbb3  8b45c8  MOV EAX,dword ptr [EBP + -0x38]
0041bbb6  e821feffff  CALL 0x0041b9dc
0041bbbb  6a10  PUSH 0x10
0041bbbd  8d4dec  LEA ECX,[EBP + -0x14]
0041bbc0  8d55f4  LEA EDX,[EBP + -0xc]
0041bbc3  8b45cc  MOV EAX,dword ptr [EBP + -0x34]
0041bbc6  e811feffff  CALL 0x0041b9dc
0041bbcb  33c0  XOR EAX,EAX
0041bbcd  8945e8  MOV dword ptr [EBP + -0x18],EAX
0041bbd0  33c0  XOR EAX,EAX
0041bbd2  8945e4  MOV dword ptr [EBP + -0x1c],EAX
0041bbd5  33c0  XOR EAX,EAX
0041bbd7  8945e0  MOV dword ptr [EBP + -0x20],EAX
0041bbda  33c0  XOR EAX,EAX
0041bbdc  8945dc  MOV dword ptr [EBP + -0x24],EAX
0041bbdf  33d2  XOR EDX,EDX
0041bbe1  55  PUSH EBP
0041bbe2  6827bd4100  PUSH 0x41bd27
0041bbe7  64ff32  PUSH dword ptr FS:[EDX]
0041bbea  648922  MOV dword ptr FS:[EDX],ESP
0041bbed  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0041bbf0  e85b9dfeff  CALL 0x00405950
0041bbf5  8945e8  MOV dword ptr [EBP + -0x18],EAX
0041bbf8  8b45f0  MOV EAX,dword ptr [EBP + -0x10]
0041bbfb  e8509dfeff  CALL 0x00405950
0041bc00  8945e4  MOV dword ptr [EBP + -0x1c],EAX
0041bc03  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0041bc06  e8459dfeff  CALL 0x00405950
0041bc0b  8945e0  MOV dword ptr [EBP + -0x20],EAX
0041bc0e  8b45ec  MOV EAX,dword ptr [EBP + -0x14]
0041bc11  e83a9dfeff  CALL 0x00405950
0041bc16  8945dc  MOV dword ptr [EBP + -0x24],EAX
0041bc19  8b45e4  MOV EAX,dword ptr [EBP + -0x1c]
0041bc1c  50  PUSH EAX
0041bc1d  6a02  PUSH 0x2
0041bc1f  8b4de8  MOV ECX,dword ptr [EBP + -0x18]
0041bc22  33d2  XOR EDX,EDX
0041bc24  8b45c8  MOV EAX,dword ptr [EBP + -0x38]
0041bc27  e8fcfdffff  CALL 0x0041ba28
0041bc2c  8b45dc  MOV EAX,dword ptr [EBP + -0x24]
0041bc2f  50  PUSH EAX
0041bc30  6a10  PUSH 0x10
0041bc32  8b4de0  MOV ECX,dword ptr [EBP + -0x20]
0041bc35  33d2  XOR EDX,EDX
0041bc37  8b45cc  MOV EAX,dword ptr [EBP + -0x34]
0041bc3a  e8e9fdffff  CALL 0x0041ba28
0041bc3f  807dff00  CMP byte ptr [EBP + -0x1],0x0
0041bc43  741e  JZ 0x0041bc63
0041bc45  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0041bc48  83c016  ADD EAX,0x16
0041bc4b  0345ec  ADD EAX,dword ptr [EBP + -0x14]
0041bc4e  0345f0  ADD EAX,dword ptr [EBP + -0x10]
0041bc51  8945d0  MOV dword ptr [EBP + -0x30],EAX
0041bc54  8d55d0  LEA EDX,[EBP + -0x30]
0041bc57  b904000000  MOV ECX,0x4
0041bc5c  8bc3  MOV EAX,EBX
0041bc5e  8b30  MOV ESI,dword ptr [EAX]
0041bc60  ff5604  CALL dword ptr [ESI + 0x4]
0041bc63  66c745d80100  MOV word ptr [EBP + -0x28],0x1
0041bc69  66c745da0100  MOV word ptr [EBP + -0x26],0x1
0041bc6f  8d55d6  LEA EDX,[EBP + -0x2a]
0041bc72  b906000000  MOV ECX,0x6
0041bc77  8bc3  MOV EAX,EBX
0041bc79  8b30  MOV ESI,dword ptr [EAX]
0041bc7b  ff5604  CALL dword ptr [ESI + 0x4]
0041bc7e  8b75e0  MOV ESI,dword ptr [EBP + -0x20]
0041bc81  8bc6  MOV EAX,ESI
0041bc83  8a5004  MOV DL,byte ptr [EAX + 0x4]
0041bc86  8855ac  MOV byte ptr [EBP + -0x54],DL
0041bc89  8a5008  MOV DL,byte ptr [EAX + 0x8]
0041bc8c  8855ad  MOV byte ptr [EBP + -0x53],DL
0041bc8f  668b500c  MOV DX,word ptr [EAX + 0xc]
0041bc93  660faf500e  IMUL DX,word ptr [EAX + 0xe]
0041bc98  668955ae  MOV word ptr [EBP + -0x52],DX
0041bc9c  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0041bc9f  0345ec  ADD EAX,dword ptr [EBP + -0x14]
0041bca2  0345f0  ADD EAX,dword ptr [EBP + -0x10]
0041bca5  8945b4  MOV dword ptr [EBP + -0x4c],EAX
0041bca8  c745b816000000  MOV dword ptr [EBP + -0x48],0x16
0041bcaf  8d55ac  LEA EDX,[EBP + -0x54]
0041bcb2  b910000000  MOV ECX,0x10
0041bcb7  8bc3  MOV EAX,EBX
0041bcb9  8b38  MOV EDI,dword ptr [EAX]
0041bcbb  ff5704  CALL dword ptr [EDI + 0x4]
0041bcbe  8bc6  MOV EAX,ESI
0041bcc0  8b5008  MOV EDX,dword ptr [EAX + 0x8]
0041bcc3  015008  ADD dword ptr [EAX + 0x8],EDX
0041bcc6  8b55e0  MOV EDX,dword ptr [EBP + -0x20]
0041bcc9  8b4df4  MOV ECX,dword ptr [EBP + -0xc]
0041bccc  8bc3  MOV EAX,EBX
0041bcce  8b30  MOV ESI,dword ptr [EAX]
0041bcd0  ff5604  CALL dword ptr [ESI + 0x4]
0041bcd3  8b55dc  MOV EDX,dword ptr [EBP + -0x24]
0041bcd6  8b4dec  MOV ECX,dword ptr [EBP + -0x14]
0041bcd9  8bc3  MOV EAX,EBX
0041bcdb  8b30  MOV ESI,dword ptr [EAX]
0041bcdd  ff5604  CALL dword ptr [ESI + 0x4]
0041bce0  8b55e4  MOV EDX,dword ptr [EBP + -0x1c]
0041bce3  8b4df0  MOV ECX,dword ptr [EBP + -0x10]
0041bce6  8bc3  MOV EAX,EBX
0041bce8  8b18  MOV EBX,dword ptr [EAX]
0041bcea  ff5304  CALL dword ptr [EBX + 0x4]
0041bced  33c0  XOR EAX,EAX
0041bcef  5a  POP EDX
0041bcf0  59  POP ECX
0041bcf1  59  POP ECX
0041bcf2  648910  MOV dword ptr FS:[EAX],EDX
0041bcf5  682ebd4100  PUSH 0x41bd2e
0041bcfa  8b55f4  MOV EDX,dword ptr [EBP + -0xc]
0041bcfd  8b45e0  MOV EAX,dword ptr [EBP + -0x20]
0041bd00  e86369feff  CALL 0x00402668
0041bd05  8b55ec  MOV EDX,dword ptr [EBP + -0x14]
0041bd08  8b45dc  MOV EAX,dword ptr [EBP + -0x24]
0041bd0b  e85869feff  CALL 0x00402668
0041bd10  8b55f8  MOV EDX,dword ptr [EBP + -0x8]
0041bd13  8b45e8  MOV EAX,dword ptr [EBP + -0x18]
0041bd16  e84d69feff  CALL 0x00402668
0041bd1b  8b55f0  MOV EDX,dword ptr [EBP + -0x10]
0041bd1e  8b45e4  MOV EAX,dword ptr [EBP + -0x1c]
0041bd21  e84269feff  CALL 0x00402668
0041bd26  c3  RET
