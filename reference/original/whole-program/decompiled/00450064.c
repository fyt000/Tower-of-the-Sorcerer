/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00450064.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00450064(int param_1)

{
  int *piVar1;
  undefined *puVar2;
  int iVar3;
  int *in_FS_OFFSET;
  int iStack_24;
  undefined *puStack_20;
  undefined4 *puStack_1c;
  int local_c;
  undefined4 *local_8;
  
  puStack_1c = (undefined4 *)&stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  local_c = 0;
  puStack_20 = &LAB_0045026d;
  iStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_24;
  DAT_0048c564 = 0;
  if (original_monsters[monster_index].defense * (original_hero.cycle_factor_minus_one + 1) -
      original_hero.attack < 0) {
    DAT_0048c56c = 0;
    DAT_0048c5b4 = original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1);
    puVar2 = &stack0xfffffffc;
    switch(monster_index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
      puStack_1c = (undefined4 *)&stack0xfffffffc;
      FUN_0045031c();
      puVar2 = (undefined *)puStack_1c;
      break;
    case 0xc:
    case 0xd:
      if (original_hero.cross == 0) {
        puStack_1c = (undefined4 *)&stack0xfffffffc;
        FUN_0045031c();
        puVar2 = (undefined *)puStack_1c;
      }
      else {
        puStack_1c = (undefined4 *)&stack0xfffffffc;
        FUN_00450360();
        puVar2 = (undefined *)puStack_1c;
      }
      break;
    case 0xe:
    case 0xf:
    case 0x10:
      puStack_1c = (undefined4 *)&stack0xfffffffc;
      FUN_0045031c();
      puVar2 = (undefined *)puStack_1c;
      break;
    case 0x11:
      if (original_hero.cross == 0) {
        puStack_1c = (undefined4 *)&stack0xfffffffc;
        FUN_0045031c();
        puVar2 = (undefined *)puStack_1c;
      }
      else {
        puStack_1c = (undefined4 *)&stack0xfffffffc;
        FUN_00450360();
        puVar2 = (undefined *)puStack_1c;
      }
      break;
    case 0x12:
      puStack_1c = (undefined4 *)&stack0xfffffffc;
      FUN_0045031c();
      puVar2 = (undefined *)puStack_1c;
      break;
    case 0x13:
      if (original_hero.dragon_slayer == 0) {
        puStack_1c = (undefined4 *)&stack0xfffffffc;
        FUN_0045031c();
        puVar2 = (undefined *)puStack_1c;
      }
      else {
        puStack_1c = (undefined4 *)&stack0xfffffffc;
        FUN_00450360();
        puVar2 = (undefined *)puStack_1c;
      }
      break;
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
      FUN_0045031c();
      puVar2 = (undefined *)puStack_1c;
    }
    puStack_1c = (undefined4 *)puVar2;
    iVar3 = original_monsters[monster_index].attack * (original_hero.cycle_factor_minus_one + 1);
    if (original_hero.defense - iVar3 < 0) {
      DAT_0048c568 = (iVar3 - original_hero.defense) * (DAT_0048c56c + -1);
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
    puStack_20 = &LAB_00450284;
    iStack_24 = 0x450240;
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
  puStack_1c = (undefined4 *)&LAB_00450274;
  puStack_20 = (undefined *)0x45026c;
  FUN_004034fc(&local_c,2);
  return;
}

