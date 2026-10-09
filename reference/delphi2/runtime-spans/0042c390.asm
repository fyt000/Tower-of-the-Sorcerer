; TTimer.WndProc; compiler-assisted focused span, not a new Ghidra ownership claim
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0042c390  55  PUSH ebp
0042c391  8bec  MOV ebp, esp
0042c393  51  PUSH ecx
0042c394  53  PUSH ebx
0042c395  56  PUSH esi
0042c396  57  PUSH edi
0042c397  8bda  MOV ebx, edx
0042c399  8945fc  MOV dword ptr [ebp - 4], eax
0042c39c  8b33  MOV esi, dword ptr [ebx]
0042c39e  81fe13010000  CMP esi, 0x113
0042c3a4  753d  JNE 0x42c3e3
0042c3a6  33c0  XOR eax, eax
0042c3a8  55  PUSH ebp
0042c3a9  68cac34200  PUSH 0x42c3ca
0042c3ae  64ff30  PUSH dword ptr fs:[eax]
0042c3b1  648920  MOV dword ptr fs:[eax], esp
0042c3b4  8b45fc  MOV eax, dword ptr [ebp - 4]
0042c3b7  66bbf6ff  MOV bx, 0xfff6
0042c3bb  e81c69fdff  CALL 0x402cdc
0042c3c0  33c0  XOR eax, eax
0042c3c2  5a  POP edx
0042c3c3  59  POP ecx
0042c3c4  59  POP ecx
0042c3c5  648910  MOV dword ptr fs:[eax], edx
0042c3c8  eb31  JMP 0x42c3fb
0042c3ca  e97d6bfdff  JMP 0x402f4c
0042c3cf  8b55fc  MOV edx, dword ptr [ebp - 4]
0042c3d2  a1f8a64800  MOV eax, dword ptr [0x48a6f8]
0042c3d7  e8448cffff  CALL 0x425020
0042c3dc  e8876efdff  CALL 0x403268
0042c3e1  eb18  JMP 0x42c3fb
0042c3e3  8b4308  MOV eax, dword ptr [ebx + 8]
0042c3e6  50  PUSH eax
0042c3e7  8b4304  MOV eax, dword ptr [ebx + 4]
0042c3ea  50  PUSH eax
0042c3eb  56  PUSH esi
0042c3ec  8b45fc  MOV eax, dword ptr [ebp - 4]
0042c3ef  8b4028  MOV eax, dword ptr [eax + 0x28]
0042c3f2  50  PUSH eax
0042c3f3  e8bc8afdff  CALL 0x404eb4
0042c3f8  89430c  MOV dword ptr [ebx + 0xc], eax
0042c3fb  5f  POP edi
0042c3fc  5e  POP esi
0042c3fd  5b  POP ebx
0042c3fe  59  POP ecx
0042c3ff  5d  POP ebp
0042c400  c3  RET
