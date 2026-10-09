/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004231e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004231e8(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  WPARAM WVar3;
  HWND pHVar4;
  uint lParam;
  BOOL BVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int iVar6;
  HWND hWnd;
  int iVar7;
  undefined4 *in_FS_OFFSET;
  HWND pHVar8;
  UINT UVar9;
  int iVar10;
  LPARAM lParam_00;
  undefined4 uStack_20;
  code *pcStack_1c;
  undefined *puStack_18;
  
  if (((*(byte *)(param_1 + 7) & 0x10) == 0) && ((*(byte *)((int)param_1 + 0x11d) & 4) != 0)) {
    puStack_18 = (undefined *)0x423218;
    uVar1 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)param_2 >> 8),1),0xf031);
    puStack_18 = (undefined *)0x42321d;
    FUN_004031f8(uVar1);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  *(byte *)((int)param_1 + 0x11d) = *(byte *)((int)param_1 + 0x11d) | 4;
  pcStack_1c = thunk_FUN_00403140;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
    if (*(char *)((int)param_1 + 199) == '\0') {
      uVar1 = *in_FS_OFFSET;
      *in_FS_OFFSET = &stack0xffffffd4;
      puStack_18 = &stack0xfffffffc;
      FUN_00402cdc(param_1,param_2,param_3);
      *in_FS_OFFSET = uVar1;
      if (*(int **)(DAT_0048a6fc + 0x40) == param_1) {
        FUN_004227b8(param_1,'\0');
      }
      if (*(char *)((int)param_1 + 0x11a) == '\x01') {
        FUN_00415130(param_1);
      }
      else if ((*(byte *)((int)param_1 + 0x11d) & 8) == 0) {
        hWnd = (HWND)0x0;
        pHVar4 = (HWND)FUN_00416cbc(param_1);
        pHVar8 = GetActiveWindow();
        if (pHVar4 == pHVar8) {
          pHVar4 = (HWND)FUN_00416cbc(param_1);
          BVar5 = IsIconic(pHVar4);
          if (BVar5 == 0) {
            iVar2 = FUN_00416cbc(param_1);
            hWnd = (HWND)FUN_0041f9b0(iVar2);
          }
        }
        if (hWnd == (HWND)0x0) {
          iVar2 = 0;
          pHVar4 = (HWND)FUN_00416cbc(param_1);
          ShowWindow(pHVar4,iVar2);
        }
        else {
          UVar9 = 0x97;
          iVar10 = 0;
          iVar7 = 0;
          iVar6 = 0;
          iVar2 = 0;
          pHVar8 = (HWND)0x0;
          pHVar4 = (HWND)FUN_00416cbc(param_1);
          SetWindowPos(pHVar4,pHVar8,iVar2,iVar6,iVar7,iVar10,UVar9);
          SetActiveWindow(hWnd);
        }
      }
      else {
        UVar9 = 0x97;
        iVar10 = 0;
        iVar7 = 0;
        iVar6 = 0;
        iVar2 = 0;
        pHVar8 = (HWND)0x0;
        pHVar4 = (HWND)FUN_00416cbc(param_1);
        SetWindowPos(pHVar4,pHVar8,iVar2,iVar6,iVar7,iVar10,UVar9);
      }
    }
    else {
      uVar1 = *in_FS_OFFSET;
      *in_FS_OFFSET = &stack0xffffffd4;
      puStack_18 = &stack0xfffffffc;
      FUN_00402cdc(param_1,param_2,param_3);
      *in_FS_OFFSET = uVar1;
      if (*(char *)((int)param_1 + 0x11b) == '\x04') {
        if (*(char *)((int)param_1 + 0x11a) == '\x01') {
          iVar2 = FUN_00413178(*(int **)(DAT_0048a6f8 + 0x28));
          iVar6 = iVar2 - param_1[0xb] >> 1;
          if (iVar6 < 0) {
            iVar6 = iVar6 + (uint)((iVar2 - param_1[0xb] & 1U) != 0);
          }
          iVar2 = FUN_004131bc(*(int **)(DAT_0048a6f8 + 0x28));
          iVar7 = iVar2 - param_1[0xc] >> 1;
          if (iVar7 < 0) {
            iVar7 = iVar7 + (uint)((iVar2 - param_1[0xc] & 1U) != 0);
          }
        }
        else {
          iVar2 = FUN_00423ba8();
          iVar6 = iVar2 - param_1[0xb] >> 1;
          if (iVar6 < 0) {
            iVar6 = iVar6 + (uint)((iVar2 - param_1[0xb] & 1U) != 0);
          }
          iVar2 = FUN_00423ba0();
          iVar7 = iVar2 - param_1[0xc] >> 1;
          if (iVar7 < 0) {
            iVar7 = iVar7 + (uint)((iVar2 - param_1[0xc] & 1U) != 0);
          }
        }
        if (iVar6 < 0) {
          iVar6 = 0;
        }
        if (iVar7 < 0) {
          iVar7 = 0;
        }
        (**(code **)(*param_1 + 0x4c))(param_1,iVar6,iVar7);
      }
      *(undefined *)((int)param_1 + 0x11b) = 0;
      if (*(char *)((int)param_1 + 0x11a) == '\x01') {
        if (*(char *)((int)param_1 + 0x116) == '\x02') {
          lParam_00 = 0;
          WVar3 = FUN_00416cbc(param_1);
          SendMessageA(*(HWND *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x134),0x223,WVar3,lParam_00);
          iVar2 = 3;
          pHVar4 = (HWND)FUN_00416cbc(param_1);
          ShowWindow(pHVar4,iVar2);
        }
        else {
          iVar2 = *(int *)((uint)*(byte *)((int)param_1 + 0x116) * 4 + 0x4895e4);
          pHVar4 = (HWND)FUN_00416cbc(param_1);
          ShowWindow(pHVar4,iVar2);
          lParam = param_1[0xc] << 0x10 | param_1[0xb];
          WVar3 = 0;
          UVar9 = 5;
          pHVar4 = (HWND)FUN_00416cbc(param_1);
          CallWindowProcA((WNDPROC)&DAT_00404eac,pHVar4,UVar9,WVar3,lParam);
          FUN_00413780(param_1,extraout_EDX_00,extraout_ECX_00);
        }
        SendMessageA(*(HWND *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x134),0x234,0,0);
      }
      else {
        iVar2 = *(int *)((uint)*(byte *)((int)param_1 + 0x116) * 4 + 0x4895e4);
        pHVar4 = (HWND)FUN_00416cbc(param_1);
        ShowWindow(pHVar4,iVar2);
      }
    }
  }
  *in_FS_OFFSET = uStack_20;
  *(byte *)((int)param_1 + 0x11d) = *(byte *)((int)param_1 + 0x11d) & 0xfb;
  return;
}

