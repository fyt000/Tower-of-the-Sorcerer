/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004218e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004218e0(int *param_1,undefined4 param_2,int *param_3)

{
  FUN_00420688(param_1,param_2,param_3);
  if ((HWND)param_1[0x4d] != (HWND)0x0) {
    SetWindowPos((HWND)param_1[0x4d],(HWND)0x1,*param_3,param_3[1],param_3[2] - *param_3,
                 param_3[3] - param_3[1],0x100);
  }
  return;
}

