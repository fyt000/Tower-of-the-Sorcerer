/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ebd0.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040ebd0(void)

{
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  
  FUN_00403f14((undefined4 *)&DAT_004891d4);
  DAT_004891c0 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
  DAT_004891c4 = FUN_00402c0c(0x408d3c,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                              extraout_ECX_00);
  DAT_004891c8 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                              extraout_ECX_01);
  DAT_0048a61c = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                              extraout_ECX_02);
  _DAT_0048a60c = GetCurrentThreadId();
  DAT_0048a618 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                              extraout_ECX_03);
  return;
}

