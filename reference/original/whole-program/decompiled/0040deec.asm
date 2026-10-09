; FUN_0040deec at 0x0040deec
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0040deec  55  PUSH EBP
0040deed  8bec  MOV EBP,ESP
0040deef  53  PUSH EBX
0040def0  33db  XOR EBX,EBX
0040def2  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040def5  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040def8  50  PUSH EAX
0040def9  e8aefaffff  CALL 0x0040d9ac
0040defe  59  POP ECX
0040deff  84c0  TEST AL,AL
0040df01  746c  JZ 0x0040df6f
0040df03  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040df06  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040df09  8b50f4  MOV EDX,dword ptr [EAX + -0xc]
0040df0c  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040df0f  8b4008  MOV EAX,dword ptr [EAX + 0x8]
0040df12  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040df15  8b401c  MOV EAX,dword ptr [EAX + 0x1c]
0040df18  e8ffa3ffff  CALL 0x0040831c
0040df1d  8bd8  MOV EBX,EAX
0040df1f  85db  TEST EBX,EBX
0040df21  744c  JZ 0x0040df6f
0040df23  8b4304  MOV EAX,dword ptr [EBX + 0x4]
0040df26  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0040df29  8b5208  MOV EDX,dword ptr [EDX + 0x8]
0040df2c  8b52fc  MOV EDX,dword ptr [EDX + -0x4]
0040df2f  3b4224  CMP EAX,dword ptr [EDX + 0x24]
0040df32  753b  JNZ 0x0040df6f
0040df34  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040df37  8378fc00  CMP dword ptr [EAX + -0x4],0x0
0040df3b  7432  JZ 0x0040df6f
0040df3d  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040df40  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040df43  8b4004  MOV EAX,dword ptr [EAX + 0x4]
0040df46  8b5508  MOV EDX,dword ptr [EBP + 0x8]
0040df49  8b5208  MOV EDX,dword ptr [EDX + 0x8]
0040df4c  8b52fc  MOV EDX,dword ptr [EDX + -0x4]
0040df4f  3b4218  CMP EAX,dword ptr [EDX + 0x18]
0040df52  751b  JNZ 0x0040df6f
0040df54  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040df57  8b40fc  MOV EAX,dword ptr [EAX + -0x4]
0040df5a  8b5008  MOV EDX,dword ptr [EAX + 0x8]
0040df5d  8b4308  MOV EAX,dword ptr [EBX + 0x8]
0040df60  e8cf7affff  CALL 0x00405a34
0040df65  85c0  TEST EAX,EAX
0040df67  7506  JNZ 0x0040df6f
0040df69  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040df6c  8b58fc  MOV EBX,dword ptr [EAX + -0x4]
0040df6f  8b4508  MOV EAX,dword ptr [EBP + 0x8]
0040df72  3b58fc  CMP EBX,dword ptr [EAX + -0x4]
0040df75  0f94c0  SETZ AL
0040df78  5b  POP EBX
0040df79  5d  POP EBP
0040df7a  c3  RET
