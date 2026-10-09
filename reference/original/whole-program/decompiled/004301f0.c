/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004301f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004301f0(int *param_1,char param_2)

{
  if (param_2 != *(char *)(param_1 + 0x84)) {
    *(char *)(param_1 + 0x84) = param_2;
    if (param_2 == '\0') {
      root_00430218(param_1,*(undefined2 *)((int)param_1 + 0x196));
    }
    else {
      FUN_0043025c(param_1);
    }
  }
  return;
}

