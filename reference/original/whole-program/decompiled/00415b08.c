/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415b08.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00415b08(int *param_1,int *param_2)

{
  bool bVar1;
  
  bVar1 = FUN_00415678(*(HWND *)(param_2[2] + 4),param_2);
  if (!bVar1) {
    (**(code **)(*param_1 + -0x10))(param_1,param_2);
  }
  return;
}

