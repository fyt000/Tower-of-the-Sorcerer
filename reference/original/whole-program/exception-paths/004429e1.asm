; Exception continuation for TTSW10.formactivate; handler 0x004429e1
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
; Bounded direct CFG; calls are retained, not inlined; unresolved exits are in inventory.json.
004429e6  8b45fc  MOV eax, dword ptr [ebp - 4]
004429e9  8b8044040000  MOV eax, dword ptr [eax + 0x444]
004429ef  8b8018010000  MOV eax, dword ptr [eax + 0x118]
004429f5  8b10  MOV edx, dword ptr [eax]
004429f7  ff5238  CALL dword ptr [edx + 0x38]
004429fa  8d45f8  LEA eax, [ebp - 8]
004429fd  e86636fcff  CALL 0x406068
00442a02  8b55f8  MOV edx, dword ptr [ebp - 8]
00442a05  b8e0c54800  MOV eax, 0x48c5e0
00442a0a  e81d0bfcff  CALL 0x40352c
00442a0f  b8dcc54800  MOV eax, 0x48c5dc
00442a14  b9182c4400  MOV ecx, 0x442c18
00442a19  8b15e0c54800  MOV edx, dword ptr [0x48c5e0]
00442a1f  e8780cfcff  CALL 0x40369c
00442a24  c605efc5480000  MOV byte ptr [0x48c5ef], 0
00442a2b  8b45fc  MOV eax, dword ptr [ebp - 4]
00442a2e  8b8044040000  MOV eax, dword ptr [eax + 0x444]
00442a34  8b8018010000  MOV eax, dword ptr [eax + 0x118]
00442a3a  8b15dcc54800  MOV edx, dword ptr [0x48c5dc]
00442a40  8b08  MOV ecx, dword ptr [eax]
00442a42  ff512c  CALL dword ptr [ecx + 0x2c]
00442a45  8b45fc  MOV eax, dword ptr [ebp - 4]
00442a48  8b8044040000  MOV eax, dword ptr [eax + 0x444]
00442a4e  8b8018010000  MOV eax, dword ptr [eax + 0x118]
00442a54  8b15e0c54800  MOV edx, dword ptr [0x48c5e0]
00442a5a  8b08  MOV ecx, dword ptr [eax]
00442a5c  ff512c  CALL dword ptr [ecx + 0x2c]
00442a5f  8d45f8  LEA eax, [ebp - 8]
00442a62  baefc54800  MOV edx, 0x48c5ef
00442a67  e8900bfcff  CALL 0x4035fc
00442a6c  8b55f8  MOV edx, dword ptr [ebp - 8]
00442a6f  8b45fc  MOV eax, dword ptr [ebp - 4]
00442a72  8b8044040000  MOV eax, dword ptr [eax + 0x444]
00442a78  8b8018010000  MOV eax, dword ptr [eax + 0x118]
00442a7e  8b08  MOV ecx, dword ptr [eax]
00442a80  ff512c  CALL dword ptr [ecx + 0x2c]
00442a83  8b45fc  MOV eax, dword ptr [ebp - 4]
00442a86  8b8044040000  MOV eax, dword ptr [eax + 0x444]
00442a8c  8b8018010000  MOV eax, dword ptr [eax + 0x118]
00442a92  8b15d4c54800  MOV edx, dword ptr [0x48c5d4]
00442a98  8b08  MOV ecx, dword ptr [eax]
00442a9a  ff515c  CALL dword ptr [ecx + 0x5c]
00442a9d  e8c607fcff  CALL 0x403268
