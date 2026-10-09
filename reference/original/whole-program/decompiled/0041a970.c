/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a970.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041a970(int param_1)

{
  if ((*(HDC *)(param_1 + 4) != (HDC)0x0) &&
     (*(byte *)(param_1 + 8) != (~DAT_0041a9c8 & *(byte *)(param_1 + 8)))) {
    SelectObject(*(HDC *)(param_1 + 4),DAT_0048a6d8);
    SelectObject(*(HDC *)(param_1 + 4),DAT_0048a6dc);
    SelectObject(*(HDC *)(param_1 + 4),DAT_0048a6e0);
    *(byte *)(param_1 + 8) = ~DAT_0041a9c8 & *(byte *)(param_1 + 8);
  }
  return;
}

