; toroad2 at 0x0044bc34
; Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
0044bc34  53  PUSH EBX
0044bc35  56  PUSH ESI
0044bc36  57  PUSH EDI
0044bc37  55  PUSH EBP
0044bc38  bbacc54800  MOV EBX,0x48c5ac
0044bc3d  be4cc74800  MOV ESI,0x48c74c
0044bc42  e8c5ffffff  CALL 0x0044bc0c
0044bc47  ff03  INC dword ptr [EBX]
0044bc49  8b13  MOV EDX,dword ptr [EBX]
0044bc4b  8d1452  LEA EDX,[EDX + EDX*0x2]
0044bc4e  66c704561100  MOV word ptr [ESI + EDX*0x2],0x11
0044bc54  66a184c54800  MOV AX,[0x0048c584]
0044bc5a  6689445602  MOV word ptr [ESI + EDX*0x2 + 0x2],AX
0044bc5f  66c74456040600  MOV word ptr [ESI + EDX*0x2 + 0x4],0x6
0044bc66  ff03  INC dword ptr [EBX]
0044bc68  8b0b  MOV ECX,dword ptr [EBX]
0044bc6a  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bc6d  66c7044e0000  MOV word ptr [ESI + ECX*0x2],0x0
0044bc73  6b1598864b007b  IMUL EDX,dword ptr [0x004b8698],0x7b
0044bc7a  81c234894b00  ADD EDX,0x4b8934
0044bc80  8b3d84c54800  MOV EDI,dword ptr [0x0048c584]
0044bc86  0fb6543a02  MOVZX EDX,byte ptr [EDX + EDI*0x1 + 0x2]
0044bc8b  6689544e02  MOV word ptr [ESI + ECX*0x2 + 0x2],DX
0044bc90  66c7444e040600  MOV word ptr [ESI + ECX*0x2 + 0x4],0x6
0044bc97  ff03  INC dword ptr [EBX]
0044bc99  8b0b  MOV ECX,dword ptr [EBX]
0044bc9b  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bc9e  66c7044e0900  MOV word ptr [ESI + ECX*0x2],0x9
0044bca4  6689444e02  MOV word ptr [ESI + ECX*0x2 + 0x2],AX
0044bca9  66c7444e04b600  MOV word ptr [ESI + ECX*0x2 + 0x4],0xb6
0044bcb0  ff03  INC dword ptr [EBX]
0044bcb2  8b0b  MOV ECX,dword ptr [EBX]
0044bcb4  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bcb7  66c7044e0000  MOV word ptr [ESI + ECX*0x2],0x0
0044bcbd  66c7444e020000  MOV word ptr [ESI + ECX*0x2 + 0x2],0x0
0044bcc4  66c7444e040000  MOV word ptr [ESI + ECX*0x2 + 0x4],0x0
0044bccb  ff03  INC dword ptr [EBX]
0044bccd  8b0b  MOV ECX,dword ptr [EBX]
0044bccf  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bcd2  66c7044e0100  MOV word ptr [ESI + ECX*0x2],0x1
0044bcd8  66c7444e020100  MOV word ptr [ESI + ECX*0x2 + 0x2],0x1
0044bcdf  66c7444e040000  MOV word ptr [ESI + ECX*0x2 + 0x4],0x0
0044bce6  ff03  INC dword ptr [EBX]
0044bce8  8b0b  MOV ECX,dword ptr [EBX]
0044bcea  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bced  66c7044e0000  MOV word ptr [ESI + ECX*0x2],0x0
0044bcf3  6b3d98864b007b  IMUL EDI,dword ptr [0x004b8698],0x7b
0044bcfa  81c734894b00  ADD EDI,0x4b8934
0044bd00  8b2d84c54800  MOV EBP,dword ptr [0x0048c584]
0044bd06  6689544e02  MOV word ptr [ESI + ECX*0x2 + 0x2],DX
0044bd0b  66c7444e040600  MOV word ptr [ESI + ECX*0x2 + 0x4],0x6
0044bd12  ff03  INC dword ptr [EBX]
0044bd14  8b0b  MOV ECX,dword ptr [EBX]
0044bd16  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bd19  66c7044e0900  MOV word ptr [ESI + ECX*0x2],0x9
0044bd1f  6689444e02  MOV word ptr [ESI + ECX*0x2 + 0x2],AX
0044bd24  66c7444e04b200  MOV word ptr [ESI + ECX*0x2 + 0x4],0xb2
0044bd2b  ff03  INC dword ptr [EBX]
0044bd2d  8b0b  MOV ECX,dword ptr [EBX]
0044bd2f  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bd32  66c7044e0000  MOV word ptr [ESI + ECX*0x2],0x0
0044bd38  66c7444e020000  MOV word ptr [ESI + ECX*0x2 + 0x2],0x0
0044bd3f  66c7444e040000  MOV word ptr [ESI + ECX*0x2 + 0x4],0x0
0044bd46  ff03  INC dword ptr [EBX]
0044bd48  8b0b  MOV ECX,dword ptr [EBX]
0044bd4a  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bd4d  66c7044e0100  MOV word ptr [ESI + ECX*0x2],0x1
0044bd53  66c7444e020100  MOV word ptr [ESI + ECX*0x2 + 0x2],0x1
0044bd5a  66c7444e040000  MOV word ptr [ESI + ECX*0x2 + 0x4],0x0
0044bd61  ff03  INC dword ptr [EBX]
0044bd63  8b0b  MOV ECX,dword ptr [EBX]
0044bd65  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bd68  66c7044e0000  MOV word ptr [ESI + ECX*0x2],0x0
0044bd6e  6b3d98864b007b  IMUL EDI,dword ptr [0x004b8698],0x7b
0044bd75  81c734894b00  ADD EDI,0x4b8934
0044bd7b  8b2d84c54800  MOV EBP,dword ptr [0x0048c584]
0044bd81  6689544e02  MOV word ptr [ESI + ECX*0x2 + 0x2],DX
0044bd86  66c7444e040600  MOV word ptr [ESI + ECX*0x2 + 0x4],0x6
0044bd8d  ff03  INC dword ptr [EBX]
0044bd8f  8b0b  MOV ECX,dword ptr [EBX]
0044bd91  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bd94  66c7044e0900  MOV word ptr [ESI + ECX*0x2],0x9
0044bd9a  6689444e02  MOV word ptr [ESI + ECX*0x2 + 0x2],AX
0044bd9f  66c7444e04ae00  MOV word ptr [ESI + ECX*0x2 + 0x4],0xae
0044bda6  ff03  INC dword ptr [EBX]
0044bda8  8b0b  MOV ECX,dword ptr [EBX]
0044bdaa  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bdad  66c7044e0000  MOV word ptr [ESI + ECX*0x2],0x0
0044bdb3  66c7444e020000  MOV word ptr [ESI + ECX*0x2 + 0x2],0x0
0044bdba  66c7444e040000  MOV word ptr [ESI + ECX*0x2 + 0x4],0x0
0044bdc1  ff03  INC dword ptr [EBX]
0044bdc3  8b0b  MOV ECX,dword ptr [EBX]
0044bdc5  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bdc8  66c7044e0100  MOV word ptr [ESI + ECX*0x2],0x1
0044bdce  66c7444e020100  MOV word ptr [ESI + ECX*0x2 + 0x2],0x1
0044bdd5  66c7444e040000  MOV word ptr [ESI + ECX*0x2 + 0x4],0x0
0044bddc  ff03  INC dword ptr [EBX]
0044bdde  8b0b  MOV ECX,dword ptr [EBX]
0044bde0  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044bde3  66c7044e0000  MOV word ptr [ESI + ECX*0x2],0x0
0044bde9  6b3d98864b007b  IMUL EDI,dword ptr [0x004b8698],0x7b
0044bdf0  81c734894b00  ADD EDI,0x4b8934
0044bdf6  8b2d84c54800  MOV EBP,dword ptr [0x0048c584]
0044bdfc  6689544e02  MOV word ptr [ESI + ECX*0x2 + 0x2],DX
0044be01  66c7444e040600  MOV word ptr [ESI + ECX*0x2 + 0x4],0x6
0044be08  ff03  INC dword ptr [EBX]
0044be0a  8b0b  MOV ECX,dword ptr [EBX]
0044be0c  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044be0f  66c7044e0900  MOV word ptr [ESI + ECX*0x2],0x9
0044be15  6689444e02  MOV word ptr [ESI + ECX*0x2 + 0x2],AX
0044be1a  66c7444e04aa00  MOV word ptr [ESI + ECX*0x2 + 0x4],0xaa
0044be21  ff03  INC dword ptr [EBX]
0044be23  8b0b  MOV ECX,dword ptr [EBX]
0044be25  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044be28  66c7044e0000  MOV word ptr [ESI + ECX*0x2],0x0
0044be2e  66c7444e020000  MOV word ptr [ESI + ECX*0x2 + 0x2],0x0
0044be35  66c7444e040000  MOV word ptr [ESI + ECX*0x2 + 0x4],0x0
0044be3c  ff03  INC dword ptr [EBX]
0044be3e  8b0b  MOV ECX,dword ptr [EBX]
0044be40  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044be43  66c7044e0100  MOV word ptr [ESI + ECX*0x2],0x1
0044be49  66c7444e020100  MOV word ptr [ESI + ECX*0x2 + 0x2],0x1
0044be50  66c7444e040000  MOV word ptr [ESI + ECX*0x2 + 0x4],0x0
0044be57  ff03  INC dword ptr [EBX]
0044be59  8b0b  MOV ECX,dword ptr [EBX]
0044be5b  8d0c49  LEA ECX,[ECX + ECX*0x2]
0044be5e  66c7044e0000  MOV word ptr [ESI + ECX*0x2],0x0
0044be64  6b3d98864b007b  IMUL EDI,dword ptr [0x004b8698],0x7b
0044be6b  81c734894b00  ADD EDI,0x4b8934
0044be71  8b2d84c54800  MOV EBP,dword ptr [0x0048c584]
0044be77  6689544e02  MOV word ptr [ESI + ECX*0x2 + 0x2],DX
0044be7c  66c7444e040600  MOV word ptr [ESI + ECX*0x2 + 0x4],0x6
0044be83  ff03  INC dword ptr [EBX]
0044be85  8b13  MOV EDX,dword ptr [EBX]
0044be87  8d1452  LEA EDX,[EDX + EDX*0x2]
0044be8a  66c704560900  MOV word ptr [ESI + EDX*0x2],0x9
0044be90  6689445602  MOV word ptr [ESI + EDX*0x2 + 0x2],AX
0044be95  66c7445604a600  MOV word ptr [ESI + EDX*0x2 + 0x4],0xa6
0044be9c  ff03  INC dword ptr [EBX]
0044be9e  8b03  MOV EAX,dword ptr [EBX]
0044bea0  8d0440  LEA EAX,[EAX + EAX*0x2]
0044bea3  66c704460000  MOV word ptr [ESI + EAX*0x2],0x0
0044bea9  66c74446020000  MOV word ptr [ESI + EAX*0x2 + 0x2],0x0
0044beb0  66c74446040000  MOV word ptr [ESI + EAX*0x2 + 0x4],0x0
0044beb7  ff03  INC dword ptr [EBX]
0044beb9  8b03  MOV EAX,dword ptr [EBX]
0044bebb  8d0440  LEA EAX,[EAX + EAX*0x2]
0044bebe  66c704460100  MOV word ptr [ESI + EAX*0x2],0x1
0044bec4  66c74446020100  MOV word ptr [ESI + EAX*0x2 + 0x2],0x1
0044becb  66c74446040000  MOV word ptr [ESI + EAX*0x2 + 0x4],0x0
0044bed2  5d  POP EBP
0044bed3  5f  POP EDI
0044bed4  5e  POP ESI
0044bed5  5b  POP EBX
0044bed6  c3  RET
