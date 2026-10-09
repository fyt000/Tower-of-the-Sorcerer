/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412d4c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00412d4c(int *param_1)

{
  if (param_1[0xe] != 0) {
    FUN_0041a9d0(param_1,0);
    FUN_00409b2c(DAT_0048a6d0,(int)param_1);
    ReleaseDC((HWND)param_1[0xf],(HDC)param_1[0xe]);
    param_1[0xe] = 0;
  }
  return;
}

