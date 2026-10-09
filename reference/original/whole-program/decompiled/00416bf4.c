/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416bf4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416bf4(int param_1)

{
  tagRECT local_14;
  
  FUN_00413118(param_1,&local_14.left);
  InflateRect(&local_14,1,1);
  InvalidateRect(*(HWND *)(*(int *)(param_1 + 0x20) + 0xc0),&local_14,1);
  return;
}

