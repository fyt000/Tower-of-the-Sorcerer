/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a874.
 * Inferred types, shared tails and runtime effects require assembly review. */

LONG FUN_0041a874(int *param_1,undefined *param_2)

{
  int c;
  LPCSTR lpString;
  BOOL BVar1;
  tagSIZE *lpsz;
  tagSIZE tStack_10;
  
  lpsz = &tStack_10;
  FUN_0041aa24(param_1,DAT_0041a8b8);
  c = FUN_00403650((int)param_2);
  lpString = FUN_00403814(param_2);
  BVar1 = GetTextExtentPointA((HDC)param_1[1],lpString,c,lpsz);
  if (BVar1 == 0) {
    tStack_10.cy = 0;
  }
  return tStack_10.cy;
}

