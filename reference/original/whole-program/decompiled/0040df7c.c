/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040df7c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040df7c(int param_1,int *param_2,undefined4 param_3,int param_4)

{
  if (*(int *)(*(int *)(*(int *)(param_4 + 8) + -4) + 0x18) == *(int *)(param_1 + 4)) {
    FUN_00403570(param_2,*(int *)(param_1 + 8));
  }
  else if (*(int *)(param_1 + 4) == 0) {
    FUN_004034dc(param_2);
  }
  else {
    FUN_00403710(param_2,3);
  }
  return;
}

