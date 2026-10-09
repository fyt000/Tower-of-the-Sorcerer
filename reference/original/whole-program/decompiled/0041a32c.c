/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a32c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041a32c(int *param_1,int *param_2,int param_3,uint param_4,int *param_5)

{
  int wSrc;
  int hSrc;
  int iVar1;
  int *piVar2;
  COLORREF CVar3;
  int iVar4;
  int iVar5;
  COLORREF color;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  int x;
  int y;
  int iVar6;
  int iVar7;
  HDC hdcSrc;
  DWORD DVar8;
  
  if (param_3 != 0) {
    (**(code **)(*param_1 + 0x10))();
    wSrc = param_5[2] - *param_5;
    hSrc = param_5[3] - param_5[1];
    FUN_0041aa24(param_1,DAT_0041a528);
    if (DAT_004894f8 == (int *)0x0) {
      DAT_004894f8 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                                         extraout_ECX);
      FUN_0041e1ec((int)DAT_004894f8,'\x01');
    }
    iVar1 = (**(code **)(*DAT_004894f8 + 0x20))();
    if (iVar1 < wSrc) {
      (**(code **)(*DAT_004894f8 + 0x2c))(DAT_004894f8,wSrc);
    }
    iVar1 = (**(code **)(*DAT_004894f8 + 0x1c))();
    if (iVar1 < hSrc) {
      (**(code **)(*DAT_004894f8 + 0x28))(DAT_004894f8,hSrc);
    }
    piVar2 = (int *)FUN_0041dad8((int)DAT_004894f8);
    FUN_0041aa24(piVar2,DAT_0041a528);
    piVar2 = (int *)FUN_0041dad8(param_3);
    FUN_0041aa24(piVar2,DAT_0041a528);
    CVar3 = FUN_00419b00(param_4);
    iVar1 = FUN_0041dad8(param_3);
    CVar3 = SetBkColor(*(HDC *)(iVar1 + 4),CVar3);
    DVar8 = 0xcc0020;
    iVar1 = param_5[1];
    iVar7 = *param_5;
    iVar4 = FUN_0041dad8(param_3);
    hdcSrc = *(HDC *)(iVar4 + 4);
    y = 0;
    x = 0;
    iVar4 = wSrc;
    iVar6 = hSrc;
    iVar5 = FUN_0041dad8((int)DAT_004894f8);
    BitBlt(*(HDC *)(iVar5 + 4),x,y,iVar4,iVar6,hdcSrc,iVar7,iVar1,DVar8);
    iVar1 = FUN_0041dad8(param_3);
    SetBkColor(*(HDC *)(iVar1 + 4),CVar3);
    FUN_0041aa24(param_1,DAT_0041a52c);
    DVar8 = 0xcc0020;
    iVar1 = param_5[1];
    iVar7 = *param_5;
    iVar4 = wSrc;
    iVar6 = hSrc;
    iVar5 = FUN_0041dad8(param_3);
    StretchBlt((HDC)param_1[1],*param_2,param_2[1],param_2[2] - *param_2,param_2[3] - param_2[1],
               *(HDC *)(iVar5 + 4),iVar7,iVar1,iVar4,iVar6,DVar8);
    CVar3 = SetTextColor((HDC)param_1[1],0);
    color = SetBkColor((HDC)param_1[1],0xffffff);
    DVar8 = 0xe20746;
    iVar4 = 0;
    iVar7 = 0;
    iVar1 = FUN_0041dad8((int)DAT_004894f8);
    StretchBlt((HDC)param_1[1],*param_2,param_2[1],param_2[2] - *param_2,param_2[3] - param_2[1],
               *(HDC *)(iVar1 + 4),iVar7,iVar4,wSrc,hSrc,DVar8);
    SetTextColor((HDC)param_1[1],CVar3);
    SetBkColor((HDC)param_1[1],color);
    (**(code **)(*param_1 + 0xc))();
  }
  return;
}

