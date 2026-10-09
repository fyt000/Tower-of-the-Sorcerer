/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004152ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004152ac(int **param_1)

{
  int **ppiVar1;
  int **ppiVar2;
  
  ppiVar1 = FUN_0041fffc(param_1);
  if (ppiVar1 != (int **)0x0) {
    ppiVar2 = param_1;
    if (ppiVar1 != param_1) {
      do {
        ppiVar2 = (int **)ppiVar2[8];
        if (*(char *)((int)ppiVar2 + 199) == '\0') {
          return;
        }
      } while (ppiVar1 != ppiVar2);
    }
    FUN_004151b4((int *)param_1);
  }
  return;
}

