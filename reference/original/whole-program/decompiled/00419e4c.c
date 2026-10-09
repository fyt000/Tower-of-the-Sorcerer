/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419e4c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00419e4c(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = MulDiv(param_2,param_1[5],0x48);
  FUN_00419dac(param_1,-iVar1);
  return;
}

