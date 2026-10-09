; root_0040ada0 at 0x0040ada0
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040ada0  53  PUSH EBX
0040ada1  56  PUSH ESI
0040ada2  57  PUSH EDI
0040ada3  8bf9  MOV EDI,ECX
0040ada5  8bf2  MOV ESI,EDX
0040ada7  8bd8  MOV EBX,EAX
0040ada9  85f6  TEST ESI,ESI
0040adab  7c05  JL 0x0040adb2
0040adad  3b730c  CMP ESI,dword ptr [EBX + 0xc]
0040adb0  7c05  JL 0x0040adb7
0040adb2  e8c1ebffff  CALL 0x00409978
0040adb7  8bc3  MOV EAX,EBX
0040adb9  8b10  MOV EDX,dword ptr [EAX]
0040adbb  ff526c  CALL dword ptr [EDX + 0x6c]
0040adbe  8b4308  MOV EAX,dword ptr [EBX + 0x8]
0040adc1  897cf004  MOV dword ptr [EAX + ESI*0x8 + 0x4],EDI
0040adc5  8bc3  MOV EAX,EBX
0040adc7  8b10  MOV EDX,dword ptr [EAX]
0040adc9  ff5268  CALL dword ptr [EDX + 0x68]
0040adcc  5f  POP EDI
0040adcd  5e  POP ESI
0040adce  5b  POP EBX
0040adcf  c3  RET
