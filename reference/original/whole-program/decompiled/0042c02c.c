/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c02c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_0042c02c(int param_1)

{
  int **ppiVar1;
  int *piVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  ppiVar1 = *(int ***)(*(int *)(param_1 + 0xac) + 4);
  piVar2 = FUN_00402c7c(ppiVar1,(int *)&PTR_FUN_004193b4);
  if ((char)piVar2 != '\0') {
    uVar3 = FUN_0041db4c((int)ppiVar1);
  }
  return uVar3;
}

