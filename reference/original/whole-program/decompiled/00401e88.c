/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401e88.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00401e88(int **param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int *local_1c;
  int *local_18;
  int *local_14;
  int local_10;
  
  local_1c = *param_1;
  local_18 = param_1[1];
  FUN_00401e3c();
  FUN_004013e8((int **)&DAT_0048a47c,&local_1c,&local_14);
  if (local_14 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    if (local_14 < local_1c) {
      uVar2 = FUN_00401c7c((int)local_1c);
      local_1c = (int *)((int)local_1c - uVar2);
      local_18 = (int *)((int)local_18 + uVar2);
    }
    if ((uint *)((int)local_1c + (int)local_18) < (uint *)((int)local_14 + local_10)) {
      uVar2 = FUN_00401cec((uint *)((int)local_1c + (int)local_18));
      local_18 = (int *)((int)local_18 + uVar2);
    }
    if ((uint *)((int)local_14 + local_10) == (uint *)((int)local_1c + (int)local_18)) {
      FUN_00401c00((uint *)((int)local_1c + (int)local_18) + -1,4);
      local_18 = local_18 + -1;
    }
    DAT_0048a474 = local_1c;
    DAT_0048a470 = local_18;
    uVar1 = CONCAT31((int3)((uint)local_18 >> 8),1);
  }
  return uVar1;
}

