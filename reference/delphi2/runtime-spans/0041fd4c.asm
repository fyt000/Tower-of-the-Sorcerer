; MakeObjectInstance; compiler-assisted focused span, not a new Ghidra ownership claim
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0041fd4c  55  PUSH ebp
0041fd4d  8bec  MOV ebp, esp
0041fd4f  53  PUSH ebx
0041fd50  56  PUSH esi
0041fd51  57  PUSH edi
0041fd52  bf20a74800  MOV edi, 0x48a720
0041fd57  833f00  CMP dword ptr [edi], 0
0041fd5a  756c  JNE 0x41fdc8
0041fd5c  6a40  PUSH 0x40
0041fd5e  6800100000  PUSH 0x1000
0041fd63  6800100000  PUSH 0x1000
0041fd68  6a00  PUSH 0
0041fd6a  e8d54efeff  CALL 0x404c44
0041fd6f  8bf0  MOV esi, eax
0041fd71  a11ca74800  MOV eax, dword ptr [0x48a71c]
0041fd76  8906  MOV dword ptr [esi], eax
0041fd78  8d5604  LEA edx, [esi + 4]
0041fd7b  b8a0954800  MOV eax, 0x4895a0
0041fd80  b902000000  MOV ecx, 2
0041fd85  e8e62afeff  CALL 0x402870
0041fd8a  ba24fd4100  MOV edx, 0x41fd24
0041fd8f  8d4605  LEA eax, [esi + 5]
0041fd92  e8adffffff  CALL 0x41fd44
0041fd97  894606  MOV dword ptr [esi + 6], eax
0041fd9a  8d5e0a  LEA ebx, [esi + 0xa]
0041fd9d  c603e8  MOV byte ptr [ebx], 0xe8
0041fda0  8d5604  LEA edx, [esi + 4]
0041fda3  8bc3  MOV eax, ebx
0041fda5  e89affffff  CALL 0x41fd44
0041fdaa  894301  MOV dword ptr [ebx + 1], eax
0041fdad  8b07  MOV eax, dword ptr [edi]
0041fdaf  894305  MOV dword ptr [ebx + 5], eax
0041fdb2  891f  MOV dword ptr [edi], ebx
0041fdb4  83c30d  ADD ebx, 0xd
0041fdb7  8bc3  MOV eax, ebx
0041fdb9  2bc6  SUB eax, esi
0041fdbb  3dfc0f0000  CMP eax, 0xffc
0041fdc0  7cdb  JL 0x41fd9d
0041fdc2  89351ca74800  MOV dword ptr [0x48a71c], esi
0041fdc8  8b07  MOV eax, dword ptr [edi]
0041fdca  8b1f  MOV ebx, dword ptr [edi]
0041fdcc  8b5305  MOV edx, dword ptr [ebx + 5]
0041fdcf  8917  MOV dword ptr [edi], edx
0041fdd1  8b5508  MOV edx, dword ptr [ebp + 8]
0041fdd4  895305  MOV dword ptr [ebx + 5], edx
0041fdd7  8b550c  MOV edx, dword ptr [ebp + 0xc]
0041fdda  895309  MOV dword ptr [ebx + 9], edx
0041fddd  5f  POP edi
0041fdde  5e  POP esi
0041fddf  5b  POP ebx
0041fde0  5d  POP ebp
0041fde1  c20800  RET 8
