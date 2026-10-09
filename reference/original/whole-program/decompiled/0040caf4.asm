; FUN_0040caf4 at 0x0040caf4
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040caf4  55  PUSH EBP
0040caf5  8bec  MOV EBP,ESP
0040caf7  83c4e4  ADD ESP,-0x1c
0040cafa  53  PUSH EBX
0040cafb  56  PUSH ESI
0040cafc  57  PUSH EDI
0040cafd  33c9  XOR ECX,ECX
0040caff  894de8  MOV dword ptr [EBP + -0x18],ECX
0040cb02  894de4  MOV dword ptr [EBP + -0x1c],ECX
0040cb05  8955f8  MOV dword ptr [EBP + -0x8],EDX
0040cb08  8945fc  MOV dword ptr [EBP + -0x4],EAX
0040cb0b  33c0  XOR EAX,EAX
0040cb0d  55  PUSH EBP
0040cb0e  6807cd4000  PUSH 0x40cd07
0040cb13  64ff30  PUSH dword ptr FS:[EAX]
0040cb16  648920  MOV dword ptr FS:[EAX],ESP
0040cb19  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cb1c  e8af020000  CALL 0x0040cdd0
0040cb21  33c0  XOR EAX,EAX
0040cb23  8945f4  MOV dword ptr [EBP + -0xc],EAX
0040cb26  33c0  XOR EAX,EAX
0040cb28  55  PUSH EBP
0040cb29  68c5cc4000  PUSH 0x40ccc5
0040cb2e  64ff30  PUSH dword ptr FS:[EAX]
0040cb31  648920  MOV dword ptr FS:[EAX],ESP
0040cb34  8d4df0  LEA ECX,[EBP + -0x10]
0040cb37  8d55ef  LEA EDX,[EBP + -0x11]
0040cb3a  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cb3d  e89af8ffff  CALL 0x0040c3dc
0040cb42  837df800  CMP dword ptr [EBP + -0x8],0x0
0040cb46  7535  JNZ 0x0040cb7d
0040cb48  8d55e8  LEA EDX,[EBP + -0x18]
0040cb4b  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cb4e  e8a1020000  CALL 0x0040cdf4
0040cb53  8b45e8  MOV EAX,dword ptr [EBP + -0x18]
0040cb56  e8f5c7ffff  CALL 0x00409350
0040cb5b  33c9  XOR ECX,ECX
0040cb5d  b201  MOV DL,0x1
0040cb5f  ff5024  CALL dword ptr [EAX + 0x24]
0040cb62  8945f4  MOV dword ptr [EBP + -0xc],EAX
0040cb65  8d55e8  LEA EDX,[EBP + -0x18]
0040cb68  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cb6b  e884020000  CALL 0x0040cdf4
0040cb70  8b55e8  MOV EDX,dword ptr [EBP + -0x18]
0040cb73  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0040cb76  8b08  MOV ECX,dword ptr [EAX]
0040cb78  ff5118  CALL dword ptr [ECX + 0x18]
0040cb7b  eb48  JMP 0x0040cbc5
0040cb7d  8b45f8  MOV EAX,dword ptr [EBP + -0x8]
0040cb80  8945f4  MOV dword ptr [EBP + -0xc],EAX
0040cb83  8d55e8  LEA EDX,[EBP + -0x18]
0040cb86  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cb89  e866020000  CALL 0x0040cdf4
0040cb8e  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0040cb91  f6401c10  TEST byte ptr [EAX + 0x1c],0x10
0040cb95  740d  JZ 0x0040cba4
0040cb97  8d55e8  LEA EDX,[EBP + -0x18]
0040cb9a  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cb9d  e852020000  CALL 0x0040cdf4
0040cba2  eb21  JMP 0x0040cbc5
0040cba4  8d55e4  LEA EDX,[EBP + -0x1c]
0040cba7  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cbaa  e845020000  CALL 0x0040cdf4
0040cbaf  8b45e4  MOV EAX,dword ptr [EBP + -0x1c]
0040cbb2  8d55e8  LEA EDX,[EBP + -0x18]
0040cbb5  e8cafeffff  CALL 0x0040ca84
0040cbba  8b55e8  MOV EDX,dword ptr [EBP + -0x18]
0040cbbd  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0040cbc0  8b08  MOV ECX,dword ptr [EAX]
0040cbc2  ff5118  CALL dword ptr [ECX + 0x18]
0040cbc5  8b45f4  MOV EAX,dword ptr [EBP + -0xc]
0040cbc8  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040cbcb  894218  MOV dword ptr [EDX + 0x18],EAX
0040cbce  833d14a6480000  CMP dword ptr [0x0048a614],0x0
0040cbd5  740d  JZ 0x0040cbe4
0040cbd7  a114a64800  MOV EAX,[0x0048a614]
0040cbdc  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040cbdf  894230  MOV dword ptr [EDX + 0x30],EAX
0040cbe2  eb12  JMP 0x0040cbf6
0040cbe4  b201  MOV DL,0x1
0040cbe6  b8c88a4000  MOV EAX,0x408ac8
0040cbeb  e81c60ffff  CALL 0x00402c0c
0040cbf0  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040cbf3  894230  MOV dword ptr [EDX + 0x30],EAX
0040cbf6  33c0  XOR EAX,EAX
0040cbf8  55  PUSH EBP
0040cbf9  68afcc4000  PUSH 0x40ccaf
0040cbfe  64ff30  PUSH dword ptr FS:[EAX]
0040cc01  648920  MOV dword ptr FS:[EAX],ESP
0040cc04  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cc07  8b5018  MOV EDX,dword ptr [EAX + 0x18]
0040cc0a  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cc0d  8b4030  MOV EAX,dword ptr [EAX + 0x30]
0040cc10  e88fcdffff  CALL 0x004099a4
0040cc15  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cc18  8b4018  MOV EAX,dword ptr [EAX + 0x18]
0040cc1b  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040cc1e  894224  MOV dword ptr [EDX + 0x24],EAX
0040cc21  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cc24  8b4018  MOV EAX,dword ptr [EAX + 0x18]
0040cc27  80481c01  OR byte ptr [EAX + 0x1c],0x1
0040cc2b  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cc2e  8b4018  MOV EAX,dword ptr [EAX + 0x18]
0040cc31  80481c02  OR byte ptr [EAX + 0x1c],0x2
0040cc35  8b55fc  MOV EDX,dword ptr [EBP + -0x4]
0040cc38  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cc3b  8b4018  MOV EAX,dword ptr [EAX + 0x18]
0040cc3e  8b08  MOV ECX,dword ptr [EAX]
0040cc40  ff5114  CALL dword ptr [ECX + 0x14]
0040cc43  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cc46  8b4018  MOV EAX,dword ptr [EAX + 0x18]
0040cc49  80601cfd  AND byte ptr [EAX + 0x1c],0xfd
0040cc4d  833d14a6480000  CMP dword ptr [0x0048a614],0x0
0040cc54  752f  JNZ 0x0040cc85
0040cc56  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cc59  8b4030  MOV EAX,dword ptr [EAX + 0x30]
0040cc5c  8b5808  MOV EBX,dword ptr [EAX + 0x8]
0040cc5f  4b  DEC EBX
0040cc60  85db  TEST EBX,EBX
0040cc62  7c21  JL 0x0040cc85
0040cc64  43  INC EBX
0040cc65  c745f000000000  MOV dword ptr [EBP + -0x10],0x0
0040cc6c  8b55f0  MOV EDX,dword ptr [EBP + -0x10]
0040cc6f  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cc72  8b4030  MOV EAX,dword ptr [EAX + 0x30]
0040cc75  e8c6cdffff  CALL 0x00409a40
0040cc7a  8b10  MOV EDX,dword ptr [EAX]
0040cc7c  ff520c  CALL dword ptr [EDX + 0xc]
0040cc7f  ff45f0  INC dword ptr [EBP + -0x10]
0040cc82  4b  DEC EBX
0040cc83  75e7  JNZ 0x0040cc6c
0040cc85  33c0  XOR EAX,EAX
0040cc87  5a  POP EDX
0040cc88  59  POP ECX
0040cc89  59  POP ECX
0040cc8a  648910  MOV dword ptr FS:[EAX],EDX
0040cc8d  68b6cc4000  PUSH 0x40ccb6
0040cc92  833d14a6480000  CMP dword ptr [0x0048a614],0x0
0040cc99  750b  JNZ 0x0040cca6
0040cc9b  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cc9e  8b4030  MOV EAX,dword ptr [EAX + 0x30]
0040cca1  e88e5fffff  CALL 0x00402c34
0040cca6  8b45fc  MOV EAX,dword ptr [EBP + -0x4]
0040cca9  33d2  XOR EDX,EDX
0040ccab  895030  MOV dword ptr [EAX + 0x30],EDX
0040ccae  c3  RET
