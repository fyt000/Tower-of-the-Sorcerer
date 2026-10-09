/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430420.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00430420(int *param_1,byte param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  HWND pHVar9;
  HWND pHVar10;
  HDC hDC;
  int *piVar11;
  int *piVar12;
  tagRECT *lprc;
  int iStack_48;
  int iStack_44;
  tagRECT tStack_40;
  int aiStack_30 [4];
  int aiStack_20 [4];
  
  if ((*(char *)((int)param_1 + 0x19d) == '\0') || (param_2 != *(byte *)((int)param_1 + 0x19e))) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  piVar1 = (int *)param_1[0x40];
  FUN_0041a20c((int *)piVar1[5],'\0');
  FUN_0041a154((int *)piVar1[5],0x8000000f);
  FUN_00419fa8((int *)piVar1[4],0x80000006);
  FUN_0041a060((int *)piVar1[4],1);
  FUN_0041a73c(piVar1,param_3,0,param_1[0xc],param_1[0x6c] + param_3);
  if (bVar3) {
    FUN_00419fa8((int *)piVar1[4],0x80000010);
    FUN_0041a6d8(piVar1,param_3 + 1,param_1[0xc] + -2);
    FUN_0041a6a0(piVar1,param_3 + 1,1);
    FUN_0041a6a0(piVar1,param_1[0x6c] + param_3 + -1,1);
  }
  else {
    FUN_00419fa8((int *)piVar1[4],0x80000014);
    FUN_0041a6d8(piVar1,param_3 + 1,param_1[0xc] + -2);
    FUN_0041a6a0(piVar1,param_3 + 1,1);
    FUN_0041a6a0(piVar1,param_1[0x6c] + param_3 + -1,1);
    FUN_00419fa8((int *)piVar1[4],0x80000010);
    FUN_0041a6d8(piVar1,param_3 + 2,param_1[0xc] + -2);
    FUN_0041a6a0(piVar1,param_1[0x6c] + param_3 + -2,param_1[0xc] + -2);
    FUN_0041a6a0(piVar1,param_1[0x6c] + param_3 + -2,1);
  }
  if ((*(char *)(param_1 + 0xe) == '\0') && ((*(byte *)(param_1 + 7) & 0x10) == 0)) {
    iVar4 = 1;
  }
  else if ((*(char *)(param_1 + 0x84) == '\0') || ((*(byte *)(param_1 + 7) & 0x10) != 0)) {
    if (*(char *)((int)param_1 + (uint)param_2 * 0x10 + 0x105) == '\0') {
      iVar4 = 1;
    }
    else {
      iVar4 = 0;
      if (*(char *)((int)param_1 + (uint)param_2 * 0x10 + 0x106) != '\0') {
        iVar4 = 2;
      }
    }
  }
  else if (*(char *)((int)param_1 + (uint)param_2 * 0x10 + 0x107) == '\0') {
    iVar4 = 1;
  }
  else {
    iVar4 = 0;
    if (*(char *)((int)param_1 + (uint)param_2 * 0x10 + 0x106) != '\0') {
      iVar4 = 2;
    }
  }
  piVar2 = (int *)param_1[(uint)param_2 * 4 + iVar4 + 0x42];
  uVar5 = (**(code **)(*piVar2 + 0x20))();
  iVar4 = (int)uVar5 >> 1;
  if (iVar4 < 0) {
    iVar4 = iVar4 + (uint)((uVar5 & 1) != 0);
  }
  iStack_48 = param_1[0x6c] >> 1;
  if (iStack_48 < 0) {
    iStack_48 = iStack_48 + (uint)((param_1[0x6c] & 1U) != 0);
  }
  iStack_48 = iStack_48 - iVar4;
  uVar5 = (**(code **)(*piVar2 + 0x1c))();
  iVar4 = (int)uVar5 >> 1;
  if (iVar4 < 0) {
    iVar4 = iVar4 + (uint)((uVar5 & 1) != 0);
  }
  iStack_44 = param_1[0xc] >> 1;
  if (iStack_44 < 0) {
    iStack_44 = iStack_44 + (uint)((param_1[0xc] & 1U) != 0);
  }
  iStack_44 = iStack_44 - iVar4;
  if (bVar3) {
    iStack_48 = iStack_48 + 1;
    iStack_44 = iStack_44 + 1;
  }
  uVar6 = (**(code **)(*piVar2 + 0x1c))();
  piVar12 = aiStack_30;
  uVar7 = (**(code **)(*piVar2 + 0x20))();
  FUN_0040923c(0,0,uVar7,piVar12,uVar6);
  piVar12 = aiStack_30;
  uVar5 = 0x8080;
  iVar4 = (**(code **)(*piVar2 + 0x1c))();
  piVar11 = aiStack_20;
  iVar8 = (**(code **)(*piVar2 + 0x20))();
  FUN_00409258(iStack_48 + param_3,iStack_44,iVar8,piVar11,iVar4);
  FUN_0041a32c(piVar1,aiStack_20,(int)piVar2,uVar5,piVar12);
  pHVar9 = (HWND)FUN_00416cbc(param_1);
  pHVar10 = GetFocus();
  if ((pHVar9 == pHVar10) && (param_2 == *(byte *)(param_1 + 0x75))) {
    FUN_00409258(param_3,0,param_1[0x6c],&tStack_40.left,param_1[0xc]);
    InflateRect(&tStack_40,-3,-3);
    if (bVar3) {
      OffsetRect(&tStack_40,1,1);
    }
    lprc = &tStack_40;
    hDC = (HDC)FUN_0041a950((int *)param_1[0x40]);
    DrawFocusRect(hDC,lprc);
  }
  return;
}

