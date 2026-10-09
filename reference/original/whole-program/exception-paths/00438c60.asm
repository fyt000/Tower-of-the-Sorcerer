; Exception continuation for TForm2.scoreload; handler 0x00438c60
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
; Bounded direct CFG; calls are retained, not inlined; unresolved exits are in inventory.json.
00438c65  b82c9c4300  MOV eax, 0x439c2c
00438c6a  e80943ffff  CALL 0x42cf78
00438c6f  33c0  XOR eax, eax
00438c71  8a45fb  MOV al, byte ptr [ebp - 5]
00438c74  83f805  CMP eax, 5
00438c77  0f87ee090000  JA 0x43966b
00438c7d  ff2485848c4300  JMP dword ptr [eax*4 + 0x438c84]
0043966b  e8f89bfcff  CALL 0x403268
