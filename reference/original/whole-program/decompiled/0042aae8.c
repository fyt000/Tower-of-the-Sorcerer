/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042aae8.
 * Inferred types, shared tails and runtime effects require assembly review. */

int root_0042aae8(int *param_1,POINT *param_2,char param_3)

{
  POINT pt;
  POINT pt_00;
  BOOL BVar1;
  int iVar2;
  int iVar3;
  LONG LVar4;
  LONG LVar5;
  RECT RStack_30;
  RECT RStack_20;
  
  LVar4 = param_2->x;
  LVar5 = param_2->y;
  pt_00 = *param_2;
  (**(code **)(*param_1 + 0x2c))(param_1,&RStack_20);
  pt.y = LVar5;
  pt.x = LVar4;
  BVar1 = PtInRect(&RStack_20,pt);
  if (BVar1 != 0) {
    iVar2 = FUN_0042aa80(param_1);
    iVar3 = (**(code **)(*(int *)param_1[0x40] + 0x10))();
    for (; iVar2 < iVar3; iVar2 = iVar2 + 1) {
      FUN_00413cb8(param_1,0x198,iVar2,&RStack_30);
      BVar1 = PtInRect(&RStack_30,pt_00);
      if (BVar1 != 0) {
        return iVar2;
      }
    }
    if (param_3 == '\0') {
      return iVar2;
    }
  }
  return -1;
}

