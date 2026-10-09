/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e7a8.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0040e7a8(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  short sVar1;
  
  if (*(int *)(param_4 + -4) != 0) {
    sVar1 = *(short *)(*(int *)(param_4 + -8) + 0x18);
    return CONCAT31((int3)(CONCAT22((short)((uint)*(int *)(param_4 + -8) >> 0x10),sVar1) >> 8),
                    sVar1 != *(short *)(*(int *)(param_4 + -4) + 0x18));
  }
  return CONCAT31((int3)((uint)*(int *)(param_4 + -8) >> 8),
                  *(short *)(*(int *)(param_4 + -8) + 0x18) != 0);
}

