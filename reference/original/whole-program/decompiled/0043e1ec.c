/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043e1ec.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043e1ec(int param_1,int param_2)

{
  if (*(int *)(param_1 + 0x158) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x158) + 0x140) = 0;
  }
  *(int *)(param_1 + 0x158) = param_2;
  if (param_2 != 0) {
    *(int *)(param_2 + 0x140) = param_1;
    FUN_0040e570(param_2,param_1,param_2);
  }
  return;
}

