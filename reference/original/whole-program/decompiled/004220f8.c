/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004220f8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004220f8(int *param_1)

{
  LPARAM LVar1;
  HWND pHVar2;
  undefined *puVar3;
  LONG LVar4;
  undefined extraout_CL;
  undefined extraout_DL;
  HWND hWndInsertAfter;
  int iVar5;
  int iVar6;
  UINT UVar7;
  int iVar8;
  WPARAM WVar9;
  int iVar10;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  FUN_00420674(param_1);
  if (DAT_0048a694 != '\0') {
    if (*(char *)((int)param_1 + 0x115) == '\x03') {
      LVar1 = 0;
      WVar9 = 1;
      UVar7 = 0x80;
      pHVar2 = (HWND)FUN_00416cbc(param_1);
      SendMessageA(pHVar2,UVar7,WVar9,LVar1);
    }
    else {
      LVar1 = FUN_00422934((int)param_1);
      WVar9 = 1;
      UVar7 = 0x80;
      pHVar2 = (HWND)FUN_00416cbc(param_1);
      SendMessageA(pHVar2,UVar7,WVar9,LVar1);
    }
  }
  if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
    if (*(char *)((int)param_1 + 0x11a) == '\x02') {
      uStack_c = 0xff00;
      uStack_10 = 0;
      if (param_1[0x4e] != 0) {
        uStack_10 = FUN_0041021c(param_1[0x4e]);
      }
      iVar10 = 0;
      iVar8 = 0;
      iVar5 = FUN_00413178(param_1);
      iVar6 = FUN_004131bc(param_1);
      pHVar2 = (HWND)FUN_00416cbc(param_1);
      iVar5 = FUN_0040530c("MDICLIENT",(LPCSTR)0x0,0x56330001,&uStack_10,DAT_0048a014,(HMENU)0x0,
                           pHVar2,iVar6,iVar5,iVar8,iVar10);
      param_1[0x4d] = iVar5;
      puVar3 = FUN_0041fd4c((char)iVar5,extraout_DL,extraout_CL,root_00421868,param_1);
      param_1[0x56] = (int)puVar3;
      LVar4 = GetWindowLongA((HWND)param_1[0x4d],-4);
      param_1[0x55] = LVar4;
      SetWindowLongA((HWND)param_1[0x4d],-4,param_1[0x56]);
    }
    else if (*(char *)((int)param_1 + 0x11a) == '\x03') {
      UVar7 = 0x13;
      iVar10 = 0;
      iVar8 = 0;
      iVar6 = 0;
      iVar5 = 0;
      hWndInsertAfter = (HWND)0xffffffff;
      pHVar2 = (HWND)FUN_00416cbc(param_1);
      SetWindowPos(pHVar2,hWndInsertAfter,iVar5,iVar6,iVar8,iVar10,UVar7);
    }
  }
  return;
}

