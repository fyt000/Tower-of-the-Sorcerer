/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409654.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409654(void)

{
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  FUN_004099a4(DAT_0048a618,DAT_0048a614);
  DAT_0048a614 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
  return;
}

