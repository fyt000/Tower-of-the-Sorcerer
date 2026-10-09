/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041016c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041016c(int param_1,int param_2,byte param_3)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_EDX;
  int iVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined4 *local_10;
  byte local_9;
  int local_8;
  
  puStack_20 = &stack0xfffffffc;
  local_10 = (undefined4 *)0x0;
  puStack_24 = &LAB_00410208;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  local_9 = param_3;
  local_8 = param_2;
  iVar1 = FUN_0041040c(param_1);
  if (-1 < iVar1 + -1) {
    iVar3 = 0;
    do {
      if (iVar3 < local_8) {
        iVar2 = FUN_0041041c(param_1,iVar3);
        if (local_9 < *(byte *)(iVar2 + 0x2d)) {
          FUN_00405bf0(0xf03e,(int *)&local_10);
          FUN_0040f714(local_10,extraout_EDX);
        }
      }
      else {
        iVar2 = FUN_0041041c(param_1,iVar3);
        if (*(byte *)(iVar2 + 0x2d) < local_9) {
          iVar2 = FUN_0041041c(param_1,iVar3);
          *(byte *)(iVar2 + 0x2d) = local_9;
        }
      }
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_0041020f;
  puStack_24 = (undefined *)0x410207;
  FUN_004034dc((int *)&local_10);
  return;
}

