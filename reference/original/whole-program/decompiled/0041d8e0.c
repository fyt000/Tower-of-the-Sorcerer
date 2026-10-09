/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d8e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041d8e0(int param_1,int *param_2,int *param_3)

{
  HPALETTE hPal;
  bool bVar1;
  undefined4 uVar2;
  HDC pHVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  int hDest;
  int wDest;
  HDC hdcDest;
  undefined4 *in_FS_OFFSET;
  int xDest;
  int xSrc;
  int ySrc;
  int hSrc;
  DWORD rop;
  int iVar7;
  HPALETTE local_c;
  
  uVar2 = FUN_0041db44(param_1);
  if ((char)uVar2 == '\0') {
    iVar7 = 3;
    pHVar3 = (HDC)FUN_0041a950(param_2);
    SetStretchBltMode(pHVar3,iVar7);
  }
  if ((*(int *)(param_1 + 0x14) == 0) || (*(int *)(*(int *)(param_1 + 0x10) + 0xc) == 0)) {
    iVar7 = 0x26;
    pHVar3 = (HDC)FUN_0041a950(param_2);
    uVar4 = GetDeviceCaps(pHVar3,iVar7);
    if (((uVar4 & 0x2000) != 0) &&
       ((*(char *)(*(int *)(param_1 + 0x10) + 0x25) == '\x01' &&
        (*(int *)(*(int *)(param_1 + 0x10) + 8) != 0)))) {
      iVar7 = FUN_0040af1c(*(int **)(*(int *)(param_1 + 0x10) + 8));
      if (iVar7 != 0) {
        bVar1 = false;
        goto LAB_0041d956;
      }
    }
  }
  bVar1 = true;
LAB_0041d956:
  iVar7 = *(int *)(param_1 + 0x10);
  FUN_0041aa24(param_2,DAT_0041da7c);
  FUN_0041dc94(param_1);
  local_c = (HPALETTE)0x0;
  hPal = *(HPALETTE *)(iVar7 + 0x10);
  if (hPal != (HPALETTE)0x0) {
    local_c = SelectPalette((HDC)param_2[1],hPal,1);
    RealizePalette((HDC)param_2[1]);
  }
  uVar2 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffd8;
  if (bVar1) {
    piVar5 = (int *)FUN_0041dad8(param_1);
    FUN_0041aa24(piVar5,DAT_0041da7c);
    rop = param_2[8];
    hSrc = *(int *)(iVar7 + 0x18);
    iVar7 = *(int *)(iVar7 + 0x14);
    ySrc = 0;
    xSrc = 0;
    iVar6 = FUN_0041dad8(param_1);
    pHVar3 = *(HDC *)(iVar6 + 4);
    hDest = param_3[3] - param_3[1];
    wDest = param_3[2] - *param_3;
    iVar6 = param_3[1];
    xDest = *param_3;
    hdcDest = (HDC)FUN_0041a950(param_2);
    StretchBlt(hdcDest,xDest,iVar6,wDest,hDest,pHVar3,xSrc,ySrc,iVar7,hSrc,rop);
  }
  else {
    StretchDIBits((HDC)param_2[1],*param_3,param_3[1],param_3[2] - *param_3,param_3[3] - param_3[1],
                  0,0,*(int *)(iVar7 + 0x14),*(int *)(iVar7 + 0x18),*(void **)(iVar7 + 0x20),
                  *(BITMAPINFO **)(iVar7 + 0x1c),0,param_2[8]);
  }
  *in_FS_OFFSET = uVar2;
  if (hPal != (HPALETTE)0x0) {
    SelectPalette((HDC)param_2[1],local_c,1);
  }
  return;
}

