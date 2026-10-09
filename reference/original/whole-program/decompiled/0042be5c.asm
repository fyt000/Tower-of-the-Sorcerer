; FUN_0042be5c at 0x0042be5c
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0042be5c  55  PUSH EBP
0042be5d  8bec  MOV EBP,ESP
0042be5f  83c4d8  ADD ESP,-0x28
0042be62  53  PUSH EBX
0042be63  8b5d08  MOV EBX,dword ptr [EBP + 0x8]
0042be66  8b5bfc  MOV EBX,dword ptr [EBX + -0x4]
0042be69  8b4308  MOV EAX,dword ptr [EBX + 0x8]
0042be6c  8945f8  MOV dword ptr [EBP + -0x8],EAX
0042be6f  8b4304  MOV EAX,dword ptr [EBX + 0x4]
0042be72  8945fc  MOV dword ptr [EBP + -0x4],EAX
0042be75  8b03  MOV EAX,dword ptr [EBX]
0042be77  8945f0  MOV dword ptr [EBP + -0x10],EAX
0042be7a  8b430c  MOV EAX,dword ptr [EBX + 0xc]
0042be7d  8945f4  MOV dword ptr [EBP + -0xc],EAX
0042be80  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0042be83  8b50f4  MOV EDX,dword ptr [EAX + -0xc]
0042be86  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0042be89  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0042be8c  8b4010  MOV EAX,dword ptr [EAX + 0x10]
0042be8f  e814e1feff  CALL 0x00419fa8
0042be94  8b45f0  MOV EAX,dword ptr [EBP + -0x10]
0042be97  8945d8  MOV dword ptr [EBP + -0x28],EAX
0042be9a  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0042be9d  8945dc  MOV dword ptr [EBP + -0x24],EAX
0042bea0  8b03  MOV EAX,dword ptr [EBX]
0042bea2  8945e0  MOV dword ptr [EBP + -0x20],EAX
0042bea5  8b4304  MOV EAX,dword ptr [EBX + 0x4]
0042bea8  8945e4  MOV dword ptr [EBP + -0x1c],EAX
0042beab  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0042beae  8945e8  MOV dword ptr [EBP + -0x18],EAX
0042beb1  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0042beb4  8945ec  MOV dword ptr [EBP + -0x14],EAX
0042beb7  8d55d8  LEA EDX,[EBP + -0x28]
0042beba  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0042bebd  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0042bec0  b902000000  MOV ECX,0x2
0042bec5  e83ae8feff  CALL 0x0041a704
0042beca  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0042becd  8b500c  MOV EDX,dword ptr [EAX + 0xc]
0042bed0  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0042bed3  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0042bed6  8b4010  MOV EAX,dword ptr [EAX + 0x10]
0042bed9  e8cae0feff  CALL 0x00419fa8
0042bede  ff4df0  DEC dword ptr [EBP + -0x10]
0042bee1  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0042bee4  8945d8  MOV dword ptr [EBP + -0x28],EAX
0042bee7  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0042beea  8945dc  MOV dword ptr [EBP + -0x24],EAX
0042beed  8b4308  MOV EAX,dword ptr [EBX + 0x8]
0042bef0  8945e0  MOV dword ptr [EBP + -0x20],EAX
0042bef3  8b430c  MOV EAX,dword ptr [EBX + 0xc]
0042bef6  8945e4  MOV dword ptr [EBP + -0x1c],EAX
0042bef9  8b45f0  MOV EAX,dword ptr [EBP + -0x10]
0042befc  8945e8  MOV dword ptr [EBP + -0x18],EAX
0042beff  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0042bf02  8945ec  MOV dword ptr [EBP + -0x14],EAX
0042bf05  8d55d8  LEA EDX,[EBP + -0x28]
0042bf08  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0042bf0b  8b40f8  MOV EAX,dword ptr [EAX + -0x8]
0042bf0e  b902000000  MOV ECX,0x2
0042bf13  e8ece7feff  CALL 0x0041a704
0042bf18  5b  POP EBX
0042bf19  8be5  MOV ESP,EBP
0042bf1b  5d  POP EBP
0042bf1c  c3  RET
