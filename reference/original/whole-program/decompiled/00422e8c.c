/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422e8c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422e8c(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = FUN_00423680(param_1,param_2,param_3);
  *(uint *)(param_2 + 0xc) = uVar1 & 0x7f;
  return;
}

