/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428da0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00428da0(int param_1,WPARAM param_2,undefined4 *param_3)

{
  HWND pHVar1;
  WPARAM WVar2;
  LRESULT LVar3;
  undefined *lParam;
  undefined4 *in_FS_OFFSET;
  UINT UVar4;
  WPARAM WVar5;
  LPARAM LVar6;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined *local_c;
  undefined4 *local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_c = (undefined *)0x0;
  puStack_20 = &LAB_00428e8b;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  local_8 = param_3;
  if ((int)param_2 < 0) goto LAB_00428e75;
  LVar6 = 0;
  UVar4 = 0xbb;
  WVar2 = param_2;
  pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  WVar2 = SendMessageA(pHVar1,UVar4,WVar2,LVar6);
  if ((int)WVar2 < 0) {
    LVar6 = 0;
    WVar2 = param_2 - 1;
    UVar4 = 0xbb;
    pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
    WVar2 = SendMessageA(pHVar1,UVar4,WVar2,LVar6);
    if ((int)WVar2 < 0) goto LAB_00428e75;
    LVar6 = 0;
    UVar4 = 0xc1;
    WVar5 = WVar2;
    pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
    LVar3 = SendMessageA(pHVar1,UVar4,WVar5,LVar6);
    if (LVar3 == 0) goto LAB_00428e75;
    WVar2 = WVar2 + LVar3;
    FUN_0040369c((int *)&local_c,(undefined4 *)&LAB_00428ea4,local_8);
  }
  else {
    FUN_0040369c((int *)&local_c,local_8,(undefined4 *)&LAB_00428ea4);
  }
  UVar4 = 0xb1;
  WVar5 = WVar2;
  pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  SendMessageA(pHVar1,UVar4,WVar2,WVar5);
  lParam = FUN_00403814(local_c);
  WVar2 = 0;
  UVar4 = 0xc2;
  pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  SendMessageA(pHVar1,UVar4,WVar2,(LPARAM)lParam);
LAB_00428e75:
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_00428e92;
  puStack_20 = (undefined *)0x428e8a;
  FUN_004034dc((int *)&local_c);
  return;
}

