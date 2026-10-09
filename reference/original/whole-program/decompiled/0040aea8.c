/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040aea8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040aea8(int *param_1,char param_2)

{
  if (param_2 != *(char *)(param_1 + 5)) {
    if (param_2 != '\0') {
      (**(code **)(*param_1 + 0x74))();
    }
    *(char *)(param_1 + 5) = param_2;
  }
  return;
}

