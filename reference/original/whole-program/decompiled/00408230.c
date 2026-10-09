/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00408230.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00408230(int param_1,undefined *param_2)

{
  int iVar1;
  int iVar2;
  undefined uVar3;
  byte bVar5;
  undefined *puVar4;
  undefined2 uVar6;
  uint uVar7;
  undefined *puVar8;
  int iVar9;
  uint uVar10;
  
  puVar4 = param_2;
  if (param_2 != (undefined *)0x0) {
    puVar4 = (undefined *)(CONCAT11(*param_2,param_2[-4]) & 0xdfff);
  }
  do {
    iVar1 = param_1 + 2 + (uint)*(byte *)(param_1 + 1);
    uVar7 = (uint)*(byte *)(iVar1 + 10);
    uVar10 = (uint)*(ushort *)(iVar1 + 0xb + uVar7);
    if (uVar10 != 0) {
      iVar2 = iVar1 + 0xd + uVar7;
      do {
        puVar8 = (undefined *)
                 (CONCAT22((short)(uVar7 >> 0x10),*(undefined2 *)(iVar2 + 0x1a)) & 0xffffdfff);
        if (puVar8 == puVar4) {
          iVar9 = CONCAT22((short)((uint)puVar8 >> 0x10),(ushort)(byte)puVar8);
          while( true ) {
            uVar6 = (undefined2)((uint)puVar4 >> 0x10);
            uVar3 = SUB41(puVar4,0);
            bVar5 = param_2[iVar9 + -1] ^ *(byte *)(iVar2 + 0x1a + iVar9);
            puVar4 = (undefined *)CONCAT22(uVar6,CONCAT11(bVar5,uVar3));
            if ((bVar5 & 0xdf) != 0) break;
            iVar9 = iVar9 + -1;
            if (iVar9 == 0) {
              return;
            }
          }
          puVar4 = (undefined *)(CONCAT22(uVar6,CONCAT11(*param_2,uVar3)) & 0xffffdfff);
          puVar8 = (undefined *)CONCAT31((int3)((uint)iVar9 >> 8),*(undefined *)(iVar2 + 0x1a));
        }
        uVar7 = CONCAT22((short)((uint)puVar8 >> 0x10),(ushort)(byte)puVar8);
        uVar10 = uVar10 - 1;
        iVar2 = iVar2 + 0x1b + uVar7;
      } while (uVar10 != 0);
    }
    param_1 = *(int *)(iVar1 + 4);
  } while (param_1 != 0);
  return;
}

