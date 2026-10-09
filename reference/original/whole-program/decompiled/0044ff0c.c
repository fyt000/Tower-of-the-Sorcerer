/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044ff0c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0044ff0c(int param_1)

{
  int *piVar1;
  int iVar2;
  int *in_FS_OFFSET;
  int iStack_24;
  undefined *puStack_20;
  undefined4 *puStack_1c;
  int local_c;
  undefined4 *local_8;
  
  puStack_1c = (undefined4 *)&stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  local_c = 0;
  puStack_20 = &LAB_0045004a;
  iStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_24;
  DAT_0048c564 = 0;
  if (original_monsters[monster_index].defense * (original_hero.cycle_factor_minus_one + 1) -
      original_hero.attack < 0) {
    DAT_0048c56c = 0;
    DAT_0048c5b4 = original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1);
    FUN_0045031c();
    iVar2 = original_monsters[monster_index].attack * (original_hero.cycle_factor_minus_one + 1);
    if (original_hero.defense - iVar2 < 0) {
      DAT_0048c568 = (iVar2 - original_hero.defense) * (DAT_0048c56c + -1);
    }
    else {
      DAT_0048c568 = 0;
    }
  }
  else {
    DAT_0048c564 = 1;
    puStack_1c = (undefined4 *)&stack0xfffffffc;
  }
  if (DAT_0048c564 == 0) {
    piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar1 + 0xc))(piVar1,0xb8,&local_8);
    puStack_1c = local_8;
    puStack_20 = &LAB_00450060;
    iStack_24 = 0x45001d;
    FUN_00405b6c(DAT_0048c568,&local_c);
    iStack_24 = local_c;
    FUN_00403710(&DAT_004b8678,3);
  }
  else if (DAT_0048c564 == 1) {
    piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar1 + 0xc))(piVar1,0xb9,&local_8);
    FUN_0040352c(&DAT_004b8678,local_8);
  }
  *in_FS_OFFSET = iStack_24;
  puStack_1c = (undefined4 *)&LAB_00450051;
  puStack_20 = (undefined *)0x450049;
  FUN_004034fc(&local_c,2);
  return;
}

