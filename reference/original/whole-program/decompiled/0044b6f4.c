/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044b6f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0044b6f4(int param_1)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_1c = &LAB_0044b77c;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
  (**(code **)(*piVar1 + 0xc))(piVar1,0x5d,&local_8);
  FUN_0040352c(&DAT_004b867c,local_8);
  if (monster_index < 0x22) {
    piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar1 + 0xc))(piVar1,monster_index + 0x5e,&local_8);
    FUN_0040352c(&DAT_004b867c,local_8);
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0044b783;
  puStack_1c = (undefined *)0x44b77b;
  FUN_004034dc((int *)&local_8);
  return;
}

