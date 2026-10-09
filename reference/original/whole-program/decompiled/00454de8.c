/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00454de8.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void FUN_00454de8(int param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  undefined4 extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_ECX_11;
  undefined4 extraout_ECX_12;
  undefined4 extraout_ECX_13;
  undefined4 extraout_ECX_14;
  undefined4 extraout_ECX_15;
  undefined4 extraout_ECX_16;
  undefined4 extraout_ECX_17;
  undefined4 extraout_ECX_18;
  undefined4 extraout_ECX_19;
  undefined4 extraout_ECX_20;
  undefined4 extraout_ECX_21;
  undefined4 extraout_ECX_22;
  undefined4 extraout_ECX_23;
  undefined4 extraout_ECX_24;
  undefined4 extraout_ECX_25;
  undefined4 extraout_ECX_26;
  undefined4 extraout_ECX_27;
  undefined4 extraout_ECX_28;
  undefined4 extraout_ECX_29;
  undefined4 extraout_ECX_30;
  undefined4 extraout_ECX_31;
  undefined4 extraout_ECX_32;
  undefined4 extraout_ECX_33;
  undefined4 extraout_ECX_34;
  undefined4 extraout_ECX_35;
  undefined4 extraout_ECX_36;
  undefined4 extraout_ECX_37;
  undefined4 extraout_ECX_38;
  undefined4 extraout_ECX_39;
  undefined4 extraout_ECX_40;
  undefined4 extraout_ECX_41;
  undefined4 extraout_ECX_42;
  undefined4 extraout_ECX_43;
  undefined4 extraout_ECX_44;
  undefined4 extraout_ECX_45;
  undefined4 extraout_ECX_46;
  undefined4 extraout_ECX_47;
  undefined4 extraout_ECX_48;
  undefined4 extraout_ECX_49;
  undefined4 extraout_ECX_50;
  undefined4 extraout_ECX_51;
  undefined4 extraout_ECX_52;
  undefined4 extraout_ECX_53;
  undefined4 extraout_ECX_54;
  undefined4 extraout_ECX_55;
  undefined4 extraout_ECX_56;
  undefined4 extraout_ECX_57;
  undefined4 extraout_ECX_58;
  undefined4 extraout_ECX_59;
  undefined4 extraout_ECX_60;
  undefined4 extraout_ECX_61;
  undefined4 extraout_ECX_62;
  undefined4 extraout_ECX_63;
  undefined4 extraout_ECX_64;
  undefined4 extraout_ECX_65;
  undefined4 extraout_ECX_66;
  undefined4 extraout_ECX_67;
  undefined4 extraout_ECX_68;
  undefined4 extraout_ECX_69;
  undefined4 extraout_ECX_70;
  int iVar4;
  undefined4 extraout_ECX_71;
  undefined4 extraout_ECX_72;
  int extraout_ECX_73;
  int extraout_ECX_74;
  int extraout_ECX_75;
  int extraout_ECX_76;
  undefined4 extraout_ECX_77;
  undefined4 extraout_ECX_78;
  undefined4 extraout_ECX_79;
  undefined4 extraout_ECX_80;
  undefined4 extraout_ECX_81;
  undefined4 extraout_ECX_82;
  undefined4 extraout_ECX_83;
  undefined4 extraout_ECX_84;
  undefined4 extraout_ECX_85;
  undefined4 extraout_ECX_86;
  undefined4 extraout_ECX_87;
  undefined4 extraout_ECX_88;
  undefined4 extraout_ECX_89;
  undefined4 extraout_ECX_90;
  undefined4 extraout_ECX_91;
  undefined4 extraout_ECX_92;
  undefined4 extraout_ECX_93;
  undefined4 extraout_ECX_94;
  undefined4 extraout_ECX_95;
  int extraout_ECX_96;
  undefined4 extraout_ECX_97;
  undefined4 extraout_ECX_98;
  undefined4 extraout_ECX_99;
  undefined4 extraout_ECX_x00100;
  undefined4 extraout_ECX_x00101;
  undefined4 extraout_ECX_x00102;
  undefined4 extraout_ECX_x00103;
  undefined4 extraout_ECX_x00104;
  undefined4 extraout_ECX_x00105;
  undefined4 extraout_ECX_x00106;
  undefined4 extraout_ECX_x00107;
  undefined4 extraout_ECX_x00108;
  undefined4 extraout_ECX_x00109;
  undefined4 extraout_ECX_x00110;
  undefined4 extraout_ECX_x00111;
  undefined4 extraout_ECX_x00112;
  undefined4 extraout_ECX_x00113;
  undefined4 extraout_ECX_x00114;
  undefined4 extraout_ECX_x00115;
  undefined4 extraout_ECX_x00116;
  undefined4 extraout_ECX_x00117;
  undefined4 extraout_ECX_x00118;
  undefined4 extraout_ECX_x00119;
  undefined4 extraout_ECX_x00120;
  undefined4 extraout_ECX_x00121;
  undefined4 extraout_ECX_x00122;
  undefined4 extraout_ECX_x00123;
  undefined4 extraout_ECX_x00124;
  int extraout_ECX_x00125;
  int extraout_ECX_x00126;
  int extraout_ECX_x00127;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 extraout_EDX_06;
  undefined4 extraout_EDX_07;
  undefined4 extraout_EDX_08;
  undefined4 extraout_EDX_09;
  undefined4 extraout_EDX_10;
  undefined4 extraout_EDX_11;
  undefined4 extraout_EDX_12;
  undefined4 extraout_EDX_13;
  undefined4 extraout_EDX_14;
  undefined4 extraout_EDX_15;
  undefined4 extraout_EDX_16;
  undefined4 extraout_EDX_17;
  undefined4 extraout_EDX_18;
  undefined4 extraout_EDX_19;
  undefined4 extraout_EDX_20;
  undefined4 extraout_EDX_21;
  undefined4 extraout_EDX_22;
  undefined4 extraout_EDX_23;
  undefined4 extraout_EDX_24;
  undefined4 extraout_EDX_25;
  undefined4 extraout_EDX_26;
  undefined4 extraout_EDX_27;
  undefined4 extraout_EDX_28;
  undefined4 extraout_EDX_29;
  undefined4 extraout_EDX_30;
  undefined4 extraout_EDX_31;
  undefined4 extraout_EDX_32;
  undefined4 extraout_EDX_33;
  undefined4 extraout_EDX_34;
  undefined4 extraout_EDX_35;
  undefined4 extraout_EDX_36;
  undefined4 extraout_EDX_37;
  undefined4 extraout_EDX_38;
  undefined4 extraout_EDX_39;
  undefined4 extraout_EDX_40;
  undefined4 extraout_EDX_41;
  undefined4 extraout_EDX_42;
  undefined4 extraout_EDX_43;
  undefined4 extraout_EDX_44;
  undefined4 extraout_EDX_45;
  undefined4 extraout_EDX_46;
  undefined4 extraout_EDX_47;
  undefined4 extraout_EDX_48;
  undefined4 extraout_EDX_49;
  undefined4 extraout_EDX_50;
  undefined4 extraout_EDX_51;
  undefined4 extraout_EDX_52;
  undefined4 extraout_EDX_53;
  undefined4 extraout_EDX_54;
  undefined4 uVar5;
  undefined4 extraout_EDX_55;
  undefined4 extraout_EDX_56;
  undefined4 extraout_EDX_57;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *in_FS_OFFSET;
  byte bVar9;
  int *piVar10;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined4 local_18 [4];
  undefined4 *local_8;
  
  bVar9 = 0;
  puStack_28 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_2c = &LAB_00455bb5;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  FUN_00413500(*(int **)(param_1 + 0x1cc),0,param_3);
  FUN_00413500(*(int **)(param_1 + 0x1d0),0,extraout_ECX);
  FUN_00413500(*(int **)(param_1 + 0x1d4),0,extraout_ECX_00);
  FUN_00413500(*(int **)(param_1 + 0x450),0,extraout_ECX_01);
  FUN_00413500(*(int **)(param_1 + 0x454),0,extraout_ECX_02);
  FUN_00413500(*(int **)(param_1 + 0x458),0,extraout_ECX_03);
  FUN_00413500(*(int **)(param_1 + 0x45c),0,extraout_ECX_04);
  FUN_00413500(*(int **)(param_1 + 0x1d8),0,extraout_ECX_05);
  FUN_00413500(*(int **)(param_1 + 0x1e0),0,extraout_ECX_06);
  FUN_00413500(*(int **)(param_1 + 0x1e4),0,extraout_ECX_07);
  FUN_00413500(*(int **)(param_1 + 0x1e8),0,extraout_ECX_08);
  FUN_00413500(*(int **)(param_1 + 0x1f0),0,extraout_ECX_09);
  FUN_00413500(*(int **)(param_1 + 500),0,extraout_ECX_10);
  FUN_00413500(*(int **)(param_1 + 0x1f8),0,extraout_ECX_11);
  FUN_00413500(*(int **)(param_1 + 0x1fc),0,extraout_ECX_12);
  FUN_00413500(*(int **)(param_1 + 0x200),0,extraout_ECX_13);
  FUN_00413500(*(int **)(param_1 + 0x204),0,extraout_ECX_14);
  FUN_00413500(*(int **)(param_1 + 0x208),0,extraout_ECX_15);
  FUN_00413500(*(int **)(param_1 + 0x20c),0,extraout_ECX_16);
  FUN_00413500(*(int **)(param_1 + 0x210),0,extraout_ECX_17);
  FUN_00413500(*(int **)(param_1 + 0x214),0,extraout_ECX_18);
  FUN_00413500(*(int **)(param_1 + 0x218),0,extraout_ECX_19);
  FUN_00413500(*(int **)(param_1 + 0x21c),0,extraout_ECX_20);
  FUN_00413500(*(int **)(param_1 + 0x220),0,extraout_ECX_21);
  FUN_00413500(*(int **)(param_1 + 0x224),0,extraout_ECX_22);
  FUN_00413500(*(int **)(param_1 + 0x228),0,extraout_ECX_23);
  FUN_00413500(*(int **)(param_1 + 0x22c),0,extraout_ECX_24);
  FUN_00413500(*(int **)(param_1 + 0x230),0,extraout_ECX_25);
  FUN_00413500(*(int **)(param_1 + 0x234),0,extraout_ECX_26);
  FUN_00413500(*(int **)(param_1 + 0x238),0,extraout_ECX_27);
  FUN_00413500(*(int **)(param_1 + 0x23c),0,extraout_ECX_28);
  FUN_00413500(*(int **)(param_1 + 0x240),0,extraout_ECX_29);
  FUN_00413500(*(int **)(param_1 + 0x244),0,extraout_ECX_30);
  FUN_00413500(*(int **)(param_1 + 0x248),0,extraout_ECX_31);
  FUN_00413500(*(int **)(param_1 + 0x24c),0,extraout_ECX_32);
  FUN_00413500(*(int **)(param_1 + 0x250),0,extraout_ECX_33);
  FUN_00413500(*(int **)(param_1 + 0x290),0,extraout_ECX_34);
  FUN_00413500(*(int **)(param_1 + 0x2cc),0,extraout_ECX_35);
  FUN_00413500(*(int **)(param_1 + 0x2d0),0,extraout_ECX_36);
  FUN_00413500(*(int **)(param_1 + 0x2dc),0,extraout_ECX_37);
  FUN_00413500(*(int **)(param_1 + 0x2e0),0,extraout_ECX_38);
  FUN_00413500(*(int **)(param_1 + 0x2e4),0,extraout_ECX_39);
  FUN_00413500(*(int **)(param_1 + 0x2e8),0,extraout_ECX_40);
  FUN_00413500(*(int **)(param_1 + 0x424),0,extraout_ECX_41);
  FUN_00413500(*(int **)(param_1 + 0x294),0,extraout_ECX_42);
  FUN_00413500(*(int **)(param_1 + 0x298),0,extraout_ECX_43);
  FUN_00413500(*(int **)(param_1 + 0x29c),0,extraout_ECX_44);
  FUN_00413500(*(int **)(param_1 + 0x2a0),0,extraout_ECX_45);
  FUN_00413500(*(int **)(param_1 + 0x2a4),0,extraout_ECX_46);
  FUN_00413500(*(int **)(param_1 + 0x2a8),0,extraout_ECX_47);
  FUN_00413500(*(int **)(param_1 + 0x2ac),0,extraout_ECX_48);
  FUN_00413500(*(int **)(param_1 + 0x2b0),0,extraout_ECX_49);
  FUN_00413500(*(int **)(param_1 + 0x2b4),0,extraout_ECX_50);
  FUN_00413500(*(int **)(param_1 + 0x2b8),0,extraout_ECX_51);
  FUN_00413500(*(int **)(param_1 + 700),0,extraout_ECX_52);
  FUN_00413500(*(int **)(param_1 + 0x2c0),0,extraout_ECX_53);
  FUN_00413500(*(int **)(param_1 + 0x2c4),0,extraout_ECX_54);
  FUN_00413500(*(int **)(param_1 + 0x2c8),0,extraout_ECX_55);
  FUN_00413500(*(int **)(param_1 + 0x2f0),0,extraout_ECX_56);
  FUN_00413500(*(int **)(param_1 + 0x2f4),0,extraout_ECX_57);
  FUN_00413500(*(int **)(param_1 + 0x2f8),0,extraout_ECX_58);
  FUN_00413500(*(int **)(param_1 + 0x2fc),0,extraout_ECX_59);
  FUN_00413500(*(int **)(param_1 + 0x300),0,extraout_ECX_60);
  FUN_00413500(*(int **)(param_1 + 0x304),0,extraout_ECX_61);
  FUN_00413500(*(int **)(param_1 + 0x308),0,extraout_ECX_62);
  FUN_00413500(*(int **)(param_1 + 0x418),0,extraout_ECX_63);
  FUN_00413500(*(int **)(param_1 + 0x428),0,extraout_ECX_64);
  FUN_00413500(*(int **)(param_1 + 0x42c),0,extraout_ECX_65);
  FUN_00413500(*(int **)(param_1 + 0x430),0,extraout_ECX_66);
  FUN_00413500(*(int **)(param_1 + 0x434),0,extraout_ECX_67);
  FUN_00413500(*(int **)(param_1 + 0x438),0,extraout_ECX_68);
  FUN_00413500(*(int **)(param_1 + 0x43c),0,extraout_ECX_69);
  FUN_00413500(*(int **)(param_1 + 0x440),0,extraout_ECX_70);
  if (original_hero.cycle_factor_minus_one == 0) {
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_00403658((int *)&local_8,DAT_0048c5fc);
    FUN_00403658((int *)&local_8,(undefined4 *)"\\left.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(param_1 + 0x1bc) + 0xac),(int)local_8);
  }
  else {
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_00403658((int *)&local_8,DAT_0048c5fc);
    FUN_00403658((int *)&local_8,(undefined4 *)"\\leftr.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(param_1 + 0x1bc) + 0xac),(int)local_8);
  }
  if (original_hero.cycle_factor_minus_one == 0) {
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_00403658((int *)&local_8,DAT_0048c5fc);
    FUN_00403658((int *)&local_8,(undefined4 *)"\\right.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(param_1 + 0x1c0) + 0xac),(int)local_8);
  }
  else {
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_00403658((int *)&local_8,DAT_0048c5fc);
    FUN_00403658((int *)&local_8,(undefined4 *)"\\rightr.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(param_1 + 0x1c0) + 0xac),(int)local_8);
  }
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x1bc) + 0x2c),local_18,
               *(undefined4 *)(*(int *)(param_1 + 0x1bc) + 0x30));
  puVar6 = local_18;
  puVar7 = &DAT_0048c53c;
  for (iVar4 = 4; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + (uint)bVar9 * -2 + 1;
    puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
  }
  piVar10 = &DAT_0048c53c;
  piVar1 = (int *)FUN_0042c150(*(int *)(param_1 + 0x1bc),extraout_EDX,0);
  piVar2 = (int *)FUN_0041dad8(DAT_0048c528);
  FUN_0041a530(piVar2,&DAT_0048c53c,piVar1,piVar10);
  iVar4 = *(int *)(*(int *)(param_1 + 0x1bc) + 0x2c);
  FUN_0040923c(iVar4,0,iVar4 + *(int *)(*(int *)(param_1 + 0x1b8) + 0x2c),local_18,
               *(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x30));
  puVar6 = local_18;
  puVar7 = &DAT_0048c53c;
  for (iVar4 = 4; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + (uint)bVar9 * -2 + 1;
    puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
  }
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x2c),local_18,
               *(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x30));
  puVar6 = local_18;
  puVar7 = &DAT_0048c52c;
  for (iVar4 = 4; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + (uint)bVar9 * -2 + 1;
    puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
  }
  FUN_004130d8(*(int **)(param_1 + 0x418),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x2c));
  FUN_004130f8(*(int **)(param_1 + 0x418),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x30));
  if (original_hero.cycle_factor_minus_one == 0) {
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_00403658((int *)&local_8,DAT_0048c5fc);
    FUN_00403658((int *)&local_8,(undefined4 *)"\\title05.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(param_1 + 0x418) + 0xac),(int)local_8);
    uVar3 = extraout_ECX_71;
    uVar5 = extraout_EDX_00;
  }
  else {
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_00403658((int *)&local_8,DAT_0048c5fc);
    FUN_00403658((int *)&local_8,(undefined4 *)"\\title05R.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(param_1 + 0x418) + 0xac),(int)local_8);
    uVar3 = extraout_ECX_72;
    uVar5 = extraout_EDX_01;
  }
  piVar10 = &DAT_0048c52c;
  piVar1 = (int *)FUN_0042c150(*(int *)(param_1 + 0x418),uVar5,uVar3);
  piVar2 = (int *)FUN_0041dad8(DAT_0048c528);
  FUN_0041a530(piVar2,&DAT_0048c53c,piVar1,piVar10);
  iVar4 = *(int *)(*(int *)(param_1 + 0x1bc) + 0x2c) + *(int *)(*(int *)(param_1 + 0x1b8) + 0x2c);
  FUN_0040923c(iVar4,0,iVar4 + *(int *)(*(int *)(param_1 + 0x1c0) + 0x2c),local_18,
               *(undefined4 *)(*(int *)(param_1 + 0x1c0) + 0x30));
  puVar6 = local_18;
  puVar7 = &DAT_0048c53c;
  for (iVar4 = 4; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + (uint)bVar9 * -2 + 1;
    puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
  }
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x1c0) + 0x2c),local_18,
               *(undefined4 *)(*(int *)(param_1 + 0x1c0) + 0x30));
  puVar6 = local_18;
  puVar7 = &DAT_0048c52c;
  for (iVar4 = 4; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + (uint)bVar9 * -2 + 1;
    puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
  }
  piVar10 = &DAT_0048c52c;
  piVar1 = (int *)FUN_0042c150(*(int *)(param_1 + 0x1c0),extraout_EDX_02,0);
  piVar2 = (int *)FUN_0041dad8(DAT_0048c528);
  FUN_0041a530(piVar2,&DAT_0048c53c,piVar1,piVar10);
  FUN_00431c8c(*(int *)(param_1 + 0x2d4),'\f');
  piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
  FUN_0040369c((int *)(*(int *)(param_1 + 0x2d4) + 0x20c),local_8,(undefined4 *)"\\wav\\open.wav");
  FUN_00430f20(*(int **)(param_1 + 0x2d4),extraout_EDX_03,extraout_ECX_73);
  FUN_00431c8c(*(int *)(param_1 + 0x460),'\f');
  piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
  FUN_0040369c((int *)(*(int *)(param_1 + 0x460) + 0x20c),local_8,(undefined4 *)"\\wav\\get.wav");
  FUN_00430f20(*(int **)(param_1 + 0x460),extraout_EDX_04,extraout_ECX_74);
  FUN_00431c8c(*(int *)(param_1 + 0x464),'\f');
  piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
  FUN_0040369c((int *)(*(int *)(param_1 + 0x464) + 0x20c),local_8,(undefined4 *)"\\wav\\taisen.wav")
  ;
  FUN_00430f20(*(int **)(param_1 + 0x464),extraout_EDX_05,extraout_ECX_75);
  FUN_00431c8c(*(int *)(param_1 + 0x468),'\f');
  piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
  FUN_0040369c((int *)(*(int *)(param_1 + 0x468) + 0x20c),local_8,(undefined4 *)"\\wav\\zeno.wav");
  FUN_00430f20(*(int **)(param_1 + 0x468),extraout_EDX_06,extraout_ECX_76);
  FUN_00431c8c(*(int *)(param_1 + 0x46c),'\f');
  DAT_0048c5c4 = 0;
  DAT_0048c570 = 1;
  DAT_0048c5d2 = 1;
  _DAT_0048c588 = 0;
  DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
  tile_class_or_message = 0;
  _DAT_0048c590 = 1;
  dialogue_continue_stage = 0;
  event_cursor = 0;
  uVar3 = extraout_ECX_77;
  uVar5 = extraout_EDX_07;
  if (*(char *)(*(int *)(param_1 + 0x41c) + 0x20) == '\0') {
    FUN_00442c38(param_1);
    uVar3 = extraout_ECX_78;
    uVar5 = extraout_EDX_08;
  }
  if (*(char *)(*(int *)(param_1 + 0x41c) + 0x20) == '\0') {
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_00403658((int *)&local_8,DAT_0048c5fc);
    FUN_00403658((int *)&local_8,(undefined4 *)"\\center.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(param_1 + 0x1b8) + 0xac),(int)local_8);
    FUN_00413500(*(int **)(param_1 + 0x1b8),CONCAT31((int3)((uint)extraout_EDX_09 >> 8),1),
                 extraout_ECX_79);
    FUN_00413500(*(int **)(param_1 + 0x1bc),CONCAT31((int3)((uint)extraout_EDX_10 >> 8),1),
                 extraout_ECX_80);
    FUN_00413500(*(int **)(param_1 + 0x1c0),CONCAT31((int3)((uint)extraout_EDX_11 >> 8),1),
                 extraout_ECX_81);
    FUN_00413500(*(int **)(param_1 + 0x288),CONCAT31((int3)((uint)extraout_EDX_12 >> 8),1),
                 extraout_ECX_82);
    FUN_00413500(*(int **)(param_1 + 0x28c),CONCAT31((int3)((uint)extraout_EDX_13 >> 8),1),
                 extraout_ECX_83);
    FUN_00413500(*(int **)(param_1 + 0x3c8),CONCAT31((int3)((uint)extraout_EDX_14 >> 8),1),
                 extraout_ECX_84);
    FUN_00413500(*(int **)(param_1 + 0x3cc),CONCAT31((int3)((uint)extraout_EDX_15 >> 8),1),
                 extraout_ECX_85);
    FUN_00413500(*(int **)(param_1 + 0x3d0),CONCAT31((int3)((uint)extraout_EDX_16 >> 8),1),
                 extraout_ECX_86);
    FUN_00413500(*(int **)(param_1 + 0x3d4),CONCAT31((int3)((uint)extraout_EDX_17 >> 8),1),
                 extraout_ECX_87);
    FUN_00413500(*(int **)(param_1 + 0x3d8),CONCAT31((int3)((uint)extraout_EDX_18 >> 8),1),
                 extraout_ECX_88);
    FUN_00413500(*(int **)(param_1 + 0x3dc),CONCAT31((int3)((uint)extraout_EDX_19 >> 8),1),
                 extraout_ECX_89);
    FUN_00413500(*(int **)(param_1 + 0x3e0),CONCAT31((int3)((uint)extraout_EDX_20 >> 8),1),
                 extraout_ECX_90);
    FUN_00413500(*(int **)(param_1 + 0x3e4),CONCAT31((int3)((uint)extraout_EDX_21 >> 8),1),
                 extraout_ECX_91);
    FUN_00413500(*(int **)(param_1 + 1000),CONCAT31((int3)((uint)extraout_EDX_22 >> 8),1),
                 extraout_ECX_92);
    FUN_00413500(*(int **)(param_1 + 0x3ec),CONCAT31((int3)((uint)extraout_EDX_23 >> 8),1),
                 extraout_ECX_93);
    FUN_00413500(*(int **)(param_1 + 0x3f0),CONCAT31((int3)((uint)extraout_EDX_24 >> 8),1),
                 extraout_ECX_94);
    uVar3 = extraout_ECX_95;
    uVar5 = extraout_EDX_25;
  }
  FUN_00413500(*(int **)(param_1 + 0x1c8),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
  (**(code **)(*DAT_0048c514 + 0x28))(DAT_0048c514,*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 0xb)
  ;
  (**(code **)(*DAT_0048c514 + 0x2c))(DAT_0048c514,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 0xb)
  ;
  uVar3 = (**(code **)(*DAT_0048c514 + 0x1c))();
  (**(code **)(*DAT_0048c518 + 0x28))(DAT_0048c518,uVar3);
  uVar3 = (**(code **)(*DAT_0048c514 + 0x20))();
  (**(code **)(*DAT_0048c518 + 0x2c))(DAT_0048c518,uVar3);
  (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 5);
  iVar4 = (**(code **)(*DAT_0048c51c + 0x20))();
  (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,iVar4 * 3);
  (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2);
  uVar3 = (**(code **)(*DAT_0048c51c + 0x20))();
  (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar3);
  (**(code **)(*DAT_0048c524 + 0x28))
            (DAT_0048c524,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  (**(code **)(*DAT_0048c524 + 0x2c))
            (DAT_0048c524,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  iVar4 = extraout_ECX_96;
  uVar3 = extraout_EDX_26;
  if (*(char *)(*(int *)(param_1 + 0x41c) + 0x20) == '\0') {
    monster_index = 0xffffffff;
    FUN_0044b78c(param_1,extraout_EDX_26,extraout_ECX_96);
    FUN_0044bed8(param_1,extraout_EDX_27,extraout_ECX_97);
    FUN_0044ccd8(param_1);
    FUN_00413500(*(int **)(param_1 + 0x1dc),CONCAT31((int3)((uint)extraout_EDX_28 >> 8),1),
                 extraout_ECX_98);
    uVar3 = extraout_ECX_99;
    uVar5 = extraout_EDX_29;
    if (original_hero.flight_orb == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x1dc),'\x01');
      uVar3 = extraout_ECX_x00100;
      uVar5 = extraout_EDX_30;
    }
    FUN_00413500(*(int **)(param_1 + 0x1ec),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    uVar3 = extraout_ECX_x00101;
    uVar5 = extraout_EDX_31;
    if (original_hero.wisdom_orb == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x1ec),'\x01');
      uVar3 = extraout_ECX_x00102;
      uVar5 = extraout_EDX_32;
    }
    FUN_00413500(*(int **)(param_1 + 0x254),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    uVar3 = extraout_ECX_x00103;
    uVar5 = extraout_EDX_33;
    if (original_hero.hero_orb == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x254),'\x01');
      uVar3 = extraout_ECX_x00104;
      uVar5 = extraout_EDX_34;
    }
    FUN_00413500(*(int **)(param_1 + 600),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    FUN_00413500(*(int **)(param_1 + 0x25c),CONCAT31((int3)((uint)extraout_EDX_35 >> 8),1),
                 extraout_ECX_x00105);
    uVar3 = extraout_ECX_x00106;
    uVar5 = extraout_EDX_36;
    if (original_hero.elixir == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x25c),'\x01');
      uVar3 = extraout_ECX_x00107;
      uVar5 = extraout_EDX_37;
    }
    FUN_00413500(*(int **)(param_1 + 0x260),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    uVar3 = extraout_ECX_x00108;
    uVar5 = extraout_EDX_38;
    if (original_hero.mattock == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x260),'\x01');
      uVar3 = extraout_ECX_x00109;
      uVar5 = extraout_EDX_39;
    }
    FUN_00413500(*(int **)(param_1 + 0x264),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    uVar3 = extraout_ECX_x00110;
    uVar5 = extraout_EDX_40;
    if (original_hero.bomb == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x264),'\x01');
      uVar3 = extraout_ECX_x00111;
      uVar5 = extraout_EDX_41;
    }
    FUN_00413500(*(int **)(param_1 + 0x268),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    uVar3 = extraout_ECX_x00112;
    uVar5 = extraout_EDX_42;
    if (0 < original_hero.warp_staff) {
      FUN_0041353c(*(int **)(param_1 + 0x268),'\x01');
      uVar3 = extraout_ECX_x00113;
      uVar5 = extraout_EDX_43;
    }
    FUN_00413500(*(int **)(param_1 + 0x26c),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    uVar3 = extraout_ECX_x00114;
    uVar5 = extraout_EDX_44;
    if (original_hero.ascent_wing == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x26c),'\x01');
      uVar3 = extraout_ECX_x00115;
      uVar5 = extraout_EDX_45;
    }
    FUN_00413500(*(int **)(param_1 + 0x270),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    uVar3 = extraout_ECX_x00116;
    uVar5 = extraout_EDX_46;
    if (original_hero.descent_wing == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x270),'\x01');
      uVar3 = extraout_ECX_x00117;
      uVar5 = extraout_EDX_47;
    }
    FUN_00413500(*(int **)(param_1 + 0x274),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    FUN_00413500(*(int **)(param_1 + 0x278),CONCAT31((int3)((uint)extraout_EDX_48 >> 8),1),
                 extraout_ECX_x00118);
    uVar3 = extraout_ECX_x00119;
    uVar5 = extraout_EDX_49;
    if (original_hero.snow_crystal == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x278),'\x01');
      uVar3 = extraout_ECX_x00120;
      uVar5 = extraout_EDX_50;
    }
    FUN_00413500(*(int **)(param_1 + 0x27c),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    uVar3 = extraout_ECX_x00121;
    uVar5 = extraout_EDX_51;
    if (original_hero.magic_key == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x27c),'\x01');
      uVar3 = extraout_ECX_x00122;
      uVar5 = extraout_EDX_52;
    }
    FUN_00413500(*(int **)(param_1 + 0x280),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    uVar3 = extraout_ECX_x00123;
    uVar5 = extraout_EDX_53;
    if (original_hero.super_mattock == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x280),'\x01');
      uVar3 = extraout_ECX_x00124;
      uVar5 = extraout_EDX_54;
    }
    FUN_00413500(*(int **)(param_1 + 0x284),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar3);
    FUN_0044cb34(param_1);
    iVar4 = extraout_ECX_x00125;
    uVar3 = extraout_EDX_55;
  }
  if (original_hero._356_4_ == 0) {
    FUN_004102f0(*(int *)(param_1 + 0x32c),1);
    iVar4 = extraout_ECX_x00126;
    uVar3 = extraout_EDX_56;
  }
  if (original_hero._360_4_ != 0) {
    FUN_004102f0(*(int *)(param_1 + 0x330),1);
    DAT_00489ba2 = 1;
    iVar4 = extraout_ECX_x00127;
    uVar3 = extraout_EDX_57;
  }
  if ((original_hero._360_4_ != 0) && (*(char *)(*(int *)(param_1 + 0x41c) + 0x20) == '\0')) {
    FUN_0047c2bc(param_1,uVar3,iVar4);
  }
  iVar8 = original_hero.y * 0xb + original_hero.x;
  iVar4 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
  DAT_0048c54c = (iVar8 * iVar4) % (iVar4 * 0xb);
  iVar4 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  DAT_0048c550 = (iVar8 / (iVar4 * 0xb)) * iVar4;
  if (*(char *)(*(int *)(param_1 + 0x41c) + 0x20) == '\0') {
    FUN_004433a4(param_1);
  }
  if (original_hero.zeno_sealed == 0) {
    original_monsters[15].hp = 8000;
    original_monsters[15].attack = 5000;
    original_monsters[15].defense = 1000;
  }
  else if (original_hero.zeno_sealed == 1) {
    iVar4 = original_hero.cycle_factor_minus_one + 1;
    original_monsters[15].hp = iVar4 * 800;
    original_monsters[15].attack = iVar4 * 500;
    original_monsters[15].defense = iVar4 * 100;
  }
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_00455bbc;
  puStack_2c = (undefined *)0x455bb4;
  FUN_004034dc((int *)&local_8);
  return;
}

