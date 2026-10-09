/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c5b0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041c5b0(int *param_1)

{
  if ((param_1 != (int *)0x0) && (param_1[1] = param_1[1] + -1, param_1[1] == 0)) {
    if ((HENHMETAFILE)param_1[2] != (HENHMETAFILE)0x0) {
      DeleteEnhMetaFile((HENHMETAFILE)param_1[2]);
    }
    if ((HGDIOBJ)param_1[5] != (HGDIOBJ)0x0) {
      DeleteObject((HGDIOBJ)param_1[5]);
    }
    FUN_00402c34(param_1);
  }
  return;
}

