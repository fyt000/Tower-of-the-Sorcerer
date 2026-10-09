/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422b28.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422b28(int *param_1,undefined4 *param_2)

{
  HWND hWnd;
  BOOL BVar1;
  
  hWnd = (HWND)FUN_00416cbc(param_1);
  BVar1 = IsIconic(hWnd);
  if (BVar1 == 0) {
    root_00415b98(param_1,param_2);
    return;
  }
  *param_2 = 0x27;
  (**(code **)(*param_1 + -0x10))(param_1,param_2);
  return;
}

