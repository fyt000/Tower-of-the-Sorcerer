/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413758.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413758(int **param_1,char param_2)

{
  bool bVar1;
  
  bVar1 = FUN_00413748(param_1);
  if ((bool)param_2 != bVar1) {
    if (param_2 == '\0') {
      FUN_004124b0((int **)0x0);
    }
    else {
      FUN_004124b0(param_1);
    }
  }
  return;
}

