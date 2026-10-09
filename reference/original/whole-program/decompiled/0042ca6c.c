/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042ca6c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042ca6c(uint *param_1,undefined4 param_2,ushort param_3)

{
  byte bVar1;
  int **ppiVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  LPCSTR pCVar6;
  HDC hdc;
  int iVar7;
  HICON pHVar8;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 uVar9;
  int *in_FS_OFFSET;
  bool bVar10;
  tagRECT *lprc;
  int iVar11;
  UINT format;
  undefined *puStack_80;
  undefined *puStack_7c;
  undefined *puStack_78;
  uint *local_68;
  tagRECT local_64;
  int **local_54;
  ushort *local_50;
  undefined **local_4c;
  int **local_48;
  int *local_44;
  byte local_3e;
  byte local_3d;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  tagSIZE local_14;
  ushort local_b;
  byte local_9;
  uint *local_8;
  
  puStack_78 = &stack0xfffffffc;
  local_68 = (uint *)0x0;
  local_9 = (byte)param_2;
  puStack_7c = &LAB_0042ce95;
  puStack_80 = (undefined *)*in_FS_OFFSET;
  *in_FS_OFFSET = (int)&puStack_80;
  local_b = param_3;
  local_8 = param_1;
  ppiVar2 = (int **)FUN_00420c70((int *)&PTR_FUN_0042c920,CONCAT31((int3)((uint)param_2 >> 8),1),
                                 DAT_0048a6f8);
  FUN_0042194c(ppiVar2,'\x03');
  iVar3 = FUN_00421a54((int)ppiVar2);
  FUN_0041a8bc(iVar3);
  piVar4 = (int *)FUN_00421a54((int)ppiVar2);
  FUN_0042c898(piVar4,&local_14);
  local_18 = MulDiv(8,local_14.cx,4);
  local_1c = MulDiv(8,local_14.cy,8);
  local_20 = MulDiv(10,local_14.cx,4);
  local_24 = MulDiv(10,local_14.cy,8);
  local_28 = MulDiv(0x32,local_14.cx,4);
  local_2c = MulDiv(0xe,local_14.cy,8);
  local_30 = MulDiv(4,local_14.cx,4);
  iVar11 = 0;
  uVar5 = FUN_00423ba8();
  iVar3 = (int)uVar5 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((uVar5 & 1) != 0);
  }
  SetRect(&local_64,0,0,iVar3,iVar11);
  format = 0x410;
  lprc = &local_64;
  iVar3 = -1;
  pCVar6 = FUN_00403814((undefined *)local_8);
  piVar4 = (int *)FUN_00421a54((int)ppiVar2);
  hdc = (HDC)FUN_0041a950(piVar4);
  DrawTextA(hdc,pCVar6,iVar3,lprc,format);
  pCVar6 = *(LPCSTR *)(&DAT_00489750 + (uint)local_9 * 4);
  local_34 = local_64.right;
  local_38 = local_64.bottom;
  if ((pCVar6 != (LPCSTR)0x0) &&
     (local_34 = local_64.right + local_20 + 0x20, local_64.bottom < 0x20)) {
    local_38 = 0x20;
  }
  iVar3 = 0;
  uVar5 = 0;
  do {
    bVar10 = (byte)uVar5 < 0xf;
    if ((byte)uVar5 < 0x10) {
      bVar10 = (*(byte *)((int)&local_b + ((int)(uVar5 & 0x7f) >> 3)) >> (uVar5 & 7) & 1) != 0;
    }
    if (bVar10) {
      iVar3 = iVar3 + 1;
    }
    uVar5 = uVar5 + 1;
  } while ((char)uVar5 != '\t');
  iVar11 = 0;
  if (iVar3 != 0) {
    iVar11 = local_28 * iVar3 + (iVar3 + -1) * local_30;
  }
  iVar3 = FUN_0042c890(local_34,iVar11);
  FUN_004214f0((int *)ppiVar2,iVar3 + local_18 * 2);
  FUN_0042151c((int *)ppiVar2,local_38 + local_2c + local_24 + local_1c * 2);
  uVar5 = FUN_00423ba8();
  iVar3 = (int)uVar5 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((uVar5 & 1) != 0);
  }
  iVar7 = (int)ppiVar2[0xb] >> 1;
  if (iVar7 < 0) {
    iVar7 = iVar7 + (uint)(((uint)ppiVar2[0xb] & 1) != 0);
  }
  FUN_00413098((int *)ppiVar2,iVar3 - iVar7);
  uVar5 = FUN_00423ba0();
  iVar3 = (int)uVar5 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((uVar5 & 1) != 0);
  }
  iVar7 = (int)ppiVar2[0xc] >> 1;
  if (iVar7 < 0) {
    iVar7 = iVar7 + (uint)(((uint)ppiVar2[0xc] & 1) != 0);
  }
  FUN_004130b8((int *)ppiVar2,iVar3 - iVar7);
  if (local_9 == 4) {
    FUN_00424bec((int)DAT_0048a6f8,(int *)&local_68);
    FUN_004135d4((int *)ppiVar2,local_68);
    uVar9 = extraout_EDX_00;
  }
  else {
    FUN_00405bf0((uint)*(ushort *)(&DAT_00489744 + (uint)local_9 * 2),(int *)&local_68);
    FUN_004135d4((int *)ppiVar2,local_68);
    uVar9 = extraout_EDX;
  }
  if (pCVar6 != (LPCSTR)0x0) {
    local_44 = FUN_0042bf80((int *)&PTR_FUN_0042b29c,CONCAT31((int3)((uint)uVar9 >> 8),1),
                            (int *)ppiVar2);
    (**(code **)(*local_44 + 0x18))(local_44,"Image");
    (**(code **)(*local_44 + 0x3c))(local_44,ppiVar2);
    pHVar8 = LoadIconA((HINSTANCE)0x0,pCVar6);
    iVar3 = FUN_0041c14c(local_44[0x2b]);
    FUN_0041e728(iVar3,pHVar8);
    (**(code **)(*local_44 + 0x4c))(local_44,local_18,local_1c,0x20,0x20);
    uVar9 = extraout_EDX_01;
  }
  piVar4 = FUN_00428174((int *)&PTR_FUN_004259bc,CONCAT31((int3)((uint)uVar9 >> 8),1),(int *)ppiVar2
                       );
  (**(code **)(*piVar4 + 0x18))(piVar4,"Message");
  (**(code **)(*piVar4 + 0x3c))(piVar4,ppiVar2);
  FUN_004284a4(piVar4,'\x01');
  FUN_004135d4(piVar4,local_8);
  FUN_00413138(piVar4,&local_64.left);
  (**(code **)(*piVar4 + 0x4c))
            (piVar4,(local_34 - local_64.right) + local_18,local_1c,local_64.bottom,local_64.right);
  if ((local_b & 4) == 0) {
    if ((local_b & 1) == 0) {
      local_3d = 5;
    }
    else {
      local_3d = 0;
    }
  }
  else {
    local_3d = 2;
  }
  if ((local_b & 8) == 0) {
    if ((local_b & 2) == 0) {
      local_3e = 2;
    }
    else {
      local_3e = 1;
    }
  }
  else {
    local_3e = 3;
  }
  iVar3 = FUN_00413178((int *)ppiVar2);
  local_3c = iVar3 - iVar11 >> 1;
  if (local_3c < 0) {
    local_3c = local_3c + (uint)((iVar3 - iVar11 & 1U) != 0);
  }
  uVar5 = 0;
  local_4c = &PTR_DAT_00489764;
  local_50 = &DAT_00489788;
  local_54 = (int **)&DAT_0048979c;
  uVar9 = extraout_EDX_02;
  iVar3 = local_64.bottom;
  do {
    bVar1 = (byte)uVar5;
    bVar10 = bVar1 < 0xf;
    if (bVar1 < 0x10) {
      bVar10 = (*(byte *)((int)&local_b + ((int)(uVar5 & 0x7f) >> 3)) >> (uVar5 & 7) & 1) != 0;
    }
    if (bVar10) {
      local_48 = (int **)FUN_0042a310((int *)&PTR_FUN_004271a4,CONCAT31((int3)((uint)uVar9 >> 8),1),
                                      (int *)ppiVar2);
      (*(code *)(*local_48)[6])(local_48,*local_4c);
      (*(code *)(*local_48)[0xf])(local_48,ppiVar2);
      FUN_00405bf0((uint)*local_50,(int *)&local_68);
      FUN_004135d4((int *)local_48,local_68);
      local_48[0x42] = *local_54;
      if (bVar1 == local_3d) {
        FUN_0042a3e8(local_48,1);
      }
      if (bVar1 == local_3e) {
        *(undefined *)((int)local_48 + 0x105) = 1;
      }
      (*(code *)(*local_48)[0x13])
                (local_48,local_3c,local_38 + local_1c + local_24,local_2c,local_28);
      local_3c = local_3c + local_28 + local_30;
      uVar9 = extraout_EDX_03;
      if (bVar1 == 8) {
        local_48[0x27] = (int *)ppiVar2;
        local_48[0x26] = (int *)&LAB_0042c9d8;
      }
    }
    uVar5 = uVar5 + 1;
    local_54 = local_54 + 1;
    local_50 = local_50 + 1;
    local_4c = local_4c + 1;
  } while ((char)uVar5 != '\t');
  *in_FS_OFFSET = iVar3;
  puStack_80 = &LAB_0042ce9c;
  FUN_004034dc((int *)&local_68);
  return;
}

