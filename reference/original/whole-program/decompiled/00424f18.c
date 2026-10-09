/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424f18.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00424f18(int param_1,int param_2,undefined4 *param_3)

{
  int **ppiVar1;
  int *piVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  code *pcStack_20;
  undefined *puStack_1c;
  
  puStack_1c = (undefined *)0x424f2d;
  ppiVar1 = (int **)(**(code **)(param_2 + -0xc))();
  *param_3 = ppiVar1;
  pcStack_20 = thunk_FUN_00402f4c;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  puStack_1c = &stack0xfffffffc;
  (*(code *)(*ppiVar1)[9])(ppiVar1,0,param_1);
  *in_FS_OFFSET = uStack_24;
  if (*(int *)(param_1 + 0x28) == 0) {
    puStack_1c = (undefined *)0x424f8d;
    piVar2 = FUN_00402c7c(ppiVar1,(int *)&PTR_FUN_0041edfc);
    if ((char)piVar2 != '\0') {
      puStack_1c = (undefined *)0x424f9b;
      FUN_00416c98((int *)ppiVar1);
      *(int ***)(param_1 + 0x28) = ppiVar1;
    }
  }
  return;
}

