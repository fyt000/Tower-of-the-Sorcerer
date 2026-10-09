/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00432c54.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00432c54(int param_1,byte param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int cy;
  int iVar4;
  int *piVar5;
  int *piVar6;
  undefined4 uVar7;
  HDC pHVar8;
  int *piVar9;
  HDC pHVar10;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  int extraout_EDX;
  undefined4 extraout_EDX_00;
  byte bVar11;
  undefined4 *in_FS_OFFSET;
  int iVar12;
  int iVar13;
  int x1;
  int iVar14;
  int y1;
  DWORD DVar15;
  COLORREF CVar16;
  undefined4 uStack_5c;
  undefined4 uStack_50;
  undefined *puStack_4c;
  undefined *puStack_48;
  int local_38 [4];
  RECT local_28;
  int *local_18;
  int *local_14;
  int *local_10;
  byte local_9;
  int local_8;
  
  local_9 = param_2;
  if ((param_2 == 2) && (*(byte *)(param_1 + 0x20) < 3)) {
    local_9 = 0;
  }
  iVar4 = *(int *)(param_1 + 0xc + (uint)local_9 * 4);
  if (iVar4 != -1) {
    return iVar4;
  }
  puStack_48 = (undefined *)0x432c96;
  local_8 = param_1;
  uVar1 = (**(code **)(**(int **)(param_1 + 4) + 0x20))();
  puStack_48 = (undefined *)0x432ca3;
  uVar2 = (**(code **)(**(int **)(local_8 + 4) + 0x1c))();
  if ((uVar1 | uVar2) == 0) {
    return -1;
  }
  puStack_48 = (undefined *)0x432cb6;
  iVar3 = (**(code **)(**(int **)(local_8 + 4) + 0x20))();
  iVar3 = iVar3 / (int)(uint)*(byte *)(local_8 + 0x20);
  puStack_48 = (undefined *)0x432ccf;
  cy = (**(code **)(**(int **)(local_8 + 4) + 0x1c))();
  uVar7 = extraout_ECX;
  iVar4 = extraout_EDX;
  if (*(int *)(local_8 + 8) == 0) {
    if (DAT_004898d4 == 0) {
      puStack_48 = (undefined *)0x432cef;
      DAT_004898d4 = FUN_00432970(0x4327a0,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX)
      ;
    }
    puStack_48 = (undefined *)0x432d02;
    iVar4 = FUN_004329d8(DAT_004898d4,iVar3,cy);
    *(int *)(local_8 + 8) = iVar4;
    uVar7 = extraout_ECX_00;
    iVar4 = local_8;
  }
  puStack_48 = (undefined *)0x432d14;
  local_10 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)iVar4 >> 8),1),uVar7);
  puStack_4c = &LAB_004331d2;
  uStack_50 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_50;
  puStack_48 = &stack0xfffffffc;
  (**(code **)(*local_10 + 0x2c))(local_10,iVar3);
  (**(code **)(*local_10 + 0x28))(local_10,cy);
  uStack_5c = 0x432d49;
  FUN_0040923c(0,0,iVar3,&local_28.left,cy);
  iVar4 = FUN_0041dad8((int)local_10);
  FUN_0041a154(*(int **)(iVar4 + 0x14),0x8000000f);
  bVar11 = local_9;
  if (*(char *)(local_8 + 0x20) <= (char)local_9) {
    bVar11 = 0;
  }
  uStack_5c = 0x432d85;
  FUN_0040923c((uint)bVar11 * iVar3,0,(bVar11 + 1) * iVar3,local_38,cy);
  if (local_9 != 0) {
    if (local_9 == 1) {
      local_14 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                                     extraout_ECX_01);
      uStack_5c = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_5c;
      if (*(byte *)(local_8 + 0x20) < 2) {
        (**(code **)(*local_14 + 8))(local_14,*(undefined4 *)(local_8 + 4));
        iVar4 = FUN_0041dad8((int)local_14);
        FUN_0041a154(*(int **)(iVar4 + 0x14),0);
        (**(code **)(*local_14 + 0x2c))(local_14,iVar3);
        uVar7 = FUN_0041db44((int)local_14);
        if ((char)uVar7 != '\0') {
          iVar4 = FUN_0041dad8((int)local_14);
          FUN_00419c7c(*(int **)(iVar4 + 0xc),0xffffff,extraout_ECX_02);
          FUN_0041e1ec((int)local_14,'\0');
          iVar4 = FUN_0041dad8((int)local_14);
          FUN_0041a154(*(int **)(iVar4 + 0x14),0xffffff);
        }
        FUN_0041e1ec((int)local_14,'\x01');
        piVar9 = (int *)FUN_0041dad8((int)local_10);
        FUN_0041a154((int *)piVar9[5],0x8000000f);
        FUN_0041a664(piVar9,&local_28);
        FUN_0041a154((int *)piVar9[5],0x80000014);
        CVar16 = 0;
        pHVar8 = (HDC)FUN_0041a950(piVar9);
        SetTextColor(pHVar8,CVar16);
        CVar16 = 0xffffff;
        pHVar8 = (HDC)FUN_0041a950(piVar9);
        SetBkColor(pHVar8,CVar16);
        DVar15 = 0xe20746;
        y1 = 0;
        x1 = 0;
        piVar5 = (int *)FUN_0041dad8((int)local_14);
        pHVar8 = (HDC)FUN_0041a950(piVar5);
        iVar13 = 1;
        iVar12 = 1;
        iVar4 = iVar3;
        iVar14 = cy;
        pHVar10 = (HDC)FUN_0041a950(piVar9);
        BitBlt(pHVar10,iVar12,iVar13,iVar4,iVar14,pHVar8,x1,y1,DVar15);
        FUN_0041a154((int *)piVar9[5],0x80000010);
        CVar16 = 0;
        pHVar8 = (HDC)FUN_0041a950(piVar9);
        SetTextColor(pHVar8,CVar16);
        CVar16 = 0xffffff;
        pHVar8 = (HDC)FUN_0041a950(piVar9);
        SetBkColor(pHVar8,CVar16);
        DVar15 = 0xe20746;
        iVar13 = 0;
        iVar12 = 0;
        piVar5 = (int *)FUN_0041dad8((int)local_14);
        pHVar8 = (HDC)FUN_0041a950(piVar5);
        iVar14 = 0;
        iVar4 = 0;
        pHVar10 = (HDC)FUN_0041a950(piVar9);
        BitBlt(pHVar10,iVar4,iVar14,iVar3,cy,pHVar8,iVar12,iVar13,DVar15);
      }
      else {
        local_18 = (int *)FUN_0041dad8((int)local_10);
        piVar9 = local_38;
        piVar5 = (int *)FUN_0041dad8(*(int *)(local_8 + 4));
        FUN_0041a530(local_18,&local_28.left,piVar5,piVar9);
        (**(code **)(*local_14 + 0x2c))(local_14,iVar3);
        (**(code **)(*local_14 + 0x28))(local_14,cy);
        FUN_0041e1ec((int)local_14,'\x01');
        iVar4 = FUN_0041dad8(*(int *)(local_8 + 4));
        FUN_0041a154(*(int **)(iVar4 + 0x14),0xffffff);
        piVar9 = local_38;
        piVar5 = (int *)FUN_0041dad8(*(int *)(local_8 + 4));
        piVar6 = (int *)FUN_0041dad8((int)local_14);
        FUN_0041a530(piVar6,&local_28.left,piVar5,piVar9);
        FUN_0041a154((int *)local_18[5],0x80000014);
        pHVar8 = (HDC)FUN_0041a950(local_18);
        SetTextColor(pHVar8,0);
        SetBkColor(pHVar8,0xffffff);
        DVar15 = 0xe20746;
        iVar14 = 0;
        iVar4 = 0;
        piVar9 = (int *)FUN_0041dad8((int)local_14);
        pHVar10 = (HDC)FUN_0041a950(piVar9);
        BitBlt(pHVar8,0,0,iVar3,cy,pHVar10,iVar4,iVar14,DVar15);
        iVar4 = FUN_0041dad8(*(int *)(local_8 + 4));
        FUN_0041a154(*(int **)(iVar4 + 0x14),0x808080);
        piVar9 = local_38;
        piVar5 = (int *)FUN_0041dad8(*(int *)(local_8 + 4));
        piVar6 = (int *)FUN_0041dad8((int)local_14);
        FUN_0041a530(piVar6,&local_28.left,piVar5,piVar9);
        FUN_0041a154((int *)local_18[5],0x80000010);
        pHVar8 = (HDC)FUN_0041a950(local_18);
        SetTextColor(pHVar8,0);
        SetBkColor(pHVar8,0xffffff);
        DVar15 = 0xe20746;
        iVar14 = 0;
        iVar4 = 0;
        piVar9 = (int *)FUN_0041dad8((int)local_14);
        pHVar10 = (HDC)FUN_0041a950(piVar9);
        BitBlt(pHVar8,0,0,iVar3,cy,pHVar10,iVar4,iVar14,DVar15);
        uVar7 = FUN_00419b00(*(uint *)(local_8 + 0x1c));
        iVar4 = FUN_0041dad8(*(int *)(local_8 + 4));
        FUN_0041a154(*(int **)(iVar4 + 0x14),uVar7);
        piVar9 = local_38;
        piVar5 = (int *)FUN_0041dad8(*(int *)(local_8 + 4));
        piVar6 = (int *)FUN_0041dad8((int)local_14);
        FUN_0041a530(piVar6,&local_28.left,piVar5,piVar9);
        FUN_0041a154((int *)local_18[5],0x8000000f);
        pHVar8 = (HDC)FUN_0041a950(local_18);
        SetTextColor(pHVar8,0);
        SetBkColor(pHVar8,0xffffff);
        DVar15 = 0xe20746;
        iVar14 = 0;
        iVar4 = 0;
        piVar9 = (int *)FUN_0041dad8((int)local_14);
        pHVar10 = (HDC)FUN_0041a950(piVar9);
        BitBlt(pHVar8,0,0,iVar3,cy,pHVar10,iVar4,iVar14,DVar15);
      }
      uVar1 = FUN_004328a0(*(int **)(local_8 + 8),local_10,(int *)0x0);
      *(uint *)(local_8 + 0xc + (uint)local_9 * 4) = uVar1;
      *in_FS_OFFSET = uStack_5c;
      iVar4 = FUN_00402c34(local_14);
      return iVar4;
    }
    if (local_9 != 2) {
      if (local_9 == 3) {
        piVar9 = local_38;
        piVar5 = (int *)FUN_0041dad8(*(int *)(local_8 + 4));
        uStack_5c = 0x432df9;
        piVar6 = (int *)FUN_0041dad8((int)local_10);
        FUN_0041a530(piVar6,&local_28.left,piVar5,piVar9);
        uVar7 = FUN_004328cc(*(int **)(local_8 + 8),local_10,*(uint *)(local_8 + 0x1c));
        *(undefined4 *)(local_8 + 0xc + (uint)local_9 * 4) = uVar7;
      }
      goto LAB_004331bc;
    }
  }
  piVar9 = local_38;
  uVar1 = *(uint *)(local_8 + 0x1c);
  uStack_5c = 0x432db2;
  piVar5 = (int *)FUN_0041dad8((int)local_10);
  uStack_5c = 0x432dc0;
  FUN_0041a32c(piVar5,&local_28.left,*(int *)(local_8 + 4),uVar1,piVar9);
  uVar1 = FUN_004328a0(*(int **)(local_8 + 8),local_10,(int *)0x0);
  *(uint *)(local_8 + 0xc + (uint)local_9 * 4) = uVar1;
LAB_004331bc:
  *in_FS_OFFSET = uStack_50;
  puStack_48 = &DAT_004331d9;
  puStack_4c = (undefined *)0x4331d1;
  iVar4 = FUN_00402c34(local_10);
  return iVar4;
}

