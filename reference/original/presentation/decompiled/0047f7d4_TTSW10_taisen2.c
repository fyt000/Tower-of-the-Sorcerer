/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0047f7d4.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Removing unreachable block (ram,0x0047f879) */
/* WARNING: Removing unreachable block (ram,0x0047f84b) */

void FUN_0047f7d4(int param_1)

{
  dword dVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  dword dVar5;
  int *in_FS_OFFSET;
  undefined *puVar6;
  undefined4 uVar7;
  int iStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  puStack_28 = &stack0xfffffffc;
  local_c = 0;
  local_10 = 0;
  local_14 = 0;
  local_18 = 0;
  puStack_2c = &LAB_00480264;
  iStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_30;
  contact_index = (dword)*(short *)(&DAT_0048c756 + event_cursor * 6);
  cVar2 = *(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index);
  if ((byte)(cVar2 - 0x3dU) < 0x23) {
    door_opened = ((int)(*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) + 1) >> 1)
                  + 0xa7;
  }
  else if ((byte)(cVar2 + 0x7cU) < 0x1a) {
    door_opened = ((int)(*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) + 1) >> 1)
                  + 0x97;
  }
  neighbor_index = door_opened - 0xc6;
  monster_index = neighbor_index;
  local_8 = param_1;
  FUN_0044b78c(param_1,contact_index,0);
  original_hero._48_4_ = 1;
  neighbor_index = monster_index;
  DAT_0048c5bc = original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1);
  FUN_0048028c();
  if (DAT_0048c568 < original_hero.hp) {
    original_hero._48_4_ = 0;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0xb;
    event_stack[event_cursor].a = 5;
    event_stack[event_cursor].b = 5;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 7;
    event_stack[event_cursor].a = *(word *)&original_monsters[monster_index].gold;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 2;
    event_stack[event_cursor].a = 0;
    event_stack[event_cursor].b = 0;
    tile_class_or_message = 1;
    FUN_0044b6f4(local_8);
    piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    (**(code **)(*piVar3 + 0xc))(piVar3,199,&local_c);
    piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    (**(code **)(*piVar3 + 0xc))
              (piVar3,200,&local_10,&DAT_00480288,DAT_004b867c,&DAT_0048027c,local_c);
    puVar6 = &DAT_0048027c;
    uVar7 = local_10;
    FUN_00405b6c(original_monsters[monster_index].gold,&local_14);
    piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    (**(code **)(*piVar3 + 0xc))(piVar3,0xc9,&local_18,local_14,puVar6,uVar7);
    iStack_30 = local_18;
    FUN_00403710(&DAT_004b8684,8);
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0x11;
    event_stack[event_cursor].a = (short)original_hero.y * 0xb + (short)original_hero.x;
    event_stack[event_cursor].b = 6;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0;
    event_stack[event_cursor].a = 0;
    event_stack[event_cursor].b = 0;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0xb;
    event_stack[event_cursor].a = 9;
    event_stack[event_cursor].b = 0;
    if ((0 < DAT_0048c56c) && (0 < DAT_0048c56c)) {
      dVar5 = 1;
      iVar4 = DAT_0048c56c;
      do {
        dVar1 = event_cursor + 1;
        scratch_index = dVar5;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 5;
        event_stack[event_cursor].a = (word)contact_index;
        event_stack[event_cursor].b = 0xc1;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a =
             (ushort)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                              original_hero.y * 0xb + original_hero.x);
        event_stack[event_cursor].b = 0xb8;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 9;
        event_stack[event_cursor].a = (word)contact_index;
        event_stack[event_cursor].b = 0xb7;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 1;
        event_stack[dVar1].a = 3;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 4;
        event_stack[event_cursor].a = (word)contact_index;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a =
             (ushort)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                              original_hero.y * 0xb + original_hero.x);
        event_stack[event_cursor].b = (original_hero._352_2_ + -1) * 8 + 0xbf;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 9;
        event_stack[event_cursor].a = (word)contact_index;
        event_stack[event_cursor].b = (original_hero._352_2_ + -1) * 8 + 0xc0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 1;
        event_stack[dVar1].a = 3;
        event_stack[dVar1].b = 0;
        dVar5 = dVar5 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  else {
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0;
    event_stack[event_cursor].a = 0;
    event_stack[event_cursor].b = 0;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 3;
    event_stack[event_cursor].a = 0;
    event_stack[event_cursor].b = 0;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0;
    event_stack[event_cursor].a = 0;
    event_stack[event_cursor].b = 0;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0;
    event_stack[event_cursor].a = 0;
    event_stack[event_cursor].b = 0;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0;
    event_stack[event_cursor].a = 0;
    event_stack[event_cursor].b = 0;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0;
    event_stack[event_cursor].a = 0;
    event_stack[event_cursor].b = 0;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0;
    event_stack[event_cursor].a = 0;
    event_stack[event_cursor].b = 0;
    event_cursor = event_cursor + 1;
    event_stack[event_cursor].opcode = 0;
    event_stack[event_cursor].a = 0;
    event_stack[event_cursor].b = 0;
    DAT_0048c56c = 0;
    DAT_0048c5b4 = original_hero.hp;
    FUN_00480340();
    DAT_0048c568 = (original_hero.attack -
                   original_monsters[monster_index].defense *
                   (original_hero.cycle_factor_minus_one + 1)) * (DAT_0048c56c + -1);
    if (0 < DAT_0048c56c) {
      dVar5 = 1;
      iVar4 = DAT_0048c56c;
      do {
        scratch_index = dVar5;
        if (dVar5 == 1) {
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
        }
        else {
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 5;
          event_stack[event_cursor].a = (word)contact_index;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a =
               (ushort)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                                original_hero.y * 0xb + original_hero.x);
          event_stack[event_cursor].b = 0xb8;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 9;
          event_stack[event_cursor].a = (word)contact_index;
          event_stack[event_cursor].b = 0xb7;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 1;
          event_stack[event_cursor].a = 3;
          event_stack[event_cursor].b = 0;
        }
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 4;
        event_stack[event_cursor].a = (word)contact_index;
        if (scratch_index == 1) {
          event_stack[event_cursor].b =
               (ushort)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                                original_hero.y * 0xb + original_hero.x);
        }
        else {
          event_stack[event_cursor].b = 0xfa;
        }
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a =
             (ushort)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                              original_hero.y * 0xb + original_hero.x);
        event_stack[event_cursor].b = (original_hero._352_2_ + -1) * 8 + 0xbf;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 9;
        event_stack[event_cursor].a = (word)contact_index;
        event_stack[event_cursor].b = (original_hero._352_2_ + -1) * 8 + 0xc0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 1;
        event_stack[dVar1].a = 3;
        event_stack[dVar1].b = 0;
        dVar5 = dVar5 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  start_event_timer(local_8);
  *in_FS_OFFSET = iStack_30;
  puStack_28 = &LAB_0048026b;
  puStack_2c = (undefined *)0x480263;
  FUN_004034fc(&local_18,4);
  return;
}

