/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00425640.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00425640(int param_1,int *param_2)

{
  int *piVar1;
  undefined *puVar2;
  char cVar3;
  LPCSTR lpchText;
  HDC hdc;
  undefined4 uVar4;
  int iVar5;
  DWORD extraout_ECX;
  undefined4 extraout_EDX;
  LONG *pLVar6;
  tagRECT *ptVar7;
  undefined4 *in_FS_OFFSET;
  byte bVar8;
  UINT format;
  undefined4 uStack_94;
  undefined *puStack_90;
  undefined *puStack_8c;
  int local_7c;
  LONG local_78 [4];
  int local_68;
  int local_64;
  tagRECT local_60;
  int *local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  tagRECT local_3c;
  int local_2c;
  int local_28;
  char local_21;
  undefined *local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int iStack_8;
  
  bVar8 = 0;
  puStack_8c = &stack0xfffffffc;
  local_7c = 0;
  local_20 = (undefined *)0x0;
  local_c = *param_2;
  iStack_8 = param_2[1];
  puStack_90 = &LAB_00425892;
  uStack_94 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_94;
  *(undefined *)(param_1 + 0x38) = 0;
  puVar2 = &stack0xfffffffc;
  if (((*(char *)(param_1 + 100) != '\0') &&
      (puVar2 = &stack0xfffffffc, *(int *)(param_1 + 0x40) != 0)) &&
     (puVar2 = &stack0xfffffffc, *(int *)(param_1 + 0x60) != 0)) {
    cVar3 = FUN_0041fa30();
    puVar2 = puStack_8c;
    if (cVar3 != '\0') {
      local_50 = *(int **)(param_1 + 0x40);
      (**(code **)(*local_50 + 0x28))(local_50,&local_68);
      local_4c = local_68;
      local_48 = local_64 + *(int *)(*(int *)(param_1 + 0x40) + 0x30) + 6;
      local_44 = FUN_00423ba8();
      local_40 = *(int *)(param_1 + 0x3c);
      FUN_00413118(*(int *)(param_1 + 0x40),local_78);
      pLVar6 = local_78;
      ptVar7 = &local_3c;
      for (iVar5 = 4; iVar5 != 0; iVar5 = iVar5 + -1) {
        ptVar7->left = *pLVar6;
        pLVar6 = pLVar6 + (uint)bVar8 * -2 + 1;
        ptVar7 = (tagRECT *)((int)ptVar7 + ((uint)bVar8 * -2 + 1) * 4);
      }
      (**(code **)(**(int **)(param_1 + 0x40) + 0x28))(*(int **)(param_1 + 0x40),&local_14);
      piVar1 = *(int **)(*(int *)(param_1 + 0x40) + 0x20);
      if (piVar1 == (int *)0x0) {
        FUN_00409224(0,0,&local_1c);
      }
      else {
        (**(code **)(*piVar1 + 0x28))(piVar1,&local_1c);
      }
      OffsetRect(&local_3c,local_1c - local_14,local_18 - local_10);
      FUN_00413278(*(int **)(param_1 + 0x40),&local_c,&local_68);
      local_2c = local_68;
      local_28 = local_64;
      FUN_00423dd8(*(int *)(param_1 + 0x40),&local_7c);
      FUN_00412400(local_7c,(int *)&local_20);
      iVar5 = FUN_00413cb8(*(int **)(param_1 + 0x40),0xb030,0,&local_50);
      local_21 = iVar5 == 0;
      if (((bool)local_21) && (*(short *)(param_1 + 0xc6) != 0)) {
        (**(code **)(param_1 + 0xc4))(*(undefined4 *)(param_1 + 200),&local_20,&local_21,&local_50);
      }
      *(char *)(param_1 + 0x38) = local_21;
      puVar2 = puStack_8c;
      if ((local_21 != '\0') && (local_20 != (undefined *)0x0)) {
        FUN_00409258(0,0,local_44,&local_60.left,0);
        format = 0xc10;
        ptVar7 = &local_60;
        iVar5 = -1;
        lpchText = FUN_00403814(local_20);
        hdc = (HDC)FUN_0041a950(*(int **)(*(int *)(param_1 + 0x60) + 0x100));
        DrawTextA(hdc,lpchText,iVar5,ptVar7,format);
        OffsetRect(&local_60,local_4c,local_48);
        local_60.right = local_60.right + 6;
        local_60.bottom = local_60.bottom + 2;
        FUN_0041324c(*(int **)(param_1 + 0x40),&local_3c.left,&local_68);
        *(int *)(param_1 + 0x44) = local_68;
        *(int *)(param_1 + 0x48) = local_64;
        FUN_0041324c(*(int **)(param_1 + 0x40),&local_3c.right,&local_68);
        *(int *)(param_1 + 0x4c) = local_68;
        *(int *)(param_1 + 0x50) = local_64;
        FUN_004136e8(*(int **)(param_1 + 0x60),local_40);
        uVar4 = (**(code **)(**(int **)(param_1 + 0x60) + 0x88))
                          (*(int **)(param_1 + 0x60),&local_60,local_20);
        FUN_00423ed4(uVar4,extraout_EDX,extraout_ECX);
        FUN_0042548c(param_1,*(UINT *)(param_1 + 0x5c),1);
        goto LAB_00425874;
      }
    }
  }
  puStack_8c = puVar2;
  FUN_00425618(param_1);
LAB_00425874:
  *in_FS_OFFSET = uStack_94;
  puStack_8c = &LAB_00425899;
  puStack_90 = (undefined *)0x425889;
  FUN_004034dc(&local_7c);
  puStack_90 = (undefined *)0x425891;
  FUN_004034dc((int *)&local_20);
  return;
}

