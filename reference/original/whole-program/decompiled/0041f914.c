/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041f914.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041f914(int *param_1)

{
  int *piVar1;
  BOOL BVar2;
  
  if (param_1 != (int *)0x0) {
    do {
      BVar2 = IsWindow((HWND)param_1[1]);
      if (BVar2 != 0) {
        EnableWindow((HWND)param_1[1],1);
      }
      piVar1 = (int *)*param_1;
      FUN_00402668((int)param_1);
      param_1 = piVar1;
    } while (piVar1 != (int *)0x0);
  }
  return;
}

