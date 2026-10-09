/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b2c0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040b2c0(int *param_1,int param_2)

{
  undefined4 uVar1;
  int local_8;
  
  local_8 = param_2;
  uVar1 = (**(code **)(*param_1 + 0xc))(param_1,&local_8);
  FUN_0040b120((int)param_1,uVar1,param_1[2]);
  param_1[4] = local_8;
  return;
}

