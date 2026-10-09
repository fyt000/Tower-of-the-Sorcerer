/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d494.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040d494(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  uint extraout_ECX;
  uint extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 uVar3;
  undefined4 extraout_EDX;
  undefined4 uVar4;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  code **in_FS_OFFSET;
  code *pcStack_158;
  undefined *puStack_154;
  undefined *puStack_150;
  code *pcStack_14c;
  undefined *puStack_148;
  undefined *puStack_144;
  code *pcStack_140;
  undefined *puStack_13c;
  undefined *puStack_138;
  undefined *puStack_128;
  byte abStack_124 [259];
  byte bStack_21;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  int iStack_14;
  int iStack_10;
  int *piStack_c;
  int iStack_8;
  
  puStack_138 = &stack0xfffffffc;
  puStack_128 = (undefined *)0x0;
  puStack_13c = &LAB_0040d749;
  pcStack_140 = *in_FS_OFFSET;
  *in_FS_OFFSET = (code *)&pcStack_140;
  puStack_144 = (undefined *)0x40d4cc;
  piStack_c = param_2;
  iStack_8 = param_1;
  FUN_00402b7c(*param_2,abStack_124);
  puStack_144 = (undefined *)0x40d4df;
  iVar1 = FUN_00403650(piStack_c[2]);
  if (*(int *)(iStack_8 + 0xc) - *(int *)(iStack_8 + 0x10) < (int)((uint)abStack_124[0] + iVar1 + 9)
     ) {
    puStack_144 = (undefined *)0x40d500;
    FUN_0040d334(iStack_8);
  }
  puStack_144 = (undefined *)0x40d508;
  iStack_10 = FUN_0040d210(iStack_8);
  bStack_21 = DAT_0040d758;
  if (*(int *)(iStack_8 + 0x1c) != 0) {
    bStack_21 = DAT_0040d758 | 1;
  }
  if ((*(int *)(iStack_8 + 0x2c) != 0) &&
     (*(int *)(iStack_8 + 0x30) < *(int *)(*(int *)(iStack_8 + 0x2c) + 8))) {
    if (*(int *)(iStack_8 + 0x1c) != 0) {
      puStack_144 = (undefined *)0x40d54f;
      iVar1 = FUN_00409a40(*(undefined4 **)(iStack_8 + 0x2c),*(int *)(iStack_8 + 0x30));
      if (iVar1 == *(int *)(iStack_8 + 0x1c)) goto LAB_0040d55b;
    }
    bStack_21 = bStack_21 | 2;
  }
LAB_0040d55b:
  puStack_144 = (undefined *)0x40d56c;
  FUN_0040d8a4(iStack_8,bStack_21,*(int *)(iStack_8 + 0x34));
  puStack_144 = (undefined *)0x40d57c;
  FUN_00402b7c(*piStack_c,abStack_124);
  puStack_144 = (undefined *)0x40d58d;
  FUN_004035fc((int *)&puStack_128,abStack_124);
  puStack_144 = (undefined *)0x40d59b;
  FUN_0040e400(iStack_8,puStack_128,extraout_ECX);
  puStack_144 = (undefined *)0x40d5a9;
  FUN_0040e400(iStack_8,(undefined *)piStack_c[2],extraout_ECX_00);
  puStack_144 = (undefined *)0x40d5b1;
  iStack_14 = FUN_0040d210(iStack_8);
  if ((*(int *)(iStack_8 + 0x2c) != 0) &&
     (*(int *)(iStack_8 + 0x30) < *(int *)(*(int *)(iStack_8 + 0x2c) + 8))) {
    if (*(int *)(iStack_8 + 0x1c) != 0) {
      *(int *)(iStack_8 + 0x30) = *(int *)(iStack_8 + 0x30) + 1;
    }
    *(int *)(iStack_8 + 0x34) = *(int *)(iStack_8 + 0x34) + 1;
  }
  puStack_144 = (undefined *)0x40d5e9;
  FUN_0040d8e8(iStack_8,piStack_c);
  puStack_144 = (undefined *)0x40d5f1;
  FUN_0040d89c(iStack_8,extraout_EDX,extraout_ECX_01);
  uStack_18 = *(undefined4 *)(iStack_8 + 0x2c);
  uStack_1c = *(undefined4 *)(iStack_8 + 0x30);
  uStack_20 = *(undefined4 *)(iStack_8 + 0x34);
  puStack_148 = &LAB_0040d6ef;
  pcStack_14c = *in_FS_OFFSET;
  *in_FS_OFFSET = (code *)&pcStack_14c;
  *(undefined4 *)(iStack_8 + 0x2c) = 0;
  *(undefined4 *)(iStack_8 + 0x30) = 0;
  uVar4 = 0;
  *(undefined4 *)(iStack_8 + 0x34) = 0;
  if (*(char *)(iStack_8 + 0x20) == '\0') {
    puStack_154 = &LAB_0040d6bf;
    pcStack_158 = *in_FS_OFFSET;
    *in_FS_OFFSET = (code *)&pcStack_158;
    uVar3 = extraout_ECX_02;
    puStack_150 = &stack0xfffffffc;
    puStack_144 = &stack0xfffffffc;
    if (*(int ***)(iStack_8 + 0x1c) != (int **)0x0) {
      puStack_150 = &stack0xfffffffc;
      puStack_144 = &stack0xfffffffc;
      piVar2 = FUN_00402c7c(*(int ***)(iStack_8 + 0x1c),(int *)&PTR_FUN_00409144);
      uVar3 = extraout_ECX_03;
      uVar4 = extraout_EDX_00;
      if ((char)piVar2 != '\0') {
        uVar4 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_03
                            );
        *(undefined4 *)(iStack_8 + 0x2c) = uVar4;
        FUN_00402cdc(*(int **)(iStack_8 + 0x1c),iStack_8,extraout_ECX_04);
        uVar3 = extraout_ECX_05;
        uVar4 = extraout_EDX_01;
      }
    }
    FUN_00402cdc(piStack_c,uVar4,uVar3);
    *in_FS_OFFSET = root_0040d458;
    FUN_00402c34(*(int **)(iStack_8 + 0x2c));
    return;
  }
  *in_FS_OFFSET = pcStack_14c;
  *(undefined4 *)(iStack_8 + 0x2c) = uStack_18;
  *(undefined4 *)(iStack_8 + 0x30) = uStack_1c;
  *(undefined4 *)(iStack_8 + 0x34) = uStack_20;
  return;
}

