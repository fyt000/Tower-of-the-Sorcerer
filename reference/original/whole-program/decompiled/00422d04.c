/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422d04.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422d04(int param_1,int param_2)

{
  bool bVar1;
  
  if (((*(int *)(param_2 + 8) == 0) && (*(int *)(param_1 + 0x128) != 0)) &&
     (bVar1 = FUN_004109bc(*(int *)(param_1 + 0x128)), bVar1)) {
    return;
  }
  root_00415a34(param_1,param_2);
  return;
}

