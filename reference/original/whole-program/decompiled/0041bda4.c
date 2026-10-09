/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041bda4.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_0041bda4(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  int **ppiVar1;
  int *piVar2;
  uint uVar3;
  
  if (*(int *)(*(int *)(param_4 + -4) + 0x1c) == 0) {
    uVar3 = (**(code **)(**(int **)(param_4 + -8) + 0x18))();
    return uVar3 ^ 1;
  }
  ppiVar1 = *(int ***)(*(int *)(param_4 + -4) + 0x1c);
  piVar2 = FUN_00402c7c(ppiVar1,(int *)&PTR_FUN_004190c4);
  if (((char)piVar2 != '\0') &&
     (piVar2 = (int *)(**(code **)(**(int **)(param_4 + -8) + 0x14))
                                (*(int **)(param_4 + -8),ppiVar1), (char)piVar2 != '\0')) {
    return 0;
  }
  return CONCAT31((int3)((uint)piVar2 >> 8),1);
}

