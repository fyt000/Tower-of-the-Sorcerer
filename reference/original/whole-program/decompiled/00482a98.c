/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00482a98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void TTSW10_timer4ontimer(int param_1)

{
  uint uVar1;
  int *piVar2;
  int *piVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  int iVar4;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *in_FS_OFFSET;
  byte bVar7;
  int iVar8;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  int iStack_18;
  undefined4 auStack_14 [4];
  
  bVar7 = 0;
  puStack_28 = &stack0xfffffffc;
  iStack_18 = 0;
  puStack_2c = &UNK_00482e3e;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  if (DAT_0048c56c < 8) {
    FUN_0042c464(*(int *)(param_1 + 0x41c),0x15e);
  }
  else if (DAT_0048c56c - 8 < 7) {
    puStack_28 = &stack0xfffffffc;
    FUN_0042c464(*(int *)(param_1 + 0x41c),0xfa);
  }
  else {
    puStack_28 = &stack0xfffffffc;
    if (DAT_0048c56c - 0xf < 6) {
      puStack_28 = &stack0xfffffffc;
      FUN_0042c464(*(int *)(param_1 + 0x41c),0x96);
    }
  }
  FUN_00402c34(DAT_0048c51c);
  FUN_00402c34(DAT_0048c520);
  FUN_00402c34(DAT_0048c524);
  DAT_0048c51c = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                                     extraout_ECX);
  DAT_0048c520 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                                     extraout_ECX_00);
  DAT_0048c524 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                                     extraout_ECX_01);
  FUN_0040923c(0,0,*(int *)(*(int *)(param_1 + 0x1b8) + 0x2c) +
                   *(int *)(*(int *)(param_1 + 0x1bc) + 0x2c) +
                   *(int *)(*(int *)(param_1 + 0x1c0) + 0x2c),auStack_14,
               *(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x30));
  puVar5 = auStack_14;
  puVar6 = &DAT_0048c53c;
  for (iVar4 = 4; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  (**(code **)(*DAT_0048c51c + 0x2c))
            (DAT_0048c51c,
             *(int *)(*(int *)(param_1 + 0x1b8) + 0x2c) + *(int *)(*(int *)(param_1 + 0x1bc) + 0x2c)
             + *(int *)(*(int *)(param_1 + 0x1c0) + 0x2c));
  (**(code **)(*DAT_0048c51c + 0x28))
            (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x30));
  FUN_004130d8(*(int **)(param_1 + 0x418),
               *(int *)(*(int *)(param_1 + 0x1b8) + 0x2c) +
               *(int *)(*(int *)(param_1 + 0x1bc) + 0x2c) +
               *(int *)(*(int *)(param_1 + 0x1c0) + 0x2c));
  FUN_004130f8(*(int **)(param_1 + 0x418),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x30));
  piVar2 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar2 + 0xc))(piVar2,1,&iStack_18);
  FUN_00403658(&iStack_18,DAT_0048c5fc);
  FUN_00403658(&iStack_18,(undefined4 *)&UNK_00482e54);
  (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,iStack_18);
  (**(code **)(*DAT_0048c520 + 0x2c))
            (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  (**(code **)(*DAT_0048c520 + 0x28))
            (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  (**(code **)(*DAT_0048c524 + 0x2c))
            (DAT_0048c524,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  (**(code **)(*DAT_0048c524 + 0x28))
            (DAT_0048c524,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  uVar1 = DAT_0048c56c & 0x80000001;
  if ((int)uVar1 < 0) {
    uVar1 = (uVar1 - 1 | 0xfffffffe) + 1;
  }
  if (uVar1 == 0) {
    iVar8 = 0;
    iVar4 = 0xd8;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar4,iVar8);
    iVar8 = 0;
    iVar4 = 0xd1;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar4,iVar8);
  }
  else {
    iVar8 = 0;
    iVar4 = 0xd9;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar4,iVar8);
    iVar8 = 0;
    iVar4 = 0xd3;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar4,iVar8);
  }
  if (DAT_00489ba4 == '\0') {
    FUN_0040923c(DAT_0048c56c + 0x130,DAT_0048c56c + 0x170,0x150,auStack_14,400);
    puVar5 = auStack_14;
    puVar6 = &DAT_0048c52c;
    for (iVar4 = 4; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
      puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
    }
  }
  else if (DAT_00489ba4 == '\x01') {
    FUN_0040923c(DAT_0048c56c + 0x17c,DAT_0048c56c + 0x1cc,0x1a4,auStack_14,500);
    puVar5 = auStack_14;
    puVar6 = &DAT_0048c52c;
    for (iVar4 = 4; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
      puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
    }
  }
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_14,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_14;
  puVar6 = &DAT_0048c53c;
  for (iVar4 = 4; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  if ((int)DAT_0048c56c < 0x13) {
    FUN_0044439c();
  }
  piVar2 = DAT_0048c51c;
  piVar3 = (int *)FUN_00421a54(DAT_0048c510);
  FUN_0041a5b8(piVar3,0,0,piVar2);
  DAT_0048c56c = DAT_0048c56c + 1;
  if (0x13 < (int)DAT_0048c56c) {
    FUN_0042c454(*(int *)(param_1 + 0x41c),'\0');
    original_hero.cycle_factor_minus_one = 0;
    original_hero.later_cycle = 0;
    FUN_00454da0(param_1);
  }
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &UNK_00482e45;
  puStack_2c = (undefined *)0x482e3d;
  FUN_004034dc(&iStack_18);
  return;
}

