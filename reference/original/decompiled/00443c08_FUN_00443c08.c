/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00443c08. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_00443c08(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  dword dVar7;
  int iVar8;
  undefined4 auStack_1c [4];

  bVar6 = 0;
  (**(code **)(*DAT_0048c51c + 0x28))
            (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2);
  uVar1 = (**(code **)(*DAT_0048c51c + 0x1c))();
  (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,uVar1);
  (**(code **)(*DAT_0048c520 + 0x2c))
            (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  uVar1 = (**(code **)(*DAT_0048c51c + 0x1c))();
  (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar1);
  uVar1 = (**(code **)(*DAT_0048c520 + 0x20))();
  (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar1);
  iVar2 = FUN_0041dad8((int)DAT_0048c51c);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = FUN_0041dad8((int)DAT_0048c520);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = FUN_0041dad8((int)DAT_0048c524);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = 0;
  dVar7 = scratch_index;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,dVar7,iVar2);
  iVar8 = 0;
  iVar2 = scratch_index + 1;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar8);
  iVar8 = 0;
  iVar2 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
          - 1;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,*(int *)(*(int *)(param_1 + 0x254) + 0x2c),iVar2,
               iVar8);
  iVar8 = 0;
  iVar2 = *(byte *)(original_hero.floor * 0x7b + original_hero.y * 0xb + original_hero.x + 0x4b8935)
          - 1;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar8);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_1c,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar4 = auStack_1c;
  puVar5 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
    puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
  }
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
  FUN_0040923c(iVar2 - neighbor_index,0,iVar2 * 2 - neighbor_index,auStack_1c,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar4 = auStack_1c;
  puVar5 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
    puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
  }
  FUN_0044439c();
  return;
}
