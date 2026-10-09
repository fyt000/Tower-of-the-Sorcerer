/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424cd8.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00424cd8(int param_1,HWND *param_2)

{
  int *piVar1;
  HWND pHVar2;
  LRESULT LVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  if ((0xff < (int)param_2[1]) && ((int)param_2[1] < 0x109)) {
    pHVar2 = GetCapture();
    if (pHVar2 == (HWND)0x0) {
      pHVar2 = *param_2;
      piVar1 = *(int **)(param_1 + 0x28);
      if ((piVar1 != (int *)0x0) && (pHVar2 == (HWND)piVar1[0x4d])) {
        pHVar2 = (HWND)FUN_00416cbc(piVar1);
      }
      LVar3 = SendMessageA(pHVar2,(UINT)(param_2[1] + 0x2f00),(WPARAM)param_2[2],(LPARAM)param_2[3])
      ;
      if (LVar3 != 0) {
        uVar4 = 1;
      }
    }
  }
  return uVar4;
}

