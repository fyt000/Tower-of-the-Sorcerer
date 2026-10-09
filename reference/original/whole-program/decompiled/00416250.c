/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416250.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416250(int *param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  
  uVar1 = FUN_00402cdc(param_1,0,param_3);
  *(uint *)(param_2 + 0xc) = uVar1 & 0x7f;
  return;
}

