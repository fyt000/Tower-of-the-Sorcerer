/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ce90.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_0040ce90(int param_1,undefined4 param_2,uint param_3)

{
  undefined4 uVar1;
  uint local_4;
  
  local_4 = param_3;
  uVar1 = FUN_0040bc08(param_1,&local_4,1);
  return CONCAT31((int3)((uint)uVar1 >> 8),(undefined)local_4);
}

