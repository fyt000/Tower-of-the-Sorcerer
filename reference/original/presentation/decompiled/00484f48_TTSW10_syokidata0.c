/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00484f48.
 * Inferred types and shared tails require assembly review. */

void FUN_00484f48(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  int iVar10;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  undefined4 extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_ECX_11;
  undefined4 extraout_ECX_12;
  undefined4 extraout_ECX_13;
  uint uVar11;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 extraout_EDX_06;
  undefined4 extraout_EDX_07;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined4 *in_FS_OFFSET;
  byte bVar14;
  int *piVar15;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined4 local_18 [4];
  int local_8;
  
  bVar14 = 0;
  puStack_28 = &stack0xfffffffc;
  local_8 = 0;
  puStack_2c = &LAB_00488842;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  iVar1 = FUN_00423ba8();
  if ((iVar1 < 800) && (DAT_00489ba4 == '\x01')) {
    DAT_00489ba4 = '\0';
  }
  if (DAT_00489ba4 == '\0') {
    iVar1 = FUN_00423ba8();
    if (iVar1 < 800) {
      FUN_00410378((int *)param_1[0x11d],0);
    }
    FUN_0040352c((int *)&DAT_0048c5fc,(undefined4 *)"\\data");
    DAT_0048c578 = 0x90;
    DAT_0048c57c = 0x18;
  }
  else if (DAT_00489ba4 == '\x01') {
    FUN_0040352c((int *)&DAT_0048c5fc,(undefined4 *)"\\data3");
    DAT_0048c578 = 0xb4;
    DAT_0048c57c = 0x1e;
  }
  FUN_004130b8(DAT_0048c510,0);
  if (DAT_00489ba4 == '\0') {
    iVar1 = FUN_00423ba8();
    if (iVar1 < 0x281) {
      FUN_00413098(DAT_0048c510,0xfffffffc);
      FUN_0042151c(DAT_0048c510,0x1a8);
      FUN_004130d8(DAT_0048c510,0x288);
    }
    else {
      FUN_00413098(DAT_0048c510,0);
      FUN_0042151c(DAT_0048c510,0x1a8);
      FUN_004130d8(DAT_0048c510,0x288);
    }
  }
  else if (DAT_00489ba4 == '\x01') {
    iVar1 = FUN_00423ba8();
    if (iVar1 < 0x321) {
      FUN_00413098(DAT_0048c510,0xfffffffd);
      FUN_0042151c(DAT_0048c510,0x212);
      FUN_004130d8(DAT_0048c510,0x328);
    }
    else {
      FUN_00413098(DAT_0048c510,0);
      FUN_0042151c(DAT_0048c510,0x212);
      FUN_004130d8(DAT_0048c510,0x328);
    }
  }
  if (DAT_00489ba4 == '\0') {
    FUN_004130f8((int *)param_1[0x6e],400);
    FUN_004130d8((int *)param_1[0x6e],0x186);
    FUN_004130b8((int *)param_1[0x6e],0);
    FUN_00413098((int *)param_1[0x6e],0x7d);
    FUN_004130f8((int *)param_1[0x95],0x20);
    FUN_004130d8((int *)param_1[0x95],*(undefined4 *)(param_1[0x95] + 0x30));
    FUN_004130b8((int *)param_1[0x95],0xc0);
    iVar1 = (int)*(uint *)(param_1[0x6e] + 0x24) >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x6e] + 0x24) & 1) != 0);
    }
    uVar11 = *(int *)(param_1[0x95] + 0x2c) * 3;
    iVar2 = (int)uVar11 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar11 & 1) != 0);
    }
    FUN_00413098((int *)param_1[0x95],(*(int *)(param_1[0x6f] + 0x24) + iVar1) - iVar2);
  }
  else if (DAT_00489ba4 == '\x01') {
    FUN_004130f8((int *)param_1[0x6e],500);
    FUN_004130d8((int *)param_1[0x6e],0x1e8);
    FUN_004130b8((int *)param_1[0x6e],0);
    FUN_00413098((int *)param_1[0x6e],0x9c);
    FUN_004130f8((int *)param_1[0x95],0x28);
    FUN_004130d8((int *)param_1[0x95],*(undefined4 *)(param_1[0x95] + 0x30));
    FUN_004130b8((int *)param_1[0x95],0xf0);
    iVar1 = (int)*(uint *)(param_1[0x6e] + 0x24) >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x6e] + 0x24) & 1) != 0);
    }
    uVar11 = *(int *)(param_1[0x95] + 0x2c) * 3;
    iVar2 = (int)uVar11 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar11 & 1) != 0);
    }
    FUN_00413098((int *)param_1[0x95],(*(int *)(param_1[0x6f] + 0x24) + iVar1) - iVar2);
  }
  FUN_004130f8((int *)param_1[0x6f],*(undefined4 *)(param_1[0x6e] + 0x30));
  FUN_004130d8((int *)param_1[0x6f],*(undefined4 *)(param_1[0x6e] + 0x24));
  FUN_004130b8((int *)param_1[0x6f],*(undefined4 *)(param_1[0x6e] + 0x28));
  FUN_00413098((int *)param_1[0x6f],0);
  FUN_004130f8((int *)param_1[0x70],*(undefined4 *)(param_1[0x6f] + 0x30));
  FUN_004130d8((int *)param_1[0x70],*(undefined4 *)(param_1[0x6f] + 0x2c));
  FUN_004130b8((int *)param_1[0x70],*(undefined4 *)(param_1[0x6e] + 0x28));
  FUN_00413098((int *)param_1[0x70],*(int *)(param_1[0x6e] + 0x24) + *(int *)(param_1[0x6e] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0x7b],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x7b],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x7b],*(undefined4 *)(param_1[0x95] + 0x28));
  FUN_00413098((int *)param_1[0x7b],*(int *)(param_1[0x95] + 0x24) + *(int *)(param_1[0x95] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0x77],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x77],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x77],*(undefined4 *)(param_1[0x95] + 0x28));
  FUN_00413098((int *)param_1[0x77],*(int *)(param_1[0x7b] + 0x24) + *(int *)(param_1[0x7b] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0x96],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x96],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x96],*(int *)(param_1[0x95] + 0x28) + *(int *)(param_1[0x95] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x96],*(undefined4 *)(param_1[0x95] + 0x24));
  FUN_004130f8((int *)param_1[0x97],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x97],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x97],*(int *)(param_1[0x95] + 0x28) + *(int *)(param_1[0x95] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x97],*(undefined4 *)(param_1[0x7b] + 0x24));
  FUN_004130f8((int *)param_1[0x98],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x98],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x98],*(int *)(param_1[0x95] + 0x28) + *(int *)(param_1[0x95] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x98],*(undefined4 *)(param_1[0x77] + 0x24));
  FUN_004130f8((int *)param_1[0x99],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x99],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x99],*(int *)(param_1[0x96] + 0x28) + *(int *)(param_1[0x96] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x99],*(undefined4 *)(param_1[0x95] + 0x24));
  FUN_004130f8((int *)param_1[0x9a],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x9a],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x9a],*(int *)(param_1[0x96] + 0x28) + *(int *)(param_1[0x96] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x9a],*(undefined4 *)(param_1[0x7b] + 0x24));
  FUN_004130f8((int *)param_1[0x9b],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x9b],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x9b],*(int *)(param_1[0x96] + 0x28) + *(int *)(param_1[0x96] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x9b],*(undefined4 *)(param_1[0x77] + 0x24));
  FUN_004130f8((int *)param_1[0x9c],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x9c],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x9c],*(int *)(param_1[0x99] + 0x28) + *(int *)(param_1[0x99] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x9c],*(undefined4 *)(param_1[0x95] + 0x24));
  FUN_004130f8((int *)param_1[0x9d],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x9d],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x9d],*(int *)(param_1[0x99] + 0x28) + *(int *)(param_1[0x99] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x9d],*(undefined4 *)(param_1[0x7b] + 0x24));
  FUN_004130f8((int *)param_1[0x9e],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x9e],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x9e],*(int *)(param_1[0x99] + 0x28) + *(int *)(param_1[0x99] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x9e],*(undefined4 *)(param_1[0x77] + 0x24));
  FUN_004130f8((int *)param_1[0x9f],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x9f],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0x9f],*(int *)(param_1[0x9c] + 0x28) + *(int *)(param_1[0x9c] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x9f],*(undefined4 *)(param_1[0x95] + 0x24));
  FUN_004130f8((int *)param_1[0xa0],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0xa0],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0xa0],*(int *)(param_1[0x9c] + 0x28) + *(int *)(param_1[0x9c] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xa0],*(undefined4 *)(param_1[0x7b] + 0x24));
  FUN_004130f8((int *)param_1[0xa1],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0xa1],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130b8((int *)param_1[0xa1],*(int *)(param_1[0x9c] + 0x28) + *(int *)(param_1[0x9c] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xa1],*(undefined4 *)(param_1[0x77] + 0x24));
  if (DAT_00489ba4 == '\0') {
    FUN_004130f8((int *)param_1[0xa2],*(undefined4 *)(param_1[0x95] + 0x30));
    FUN_004130d8((int *)param_1[0xa2],*(undefined4 *)(param_1[0x95] + 0x2c));
    FUN_004130b8((int *)param_1[0xa2],0x30);
    FUN_00413098((int *)param_1[0xa2],*(int *)(param_1[0x70] + 0x24) + 0x50);
    FUN_004130f8((int *)param_1[0xa3],*(undefined4 *)(param_1[0x95] + 0x30));
    FUN_004130d8((int *)param_1[0xa3],*(undefined4 *)(param_1[0x95] + 0x2c));
    FUN_004130b8((int *)param_1[0xa3],0x60);
    FUN_00413098((int *)param_1[0xa3],*(undefined4 *)(param_1[0xa2] + 0x24));
    FUN_004130f8((int *)param_1[0x102],*(int *)(param_1[0x95] + 0x30) * 2);
    FUN_004130d8((int *)param_1[0x102],*(int *)(param_1[0x95] + 0x2c) * 3);
    FUN_004130b8((int *)param_1[0x102],0x90);
    iVar1 = (int)*(uint *)(param_1[0x70] + 0x2c) >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x70] + 0x2c) & 1) != 0);
    }
    iVar2 = (int)*(uint *)(param_1[0x102] + 0x2c) >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((*(uint *)(param_1[0x102] + 0x2c) & 1) != 0);
    }
    FUN_00413098((int *)param_1[0x102],(*(int *)(param_1[0x70] + 0x24) + iVar1) - iVar2);
  }
  else if (DAT_00489ba4 == '\x01') {
    FUN_004130f8((int *)param_1[0xa2],*(undefined4 *)(param_1[0x95] + 0x30));
    FUN_004130d8((int *)param_1[0xa2],*(undefined4 *)(param_1[0x95] + 0x2c));
    FUN_004130b8((int *)param_1[0xa2],0x3c);
    FUN_00413098((int *)param_1[0xa2],*(int *)(param_1[0x70] + 0x24) + 100);
    FUN_004130f8((int *)param_1[0xa3],*(undefined4 *)(param_1[0x95] + 0x30));
    FUN_004130d8((int *)param_1[0xa3],*(undefined4 *)(param_1[0x95] + 0x2c));
    FUN_004130b8((int *)param_1[0xa3],0x78);
    FUN_00413098((int *)param_1[0xa3],*(undefined4 *)(param_1[0xa2] + 0x24));
    FUN_004130f8((int *)param_1[0x102],*(int *)(param_1[0x95] + 0x30) * 2);
    FUN_004130d8((int *)param_1[0x102],*(int *)(param_1[0x95] + 0x2c) * 3);
    FUN_004130b8((int *)param_1[0x102],0xb4);
    iVar1 = (int)*(uint *)(param_1[0x70] + 0x2c) >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x70] + 0x2c) & 1) != 0);
    }
    iVar2 = (int)*(uint *)(param_1[0x102] + 0x2c) >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((*(uint *)(param_1[0x102] + 0x2c) & 1) != 0);
    }
    FUN_00413098((int *)param_1[0x102],(*(int *)(param_1[0x70] + 0x24) + iVar1) - iVar2);
  }
  FUN_004130d8((int *)param_1[0xfe],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130f8((int *)param_1[0xfe],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130d8((int *)param_1[0x106],
               *(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
               *(int *)(param_1[0x70] + 0x2c));
  FUN_004130f8((int *)param_1[0x106],*(undefined4 *)(param_1[0x6e] + 0x30));
  FUN_004130d8((int *)param_1[0x10a],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130f8((int *)param_1[0x10a],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x10b],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130f8((int *)param_1[0x10b],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x10c],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130f8((int *)param_1[0x10c],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x10d],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130f8((int *)param_1[0x10d],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x10e],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130f8((int *)param_1[0x10e],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x10f],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130f8((int *)param_1[0x10f],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x110],*(undefined4 *)(param_1[0x95] + 0x2c));
  FUN_004130f8((int *)param_1[0x110],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130f8((int *)param_1[0x101],*(undefined4 *)(param_1[0x95] + 0x30));
  FUN_004130d8((int *)param_1[0x101],*(undefined4 *)(param_1[0x95] + 0x2c));
  if (DAT_00489ba4 == '\0') {
    FUN_004130b8((int *)param_1[0x101],0xe6);
    iVar1 = (int)*(uint *)(param_1[0x70] + 0x2c) >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x70] + 0x2c) & 1) != 0);
    }
    FUN_00413098((int *)param_1[0x101],iVar1 + -0x10 + *(int *)(param_1[0x70] + 0x24));
    FUN_004130f8((int *)param_1[0x74],0x19);
    FUN_004130d8((int *)param_1[0x74],0x4b);
    FUN_004130b8((int *)param_1[0x74],0x110);
    FUN_00413098((int *)param_1[0x74],0x170);
    FUN_004130f8((int *)param_1[0x114],0x14);
    FUN_004130d8((int *)param_1[0x114],*(undefined4 *)(param_1[0x95] + 0x2c));
    FUN_004130b8((int *)param_1[0x114],0x163);
    iVar1 = (int)*(uint *)(param_1[0x70] + 0x2c) >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x70] + 0x2c) & 1) != 0);
    }
    iVar2 = (int)*(uint *)(param_1[0x114] + 0x2c) >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((*(uint *)(param_1[0x114] + 0x2c) & 1) != 0);
    }
    FUN_00413098((int *)param_1[0x114],(*(int *)(param_1[0x70] + 0x24) + iVar1) - iVar2);
    FUN_00413098((int *)param_1[0x75],0x108);
  }
  else if (DAT_00489ba4 == '\x01') {
    FUN_004130b8((int *)param_1[0x101],0x120);
    iVar1 = (int)*(uint *)(param_1[0x70] + 0x2c) >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x70] + 0x2c) & 1) != 0);
    }
    FUN_00413098((int *)param_1[0x101],iVar1 + -0x10 + *(int *)(param_1[0x70] + 0x24));
    FUN_004130f8((int *)param_1[0x74],0x1f);
    FUN_004130d8((int *)param_1[0x74],0x5e);
    FUN_004130b8((int *)param_1[0x74],0x154);
    FUN_00413098((int *)param_1[0x74],0x1cc);
    FUN_004130f8((int *)param_1[0x114],0x19);
    FUN_004130d8((int *)param_1[0x114],*(undefined4 *)(param_1[0x95] + 0x2c));
    FUN_004130b8((int *)param_1[0x114],0x1bc);
    iVar1 = (int)*(uint *)(param_1[0x70] + 0x2c) >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x70] + 0x2c) & 1) != 0);
    }
    iVar2 = (int)*(uint *)(param_1[0x114] + 0x2c) >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((*(uint *)(param_1[0x114] + 0x2c) & 1) != 0);
    }
    FUN_00413098((int *)param_1[0x114],(*(int *)(param_1[0x70] + 0x24) + iVar1) - iVar2);
    FUN_00413098((int *)param_1[0x75],0x14a);
  }
  FUN_004130f8((int *)param_1[0x75],*(undefined4 *)(param_1[0x74] + 0x30));
  FUN_004130d8((int *)param_1[0x75],*(undefined4 *)(param_1[0x74] + 0x2c));
  FUN_004130b8((int *)param_1[0x75],*(undefined4 *)(param_1[0x74] + 0x28));
  FUN_004130f8((int *)param_1[0x76],*(undefined4 *)(param_1[0x74] + 0x30));
  FUN_004130d8((int *)param_1[0x76],*(undefined4 *)(param_1[0x74] + 0x2c));
  FUN_004130b8((int *)param_1[0x76],*(undefined4 *)(param_1[0x74] + 0x28));
  FUN_00413098((int *)param_1[0x76],*(undefined4 *)(param_1[0x74] + 0x24));
  FUN_004130f8((int *)param_1[0x115],*(undefined4 *)(param_1[0x114] + 0x30));
  FUN_004130d8((int *)param_1[0x115],*(undefined4 *)(param_1[0x114] + 0x2c));
  uVar11 = *(uint *)(param_1[0x114] + 0x30);
  iVar1 = (int)uVar11 >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((uVar11 & 1) != 0);
  }
  FUN_004130b8((int *)param_1[0x115],*(int *)(param_1[0x114] + 0x28) + iVar1);
  FUN_00413098((int *)param_1[0x115],
               (*(int *)(param_1[0x114] + 0x24) - ((int *)param_1[0x115])[0xb]) -
               *(int *)(param_1[0x114] + 0x30) / 10);
  FUN_004130f8((int *)param_1[0x116],*(undefined4 *)(param_1[0x114] + 0x30));
  FUN_004130d8((int *)param_1[0x116],*(undefined4 *)(param_1[0x114] + 0x2c));
  FUN_004130b8((int *)param_1[0x116],*(undefined4 *)(param_1[0x115] + 0x28));
  iVar1 = param_1[0x114];
  FUN_00413098((int *)param_1[0x116],
               *(int *)(iVar1 + 0x30) / 10 + *(int *)(iVar1 + 0x24) + *(int *)(iVar1 + 0x2c));
  FUN_004130f8((int *)param_1[0x117],*(undefined4 *)(param_1[0x114] + 0x30));
  FUN_004130d8((int *)param_1[0x117],*(undefined4 *)(param_1[0x114] + 0x2c));
  FUN_004130b8((int *)param_1[0x117],
               *(int *)(param_1[0x114] + 0x30) / 10 +
               *(int *)(param_1[0x114] + 0x28) + *(int *)(param_1[0x114] + 0x30));
  FUN_00413098((int *)param_1[0x117],*(undefined4 *)(param_1[0x114] + 0x24));
  iVar1 = (int)*(uint *)(param_1[0x77] + 0x30) >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x77] + 0x30) & 1) != 0);
  }
  FUN_004130f8((int *)param_1[0x78],iVar1);
  iVar1 = (int)*(uint *)(param_1[0x77] + 0x2c) >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x77] + 0x2c) & 1) != 0);
  }
  FUN_004130d8((int *)param_1[0x78],*(int *)(param_1[0x77] + 0x2c) + iVar1);
  FUN_004130b8((int *)param_1[0x78],*(int *)(param_1[0x77] + 0x28) + *(int *)(param_1[0x77] + 0x30))
  ;
  iVar1 = (int)*(uint *)(param_1[0x77] + 0x2c) >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x77] + 0x2c) & 1) != 0);
  }
  iVar2 = (int)*(uint *)(param_1[0x78] + 0x2c) >> 1;
  if (iVar2 < 0) {
    iVar2 = iVar2 + (uint)((*(uint *)(param_1[0x78] + 0x2c) & 1) != 0);
  }
  FUN_00413098((int *)param_1[0x78],(*(int *)(param_1[0x77] + 0x24) + iVar1) - iVar2);
  FUN_004130f8((int *)param_1[0x79],*(undefined4 *)(param_1[0x78] + 0x30));
  FUN_004130d8((int *)param_1[0x79],*(undefined4 *)(param_1[0x78] + 0x2c));
  FUN_004130b8((int *)param_1[0x79],*(int *)(param_1[0x78] + 0x28) + *(int *)(param_1[0x78] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x79],*(undefined4 *)(param_1[0x78] + 0x24));
  FUN_004130f8((int *)param_1[0x7a],*(undefined4 *)(param_1[0x78] + 0x30));
  FUN_004130d8((int *)param_1[0x7a],*(undefined4 *)(param_1[0x78] + 0x2c));
  FUN_004130b8((int *)param_1[0x7a],*(int *)(param_1[0x79] + 0x28) + *(int *)(param_1[0x79] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x7a],*(undefined4 *)(param_1[0x78] + 0x24));
  iVar1 = (int)*(uint *)(param_1[0x7b] + 0x30) >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x7b] + 0x30) & 1) != 0);
  }
  FUN_004130f8((int *)param_1[0x7c],iVar1);
  iVar1 = (int)*(uint *)(param_1[0x7b] + 0x2c) >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x7b] + 0x2c) & 1) != 0);
  }
  FUN_004130d8((int *)param_1[0x7c],iVar1);
  FUN_004130b8((int *)param_1[0x7c],*(int *)(param_1[0x7b] + 0x28) + *(int *)(param_1[0x7b] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x7c],*(int *)(param_1[0x7b] + 0x24) - *(int *)(param_1[0x7b] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0x7d],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x7d],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x7d],*(undefined4 *)(param_1[0x7c] + 0x28));
  FUN_00413098((int *)param_1[0x7d],*(int *)(param_1[0x7c] + 0x24) + *(int *)(param_1[0x7c] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0x7e],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x7e],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x7e],*(undefined4 *)(param_1[0x7c] + 0x28));
  FUN_00413098((int *)param_1[0x7e],*(int *)(param_1[0x7d] + 0x24) + *(int *)(param_1[0x7d] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0x7f],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x7f],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x7f],*(undefined4 *)(param_1[0x7c] + 0x28));
  FUN_00413098((int *)param_1[0x7f],*(int *)(param_1[0x7e] + 0x24) + *(int *)(param_1[0x7e] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0x80],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x80],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x80],*(undefined4 *)(param_1[0x7c] + 0x28));
  FUN_00413098((int *)param_1[0x80],*(int *)(param_1[0x7f] + 0x24) + *(int *)(param_1[0x7f] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0x81],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x81],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x81],*(undefined4 *)(param_1[0x7c] + 0x28));
  FUN_00413098((int *)param_1[0x81],*(int *)(param_1[0x80] + 0x24) + *(int *)(param_1[0x80] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0x82],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x82],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x82],*(int *)(param_1[0x7c] + 0x28) + *(int *)(param_1[0x7c] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x82],*(undefined4 *)(param_1[0x7c] + 0x24));
  FUN_004130f8((int *)param_1[0x83],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x83],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x83],*(undefined4 *)(param_1[0x82] + 0x28));
  FUN_00413098((int *)param_1[0x83],*(undefined4 *)(param_1[0x7d] + 0x24));
  FUN_004130f8((int *)param_1[0x84],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x84],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x84],*(undefined4 *)(param_1[0x82] + 0x28));
  FUN_00413098((int *)param_1[0x84],*(undefined4 *)(param_1[0x7e] + 0x24));
  FUN_004130f8((int *)param_1[0x85],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x85],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x85],*(undefined4 *)(param_1[0x82] + 0x28));
  FUN_00413098((int *)param_1[0x85],*(undefined4 *)(param_1[0x7f] + 0x24));
  FUN_004130f8((int *)param_1[0x86],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x86],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x86],*(undefined4 *)(param_1[0x82] + 0x28));
  FUN_00413098((int *)param_1[0x86],*(undefined4 *)(param_1[0x80] + 0x24));
  FUN_004130f8((int *)param_1[0x87],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x87],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x87],*(undefined4 *)(param_1[0x82] + 0x28));
  FUN_00413098((int *)param_1[0x87],*(undefined4 *)(param_1[0x81] + 0x24));
  FUN_004130f8((int *)param_1[0x88],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x88],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x88],*(int *)(param_1[0x82] + 0x28) + *(int *)(param_1[0x82] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x88],*(undefined4 *)(param_1[0x7c] + 0x24));
  FUN_004130f8((int *)param_1[0x89],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x89],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x89],*(undefined4 *)(param_1[0x88] + 0x28));
  FUN_00413098((int *)param_1[0x89],*(undefined4 *)(param_1[0x7d] + 0x24));
  FUN_004130f8((int *)param_1[0x8a],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x8a],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x8a],*(undefined4 *)(param_1[0x88] + 0x28));
  FUN_00413098((int *)param_1[0x8a],*(undefined4 *)(param_1[0x7e] + 0x24));
  FUN_004130f8((int *)param_1[0x8b],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x8b],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x8b],*(undefined4 *)(param_1[0x88] + 0x28));
  FUN_00413098((int *)param_1[0x8b],*(undefined4 *)(param_1[0x7f] + 0x24));
  FUN_004130f8((int *)param_1[0x8c],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x8c],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x8c],*(undefined4 *)(param_1[0x88] + 0x28));
  FUN_00413098((int *)param_1[0x8c],*(undefined4 *)(param_1[0x80] + 0x24));
  FUN_004130f8((int *)param_1[0x8d],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x8d],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x8d],*(undefined4 *)(param_1[0x88] + 0x28));
  FUN_00413098((int *)param_1[0x8d],*(undefined4 *)(param_1[0x81] + 0x24));
  FUN_004130f8((int *)param_1[0x8e],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x8e],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x8e],*(int *)(param_1[0x88] + 0x28) + *(int *)(param_1[0x88] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x8e],*(undefined4 *)(param_1[0x7c] + 0x24));
  FUN_004130f8((int *)param_1[0x8f],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x8f],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x8f],*(undefined4 *)(param_1[0x8e] + 0x28));
  FUN_00413098((int *)param_1[0x8f],*(undefined4 *)(param_1[0x7d] + 0x24));
  FUN_004130f8((int *)param_1[0x90],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x90],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x90],*(undefined4 *)(param_1[0x8e] + 0x28));
  FUN_00413098((int *)param_1[0x90],*(undefined4 *)(param_1[0x7e] + 0x24));
  FUN_004130f8((int *)param_1[0x91],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x91],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x91],*(undefined4 *)(param_1[0x8e] + 0x28));
  FUN_00413098((int *)param_1[0x91],*(undefined4 *)(param_1[0x7f] + 0x24));
  FUN_004130f8((int *)param_1[0x92],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x92],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x92],*(undefined4 *)(param_1[0x8e] + 0x28));
  FUN_00413098((int *)param_1[0x92],*(undefined4 *)(param_1[0x80] + 0x24));
  FUN_004130f8((int *)param_1[0x93],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x93],*(undefined4 *)(param_1[0x7c] + 0x2c));
  FUN_004130b8((int *)param_1[0x93],*(undefined4 *)(param_1[0x8e] + 0x28));
  FUN_00413098((int *)param_1[0x93],*(undefined4 *)(param_1[0x81] + 0x24));
  FUN_004130f8((int *)param_1[0x94],*(undefined4 *)(param_1[0x7c] + 0x30));
  FUN_004130d8((int *)param_1[0x94],*(undefined4 *)(param_1[0x7b] + 0x2c));
  FUN_004130b8((int *)param_1[0x94],*(int *)(param_1[0x8e] + 0x28) + *(int *)(param_1[0x8e] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x94],*(undefined4 *)(param_1[0x80] + 0x24));
  if (DAT_00489ba4 == '\0') {
    FUN_004130f8((int *)param_1[0xa4],0x14);
    FUN_004130d8((int *)param_1[0xa4],0x40);
    FUN_004130b8((int *)param_1[0xa4],0x16a);
    FUN_00413098((int *)param_1[0xa4],400);
    FUN_004130f8((int *)param_1[0xb7],0x20);
    FUN_004130d8((int *)param_1[0xb7],0xe0);
    FUN_004130b8((int *)param_1[0xb7],0x50);
    FUN_00413098((int *)param_1[0xb7],0xd0);
  }
  else if (DAT_00489ba4 == '\x01') {
    FUN_004130f8((int *)param_1[0xa4],0x19);
    FUN_004130d8((int *)param_1[0xa4],0x50);
    FUN_004130b8((int *)param_1[0xa4],0x1c5);
    FUN_00413098((int *)param_1[0xa4],500);
    FUN_004130f8((int *)param_1[0xb7],0x28);
    FUN_004130d8((int *)param_1[0xb7],0x118);
    FUN_004130b8((int *)param_1[0xb7],100);
    FUN_00413098((int *)param_1[0xb7],0xff);
  }
  FUN_004130f8((int *)param_1[0xb8],*(undefined4 *)(param_1[0xb7] + 0x30));
  FUN_004130d8((int *)param_1[0xb8],*(undefined4 *)(param_1[0xb7] + 0x2c));
  FUN_004130b8((int *)param_1[0xb8],*(int *)(param_1[0xb7] + 0x28) + *(int *)(param_1[0xb7] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xb8],*(undefined4 *)(param_1[0xb7] + 0x24));
  FUN_004130f8((int *)param_1[0xb9],*(undefined4 *)(param_1[0xb7] + 0x30));
  FUN_004130d8((int *)param_1[0xb9],*(undefined4 *)(param_1[0xb7] + 0x2c));
  FUN_004130b8((int *)param_1[0xb9],*(int *)(param_1[0xb8] + 0x28) + *(int *)(param_1[0xb8] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xb9],*(undefined4 *)(param_1[0xb7] + 0x24));
  FUN_004130f8((int *)param_1[0xba],*(undefined4 *)(param_1[0xb7] + 0x30));
  FUN_004130d8((int *)param_1[0xba],*(undefined4 *)(param_1[0xb7] + 0x2c));
  FUN_004130b8((int *)param_1[0xba],*(int *)(param_1[0xb9] + 0x28) + *(int *)(param_1[0xb9] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xba],*(undefined4 *)(param_1[0xb7] + 0x24));
  iVar1 = FUN_004131bc(DAT_0048c510);
  FUN_004130f8((int *)param_1[0x72],iVar1 - *(int *)(param_1[0x6e] + 0x30));
  FUN_004130d8((int *)param_1[0x72],DAT_0048c510[0xb]);
  FUN_004130b8((int *)param_1[0x72],*(int *)(param_1[0x6e] + 0x28) + *(int *)(param_1[0x6e] + 0x30))
  ;
  FUN_00413098((int *)param_1[0x72],*(undefined4 *)(param_1[0x6f] + 0x24));
  if (DAT_00489ba4 == '\0') {
    FUN_004130f8((int *)param_1[0xfc],*(undefined4 *)(param_1[0x72] + 0x30));
    FUN_004130d8((int *)param_1[0xfc],0x67);
    FUN_004130b8((int *)param_1[0xfc],0x2d);
    iVar1 = (int)*(uint *)(param_1[0x6f] + 0x2c) >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x6f] + 0x2c) & 1) != 0);
    }
    iVar2 = (int)*(uint *)(param_1[0xfc] + 0x2c) >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((*(uint *)(param_1[0xfc] + 0x2c) & 1) != 0);
    }
    FUN_00413098((int *)param_1[0xfc],(*(int *)(param_1[0x6f] + 0x24) + iVar1) - iVar2);
    FUN_004130f8((int *)param_1[0xf2],0x14);
    FUN_004130d8((int *)param_1[0xf2],0x4c);
    FUN_004130b8((int *)param_1[0xf2],0x4e);
    FUN_00413098((int *)param_1[0xf2],
                 (*(int *)(param_1[0xfc] + 0x24) + *(int *)(param_1[0xfc] + 0x2c)) -
                 *(int *)(param_1[0xf2] + 0x2c));
    FUN_004130f8((int *)param_1[0xfa],*(undefined4 *)(param_1[0xf2] + 0x30));
    FUN_004130d8((int *)param_1[0xfa],0x44);
    FUN_004130b8((int *)param_1[0xfa],0x40);
    FUN_00413098((int *)param_1[0xfa],*(int *)(param_1[0x70] + 0x24) + 9);
    FUN_004130f8((int *)param_1[0xfb],*(undefined4 *)(param_1[0xf2] + 0x30));
    FUN_004130d8((int *)param_1[0xfb],*(undefined4 *)(param_1[0xfa] + 0x2c));
    FUN_004130b8((int *)param_1[0xfb],0x70);
    FUN_00413098((int *)param_1[0xfb],*(undefined4 *)(param_1[0xfa] + 0x24));
    FUN_004130f8((int *)param_1[0xf9],*(undefined4 *)(param_1[0xf2] + 0x30));
    FUN_004130d8((int *)param_1[0xf9],0x67);
    FUN_004130b8((int *)param_1[0xf9],0x10c);
    FUN_00413098((int *)param_1[0xf9],*(int *)(param_1[0x70] + 0x24) + 9);
    FUN_004130f8((int *)param_1[0xf6],*(undefined4 *)(param_1[0xf2] + 0x30));
    FUN_004130b8((int *)param_1[0xf6],
                 *(int *)(param_1[0xf9] + 0x28) + *(int *)(param_1[0xf9] + 0x30));
    FUN_00413098((int *)param_1[0xf6],*(int *)(param_1[0x70] + 0x24) + 0x2a);
    FUN_004130d8((int *)param_1[0xf6],
                 (*(int *)(param_1[0xf9] + 0x24) + *(int *)(param_1[0xf9] + 0x2c)) -
                 *(int *)(param_1[0xf6] + 0x24));
    FUN_004130f8((int *)param_1[0xa5],0x14);
    FUN_004130d8((int *)param_1[0xa5],0x72);
    FUN_004130b8((int *)param_1[0xa5],0x50);
    FUN_00413098((int *)param_1[0xa5],0xb5);
    FUN_004130f8((int *)param_1[0xa6],*(undefined4 *)(param_1[0xa5] + 0x30));
    FUN_004130d8((int *)param_1[0xa6],0x13e);
    FUN_004130f8((int *)param_1[0x120],0x28);
    FUN_004130d8((int *)param_1[0x120],0xb8);
  }
  else if (DAT_00489ba4 == '\x01') {
    FUN_004130f8((int *)param_1[0xfc],*(undefined4 *)(param_1[0x72] + 0x30));
    FUN_004130d8((int *)param_1[0xfc],0x81);
    FUN_004130b8((int *)param_1[0xfc],0x38);
    iVar1 = (int)*(uint *)(param_1[0x6f] + 0x2c) >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x6f] + 0x2c) & 1) != 0);
    }
    iVar2 = (int)*(uint *)(param_1[0xfc] + 0x2c) >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((*(uint *)(param_1[0xfc] + 0x2c) & 1) != 0);
    }
    FUN_00413098((int *)param_1[0xfc],(*(int *)(param_1[0x6f] + 0x24) + iVar1) - iVar2);
    FUN_004130f8((int *)param_1[0xf2],0x19);
    FUN_004130d8((int *)param_1[0xf2],0x5f);
    FUN_004130b8((int *)param_1[0xf2],0x62);
    FUN_00413098((int *)param_1[0xf2],
                 (*(int *)(param_1[0xfc] + 0x24) + *(int *)(param_1[0xfc] + 0x2c)) -
                 *(int *)(param_1[0xf2] + 0x2c));
    FUN_004130f8((int *)param_1[0xfa],*(undefined4 *)(param_1[0xf2] + 0x30));
    FUN_004130d8((int *)param_1[0xfa],0x55);
    FUN_004130b8((int *)param_1[0xfa],0x50);
    FUN_00413098((int *)param_1[0xfa],*(int *)(param_1[0x70] + 0x24) + 0xb);
    FUN_004130f8((int *)param_1[0xfb],*(undefined4 *)(param_1[0xf2] + 0x30));
    FUN_004130d8((int *)param_1[0xfb],*(undefined4 *)(param_1[0xfa] + 0x2c));
    FUN_004130b8((int *)param_1[0xfb],0x8c);
    FUN_00413098((int *)param_1[0xfb],*(undefined4 *)(param_1[0xfa] + 0x24));
    FUN_004130f8((int *)param_1[0xf9],*(undefined4 *)(param_1[0xf2] + 0x30));
    FUN_004130d8((int *)param_1[0xf9],0x81);
    FUN_004130b8((int *)param_1[0xf9],0x14f);
    FUN_00413098((int *)param_1[0xf9],*(int *)(param_1[0x70] + 0x24) + 0xb);
    FUN_004130f8((int *)param_1[0xf6],*(undefined4 *)(param_1[0xf2] + 0x30));
    FUN_004130b8((int *)param_1[0xf6],
                 *(int *)(param_1[0xf9] + 0x28) + *(int *)(param_1[0xf9] + 0x30));
    FUN_00413098((int *)param_1[0xf6],*(int *)(param_1[0x70] + 0x24) + 0x35);
    FUN_004130d8((int *)param_1[0xf6],
                 (*(int *)(param_1[0xf9] + 0x24) + *(int *)(param_1[0xf9] + 0x2c)) -
                 *(int *)(param_1[0xf6] + 0x24));
    FUN_004130f8((int *)param_1[0xa5],0x19);
    FUN_004130d8((int *)param_1[0xa5],0x8f);
    FUN_004130b8((int *)param_1[0xa5],100);
    FUN_00413098((int *)param_1[0xa5],0xe2);
    FUN_004130f8((int *)param_1[0xa6],*(undefined4 *)(param_1[0xa5] + 0x30));
    FUN_004130d8((int *)param_1[0xa6],0x18e);
    FUN_004130f8((int *)param_1[0x120],0x32);
    FUN_004130d8((int *)param_1[0x120],0xe6);
  }
  iVar1 = FUN_004131bc(param_1);
  FUN_004130b8((int *)param_1[0x120],
               ((iVar1 - *(int *)(param_1[0x72] + 0x30)) - *(int *)(param_1[0x120] + 0x30)) + -4);
  iVar1 = FUN_00413178(param_1);
  FUN_00413098((int *)param_1[0x120],(iVar1 - *(int *)(param_1[0x120] + 0x2c)) + -4);
  FUN_004130f8((int *)param_1[0x121],*(int *)(param_1[0x120] + 0x30) + -4);
  FUN_004130d8((int *)param_1[0x121],*(int *)(param_1[0x120] + 0x2c) + -4);
  uVar11 = *(int *)(param_1[0x120] + 0x30) - *(int *)(param_1[0x121] + 0x30);
  iVar1 = (int)uVar11 >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((uVar11 & 1) != 0);
  }
  FUN_004130b8((int *)param_1[0x121],iVar1);
  uVar11 = *(int *)(param_1[0x120] + 0x2c) - *(int *)(param_1[0x121] + 0x2c);
  iVar1 = (int)uVar11 >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((uVar11 & 1) != 0);
  }
  FUN_00413098((int *)param_1[0x121],iVar1);
  FUN_004130f8((int *)param_1[0xf3],*(undefined4 *)(param_1[0xf2] + 0x30));
  FUN_004130d8((int *)param_1[0xf3],*(undefined4 *)(param_1[0xf2] + 0x2c));
  FUN_004130b8((int *)param_1[0xf3],*(int *)(param_1[0xf2] + 0x28) + *(int *)(param_1[0xfc] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xf3],*(undefined4 *)(param_1[0xf2] + 0x24));
  FUN_004130f8((int *)param_1[0xf4],*(undefined4 *)(param_1[0xf2] + 0x30));
  FUN_004130d8((int *)param_1[0xf4],*(undefined4 *)(param_1[0xf2] + 0x2c));
  FUN_004130b8((int *)param_1[0xf4],*(int *)(param_1[0xf3] + 0x28) + *(int *)(param_1[0xfc] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xf4],*(undefined4 *)(param_1[0xf2] + 0x24));
  FUN_004130f8((int *)param_1[0xf5],*(undefined4 *)(param_1[0xf2] + 0x30));
  FUN_004130d8((int *)param_1[0xf5],*(undefined4 *)(param_1[0xf2] + 0x2c));
  FUN_004130b8((int *)param_1[0xf5],*(int *)(param_1[0xf4] + 0x28) + *(int *)(param_1[0xfc] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xf5],*(undefined4 *)(param_1[0xf2] + 0x24));
  FUN_004130f8((int *)param_1[0xf7],*(undefined4 *)(param_1[0xf2] + 0x30));
  FUN_004130d8((int *)param_1[0xf7],*(undefined4 *)(param_1[0xf6] + 0x2c));
  FUN_004130b8((int *)param_1[0xf7],*(int *)(param_1[0xf6] + 0x28) + *(int *)(param_1[0xf6] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xf7],*(undefined4 *)(param_1[0xf6] + 0x24));
  FUN_004130f8((int *)param_1[0xf8],*(undefined4 *)(param_1[0xf2] + 0x30));
  FUN_004130d8((int *)param_1[0xf8],*(undefined4 *)(param_1[0xf6] + 0x2c));
  FUN_004130b8((int *)param_1[0xf8],*(int *)(param_1[0xf7] + 0x28) + *(int *)(param_1[0xf7] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xf8],*(undefined4 *)(param_1[0xf7] + 0x24));
  FUN_004130b8((int *)param_1[0xa6],*(int *)(param_1[0xa5] + 0x28) + *(int *)(param_1[0xa5] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xa6],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xa7],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xa7],*(undefined4 *)(param_1[0xa5] + 0x2c));
  FUN_004130b8((int *)param_1[0xa7],*(int *)(param_1[0xa6] + 0x28) + *(int *)(param_1[0xa6] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xa7],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xa8],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xa8],*(undefined4 *)(param_1[0xa6] + 0x2c));
  FUN_004130b8((int *)param_1[0xa8],*(int *)(param_1[0xa7] + 0x28) + *(int *)(param_1[0xa7] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xa8],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xa9],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xa9],*(undefined4 *)(param_1[0xa5] + 0x2c));
  FUN_004130b8((int *)param_1[0xa9],*(int *)(param_1[0xa8] + 0x28) + *(int *)(param_1[0xa8] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xa9],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xaa],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xaa],*(undefined4 *)(param_1[0xa6] + 0x2c));
  FUN_004130b8((int *)param_1[0xaa],*(int *)(param_1[0xa9] + 0x28) + *(int *)(param_1[0xa9] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xaa],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xab],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xab],*(undefined4 *)(param_1[0xa5] + 0x2c));
  FUN_004130b8((int *)param_1[0xab],*(int *)(param_1[0xaa] + 0x28) + *(int *)(param_1[0xaa] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xab],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xac],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xac],*(undefined4 *)(param_1[0xa6] + 0x2c));
  FUN_004130b8((int *)param_1[0xac],*(int *)(param_1[0xab] + 0x28) + *(int *)(param_1[0xab] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xac],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xad],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xad],*(undefined4 *)(param_1[0xa5] + 0x2c));
  FUN_004130b8((int *)param_1[0xad],*(int *)(param_1[0xac] + 0x28) + *(int *)(param_1[0xac] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xad],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xae],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xae],*(undefined4 *)(param_1[0xa6] + 0x2c));
  FUN_004130b8((int *)param_1[0xae],*(int *)(param_1[0xad] + 0x28) + *(int *)(param_1[0xad] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xae],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xaf],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xaf],*(undefined4 *)(param_1[0xa5] + 0x2c));
  FUN_004130b8((int *)param_1[0xaf],*(int *)(param_1[0xae] + 0x28) + *(int *)(param_1[0xae] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xaf],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xb0],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xb0],*(undefined4 *)(param_1[0xa6] + 0x2c));
  FUN_004130b8((int *)param_1[0xb0],*(int *)(param_1[0xaf] + 0x28) + *(int *)(param_1[0xaf] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xb0],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xb1],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xb1],*(undefined4 *)(param_1[0xa5] + 0x2c));
  FUN_004130b8((int *)param_1[0xb1],*(int *)(param_1[0xb0] + 0x28) + *(int *)(param_1[0xb0] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xb1],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xb2],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xb2],*(undefined4 *)(param_1[0xa6] + 0x2c));
  FUN_004130b8((int *)param_1[0xb2],*(int *)(param_1[0xb1] + 0x28) + *(int *)(param_1[0xb1] + 0x30))
  ;
  FUN_00413098((int *)param_1[0xb2],*(undefined4 *)(param_1[0xa5] + 0x24));
  FUN_004130f8((int *)param_1[0xbc],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xbc],*(int *)(param_1[0xa6] + 0x2c) - *(int *)(param_1[0xa5] + 0x2c))
  ;
  FUN_004130b8((int *)param_1[0xbc],*(undefined4 *)(param_1[0xa5] + 0x28));
  FUN_00413098((int *)param_1[0xbc],*(int *)(param_1[0xa5] + 0x24) + *(int *)(param_1[0xa5] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0xbd],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xbd],*(int *)(param_1[0xa6] + 0x2c) - *(int *)(param_1[0xa5] + 0x2c))
  ;
  FUN_004130b8((int *)param_1[0xbd],*(undefined4 *)(param_1[0xa7] + 0x28));
  FUN_00413098((int *)param_1[0xbd],*(int *)(param_1[0xa7] + 0x24) + *(int *)(param_1[0xa7] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0xbe],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xbe],*(int *)(param_1[0xa6] + 0x2c) - *(int *)(param_1[0xa5] + 0x2c))
  ;
  FUN_004130b8((int *)param_1[0xbe],*(undefined4 *)(param_1[0xa9] + 0x28));
  FUN_00413098((int *)param_1[0xbe],*(int *)(param_1[0xa9] + 0x24) + *(int *)(param_1[0xa9] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0xbf],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xbf],*(int *)(param_1[0xa6] + 0x2c) - *(int *)(param_1[0xa5] + 0x2c))
  ;
  FUN_004130b8((int *)param_1[0xbf],*(undefined4 *)(param_1[0xab] + 0x28));
  FUN_00413098((int *)param_1[0xbf],*(int *)(param_1[0xab] + 0x24) + *(int *)(param_1[0xab] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0xc0],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xc0],*(int *)(param_1[0xa6] + 0x2c) - *(int *)(param_1[0xa5] + 0x2c))
  ;
  FUN_004130b8((int *)param_1[0xc0],*(undefined4 *)(param_1[0xad] + 0x28));
  FUN_00413098((int *)param_1[0xc0],*(int *)(param_1[0xad] + 0x24) + *(int *)(param_1[0xad] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0xc1],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xc1],*(int *)(param_1[0xa6] + 0x2c) - *(int *)(param_1[0xa5] + 0x2c))
  ;
  FUN_004130b8((int *)param_1[0xc1],*(undefined4 *)(param_1[0xaf] + 0x28));
  FUN_00413098((int *)param_1[0xc1],*(int *)(param_1[0xaf] + 0x24) + *(int *)(param_1[0xaf] + 0x2c))
  ;
  FUN_004130f8((int *)param_1[0xc2],*(undefined4 *)(param_1[0xa5] + 0x30));
  FUN_004130d8((int *)param_1[0xc2],*(int *)(param_1[0xa6] + 0x2c) - *(int *)(param_1[0xa5] + 0x2c))
  ;
  FUN_004130b8((int *)param_1[0xc2],*(undefined4 *)(param_1[0xb1] + 0x28));
  FUN_00413098((int *)param_1[0xc2],*(int *)(param_1[0xb1] + 0x24) + *(int *)(param_1[0xb1] + 0x2c))
  ;
  if (DAT_00489ba4 == '\0') {
    FUN_004130f8((int *)param_1[0x73],200);
    FUN_004130d8((int *)param_1[0x73],0x17e);
    FUN_004130b8((int *)param_1[0x73],0x2d);
    FUN_00413098((int *)param_1[0x73],0x81);
    uVar5 = extraout_ECX_00;
  }
  else {
    uVar5 = extraout_ECX;
    if (DAT_00489ba4 == '\x01') {
      FUN_004130f8((int *)param_1[0x73],0xfa);
      FUN_004130d8((int *)param_1[0x73],0x1de);
      FUN_004130b8((int *)param_1[0x73],0x38);
      FUN_00413098((int *)param_1[0x73],0xa1);
      uVar5 = extraout_ECX_01;
    }
  }
  FUN_00413500((int *)param_1[0x6e],0,uVar5);
  FUN_00413500((int *)param_1[0x6f],0,extraout_ECX_02);
  FUN_00413500((int *)param_1[0x70],0,extraout_ECX_03);
  (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
            (*(int **)(param_1[0x111] + 0x118),1,&local_8);
  FUN_00403658(&local_8,DAT_0048c5fc);
  FUN_00403658(&local_8,(undefined4 *)"\\center.bmp");
  FUN_0041c1e8(*(int *)(param_1[0x6e] + 0xac),local_8);
  if (original_hero.cycle_factor_minus_one == 0) {
    (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
              (*(int **)(param_1[0x111] + 0x118),1,&local_8);
    FUN_00403658(&local_8,DAT_0048c5fc);
    FUN_00403658(&local_8,(undefined4 *)"\\left.bmp");
    FUN_0041c1e8(*(int *)(param_1[0x6f] + 0xac),local_8);
  }
  else {
    (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
              (*(int **)(param_1[0x111] + 0x118),1,&local_8);
    FUN_00403658(&local_8,DAT_0048c5fc);
    FUN_00403658(&local_8,(undefined4 *)"\\leftr.bmp");
    FUN_0041c1e8(*(int *)(param_1[0x6f] + 0xac),local_8);
  }
  if (original_hero.cycle_factor_minus_one == 0) {
    (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
              (*(int **)(param_1[0x111] + 0x118),1,&local_8);
    FUN_00403658(&local_8,DAT_0048c5fc);
    FUN_00403658(&local_8,(undefined4 *)"\\right.bmp");
    FUN_0041c1e8(*(int *)(param_1[0x70] + 0xac),local_8);
    uVar5 = extraout_ECX_04;
    uVar6 = extraout_EDX;
  }
  else {
    (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
              (*(int **)(param_1[0x111] + 0x118),1,&local_8);
    FUN_00403658(&local_8,DAT_0048c5fc);
    FUN_00403658(&local_8,(undefined4 *)"\\rightr.bmp");
    FUN_0041c1e8(*(int *)(param_1[0x70] + 0xac),local_8);
    uVar5 = extraout_ECX_05;
    uVar6 = extraout_EDX_00;
  }
  DAT_0048c514 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)uVar6 >> 8),1),uVar5);
  (**(code **)(*DAT_0048c514 + 0x28))(DAT_0048c514,*(int *)(param_1[0x95] + 0x30) * 0xb);
  (**(code **)(*DAT_0048c514 + 0x2c))
            (DAT_0048c514,
             *(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
             *(int *)(param_1[0x70] + 0x2c));
  (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
            (*(int **)(param_1[0x111] + 0x118),1,&local_8);
  FUN_00403658(&local_8,DAT_0048c5fc);
  FUN_00403658(&local_8,(undefined4 *)"\\chtable.oz");
  (**(code **)(*DAT_0048c514 + 0x34))(DAT_0048c514,local_8);
  DAT_0048c518 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                                     extraout_ECX_06);
  (**(code **)(*DAT_0048c518 + 0x2c))(DAT_0048c518,*(undefined4 *)(param_1[0x95] + 0x2c));
  (**(code **)(*DAT_0048c518 + 0x28))(DAT_0048c518,*(undefined4 *)(param_1[0x95] + 0x30));
  iVar1 = FUN_0041dad8((int)DAT_0048c518);
  *(undefined4 *)(iVar1 + 0x20) = 0xcc0020;
  FUN_0040923c(0,0,*(undefined4 *)(param_1[0x95] + 0x2c),local_18,
               *(undefined4 *)(param_1[0x95] + 0x30));
  puVar12 = local_18;
  puVar13 = &DAT_0048c53c;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + (uint)bVar14 * -2 + 1;
    puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
  }
  FUN_004178f4((int *)param_1[0x6c],*(int *)(param_1[0x95] + 0x2c));
  FUN_0041793c((int *)param_1[0x6c],*(int *)(param_1[0x95] + 0x30));
  iVar1 = 0;
  do {
    iVar2 = 0;
    do {
      if ((iVar1 < 0x13) || ((iVar1 == 0x13 && (iVar2 < 9)))) {
        FUN_0040923c(*(int *)(param_1[0x95] + 0x2c) * iVar2,*(int *)(param_1[0x95] + 0x30) * iVar1,
                     (iVar2 + 1) * *(int *)(param_1[0x95] + 0x2c),local_18,
                     (iVar1 + 1) * *(int *)(param_1[0x95] + 0x30));
        puVar12 = local_18;
        puVar13 = &DAT_0048c52c;
        for (iVar10 = 4; iVar10 != 0; iVar10 = iVar10 + -1) {
          *puVar13 = *puVar12;
          puVar12 = puVar12 + (uint)bVar14 * -2 + 1;
          puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
        }
        piVar15 = &DAT_0048c52c;
        piVar3 = (int *)FUN_0041dad8((int)DAT_0048c514);
        piVar4 = (int *)FUN_0041dad8((int)DAT_0048c518);
        FUN_0041a530(piVar4,&DAT_0048c53c,piVar3,piVar15);
        FUN_00417b00((int *)param_1[0x6c],DAT_0048c518,0);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != 0xb);
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x14);
  (**(code **)(*DAT_0048c514 + 0x28))(DAT_0048c514,*(int *)(param_1[0x95] + 0x30) * 0xb);
  (**(code **)(*DAT_0048c514 + 0x2c))(DAT_0048c514,*(int *)(param_1[0x95] + 0x2c) * 0xf);
  (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
            (*(int **)(param_1[0x111] + 0x118),1,&local_8);
  FUN_00403658(&local_8,DAT_0048c5fc);
  FUN_00403658(&local_8,(undefined4 *)"\\chtableb.oz");
  (**(code **)(*DAT_0048c514 + 0x34))(DAT_0048c514,local_8);
  FUN_004178f4((int *)param_1[0x103],*(int *)(param_1[0x95] + 0x2c));
  FUN_0041793c((int *)param_1[0x103],*(int *)(param_1[0x95] + 0x30));
  DAT_0048c518 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                                     extraout_ECX_07);
  (**(code **)(*DAT_0048c518 + 0x2c))(DAT_0048c518,*(undefined4 *)(param_1[0x95] + 0x2c));
  (**(code **)(*DAT_0048c518 + 0x28))(DAT_0048c518,*(undefined4 *)(param_1[0x95] + 0x30));
  iVar1 = FUN_0041dad8((int)DAT_0048c518);
  *(undefined4 *)(iVar1 + 0x20) = 0xcc0020;
  FUN_0040923c(0,0,*(undefined4 *)(param_1[0x95] + 0x2c),local_18,
               *(undefined4 *)(param_1[0x95] + 0x30));
  puVar12 = local_18;
  puVar13 = &DAT_0048c53c;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + (uint)bVar14 * -2 + 1;
    puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
  }
  iVar1 = 0;
  do {
    iVar2 = 0;
    do {
      if ((iVar1 < 0xe) || ((iVar1 == 0xe && (iVar2 < 5)))) {
        FUN_0040923c(*(int *)(param_1[0x95] + 0x2c) * iVar2,*(int *)(param_1[0x95] + 0x30) * iVar1,
                     (iVar2 + 1) * *(int *)(param_1[0x95] + 0x2c),local_18,
                     (iVar1 + 1) * *(int *)(param_1[0x95] + 0x30));
        puVar12 = local_18;
        puVar13 = &DAT_0048c52c;
        for (iVar10 = 4; iVar10 != 0; iVar10 = iVar10 + -1) {
          *puVar13 = *puVar12;
          puVar12 = puVar12 + (uint)bVar14 * -2 + 1;
          puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
        }
        piVar15 = &DAT_0048c52c;
        piVar3 = (int *)FUN_0041dad8((int)DAT_0048c514);
        piVar4 = (int *)FUN_0041dad8((int)DAT_0048c518);
        FUN_0041a530(piVar4,&DAT_0048c53c,piVar3,piVar15);
        FUN_00417b00((int *)param_1[0x103],DAT_0048c518,0);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != 0xb);
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0xf);
  FUN_00402c34(DAT_0048c514);
  DAT_0048c514 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                                     extraout_ECX_08);
  (**(code **)(*DAT_0048c514 + 0x28))(DAT_0048c514,*(undefined4 *)(param_1[0x95] + 0x30));
  (**(code **)(*DAT_0048c514 + 0x2c))(DAT_0048c514,*(undefined4 *)(param_1[0x95] + 0x2c));
  (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
            (*(int **)(param_1[0x111] + 0x118),1,&local_8);
  FUN_00403658(&local_8,DAT_0048c5fc);
  FUN_00403658(&local_8,(undefined4 *)"\\key.oz");
  (**(code **)(*DAT_0048c514 + 0x34))(DAT_0048c514,local_8);
  iVar1 = (int)*(uint *)(param_1[0x95] + 0x2c) >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x95] + 0x2c) & 1) != 0);
  }
  FUN_004178f4((int *)param_1[0x71],iVar1);
  iVar1 = (int)*(uint *)(param_1[0x95] + 0x30) >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x95] + 0x30) & 1) != 0);
  }
  FUN_0041793c((int *)param_1[0x71],iVar1);
  iVar1 = (int)*(uint *)(param_1[0x95] + 0x2c) >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x95] + 0x2c) & 1) != 0);
  }
  (**(code **)(*DAT_0048c518 + 0x2c))(DAT_0048c518,iVar1);
  iVar1 = (int)*(uint *)(param_1[0x95] + 0x30) >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((*(uint *)(param_1[0x95] + 0x30) & 1) != 0);
  }
  (**(code **)(*DAT_0048c518 + 0x28))(DAT_0048c518,iVar1);
  iVar1 = FUN_0041dad8((int)DAT_0048c518);
  *(undefined4 *)(iVar1 + 0x20) = 0xcc0020;
  uVar5 = (**(code **)(*DAT_0048c518 + 0x1c))();
  puVar12 = local_18;
  uVar6 = (**(code **)(*DAT_0048c518 + 0x20))();
  FUN_0040923c(0,0,uVar6,puVar12,uVar5);
  puVar12 = local_18;
  puVar13 = &DAT_0048c53c;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + (uint)bVar14 * -2 + 1;
    puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
  }
  iVar1 = 0;
  do {
    iVar2 = 0;
    do {
      iVar10 = (**(code **)(*DAT_0048c518 + 0x1c))();
      iVar10 = iVar10 * (iVar1 + 1);
      puVar12 = local_18;
      iVar7 = (**(code **)(*DAT_0048c518 + 0x20))();
      iVar8 = (**(code **)(*DAT_0048c518 + 0x1c))();
      iVar9 = (**(code **)(*DAT_0048c518 + 0x20))();
      FUN_0040923c(iVar9 * iVar2,iVar8 * iVar1,iVar7 * (iVar2 + 1),puVar12,iVar10);
      puVar12 = local_18;
      puVar13 = &DAT_0048c52c;
      for (iVar10 = 4; iVar10 != 0; iVar10 = iVar10 + -1) {
        *puVar13 = *puVar12;
        puVar12 = puVar12 + (uint)bVar14 * -2 + 1;
        puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
      }
      piVar15 = &DAT_0048c52c;
      piVar3 = (int *)FUN_0041dad8((int)DAT_0048c514);
      piVar4 = (int *)FUN_0041dad8((int)DAT_0048c518);
      FUN_0041a530(piVar4,&DAT_0048c53c,piVar3,piVar15);
      FUN_00417b00((int *)param_1[0x71],DAT_0048c518,0);
      iVar2 = iVar2 + 1;
    } while (iVar2 != 2);
    iVar1 = iVar1 + 1;
  } while (iVar1 != 2);
  (**(code **)(*DAT_0048c514 + 0x28))(DAT_0048c514,*(int *)(param_1[0x95] + 0x30) * 0xb);
  (**(code **)(*DAT_0048c514 + 0x2c))(DAT_0048c514,*(int *)(param_1[0x95] + 0x2c) * 0xb);
  uVar5 = (**(code **)(*DAT_0048c514 + 0x1c))();
  (**(code **)(*DAT_0048c518 + 0x28))(DAT_0048c518,uVar5);
  uVar5 = (**(code **)(*DAT_0048c514 + 0x20))();
  (**(code **)(*DAT_0048c518 + 0x2c))(DAT_0048c518,uVar5);
  DAT_0048c51c = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_04 >> 8),1),
                                     extraout_ECX_09);
  (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,*(int *)(param_1[0x95] + 0x30) * 5);
  (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,*(int *)(param_1[0x95] + 0x2c) * 3);
  DAT_0048c520 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_05 >> 8),1),
                                     extraout_ECX_10);
  (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,*(int *)(param_1[0x95] + 0x30) * 2);
  (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,*(int *)(param_1[0x95] + 0x2c) * 3);
  DAT_0048c524 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_06 >> 8),1),
                                     extraout_ECX_11);
  (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,*(undefined4 *)(param_1[0x95] + 0x30));
  (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,*(undefined4 *)(param_1[0x95] + 0x2c));
  DAT_0048c528 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_07 >> 8),1),
                                     extraout_ECX_12);
  (**(code **)(*DAT_0048c528 + 0x2c))
            (DAT_0048c528,
             *(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
             *(int *)(param_1[0x70] + 0x2c));
  (**(code **)(*DAT_0048c528 + 0x28))(DAT_0048c528,*(undefined4 *)(param_1[0x6e] + 0x30));
  FUN_0040352c((int *)(param_1[0x7c] + 0x54),(undefined4 *)"Old Man of 4F");
  FUN_0040352c((int *)(param_1[0x7d] + 0x54),(undefined4 *)"Old Man of 6F");
  FUN_0040352c((int *)(param_1[0x7e] + 0x54),(undefined4 *)"Merchant of 6F");
  FUN_0040352c((int *)(param_1[0x7f] + 0x54),(undefined4 *)"Merchant of 7F");
  FUN_0040352c((int *)(param_1[0x80] + 0x54),(undefined4 *)"Merchant of 12F");
  FUN_0040352c((int *)(param_1[0x81] + 0x54),(undefined4 *)"Merchant of 15F");
  FUN_0040352c((int *)(param_1[0x82] + 0x54),(undefined4 *)"Old Man of 16F");
  FUN_0040352c((int *)(param_1[0x83] + 0x54),(undefined4 *)"Old Man of 18F");
  FUN_0040352c((int *)(param_1[0x84] + 0x54),(undefined4 *)"Old Man of 21F");
  FUN_0040352c((int *)(param_1[0x85] + 0x54),(undefined4 *)"Old Man of 27F");
  FUN_0040352c((int *)(param_1[0x86] + 0x54),(undefined4 *)"Old Man of 31F");
  FUN_0040352c((int *)(param_1[0x87] + 0x54),(undefined4 *)"Merchant of 31F");
  FUN_0040352c((int *)(param_1[0x88] + 0x54),(undefined4 *)"Old Man of 33F");
  FUN_0040352c((int *)(param_1[0x89] + 0x54),(undefined4 *)"Old Man of 36F");
  FUN_0040352c((int *)(param_1[0x8a] + 0x54),(undefined4 *)"Old Man of 37F");
  FUN_0040352c((int *)(param_1[0x8b] + 0x54),(undefined4 *)"Merchant of 38F");
  FUN_0040352c((int *)(param_1[0x8c] + 0x54),(undefined4 *)"Old Man of 39F");
  FUN_0040352c((int *)(param_1[0x8d] + 0x54),(undefined4 *)"Merchant of 39F");
  FUN_0040352c((int *)(param_1[0x8e] + 0x54),(undefined4 *)"Old Man of 42F");
  FUN_0040352c((int *)(param_1[0x8f] + 0x54),(undefined4 *)"Old Man of 45F");
  FUN_0040352c((int *)(param_1[0x90] + 0x54),(undefined4 *)"Merchant of 45F");
  FUN_0040352c((int *)(param_1[0x91] + 0x54),(undefined4 *)"Old Man of 46F");
  FUN_0040352c((int *)(param_1[0x92] + 0x54),(undefined4 *)"Merchant of 47F");
  FUN_0040352c((int *)(param_1[0x93] + 0x54),(undefined4 *)"Old Man of 48F");
  FUN_0040352c((int *)(param_1[0xf2] + 0x54),(undefined4 *)"Vital Power");
  FUN_0040352c((int *)(param_1[0xf3] + 0x54),(undefined4 *)"Offensive Power");
  FUN_0040352c((int *)(param_1[0xf4] + 0x54),(undefined4 *)"Defensive Power");
  FUN_0040352c((int *)(param_1[0xf5] + 0x54),(undefined4 *)&DAT_00488b9c);
  FUN_0040352c((int *)(param_1[0xfa] + 0x54),(undefined4 *)"Name of Sword");
  FUN_0040352c((int *)(param_1[0xfb] + 0x54),(undefined4 *)"Name of Shield");
  FUN_0040352c((int *)(param_1[0x72] + 0x54),(undefined4 *)"Show message.");
  FUN_0040352c((int *)(param_1[0x77] + 0x54),(undefined4 *)"Orb of Flying");
  FUN_0040352c((int *)(param_1[0x7b] + 0x54),(undefined4 *)"Orb of Wisdom");
  FUN_0040352c((int *)(param_1[0x95] + 0x54),(undefined4 *)"Orb of the Hero");
  FUN_0040352c((int *)(param_1[0x96] + 0x54),(undefined4 *)"Cross");
  FUN_0040352c((int *)(param_1[0x97] + 0x54),(undefined4 *)"Magic Elixir");
  FUN_0040352c((int *)(param_1[0x98] + 0x54),(undefined4 *)"Magic Mattock");
  FUN_0040352c((int *)(param_1[0x99] + 0x54),(undefined4 *)"The destructible Ball");
  FUN_0040352c((int *)(param_1[0x9a] + 0x54),(undefined4 *)"Warp Staff");
  FUN_0040352c((int *)(param_1[0x9b] + 0x54),(undefined4 *)"Wing to fly up");
  FUN_0040352c((int *)(param_1[0x9c] + 0x54),(undefined4 *)"Wing to fly down");
  FUN_0040352c((int *)(param_1[0x9d] + 0x54),(undefined4 *)"Dragon Slayer");
  FUN_0040352c((int *)(param_1[0x9e] + 0x54),(undefined4 *)"Snow Crystal");
  FUN_0040352c((int *)(param_1[0x9f] + 0x54),(undefined4 *)"Magic Key");
  FUN_0040352c((int *)(param_1[0xa0] + 0x54),(undefined4 *)"Super Magic Mattock");
  FUN_0040352c((int *)(param_1[0xa1] + 0x54),(undefined4 *)"Lucky Gold");
  FUN_004136ac((int *)param_1[0x7c],'\x01');
  FUN_004136ac((int *)param_1[0x7d],'\x01');
  FUN_004136ac((int *)param_1[0x7e],'\x01');
  FUN_004136ac((int *)param_1[0x7f],'\x01');
  FUN_004136ac((int *)param_1[0x80],'\x01');
  FUN_004136ac((int *)param_1[0x81],'\x01');
  FUN_004136ac((int *)param_1[0x82],'\x01');
  FUN_004136ac((int *)param_1[0x83],'\x01');
  FUN_004136ac((int *)param_1[0x84],'\x01');
  FUN_004136ac((int *)param_1[0x85],'\x01');
  FUN_004136ac((int *)param_1[0x86],'\x01');
  FUN_004136ac((int *)param_1[0x87],'\x01');
  FUN_004136ac((int *)param_1[0x88],'\x01');
  FUN_004136ac((int *)param_1[0x89],'\x01');
  FUN_004136ac((int *)param_1[0x8a],'\x01');
  FUN_004136ac((int *)param_1[0x8b],'\x01');
  FUN_004136ac((int *)param_1[0x8c],'\x01');
  FUN_004136ac((int *)param_1[0x8d],'\x01');
  FUN_004136ac((int *)param_1[0x8e],'\x01');
  FUN_004136ac((int *)param_1[0x8f],'\x01');
  FUN_004136ac((int *)param_1[0x90],'\x01');
  FUN_004136ac((int *)param_1[0x91],'\x01');
  FUN_004136ac((int *)param_1[0x92],'\x01');
  FUN_004136ac((int *)param_1[0x93],'\x01');
  FUN_004136ac((int *)param_1[0xf2],'\x01');
  FUN_004136ac((int *)param_1[0xf3],'\x01');
  FUN_004136ac((int *)param_1[0xf4],'\x01');
  FUN_004136ac((int *)param_1[0xf5],'\x01');
  FUN_004136ac((int *)param_1[0xfa],'\x01');
  FUN_004136ac((int *)param_1[0xfb],'\x01');
  FUN_004136ac((int *)param_1[0x72],'\x01');
  FUN_00419c7c(*(int **)(param_1[0xfc] + 0x44),0xffffff,extraout_ECX_13);
  DAT_0048c5ce = 0;
  DAT_0048c5d0 = 0;
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_00488849;
  puStack_2c = (undefined *)0x488841;
  FUN_004034dc(&local_8);
  return;
}

