/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415a08.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00415a08(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_00414ccc((int)param_1);
  if (iVar1 == 0) {
    (**(code **)(*param_1 + -0x10))(param_1,param_2);
    return;
  }
  FUN_004156ac(param_1,param_2);
  return;
}

