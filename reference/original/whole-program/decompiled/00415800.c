/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415800.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00415800(int param_1,HDC param_2,int param_3)

{
  int *piVar1;
  BOOL BVar2;
  int nSavedDC;
  int iVar3;
  COLORREF CVar4;
  HBRUSH pHVar5;
  int iVar6;
  HBRUSH pHVar7;
  int local_24;
  RECT local_20;
  
  if (*(int *)(param_1 + 0xb0) != 0) {
    iVar6 = 0;
    if ((param_3 != 0) && (iVar6 = FUN_00409a88(*(int *)(param_1 + 0xb0),param_3), iVar6 < 0)) {
      iVar6 = 0;
    }
    iVar3 = *(int *)(*(int *)(param_1 + 0xb0) + 8);
    for (; iVar6 < iVar3; iVar6 = iVar6 + 1) {
      piVar1 = (int *)FUN_00409a40(*(undefined4 **)(param_1 + 0xb0),iVar6);
      if ((*(char *)((int)piVar1 + 0x37) != '\0') ||
         (((*(byte *)(piVar1 + 7) & 0x10) != 0 && ((*(byte *)((int)piVar1 + 0x35) & 4) == 0)))) {
        FUN_0040923c(piVar1[9],piVar1[10],piVar1[9] + piVar1[0xb],&local_20.left,
                     piVar1[10] + piVar1[0xc]);
        BVar2 = RectVisible(param_2,&local_20);
        if (BVar2 != 0) {
          if ((*(byte *)(param_1 + 0x36) & 0x80) != 0) {
            *(byte *)((int)piVar1 + 0x36) = *(byte *)((int)piVar1 + 0x36) | 0x80;
          }
          nSavedDC = SaveDC(param_2);
          FUN_00412c74(param_2,piVar1[9],piVar1[10]);
          IntersectClipRect(param_2,0,0,piVar1[0xb],piVar1[0xc]);
          FUN_00413cb8(piVar1,0xf,param_2,0);
          RestoreDC(param_2,nSavedDC);
          *(byte *)((int)piVar1 + 0x36) = *(byte *)((int)piVar1 + 0x36) & 0x7f;
        }
      }
    }
  }
  if ((*(int *)(param_1 + 0xb4) != 0) &&
     (local_24 = *(int *)(*(int *)(param_1 + 0xb4) + 8), -1 < local_24 + -1)) {
    iVar6 = 0;
    do {
      iVar3 = FUN_00409a40(*(undefined4 **)(param_1 + 0xb4),iVar6);
      if (((*(char *)(iVar3 + 0xc5) != '\0') && ((*(byte *)(iVar3 + 0x34) & 0x10) != 0)) &&
         ((*(char *)(iVar3 + 0x37) != '\0' ||
          (((*(byte *)(iVar3 + 0x1c) & 0x10) != 0 && ((*(byte *)(iVar3 + 0x35) & 4) == 0)))))) {
        CVar4 = FUN_00419b00(0x80000010);
        pHVar5 = CreateSolidBrush(CVar4);
        pHVar7 = pHVar5;
        FUN_0040923c(*(int *)(iVar3 + 0x24) + -1,*(int *)(iVar3 + 0x28) + -1,
                     *(int *)(iVar3 + 0x24) + *(int *)(iVar3 + 0x2c),&local_20.left,
                     *(int *)(iVar3 + 0x28) + *(int *)(iVar3 + 0x30));
        FrameRect(param_2,&local_20,pHVar7);
        DeleteObject(pHVar5);
        CVar4 = FUN_00419b00(0x80000014);
        pHVar5 = CreateSolidBrush(CVar4);
        pHVar7 = pHVar5;
        FUN_0040923c(*(undefined4 *)(iVar3 + 0x24),*(undefined4 *)(iVar3 + 0x28),
                     *(int *)(iVar3 + 0x24) + *(int *)(iVar3 + 0x2c) + 1,&local_20.left,
                     *(int *)(iVar3 + 0x28) + *(int *)(iVar3 + 0x30) + 1);
        FrameRect(param_2,&local_20,pHVar7);
        DeleteObject(pHVar5);
      }
      iVar6 = iVar6 + 1;
      local_24 = local_24 + -1;
    } while (local_24 != 0);
  }
  return;
}

