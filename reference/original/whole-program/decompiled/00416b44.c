/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416b44.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416b44(int *param_1,int *param_2)

{
  HWND pHVar1;
  HDC pHVar2;
  undefined4 uVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  HRGN hrgnClip;
  DWORD flags;
  
  if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    pHVar2 = GetDC(pHVar1);
    uVar3 = extraout_EDX_00;
  }
  else {
    flags = 0x12;
    hrgnClip = (HRGN)0x0;
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    pHVar2 = GetDCEx(pHVar1,hrgnClip,flags);
    uVar3 = extraout_EDX;
  }
  if (pHVar2 == (HDC)0x0) {
    uVar3 = FUN_004074cc(0x411138,CONCAT31((int3)((uint)uVar3 >> 8),1),0xf02a);
    FUN_004031f8(uVar3);
  }
  *param_2 = param_1[0x30];
  return;
}

