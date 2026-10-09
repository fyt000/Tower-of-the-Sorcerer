/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00425020.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00425020(int param_1,undefined4 param_2)

{
  HWND pHVar1;
  int **ppiVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  
  pHVar1 = GetCapture();
  if (pHVar1 != (HWND)0x0) {
    lParam = 0;
    wParam = 0;
    Msg = 0x1f;
    pHVar1 = GetCapture();
    SendMessageA(pHVar1,Msg,wParam,lParam);
  }
  ppiVar2 = (int **)root_00407298();
  piVar3 = FUN_00402c7c(ppiVar2,(int *)&DAT_00405390);
  if ((char)piVar3 == '\0') {
    iVar5 = root_004072b8();
    ppiVar2 = (int **)root_00407298();
    FUN_00407314(ppiVar2,iVar5);
  }
  else {
    ppiVar2 = (int **)root_00407298();
    piVar3 = FUN_00402c7c(ppiVar2,(int *)&UNK_004053e0);
    if ((char)piVar3 == '\0') {
      if (*(short *)(param_1 + 0x8e) == 0) {
        iVar5 = root_00407298();
        FUN_00425120(param_1,iVar5);
        return;
      }
      uVar4 = root_00407298();
      (**(code **)(param_1 + 0x8c))(*(undefined4 *)(param_1 + 0x90),param_2,uVar4);
    }
  }
  return;
}

