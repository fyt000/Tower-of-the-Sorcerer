/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004134b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004134b8(int **param_1,int **param_2)

{
  undefined4 uVar1;
  
  if (param_2 != (int **)param_1[8]) {
    if (param_1 == (int **)param_1[8]) {
      uVar1 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)param_2 >> 8),1),0xf043);
      FUN_004031f8(uVar1);
    }
    if (param_1[8] != (int *)0x0) {
      FUN_00414c34(param_1[8],param_1);
    }
    if (param_2 != (int **)0x0) {
      FUN_00414b98(param_2,param_1);
    }
  }
  return;
}

