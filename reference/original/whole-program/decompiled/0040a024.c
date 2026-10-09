/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a024.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040a024(int *param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_34;
  undefined *puStack_30;
  undefined *puStack_2c;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined4 local_10;
  int *local_c;
  int *local_8;
  
  puStack_20 = &stack0xfffffffc;
  local_10 = 0;
  puStack_24 = &LAB_0040a0cb;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  puStack_2c = (undefined *)0x40a04e;
  local_c = param_2;
  local_8 = param_1;
  FUN_0040a14c(param_1);
  puStack_30 = &LAB_0040a0ae;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  puStack_2c = &stack0xfffffffc;
  iVar2 = (**(code **)(*local_c + 0x10))();
  if (-1 < iVar2 + -1) {
    iVar4 = 0;
    do {
      (**(code **)(*local_c + 0xc))(local_c,iVar4,&local_10);
      uVar1 = local_10;
      uVar3 = (**(code **)(*local_c + 0x14))(local_c,iVar4);
      (**(code **)(*local_8 + 0x30))(local_8,uVar1,uVar3);
      iVar4 = iVar4 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  *in_FS_OFFSET = uStack_34;
  puStack_2c = &LAB_0040a0b5;
  puStack_30 = (undefined *)0x40a0ad;
  FUN_0040a204(local_8);
  return;
}

