/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417488.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00417488(int *param_1,undefined4 *param_2,uint *param_3)

{
  HWND hWnd;
  int iVar1;
  int *piVar2;
  HWND hWndInsertAfter;
  int Y;
  int cx;
  int cy;
  UINT uFlags;
  int aiStack_1c [4];
  
  piVar2 = aiStack_1c;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = *param_2;
    param_2 = param_2 + 1;
    piVar2 = piVar2 + 1;
  }
  FUN_004135d4(param_1,param_3);
  FUN_00413138(param_1,aiStack_1c);
  iVar1 = FUN_00423ba0();
  if (iVar1 < aiStack_1c[1] + param_1[0xc]) {
    aiStack_1c[1] = FUN_00423ba0();
    aiStack_1c[1] = aiStack_1c[1] - param_1[0xc];
  }
  iVar1 = FUN_00423ba8();
  if (iVar1 < aiStack_1c[0] + param_1[0xb]) {
    aiStack_1c[0] = FUN_00423ba8();
    aiStack_1c[0] = aiStack_1c[0] - param_1[0xb];
  }
  if (aiStack_1c[0] < 0) {
    aiStack_1c[0] = 0;
  }
  if (aiStack_1c[3] < 0) {
    aiStack_1c[3] = 0;
  }
  uFlags = 0x51;
  cy = 0;
  cx = 0;
  hWndInsertAfter = (HWND)0xffffffff;
  iVar1 = aiStack_1c[0];
  Y = aiStack_1c[1];
  hWnd = (HWND)FUN_00416cbc(param_1);
  SetWindowPos(hWnd,hWndInsertAfter,iVar1,Y,cx,cy,uFlags);
  return;
}

