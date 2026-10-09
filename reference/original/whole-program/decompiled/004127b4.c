/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004127b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004127b4(POINT *param_1,undefined4 param_2,HWND param_3)

{
  bool bVar1;
  short sVar2;
  uint uVar3;
  HWND pHVar4;
  int iVar5;
  HCURSOR pHVar6;
  uint uVar7;
  LONG LVar8;
  HWND local_10;
  
  if (((DAT_0048a6c8 != '\0') ||
      (uVar3 = DAT_0048a6b4 - param_1->x, uVar7 = (int)uVar3 >> 0x1f,
      4 < (int)((uVar3 ^ uVar7) - uVar7))) ||
     (uVar3 = DAT_0048a6b8 - param_1->y, uVar7 = (int)uVar3 >> 0x1f,
     4 < (int)((uVar3 ^ uVar7) - uVar7))) {
    local_10 = param_3;
    if ((DAT_0048a6c8 == '\0') && (DAT_0048a6cc != (int *)0x0)) {
      iVar5 = DAT_0048a6b8;
      pHVar4 = GetDesktopWindow();
      FUN_004182b0(DAT_0048a6cc,pHVar4,DAT_0048a6b4,iVar5);
    }
    DAT_0048a6c8 = '\x01';
    iVar5 = FUN_0041275c(param_1,&local_10);
    if (iVar5 != DAT_0048a6a8) {
      FUN_00412780(CONCAT31((int3)((uint)iVar5 >> 8),1));
      DAT_0048a6ac = local_10;
      DAT_0048a6bc = param_1->x;
      DAT_0048a6c0 = param_1->y;
      DAT_0048a6a8 = iVar5;
      FUN_00412780(0);
    }
    DAT_0048a6bc = param_1->x;
    DAT_0048a6c0 = param_1->y;
    LVar8 = param_1->y;
    bVar1 = FUN_00412780(CONCAT31((int3)((uint)LVar8 >> 8),2));
    sVar2 = (**(code **)(*DAT_0048a6a0 + 4))(DAT_0048a6a0,bVar1,param_1->x,LVar8);
    if (DAT_0048a6cc == (int *)0x0) {
      pHVar6 = (HCURSOR)FUN_00423d24(DAT_0048a6fc,(int)sVar2);
      SetCursor(pHVar6);
    }
    else if ((iVar5 == 0) || ((*(byte *)(iVar5 + 0x35) & 0x20) != 0)) {
      FUN_0041825c((int)DAT_0048a6cc,sVar2);
      if (*(char *)(DAT_0048a6cc + 0x11) == '\0') {
        LVar8 = param_1->y;
        pHVar4 = GetDesktopWindow();
        FUN_004182b0(DAT_0048a6cc,pHVar4,param_1->x,LVar8);
      }
      else {
        FUN_00418394((int)DAT_0048a6cc,param_1->x,param_1->y);
      }
    }
    else {
      FUN_00418408((int)DAT_0048a6cc);
      pHVar6 = (HCURSOR)FUN_00423d24(DAT_0048a6fc,(int)sVar2);
      SetCursor(pHVar6);
    }
  }
  return;
}

