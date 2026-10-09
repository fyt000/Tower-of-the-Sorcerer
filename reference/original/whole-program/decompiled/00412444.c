/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412444.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00412444(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = FUN_0040edcc((uint *)&DAT_00412484,param_1);
  if (iVar1 == 0) {
    FUN_00403570(param_2,param_1);
  }
  else {
    FUN_00403854(param_1,iVar1 + 1,0x7fffffff,param_2);
  }
  return;
}

