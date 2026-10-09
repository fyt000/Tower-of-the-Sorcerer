/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416108.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416108(int *param_1,int *param_2)

{
  bool bVar1;
  
  if (((*(short *)(param_2 + 1) == 1) || (*(short *)(param_2 + 1) == 2)) &&
     (bVar1 = FUN_00415678((HWND)param_2[2],param_2), bVar1)) {
    return;
  }
  (**(code **)(*param_1 + -0x10))(param_1,param_2);
  return;
}

