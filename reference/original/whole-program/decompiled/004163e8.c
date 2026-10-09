/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004163e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004163e8(int *param_1)

{
  HWND pHVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  tagPOINT tStack_c;
  
  pHVar1 = GetCapture();
  if (pHVar1 == (HWND)0x0) {
    GetCursorPos(&tStack_c);
    piVar2 = FUN_00412be8(&tStack_c,0);
    if (param_1 == piVar2) {
      uVar4 = 1;
      iVar3 = FUN_00416cbc(param_1);
      FUN_00413cb8(param_1,0x20,iVar3,uVar4);
    }
  }
  return;
}

