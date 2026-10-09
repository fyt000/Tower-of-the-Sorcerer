/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004033f8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004033f8(void)

{
  int **ppiVar1;
  int **in_FS_OFFSET;
  
  ppiVar1 = (int **)*in_FS_OFFSET;
  if (DAT_0048a48c == ppiVar1) {
    *in_FS_OFFSET = *DAT_0048a48c;
    return;
  }
  while( true ) {
    if (ppiVar1 == (int **)0xffffffff) {
      return;
    }
    if ((int **)*ppiVar1 == DAT_0048a48c) break;
    ppiVar1 = (int **)*ppiVar1;
  }
  *ppiVar1 = *DAT_0048a48c;
  return;
}

