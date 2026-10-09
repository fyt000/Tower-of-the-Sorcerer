/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0047c978.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void FUN_0047c978(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  dword dVar8;
  int iVar9;
  undefined4 auStack_20 [4];
  
  bVar7 = 0;
  (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 3);
  (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 3);
  (**(code **)(*DAT_0048c520 + 0x28))
            (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  (**(code **)(*DAT_0048c520 + 0x2c))
            (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  uVar1 = (**(code **)(*DAT_0048c520 + 0x1c))();
  (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar1);
  uVar1 = (**(code **)(*DAT_0048c520 + 0x20))();
  (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar1);
  iVar2 = FUN_0041dad8((int)DAT_0048c51c);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = FUN_0041dad8((int)DAT_0048c520);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = FUN_0041dad8((int)DAT_0048c524);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar9 = 0;
  iVar2 = 5;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  iVar9 = 0;
  iVar2 = 5;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,*(int *)(*(int *)(param_1 + 0x254) + 0x2c),iVar2,
               iVar9);
  iVar9 = 0;
  iVar2 = 5;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2,
               iVar2,iVar9);
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  iVar9 = 5;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar9,iVar2);
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  iVar9 = 5;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,*(int *)(*(int *)(param_1 + 0x254) + 0x2c),iVar9,
               iVar2);
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  iVar9 = 5;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2,
               iVar9,iVar2);
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2;
  iVar9 = 5;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar9,iVar2);
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2;
  iVar9 = 5;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,*(int *)(*(int *)(param_1 + 0x254) + 0x2c),iVar9,
               iVar2);
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2;
  iVar9 = 5;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2,
               iVar9,iVar2);
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,iVar2,iVar9);
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0040923c(scratch_index,scratch_index,
               *(int *)(*(int *)(param_1 + 0x254) + 0x2c) + scratch_index,auStack_20,
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) + scratch_index);
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0044439c();
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,iVar2,iVar9);
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0040923c(scratch_index,*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2 - scratch_index,
               *(int *)(*(int *)(param_1 + 0x254) + 0x2c) + scratch_index,auStack_20,
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 3 - scratch_index);
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0044439c();
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,iVar2,iVar9);
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0040923c(*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2 - scratch_index,scratch_index,
               (*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2 - scratch_index) +
               *(int *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) + scratch_index);
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0044439c();
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,iVar2,iVar9);
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0040923c(*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2 - scratch_index,
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2 - scratch_index,
               (*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2 - scratch_index) +
               *(int *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 3 - scratch_index);
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0044439c();
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,iVar2,iVar9);
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0040923c(*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),scratch_index,
               *(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2,auStack_20,
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) + scratch_index);
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0044439c();
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,iVar2,iVar9);
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0040923c(*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2 - scratch_index,
               *(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2,auStack_20,
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 3 - scratch_index);
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0044439c();
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,iVar2,iVar9);
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0040923c(scratch_index,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30),
               *(int *)(*(int *)(param_1 + 0x254) + 0x2c) + scratch_index,auStack_20,
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2);
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0044439c();
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,iVar2,iVar9);
  iVar9 = 0;
  iVar2 = door_opened + 0x52;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0040923c(*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2 - scratch_index,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30),
               (*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2 - scratch_index) +
               *(int *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2);
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0044439c();
  if (DAT_00489ba4 == '\0') {
    iVar2 = (int)scratch_index >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((scratch_index & 1) != 0);
    }
    neighbor_index = iVar2 + 0xa5;
  }
  else if (DAT_00489ba4 == '\x01') {
    uVar4 = (int)(scratch_index << 2) / 5;
    iVar2 = (int)uVar4 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar4 & 1) != 0);
    }
    neighbor_index = iVar2 + 0xa5;
  }
  iVar2 = 0;
  dVar8 = neighbor_index;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,dVar8,iVar2);
  iVar9 = 0;
  iVar2 = door_opened + 0x5e;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0040923c(*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30),
               *(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2,auStack_20,
               *(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2);
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  FUN_0044439c();
  return;
}

