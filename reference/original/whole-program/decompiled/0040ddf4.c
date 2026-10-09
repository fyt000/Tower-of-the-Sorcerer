/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ddf4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040ddf4(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  puStack_1c = &LAB_0040de6b;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  uVar1 = FUN_0040d9ac((char)*(undefined4 *)(param_4 + 8),param_2,param_3,
                       *(undefined4 *)(param_4 + 8));
  if ((char)uVar1 != '\0') {
    FUN_00408510(*(int **)(*(int *)(*(int *)(param_4 + 8) + -4) + 0x1c),
                 *(char ***)(*(int *)(param_4 + 8) + -0xc),(int *)&local_8);
    FUN_00403760(*(uint **)(param_4 + -4),local_8);
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040de72;
  puStack_1c = (undefined *)0x40de6a;
  FUN_004034dc((int *)&local_8);
  return;
}

