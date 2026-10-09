/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416c2c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00416c2c(int **param_1)

{
  int **ppiVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  ppiVar1 = FUN_0041fffc(param_1);
  if (ppiVar1 != (int **)0x0) {
    if (ppiVar1 != param_1) {
      do {
        if (*(char *)((int)param_1 + 0x37) == '\0') {
          return 0;
        }
        if (*(char *)(param_1 + 0xe) == '\0') {
          return 0;
        }
        param_1 = (int **)param_1[8];
      } while (ppiVar1 != param_1);
    }
    uVar2 = 1;
  }
  return uVar2;
}

