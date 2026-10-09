/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412d80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00412d80(int *param_1,int param_2)

{
  if (param_2 != param_1[0xd]) {
    FUN_00412d4c(param_1);
    param_1[0xd] = param_2;
  }
  return;
}

