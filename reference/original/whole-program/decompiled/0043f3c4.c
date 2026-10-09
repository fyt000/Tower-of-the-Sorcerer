/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043f3c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043f3c4(int param_1)

{
  int *piVar1;
  undefined *puVar2;
  int iVar3;
  int **in_FS_OFFSET;
  uint **in_stack_ffffffdc;
  int *piStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  puStack_1c = &LAB_0043f42c;
  piStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int *)&piStack_20;
  piVar1 = *(int **)(param_1 + 0x144);
  puVar2 = &stack0xfffffffc;
  if (piVar1 != (int *)0x0) {
    iVar3 = *(int *)(param_1 + 0x2c);
    if (*(char *)((int)piVar1 + 0xb1) == '\0') {
      iVar3 = piVar1[0xb];
    }
    in_stack_ffffffdc = &local_8;
    FUN_0043d6f0(*(int *)(param_1 + 0x158),(int *)piVar1[0x2a],iVar3,(int *)in_stack_ffffffdc);
    FUN_004135d4(piVar1,local_8);
    puVar2 = puStack_18;
  }
  puStack_18 = puVar2;
  *in_FS_OFFSET = (int *)in_stack_ffffffdc;
  puStack_1c = &LAB_0043f433;
  piStack_20 = (int *)0x43f42b;
  FUN_004034dc((int *)&local_8);
  return;
}

