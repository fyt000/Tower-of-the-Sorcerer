/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042edb0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042edb0(int param_1,int *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  HWND pHVar2;
  undefined4 extraout_EDX;
  WPARAM WVar3;
  undefined4 *in_FS_OFFSET;
  UINT UVar4;
  WPARAM wParam;
  int ***pppiVar5;
  undefined4 uStack_38;
  undefined *puStack_34;
  undefined *puStack_30;
  int **ppiStack_20;
  int iStack_1c;
  code *pcStack_18;
  int *piStack_14;
  int *piStack_10;
  int *piStack_c;
  int iStack_8;
  
  piStack_14 = *(int **)(param_1 + 0x10);
  piStack_c = param_2;
  iStack_8 = param_1;
  if (piStack_14 == (int *)0x0) {
    puStack_30 = (undefined *)0x42ede3;
    piStack_14 = (int *)FUN_00402c0c(*(int *)(*(int *)(param_1 + 8) + 0x154),
                                     CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  }
  piStack_10 = piStack_14;
  puStack_34 = &LAB_0042eec5;
  uStack_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_38;
  ppiStack_20 = &piStack_10;
  pcStack_18 = root_0042ecbc;
  iStack_1c = 0;
  puStack_30 = &stack0xfffffffc;
  uVar1 = FUN_0040af00(param_2);
  if (*(char *)(iStack_8 + 0xc) == '\0') {
    WVar3 = 2;
  }
  else {
    WVar3 = 1;
  }
  pppiVar5 = &ppiStack_20;
  UVar4 = 0x449;
  wParam = WVar3;
  pHVar2 = (HWND)FUN_00416cbc(*(int **)(iStack_8 + 8));
  SendMessageA(pHVar2,UVar4,wParam,(LPARAM)pppiVar5);
  if ((WVar3 == 2) && (iStack_1c != 0)) {
    FUN_0040af10(param_2,uVar1);
    if (*(char *)(iStack_8 + 0xc) == '\0') {
      WVar3 = 1;
    }
    else {
      WVar3 = 2;
    }
    pppiVar5 = &ppiStack_20;
    UVar4 = 0x449;
    pHVar2 = (HWND)FUN_00416cbc(*(int **)(iStack_8 + 8));
    SendMessageA(pHVar2,UVar4,WVar3,(LPARAM)pppiVar5);
    if (iStack_1c != 0) {
      uVar1 = FUN_004074cc(0x411138,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf208);
      FUN_004031f8(uVar1);
    }
  }
  *in_FS_OFFSET = uStack_38;
  puStack_30 = &LAB_0042eecc;
  if (*(int *)(iStack_8 + 0x10) == 0) {
    puStack_34 = (undefined *)0x42eec4;
    FUN_00402c34(piStack_14);
  }
  return;
}

