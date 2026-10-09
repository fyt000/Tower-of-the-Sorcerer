/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004331fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004331fc(int param_1,int *param_2,int param_3,byte param_4,int param_5)

{
  int iVar1;
  HDC pHVar2;
  HIMAGELIST p_Var3;
  int iVar4;
  int iVar5;
  COLORREF CVar6;
  COLORREF CVar7;
  UINT UVar8;
  
  if (*(int *)(param_1 + 4) != 0) {
    iVar1 = (**(code **)(**(int **)(param_1 + 4) + 0x20))();
    if (iVar1 != 0) {
      iVar1 = (**(code **)(**(int **)(param_1 + 4) + 0x1c))();
      if (iVar1 != 0) {
        iVar1 = FUN_00432c54(param_1,param_4);
        if (param_4 == 3) {
          UVar8 = 1;
          CVar7 = 0x1fffffff;
          CVar6 = 0x1fffffff;
          iVar5 = 0;
          iVar4 = 0;
          pHVar2 = (HDC)FUN_0041a950(param_2);
          p_Var3 = (HIMAGELIST)FUN_00417984(*(int **)(param_1 + 8));
          ImageList_DrawEx(p_Var3,iVar1,pHVar2,param_3,param_5,iVar4,iVar5,CVar6,CVar7,UVar8);
        }
        else {
          UVar8 = 0;
          CVar7 = 0x1fffffff;
          CVar6 = FUN_00419b00(0x8000000f);
          iVar5 = 0;
          iVar4 = 0;
          pHVar2 = (HDC)FUN_0041a950(param_2);
          p_Var3 = (HIMAGELIST)FUN_00417984(*(int **)(param_1 + 8));
          ImageList_DrawEx(p_Var3,iVar1,pHVar2,param_3,param_5,iVar4,iVar5,CVar6,CVar7,UVar8);
        }
      }
    }
  }
  return;
}

