/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043fa20.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043fa20(int **param_1,char param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 != *(char *)(param_1 + 0x5b)) {
    *(char *)(param_1 + 0x5b) = param_2;
    if (*(char *)(param_1 + 0x5b) == '\x01') {
      iVar1 = (**(code **)(*param_1[0x55] + 0x1c))();
      iVar2 = root_0042a98c(param_1);
      if (iVar2 < iVar1 + 1) {
        FUN_0043fdc4(param_1);
      }
    }
    (*(code *)(*param_1)[0x11])();
  }
  return;
}

