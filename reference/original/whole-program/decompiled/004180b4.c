/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004180b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004180b4(int *param_1,int **param_2)

{
  bool bVar1;
  int *piVar2;
  HIMAGELIST p_Var3;
  COLORREF CVar4;
  uint uVar5;
  int *cx;
  
  piVar2 = FUN_00402c7c(param_2,(int *)&PTR_root_00411ed8);
  if ((char)piVar2 != '\0') {
    *(undefined *)((int)param_2 + 0x31) = *(undefined *)((int)param_1 + 0x31);
    *(undefined *)((int)param_2 + 0x33) = *(undefined *)((int)param_1 + 0x33);
    *(undefined *)(param_2 + 0xc) = *(undefined *)(param_1 + 0xc);
    *(undefined *)((int)param_2 + 0x32) = *(undefined *)((int)param_1 + 0x32);
    param_2[0xe] = (int *)param_1[0xe];
    FUN_00417dc4((int *)param_2);
    p_Var3 = (HIMAGELIST)FUN_00417984(param_1);
    FUN_004178bc((int)param_2,p_Var3);
    bVar1 = FUN_00417800((int)param_2);
    if (bVar1) {
      piVar2 = param_2[8];
      cx = param_2[9];
      p_Var3 = (HIMAGELIST)FUN_00417984((int *)param_2);
      ImageList_SetIconSize(p_Var3,(int)cx,(int)piVar2);
    }
    else {
      FUN_00417808((int *)param_2);
    }
    p_Var3 = (HIMAGELIST)FUN_00417984(param_1);
    CVar4 = ImageList_GetBkColor(p_Var3);
    uVar5 = FUN_0041763c(CVar4);
    FUN_00417de0((int *)param_2,uVar5);
    FUN_00417fdc((int *)param_2,param_1);
    return;
  }
  FUN_00409e5c(param_1,(int *)param_2);
  return;
}

