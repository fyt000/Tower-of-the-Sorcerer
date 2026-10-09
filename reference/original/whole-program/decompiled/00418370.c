/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00418370.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00418370(int param_1)

{
  bool bVar1;
  
  bVar1 = FUN_00417800(param_1);
  if ((bVar1) && (*(int *)(param_1 + 0x40) != 0)) {
    ImageList_DragLeave(*(HWND *)(param_1 + 0x40));
    *(undefined4 *)(param_1 + 0x40) = 0;
  }
  return;
}

