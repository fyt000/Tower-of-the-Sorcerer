/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041622c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041622c(int *param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  
  *(byte *)((int)param_1 + 0x36) = *(byte *)((int)param_1 + 0x36) | 4;
  uVar1 = FUN_00402cdc(param_1,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  *(uint *)(param_2 + 0xc) = uVar1 & 0x7f;
  return;
}

