/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417bc8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417bc8(int *param_1,int param_2,int *param_3,uint param_4)

{
  bool bVar1;
  int i;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  HDC pHVar5;
  HIMAGELIST p_Var6;
  HBITMAP hbmMask;
  HBITMAP hbmImage;
  BOOL BVar7;
  undefined4 uVar8;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined3 uVar10;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 uVar9;
  undefined4 *in_FS_OFFSET;
  int iVar11;
  int iVar12;
  int y;
  UINT UVar13;
  undefined4 uStack_34;
  undefined *puStack_30;
  undefined *puStack_2c;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  
  puStack_20 = (undefined *)0x417bdf;
  bVar1 = FUN_00417800((int)param_1);
  uVar8 = extraout_ECX;
  uVar9 = extraout_EDX;
  if (bVar1) {
    puStack_20 = (undefined *)0x417bf1;
    FUN_00418160((int)param_1,param_3);
    puStack_20 = (undefined *)0x417bfe;
    i = FUN_00417b00(param_1,param_3,param_4);
    uVar10 = (undefined3)((uint)extraout_EDX_00 >> 8);
    if (i != -1) {
      puStack_24 = &LAB_00417d42;
      uStack_28 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_28;
      puStack_2c = (undefined *)0x417c25;
      puStack_20 = &stack0xfffffffc;
      piVar2 = (int *)FUN_0041d718(0x4193b4,CONCAT31(uVar10,1),extraout_ECX_00);
      puStack_2c = (undefined *)0x417c34;
      piVar3 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                                   extraout_ECX_01);
      puStack_30 = &LAB_00417d22;
      uStack_34 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_34;
      puStack_2c = &stack0xfffffffc;
      (**(code **)(*piVar2 + 0x28))(piVar2,param_1[8]);
      (**(code **)(*piVar2 + 0x2c))(piVar2,param_1[9]);
      (**(code **)(*piVar3 + 0x28))(piVar3,param_1[8]);
      (**(code **)(*piVar3 + 0x2c))(piVar3,param_1[9]);
      UVar13 = 0;
      y = 0;
      iVar11 = 0;
      piVar4 = (int *)FUN_0041dad8((int)piVar2);
      pHVar5 = (HDC)FUN_0041a950(piVar4);
      iVar12 = i;
      p_Var6 = (HIMAGELIST)FUN_00417984(param_1);
      ImageList_Draw(p_Var6,iVar12,pHVar5,iVar11,y,UVar13);
      UVar13 = 0x10;
      iVar11 = 0;
      iVar12 = 0;
      piVar4 = (int *)FUN_0041dad8((int)piVar3);
      pHVar5 = (HDC)FUN_0041a950(piVar4);
      p_Var6 = (HIMAGELIST)FUN_00417984(param_1);
      ImageList_Draw(p_Var6,i,pHVar5,iVar12,iVar11,UVar13);
      hbmMask = (HBITMAP)(**(code **)(*piVar3 + 0x4c))();
      hbmImage = (HBITMAP)(**(code **)(*piVar2 + 0x4c))();
      p_Var6 = (HIMAGELIST)FUN_00417984(param_1);
      BVar7 = ImageList_Replace(p_Var6,param_2,hbmImage,hbmMask);
      if (BVar7 == 0) {
        uVar8 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),0xf028);
        FUN_004031f8(uVar8);
      }
      *in_FS_OFFSET = uStack_34;
      puStack_2c = &LAB_00417d29;
      puStack_30 = (undefined *)0x417d19;
      FUN_00402c34(piVar2);
      puStack_30 = (undefined *)0x417d21;
      FUN_00402c34(piVar3);
      return;
    }
    puStack_20 = (undefined *)0x417d5a;
    uVar8 = FUN_004074cc(0x41117c,CONCAT31(uVar10,1),0xf028);
    puStack_20 = (undefined *)0x417d5f;
    FUN_004031f8(uVar8);
    uVar8 = extraout_ECX_02;
    uVar9 = extraout_EDX_03;
  }
  puStack_20 = (undefined *)0x417d6b;
  FUN_00402cdc(param_1,uVar9,uVar8);
  return;
}

