/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004139dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004139dc(int *param_1)

{
  bool bVar1;
  HWND pHVar2;
  HDC hdc;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar3;
  
  if (((*(char *)((int)param_1 + 0x37) != '\0') ||
      (((*(byte *)(param_1 + 7) & 0x10) != 0 && ((*(byte *)((int)param_1 + 0x35) & 4) == 0)))) &&
     (param_1[8] != 0)) {
    bVar1 = FUN_00416e54(param_1[8]);
    if (bVar1) {
      if ((*(byte *)(param_1 + 0xd) & 0x40) != 0) {
        pHVar2 = (HWND)FUN_00416cbc((int *)param_1[8]);
        hdc = GetDC(pHVar2);
        uVar3 = *in_FS_OFFSET;
        *in_FS_OFFSET = &stack0xffffffe4;
        IntersectClipRect(hdc,param_1[9],param_1[10],param_1[9] + param_1[0xb],
                          param_1[10] + param_1[0xc]);
        FUN_00415800(param_1[8],hdc,(int)param_1);
        *in_FS_OFFSET = uVar3;
        pHVar2 = (HWND)FUN_00416cbc((int *)param_1[8]);
        ReleaseDC(pHVar2,hdc);
        return;
      }
      (**(code **)(*param_1 + 0x44))();
      (**(code **)(*param_1 + 0x50))();
    }
  }
  return;
}

