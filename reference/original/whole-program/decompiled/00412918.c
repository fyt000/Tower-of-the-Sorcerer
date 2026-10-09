/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412918.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00412918(undefined4 *param_1,char param_2)

{
  HWND pHVar1;
  HWND extraout_ECX;
  HWND extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar2;
  int iVar3;
  
  DAT_0048a6a8 = 0;
  DAT_0048a6a0 = param_1;
  GetCursorPos((LPPOINT)&DAT_0048a6b4);
  DAT_0048a6c4 = GetCursor();
  DAT_0048a6c8 = param_2;
  DAT_0048a6cc = (int *)(**(code **)*DAT_0048a6a0)();
  DAT_0048a6b0 = FUN_00412528();
  pHVar1 = extraout_ECX;
  uVar2 = extraout_EDX;
  if ((DAT_0048a6c8 != '\0') && (DAT_0048a6cc != (int *)0x0)) {
    iVar3 = DAT_0048a6b8;
    pHVar1 = GetDesktopWindow();
    FUN_004182b0(DAT_0048a6cc,pHVar1,DAT_0048a6b4,iVar3);
    pHVar1 = extraout_ECX_00;
    uVar2 = extraout_EDX_00;
  }
  if (DAT_0048a6c8 != '\0') {
    FUN_004127b4((POINT *)&DAT_0048a6b4,uVar2,pHVar1);
  }
  return;
}

