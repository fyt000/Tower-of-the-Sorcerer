/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412780.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00412780(uint param_1)

{
  LRESULT LVar1;
  bool bVar2;
  
  bVar2 = false;
  if (DAT_0048a6a8 != 0) {
    LVar1 = FUN_004126c4(DAT_0048a6ac,param_1,DAT_0048a6a0,&DAT_0048a6bc,DAT_0048a6a8);
    bVar2 = LVar1 != 0;
  }
  return bVar2;
}

