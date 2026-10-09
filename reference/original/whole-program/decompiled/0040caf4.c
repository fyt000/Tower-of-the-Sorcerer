/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040caf4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040caf4(int param_1,int *param_2)

{
  byte *pbVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  uint extraout_ECX;
  uint extraout_ECX_00;
  undefined4 extraout_ECX_01;
  uint extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_50;
  undefined *puStack_4c;
  undefined *puStack_48;
  undefined4 uStack_44;
  undefined *puStack_40;
  undefined *puStack_3c;
  undefined4 uStack_38;
  undefined *puStack_34;
  undefined *puStack_30;
  int local_20;
  int local_1c;
  byte local_15;
  int local_14;
  int *local_10;
  int *local_c;
  int local_8;
  
  puStack_30 = &stack0xfffffffc;
  local_1c = 0;
  local_20 = 0;
  puStack_34 = &LAB_0040cd07;
  uStack_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_38;
  puStack_3c = (undefined *)0x40cb21;
  local_c = param_2;
  local_8 = param_1;
  FUN_0040cdd0(param_1,param_2,0);
  local_10 = (int *)0x0;
  puStack_40 = &LAB_0040ccc5;
  uStack_44 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_44;
  puStack_48 = (undefined *)0x40cb42;
  puStack_3c = &stack0xfffffffc;
  FUN_0040c3dc(local_8,&local_15,&local_14);
  if (local_c == (int *)0x0) {
    puStack_48 = (undefined *)0x40cb53;
    FUN_0040cdf4(local_8,&local_1c,extraout_ECX);
    puStack_48 = (undefined *)0x40cb5b;
    iVar2 = FUN_00409350(local_1c);
    puStack_48 = (undefined *)0x40cb62;
    local_10 = (int *)(**(code **)(iVar2 + 0x24))(iVar2,1,0);
    puStack_48 = (undefined *)0x40cb70;
    FUN_0040cdf4(local_8,&local_1c,extraout_ECX_00);
    puStack_48 = (undefined *)0x40cb7b;
    (**(code **)(*local_10 + 0x18))(local_10,local_1c);
    uVar3 = extraout_ECX_01;
  }
  else {
    local_10 = local_c;
    puStack_48 = (undefined *)0x40cb8e;
    FUN_0040cdf4(local_8,&local_1c,extraout_ECX);
    if ((*(byte *)(local_10 + 7) & 0x10) == 0) {
      puStack_48 = (undefined *)0x40cbaf;
      FUN_0040cdf4(local_8,&local_20,extraout_ECX_02);
      puStack_48 = (undefined *)0x40cbba;
      FUN_0040ca84(local_20,&local_1c);
      puStack_48 = (undefined *)0x40cbc5;
      (**(code **)(*local_10 + 0x18))(local_10,local_1c);
      uVar3 = extraout_ECX_04;
    }
    else {
      puStack_48 = (undefined *)0x40cba2;
      FUN_0040cdf4(local_8,&local_1c,extraout_ECX_02);
      uVar3 = extraout_ECX_03;
    }
  }
  *(int **)(local_8 + 0x18) = local_10;
  if (DAT_0048a614 == 0) {
    puStack_48 = (undefined *)0x40cbf0;
    uVar3 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)local_8 >> 8),1),uVar3);
    *(undefined4 *)(local_8 + 0x30) = uVar3;
  }
  else {
    *(int *)(local_8 + 0x30) = DAT_0048a614;
  }
  puStack_4c = &LAB_0040ccaf;
  uStack_50 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_50;
  puStack_48 = &stack0xfffffffc;
  FUN_004099a4(*(int **)(local_8 + 0x30),*(undefined4 *)(local_8 + 0x18));
  *(undefined4 *)(local_8 + 0x24) = *(undefined4 *)(local_8 + 0x18);
  pbVar1 = (byte *)(*(int *)(local_8 + 0x18) + 0x1c);
  *pbVar1 = *pbVar1 | 1;
  pbVar1 = (byte *)(*(int *)(local_8 + 0x18) + 0x1c);
  *pbVar1 = *pbVar1 | 2;
  (**(code **)(**(int **)(local_8 + 0x18) + 0x14))(*(int **)(local_8 + 0x18),local_8);
  pbVar1 = (byte *)(*(int *)(local_8 + 0x18) + 0x1c);
  *pbVar1 = *pbVar1 & 0xfd;
  if ((DAT_0048a614 == 0) && (iVar2 = *(int *)(*(int *)(local_8 + 0x30) + 8), -1 < iVar2 + -1)) {
    local_14 = 0;
    do {
      piVar4 = (int *)FUN_00409a40(*(undefined4 **)(local_8 + 0x30),local_14);
      (**(code **)(*piVar4 + 0xc))();
      local_14 = local_14 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  *in_FS_OFFSET = uStack_50;
  puStack_48 = &LAB_0040ccb6;
  if (DAT_0048a614 == 0) {
    puStack_4c = (undefined *)0x40cca6;
    FUN_00402c34(*(int **)(local_8 + 0x30));
  }
  *(undefined4 *)(local_8 + 0x30) = 0;
  return;
}

