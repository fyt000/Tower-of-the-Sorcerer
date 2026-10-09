/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00418408.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00418408(int param_1)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = FUN_00417800(param_1);
  if ((bVar1) && (*(char *)(param_1 + 0x44) != '\0')) {
    iVar2 = FUN_00418370(param_1);
    ImageList_EndDrag();
    bVar1 = iVar2 != 0;
    *(undefined *)(param_1 + 0x44) = 0;
    FUN_0041825c(param_1,-1);
    ShowCursor(1);
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

