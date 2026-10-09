/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416c74.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00416c74(int param_1)

{
  HWND pHVar1;
  
  if (*(int *)(param_1 + 0xc0) != 0) {
    pHVar1 = GetFocus();
    if (pHVar1 == *(HWND *)(param_1 + 0xc0)) {
      return CONCAT31((int3)((uint)pHVar1 >> 8),1);
    }
  }
  return 0;
}

