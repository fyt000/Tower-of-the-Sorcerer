/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004241e4.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004241e4(int param_1)

{
  ATOM AVar1;
  undefined *puVar2;
  BOOL BVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  LPCSTR pCVar8;
  LPARAM lParam;
  undefined in_CL;
  undefined in_DL;
  undefined4 extraout_EDX;
  LPVOID pvVar9;
  HINSTANCE pHVar10;
  HMENU pHVar11;
  HWND pHVar12;
  int iVar13;
  int iVar14;
  tagWNDCLASSA tStack_2c;
  
  if (*(char *)(param_1 + 0x7e) == '\0') {
    puVar2 = FUN_0041fd4c((char)param_1,in_DL,in_CL,&LAB_0042457c,param_1);
    *(undefined **)(param_1 + 0x24) = puVar2;
    BVar3 = GetClassInfoA(DAT_0048a014,PTR_s_TApplication_00489660,&tStack_2c);
    if (BVar3 == 0) {
      _DAT_0048964c = DAT_0048a014;
      AVar1 = RegisterClassA((WNDCLASSA *)&DAT_0048963c);
      if (AVar1 == 0) {
        uVar4 = FUN_004074cc(0x411138,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf02c);
        FUN_004031f8(uVar4);
      }
    }
    uVar5 = GetSystemMetrics(0);
    iVar6 = (int)uVar5 >> 1;
    if (iVar6 < 0) {
      iVar6 = iVar6 + (uint)((uVar5 & 1) != 0);
    }
    uVar5 = GetSystemMetrics(1);
    iVar7 = (int)uVar5 >> 1;
    if (iVar7 < 0) {
      iVar7 = iVar7 + (uint)((uVar5 & 1) != 0);
    }
    iVar14 = 0;
    iVar13 = 0;
    pHVar12 = (HWND)0x0;
    pHVar11 = (HMENU)0x0;
    pvVar9 = (LPVOID)0x0;
    pHVar10 = DAT_0048a014;
    pCVar8 = FUN_00403814(*(undefined **)(param_1 + 0x6c));
    uVar4 = FUN_0040530c(PTR_s_TApplication_00489660,pCVar8,0x94ca0000,pvVar9,pHVar10,pHVar11,
                         pHVar12,iVar13,iVar14,iVar7,iVar6);
    *(undefined4 *)(param_1 + 0x20) = uVar4;
    FUN_004034dc((int *)(param_1 + 0x6c));
    *(undefined *)(param_1 + 0x7e) = 1;
    FUN_00423fbc(*(HWND *)(param_1 + 0x20),9);
    SetWindowLongA(*(HWND *)(param_1 + 0x20),-4,*(LONG *)(param_1 + 0x24));
    if (DAT_0048a694 != '\0') {
      lParam = FUN_00424ae8(param_1);
      SendMessageA(*(HWND *)(param_1 + 0x20),0x80,1,lParam);
    }
    pHVar11 = GetSystemMenu(*(HWND *)(param_1 + 0x20),0);
    DeleteMenu(pHVar11,0xf030,0);
    DeleteMenu(pHVar11,0xf000,0);
    if (DAT_0048a694 != '\0') {
      DeleteMenu(pHVar11,0xf010,0);
    }
  }
  return;
}

