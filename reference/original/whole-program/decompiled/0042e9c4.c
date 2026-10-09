/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e9c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042e9c4(int param_1,WPARAM param_2,undefined4 param_3)

{
  HWND pHVar1;
  LRESULT LVar2;
  undefined *lParam;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *puVar6;
  undefined4 *in_FS_OFFSET;
  UINT UVar7;
  undefined4 *puVar8;
  WPARAM WVar9;
  LPARAM LVar10;
  WPARAM lParam_00;
  undefined **ppuVar11;
  undefined4 uStack_38;
  undefined *puStack_34;
  undefined *puStack_30;
  byte *pbStack_20;
  undefined4 uStack_1c;
  undefined uStack_18;
  undefined *puStack_14;
  WPARAM WStack_10;
  WPARAM WStack_c;
  undefined4 uStack_8;
  
  puStack_30 = &stack0xfffffffc;
  pbStack_20 = (byte *)0x0;
  puStack_14 = (undefined *)0x0;
  puStack_34 = &LAB_0042eb12;
  uStack_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_38;
  uStack_8 = param_3;
  if ((int)param_2 < 0) goto LAB_0042eaf4;
  LVar10 = 0;
  UVar7 = 0xbb;
  WVar9 = param_2;
  pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  WStack_10 = SendMessageA(pHVar1,UVar7,WVar9,LVar10);
  if ((int)WStack_10 < 0) {
    LVar10 = 0;
    param_2 = param_2 - 1;
    UVar7 = 0xbb;
    pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
    WVar9 = SendMessageA(pHVar1,UVar7,param_2,LVar10);
    WStack_10 = WVar9;
    if ((int)WVar9 < 0) goto LAB_0042eaf4;
    LVar10 = 0;
    UVar7 = 0xc1;
    pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
    LVar2 = SendMessageA(pHVar1,UVar7,WVar9,LVar10);
    if (LVar2 == 0) goto LAB_0042eaf4;
    WStack_10 = WStack_10 + LVar2;
    puVar6 = (undefined4 *)&DAT_0042eb28;
  }
  else {
    puVar6 = (undefined4 *)&DAT_0042eb20;
  }
  WStack_c = WStack_10;
  UVar7 = 0xb1;
  WVar9 = WStack_10;
  lParam_00 = WStack_10;
  pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  SendMessageA(pHVar1,UVar7,WVar9,lParam_00);
  ppuVar11 = &puStack_14;
  uStack_1c = uStack_8;
  uStack_18 = 0xb;
  puVar8 = &uStack_1c;
  FUN_00403608((int *)&pbStack_20,puVar6);
  FUN_0040661c(pbStack_20,puVar8,0,(int *)ppuVar11);
  lParam = FUN_00403814(puStack_14);
  WVar9 = 0;
  UVar7 = 0xc2;
  pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  SendMessageA(pHVar1,UVar7,WVar9,(LPARAM)lParam);
  iVar3 = FUN_0042882c(*(int **)(param_1 + 8),extraout_EDX,extraout_ECX);
  iVar4 = FUN_00403650((int)puStack_14);
  if (iVar3 != iVar4 + WStack_c) {
    uVar5 = FUN_004074cc(0x411138,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),0xf207);
    FUN_004031f8(uVar5);
  }
LAB_0042eaf4:
  *in_FS_OFFSET = uStack_38;
  puStack_30 = &LAB_0042eb19;
  puStack_34 = (undefined *)0x42eb09;
  FUN_004034dc((int *)&pbStack_20);
  puStack_34 = (undefined *)0x42eb11;
  FUN_004034dc((int *)&puStack_14);
  return;
}

