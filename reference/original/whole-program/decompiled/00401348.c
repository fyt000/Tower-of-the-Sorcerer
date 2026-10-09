/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401348.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_00401348(void)

{
  int **ppiVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  
  if (DAT_0048a43c == (int **)0x0) {
    puVar2 = (undefined4 *)LocalAlloc(0,0x644);
    if (puVar2 == (undefined4 *)0x0) {
      return (int *)0x0;
    }
    *puVar2 = DAT_0048a438;
    iVar4 = 0;
    DAT_0048a438 = puVar2;
    do {
      ppiVar1 = (int **)(puVar2 + iVar4 * 4 + 1);
      *ppiVar1 = (int *)DAT_0048a43c;
      iVar4 = iVar4 + 1;
      DAT_0048a43c = ppiVar1;
    } while (iVar4 != 100);
  }
  piVar3 = (int *)DAT_0048a43c;
  DAT_0048a43c = (int **)*DAT_0048a43c;
  return piVar3;
}

