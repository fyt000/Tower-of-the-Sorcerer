/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042240c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042240c(int **param_1,int param_2,char param_3)

{
  bool bVar1;
  undefined4 extraout_ECX;
  
  if (param_3 != '\0') {
    bVar1 = thunk_FUN_00414ad5(param_2,(int)param_1[0x44]);
    if (bVar1) {
      param_1[0x44] = *(int **)(param_2 + 0x20);
    }
  }
  bVar1 = thunk_FUN_00414ad5(param_2,(int)param_1[0x43]);
  if (bVar1) {
    FUN_004223a4(param_1,(int **)0x0,extraout_ECX);
  }
  return;
}

