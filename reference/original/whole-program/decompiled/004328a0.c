/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004328a0.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_004328a0(int *param_1,int *param_2,int *param_3)

{
  uint uVar1;
  
  uVar1 = FUN_00432860(param_1);
  FUN_00417b60(param_1,uVar1,param_2,param_3);
  param_1[0x16] = param_1[0x16] + 1;
  return uVar1;
}

