/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004284b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004284b8(int param_1,int param_2,char param_3)

{
  FUN_00412f9c(param_1,param_2,param_3);
  if ((param_3 == '\x01') && (param_2 == *(int *)(param_1 + 0xac))) {
    *(undefined4 *)(param_1 + 0xac) = 0;
  }
  return;
}

