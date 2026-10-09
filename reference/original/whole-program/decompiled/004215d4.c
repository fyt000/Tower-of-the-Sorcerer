/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004215d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004215d4(int param_1,int param_2,undefined *param_3,undefined *param_4)

{
  int *piVar1;
  
  FUN_0040e8f0(param_1,param_2,param_3,param_4);
  piVar1 = *(int **)(param_1 + 0x130);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x10))(piVar1,param_2,param_3,param_4);
  }
  return;
}

