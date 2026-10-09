/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a5b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040a5b8(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  int local_c;
  int *local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_c = 0;
  puStack_20 = &LAB_0040a656;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  puStack_28 = (undefined *)0x40a5e1;
  local_8 = param_1;
  FUN_0040a14c(param_1);
  puStack_2c = &LAB_0040a639;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  puStack_28 = &stack0xfffffffc;
  iVar1 = FUN_0040af1c(param_2);
  iVar2 = FUN_0040af00(param_2);
  FUN_004035bc(&local_c,(undefined4 *)0x0,iVar1 - iVar2);
  (**(code **)*param_2)(param_2,local_c,iVar1 - iVar2);
  (**(code **)(*local_8 + 0x24))(local_8,local_c);
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_0040a640;
  puStack_2c = (undefined *)0x40a638;
  FUN_0040a204(local_8);
  return;
}

