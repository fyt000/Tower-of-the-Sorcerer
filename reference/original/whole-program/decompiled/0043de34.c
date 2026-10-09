/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043de34.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043de34(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined local_18 [4];
  undefined local_14;
  undefined4 local_10;
  undefined local_c;
  int local_8;
  
  puStack_28 = &stack0xfffffffc;
  local_8 = 0;
  puStack_2c = &LAB_0043deaa;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  local_18[0] = *(undefined *)(param_4 + -5);
  local_14 = 2;
  local_c = 0xb;
  local_10 = param_1;
  FUN_0040661c((byte *)"%s: %s",local_18,1,&local_8);
  piVar1 = *(int **)(*(int *)(param_4 + -4) + 0x100);
  (**(code **)(*piVar1 + 0x30))(piVar1,local_8,param_2);
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_0043deb1;
  puStack_2c = (undefined *)0x43dea9;
  FUN_004034dc(&local_8);
  return;
}

