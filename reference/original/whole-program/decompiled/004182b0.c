/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004182b0.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_004182b0(int *param_1,HWND param_2,int param_3,int param_4)

{
  bool bVar1;
  bool bVar2;
  
  bVar2 = false;
  bVar1 = FUN_00417800((int)param_1);
  if (bVar1) {
    if (*(char *)(param_1 + 0x11) == '\0') {
      FUN_00418274(param_1,0,0,0);
    }
    FUN_0041819c((int)param_1);
    bVar2 = FUN_0041830c((int)param_1,param_2,param_3,param_4);
    if (bVar2) {
      ShowCursor(0);
    }
  }
  return bVar2;
}

