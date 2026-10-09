/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040cd18.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040cd18(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint extraout_ECX;
  uint extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_30;
  code *pcStack_2c;
  undefined *puStack_28;
  undefined4 local_24;
  code *pcStack_20;
  undefined *puStack_1c;
  int local_c;
  int local_8;
  
  puStack_1c = &stack0xfffffffc;
  puStack_28 = &stack0xfffffffc;
  local_c = 0;
  pcStack_20 = thunk_FUN_00403140;
  local_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &local_24;
  pcStack_2c = thunk_FUN_00402f4c;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  local_8 = param_1;
  uVar1 = FUN_0040ce90(param_1,param_2,0);
  if ((char)uVar1 != '\v') {
    FUN_0040b8e0(uVar1,extraout_EDX);
  }
  iVar2 = FUN_004081a0(param_2);
  iVar2 = *(int *)(iVar2 + 1);
  uVar1 = extraout_ECX;
  while (FUN_0040cdf4(local_8,&local_c,uVar1), local_c != 0) {
    FUN_0040b8f8(iVar2,local_c);
    uVar1 = extraout_ECX_00;
  }
  *in_FS_OFFSET = uStack_30;
  *in_FS_OFFSET = local_24;
  puStack_1c = &LAB_0040cdc7;
  pcStack_20 = (code *)0x40cdbf;
  FUN_004034dc(&local_c);
  return;
}

