/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043036c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043036c(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_00430344((int)param_1);
  FUN_004130d8(param_1,(param_1[0x6c] + -1) * iVar1 + 1);
  (**(code **)(*param_1 + 0x44))();
  return;
}

