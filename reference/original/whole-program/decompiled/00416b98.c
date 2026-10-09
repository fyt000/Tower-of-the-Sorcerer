/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416b98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416b98(int param_1)

{
  bool bVar1;
  
  bVar1 = FUN_00416e54(param_1);
  if (bVar1) {
    InvalidateRect(*(HWND *)(param_1 + 0xc0),(RECT *)0x0,
                   (uint)((*(byte *)(param_1 + 0x34) & 0x40) == 0));
  }
  return;
}

