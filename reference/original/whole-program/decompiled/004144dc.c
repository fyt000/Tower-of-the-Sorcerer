/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004144dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004144dc(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  
  if (*(int *)(param_1 + 0xb4) != 0) {
    puStack_1c = (undefined *)0x414503;
    piVar2 = (int *)FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
    puStack_20 = &LAB_004145a0;
    uStack_24 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_24;
    iVar5 = *(int *)(*(int *)(param_1 + 0xb4) + 8);
    puStack_1c = &stack0xfffffffc;
    FUN_00409b80(piVar2,iVar5);
    if (-1 < iVar5 + -1) {
      iVar6 = 0;
      iVar4 = iVar5;
      do {
        iVar3 = FUN_00409a40(*(undefined4 **)(param_1 + 0xb4),iVar6);
        iVar1 = *(int *)(iVar3 + 200);
        if ((-1 < iVar1) && (iVar1 < iVar5)) {
          FUN_00409b08(piVar2,iVar1,iVar3);
        }
        iVar6 = iVar6 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    if (-1 < iVar5 + -1) {
      iVar4 = 0;
      do {
        iVar6 = FUN_00409a40(piVar2,iVar4);
        if (iVar6 != 0) {
          FUN_00416d80(iVar6,(short)iVar4);
        }
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    *in_FS_OFFSET = uStack_24;
    puStack_1c = (undefined *)0x4145a7;
    puStack_20 = (undefined *)0x41459f;
    FUN_00402c34(piVar2);
    return;
  }
  return;
}

