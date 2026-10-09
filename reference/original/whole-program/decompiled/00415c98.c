/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415c98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00415c98(int *param_1,int param_2)

{
  int *piVar1;
  HCURSOR hCursor;
  HWND pHVar2;
  HWND pHVar3;
  short sVar4;
  tagPOINT tStack_1c;
  int local_14 [2];
  
  if (*(int *)(param_2 + 4) == param_1[0x30]) {
    if (*(short *)(param_2 + 8) == -2) {
      if ((*(short *)(param_2 + 10) == 0x201) && (*(int *)(DAT_0048a6f8 + 0x20) != 0)) {
        pHVar2 = GetLastActivePopup(*(HWND *)(DAT_0048a6f8 + 0x20));
        pHVar3 = GetForegroundWindow();
        if (pHVar2 != pHVar3) {
          FUN_00424bb0(DAT_0048a6f8);
          return;
        }
      }
    }
    else if (*(short *)(param_2 + 8) == 1) {
      if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
        sVar4 = *(short *)(DAT_0048a6fc + 0x28);
        if (sVar4 == 0) {
          GetCursorPos(&tStack_1c);
          FUN_00413278(param_1,&tStack_1c.x,local_14);
          piVar1 = FUN_00415350((int)param_1,local_14,0);
          if (piVar1 != (int *)0x0) {
            sVar4 = *(short *)(piVar1 + 0x13);
          }
          if (sVar4 == 0) {
            sVar4 = *(short *)(param_1 + 0x13);
          }
        }
      }
      else {
        sVar4 = -2;
      }
      if (sVar4 != 0) {
        hCursor = (HCURSOR)FUN_00423d24(DAT_0048a6fc,(int)sVar4);
        SetCursor(hCursor);
        *(undefined4 *)(param_2 + 0xc) = 1;
        return;
      }
    }
  }
  (**(code **)(*param_1 + -0x10))(param_1,param_2);
  return;
}

