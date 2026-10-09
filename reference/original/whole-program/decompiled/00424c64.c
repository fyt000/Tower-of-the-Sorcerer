/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424c64.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00424c64(int param_1,LPMSG param_2)

{
  BOOL BVar1;
  bool bVar2;
  
  bVar2 = false;
  if (*(HWND *)(param_1 + 0x88) != (HWND)0x0) {
    BVar1 = IsDialogMessageA(*(HWND *)(param_1 + 0x88),param_2);
    bVar2 = BVar1 != 0;
  }
  return bVar2;
}

