/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406994.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00406994(int param_1,int *param_2)

{
  BYTE BVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  undefined4 unaff_EBX;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined4 *local_10;
  byte local_9;
  int *local_8;
  
  puStack_20 = &stack0xfffffffc;
  local_10 = (undefined4 *)0x0;
  puStack_24 = &LAB_00406aaf;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  iVar4 = 1;
  local_8 = param_2;
  FUN_004034dc(param_2);
  local_9 = 0;
  while( true ) {
    iVar3 = FUN_00403650(param_1);
    if (iVar3 < iVar4) break;
    BVar1 = *(BYTE *)(param_1 + -1 + iVar4);
    unaff_EBX = CONCAT31((int3)((uint)unaff_EBX >> 8),BVar1);
    bVar2 = FUN_00406054(BVar1);
    if ((short)CONCAT31(extraout_var,bVar2) == 0) {
      if (BVar1 == '\'') {
        local_9 = local_9 ^ 1;
        FUN_004035ec((int *)&local_10,unaff_EBX);
        FUN_00403658(local_8,local_10);
      }
      else if (local_9 == 0) {
        FUN_00403854(param_1,iVar4,2,(int *)&local_10);
        iVar3 = FUN_00405a34((undefined *)local_10,&DAT_00406ac8);
        if (iVar3 == 0) {
          FUN_00403658(local_8,(undefined4 *)&DAT_00406ad4);
          iVar4 = iVar4 + 1;
        }
        else {
          FUN_004035ec((int *)&local_10,unaff_EBX);
          FUN_00403658(local_8,local_10);
        }
      }
      else {
        FUN_004035ec((int *)&local_10,unaff_EBX);
        FUN_00403658(local_8,local_10);
      }
      iVar4 = iVar4 + 1;
    }
    else {
      FUN_00403854(param_1,iVar4,2,(int *)&local_10);
      FUN_00403658(local_8,local_10);
      iVar4 = iVar4 + 2;
    }
  }
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_00406ab6;
  puStack_24 = (undefined *)0x406aae;
  FUN_004034dc((int *)&local_10);
  return;
}

