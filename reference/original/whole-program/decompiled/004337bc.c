/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004337bc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004337bc(int *param_1,char param_2)

{
  if (param_2 != *(char *)(param_1 + 0x48)) {
    *(char *)(param_1 + 0x48) = param_2;
    FUN_004139d4(param_1);
  }
  return;
}

