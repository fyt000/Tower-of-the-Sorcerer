/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004204e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004204e0(int param_1,int param_2)

{
  *(int *)(param_1 + 0x10) = param_2;
  if (param_2 < 0) {
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  FUN_00420784(*(int *)(param_1 + 4));
  return;
}

