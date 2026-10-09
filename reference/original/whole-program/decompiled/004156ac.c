/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004156ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004156ac(int *param_1,int param_2)

{
  HWND pHVar1;
  HDC hdc;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar5;
  tagPAINTSTRUCT *ptVar6;
  tagPAINTSTRUCT local_54;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  hdc = *(HDC *)(param_2 + 4);
  local_c = param_2;
  local_8 = param_1;
  if (hdc == (HDC)0x0) {
    ptVar6 = &local_54;
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    hdc = BeginPaint(pHVar1,ptVar6);
  }
  uVar5 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffff94;
  if (local_8[0x2c] == 0) {
    (**(code **)(*local_8 + 0x70))(local_8,hdc);
  }
  else {
    local_14 = SaveDC(hdc);
    local_10 = 2;
    iVar4 = *(int *)(local_8[0x2c] + 8);
    if (-1 < iVar4 + -1) {
      iVar3 = 0;
      do {
        iVar2 = FUN_00409a40((undefined4 *)local_8[0x2c],iVar3);
        if (((*(char *)(iVar2 + 0x37) != '\0') ||
            (((*(byte *)(iVar2 + 0x1c) & 0x10) != 0 && ((*(byte *)(iVar2 + 0x35) & 4) == 0)))) &&
           ((*(byte *)(iVar2 + 0x34) & 0x40) != 0)) {
          local_10 = ExcludeClipRect(hdc,*(int *)(iVar2 + 0x24),*(int *)(iVar2 + 0x28),
                                     *(int *)(iVar2 + 0x24) + *(int *)(iVar2 + 0x2c),
                                     *(int *)(iVar2 + 0x28) + *(int *)(iVar2 + 0x30));
          if (local_10 == 1) break;
        }
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    if (local_10 != 1) {
      (**(code **)(*local_8 + 0x70))(local_8,hdc);
    }
    RestoreDC(hdc,local_14);
  }
  FUN_00415800((int)local_8,hdc,0);
  *in_FS_OFFSET = uVar5;
  if (*(int *)(local_c + 4) == 0) {
    ptVar6 = &local_54;
    pHVar1 = (HWND)FUN_00416cbc(local_8);
    EndPaint(pHVar1,ptVar6);
  }
  return;
}

