/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044a480.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Removing unreachable block (ram,0x0044a53a) */
/* WARNING: Removing unreachable block (ram,0x0044a4f4) */

void taisen(int param_1)

{
  dword dVar1;
  char cVar2;
  int *piVar3;
  word wVar4;
  int iVar5;
  int *in_FS_OFFSET;
  undefined *puVar6;
  undefined4 uVar7;
  int iStack_34;
  undefined *puStack_30;
  undefined *puStack_2c;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 *local_10;
  dword local_c;
  int local_8;
  
  puStack_2c = &stack0xfffffffc;
  local_c = 0;
  local_10 = (undefined4 *)0x0;
  local_14 = 0;
  local_18 = 0;
  local_1c = 0;
  puStack_30 = &LAB_0044b6cd;
  iStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_34;
  cVar2 = *(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index);
  if ((byte)(cVar2 - 0x3dU) < 0x23) {
    door_opened = ((int)(*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) + 1) >> 1)
                  + 0xa7;
  }
  else if ((byte)(cVar2 + 0x9fU) < 9) {
    door_opened = 0xd8;
  }
  else if ((byte)(cVar2 + 0x8dU) < 9) {
    door_opened = 0xd9;
  }
  else if ((byte)(cVar2 + 0x7cU) < 0x1a) {
    door_opened = ((int)(*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) + 1) >> 1)
                  + 0x97;
  }
  neighbor_index = door_opened - 0xc6;
  monster_index = neighbor_index;
  local_8 = param_1;
  FUN_0044b78c(param_1,contact_index,0);
  if (original_monsters[monster_index].defense * (original_hero.cycle_factor_minus_one + 1) -
      original_hero.attack < 0) {
    FUN_0044c04c(local_8);
    original_hero._48_4_ = 1;
  }
  neighbor_index = monster_index;
  DAT_0048c5bc = original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1);
  if (original_monsters[monster_index].defense * (original_hero.cycle_factor_minus_one + 1) -
      original_hero.attack < 0) {
    FUN_00450064(local_8);
    if (DAT_0048c568 < original_hero.hp) {
      original_hero._48_4_ = 0;
      FUN_00450064(local_8);
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
      FUN_0044b6f4(local_8);
      tile_class_or_message = 1;
      piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,199,&local_10);
      piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))
                (piVar3,200,&local_14,&DAT_0044b6f0,DAT_004b867c,&DAT_0044b6e4,local_10);
      puVar6 = &DAT_0044b6e4;
      uVar7 = local_14;
      FUN_00405b6c(original_monsters[monster_index].gold * (original_hero.lucky_gold + 1),&local_18)
      ;
      piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xc9,&local_1c,local_18,puVar6,uVar7);
      iStack_34 = local_1c;
      FUN_00403710(&DAT_004b8684,8);
      cVar2 = *(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index);
      if ((byte)(cVar2 + 0x9fU) < 7) {
        if (original_hero.lucky_gold == 0) {
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xf0,&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))
                    (piVar3,200,&local_14,&DAT_0044b6f0,DAT_004b867c,&DAT_0044b6e4,local_10);
          puVar6 = &DAT_0044b6e4;
          iVar5 = original_monsters[monster_index].gold >> 1;
          if (iVar5 < 0) {
            iVar5 = iVar5 + (uint)((original_monsters[monster_index].gold & 1U) != 0);
          }
          uVar7 = local_14;
          FUN_00405b6c(iVar5,&local_18);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xc9,&local_1c,local_18,puVar6,uVar7);
          iStack_34 = local_1c;
          FUN_00403710(&DAT_004b8684,8);
          iVar5 = (int)*(short *)(&DAT_0048c748 + event_cursor * 6) >> 1;
          if (iVar5 < 0) {
            iVar5 = iVar5 + (uint)(((int)*(short *)(&DAT_0048c748 + event_cursor * 6) & 1U) != 0);
          }
          *(short *)(&DAT_0048c748 + event_cursor * 6) = (short)iVar5;
        }
        else {
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xf0,&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))
                    (piVar3,200,&local_14,&DAT_0044b6f0,DAT_004b867c,&DAT_0044b6e4,local_10);
          puVar6 = &DAT_0044b6e4;
          uVar7 = local_14;
          FUN_00405b6c(original_monsters[monster_index].gold,&local_18);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xc9,&local_1c,local_18,puVar6,uVar7);
          iStack_34 = local_1c;
          FUN_00403710(&DAT_004b8684,8);
          iVar5 = (int)*(short *)(&DAT_0048c748 + event_cursor * 6) >> 1;
          if (iVar5 < 0) {
            iVar5 = iVar5 + (uint)(((int)*(short *)(&DAT_0048c748 + event_cursor * 6) & 1U) != 0);
          }
          *(short *)(&DAT_0048c748 + event_cursor * 6) = (short)iVar5;
        }
      }
      else if (cVar2 == 'i') {
        if (original_hero.lucky_gold == 0) {
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xf0,&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))
                    (piVar3,200,&local_14,&DAT_0044b6f0,DAT_004b867c,&DAT_0044b6e4,local_10);
          puVar6 = &DAT_0044b6e4;
          iVar5 = original_monsters[monster_index].gold >> 1;
          if (iVar5 < 0) {
            iVar5 = iVar5 + (uint)((original_monsters[monster_index].gold & 1U) != 0);
          }
          uVar7 = local_14;
          FUN_00405b6c(iVar5,&local_18);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xc9,&local_1c,local_18,puVar6,uVar7);
          iStack_34 = local_1c;
          FUN_00403710(&DAT_004b8684,8);
          iVar5 = (int)*(short *)(&DAT_0048c748 + event_cursor * 6) >> 1;
          if (iVar5 < 0) {
            iVar5 = iVar5 + (uint)(((int)*(short *)(&DAT_0048c748 + event_cursor * 6) & 1U) != 0);
          }
          *(short *)(&DAT_0048c748 + event_cursor * 6) = (short)iVar5;
        }
        else {
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xf0,&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))
                    (piVar3,200,&local_14,&DAT_0044b6f0,DAT_004b867c,&DAT_0044b6e4,local_10);
          puVar6 = &DAT_0044b6e4;
          uVar7 = local_14;
          FUN_00405b6c(original_monsters[monster_index].gold,&local_18);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xc9,&local_1c,local_18,puVar6,uVar7);
          iStack_34 = local_1c;
          FUN_00403710(&DAT_004b8684,8);
          iVar5 = (int)*(short *)(&DAT_0048c748 + event_cursor * 6) >> 1;
          if (iVar5 < 0) {
            iVar5 = iVar5 + (uint)(((int)*(short *)(&DAT_0048c748 + event_cursor * 6) & 1U) != 0);
          }
          *(short *)(&DAT_0048c748 + event_cursor * 6) = (short)iVar5;
        }
      }
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0x11;
      event_stack[event_cursor].a = (short)original_hero.y * 0xb + (short)original_hero.x;
      event_stack[event_cursor].b = 6;
      if (monster_index == 0x12) {
        if (*(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) == 'h') {
          event_stack[event_cursor].opcode = 0x11;
          event_stack[event_cursor].a =
               ((short)original_hero.y * 0xb + (short)original_hero.x) - 0x15;
          event_stack[event_cursor].b = 6;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0x11;
          event_stack[event_cursor].a =
               ((short)original_hero.y * 0xb + (short)original_hero.x) - 0x16;
          event_stack[event_cursor].b = 6;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0x11;
          event_stack[event_cursor].a =
               ((short)original_hero.y * 0xb + (short)original_hero.x) - 0x17;
          event_stack[event_cursor].b = 6;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0x11;
          event_stack[event_cursor].a =
               ((short)original_hero.y * 0xb + (short)original_hero.x) - 0xc;
          event_stack[event_cursor].b = 6;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0x11;
          event_stack[event_cursor].a =
               ((short)original_hero.y * 0xb + (short)original_hero.x) - 0xb;
          event_stack[event_cursor].b = 6;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0x11;
          event_stack[event_cursor].a = ((short)original_hero.y * 0xb + (short)original_hero.x) - 10
          ;
          event_stack[event_cursor].b = 6;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0x11;
          event_stack[event_cursor].a = ((short)original_hero.y * 0xb + (short)original_hero.x) - 1;
          event_stack[event_cursor].b = 6;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0x11;
          event_stack[event_cursor].a = (short)original_hero.y * 0xb + (short)original_hero.x;
          event_stack[event_cursor].b = 6;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0x11;
          event_stack[event_cursor].a = (short)original_hero.y * 0xb + (short)original_hero.x + 1;
          event_stack[event_cursor].b = 6;
        }
      }
      else if ((monster_index == 0x13) &&
              (*(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) == 'z')) {
        event_stack[event_cursor].opcode = 0x11;
        event_stack[event_cursor].a = ((short)original_hero.y * 0xb + (short)original_hero.x) - 0x15
        ;
        event_stack[event_cursor].b = 6;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0x11;
        event_stack[event_cursor].a = ((short)original_hero.y * 0xb + (short)original_hero.x) - 0x16
        ;
        event_stack[event_cursor].b = 6;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0x11;
        event_stack[event_cursor].a = ((short)original_hero.y * 0xb + (short)original_hero.x) - 0x17
        ;
        event_stack[event_cursor].b = 6;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0x11;
        event_stack[event_cursor].a = ((short)original_hero.y * 0xb + (short)original_hero.x) - 0xc;
        event_stack[event_cursor].b = 6;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0x11;
        event_stack[event_cursor].a = ((short)original_hero.y * 0xb + (short)original_hero.x) - 0xb;
        event_stack[event_cursor].b = 6;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0x11;
        event_stack[event_cursor].a = ((short)original_hero.y * 0xb + (short)original_hero.x) - 10;
        event_stack[event_cursor].b = 6;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0x11;
        event_stack[event_cursor].a = ((short)original_hero.y * 0xb + (short)original_hero.x) - 1;
        event_stack[event_cursor].b = 6;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0x11;
        event_stack[event_cursor].a = (short)original_hero.y * 0xb + (short)original_hero.x;
        event_stack[event_cursor].b = 6;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0x11;
        event_stack[event_cursor].a = (short)original_hero.y * 0xb + (short)original_hero.x + 1;
        event_stack[event_cursor].b = 6;
      }
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0xb;
      event_stack[event_cursor].a = 9;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 5;
      event_stack[event_cursor].a = (word)contact_index;
      event_stack[event_cursor].b = 0;
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
      if (monster_index == 0x12) {
        if (*(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) == 'h') {
          event_stack[event_cursor].opcode = 0xe;
        }
      }
      else if ((monster_index == 0x13) &&
              (*(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) == 'z')) {
        event_stack[event_cursor].opcode = 0xe;
      }
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 1;
      event_stack[event_cursor].a = 3;
      event_stack[event_cursor].b = 0;
      if ((1 < DAT_0048c56c) && (iVar5 = DAT_0048c56c + -1, 0 < iVar5)) {
        local_c = 1;
        do {
          scratch_index = local_c;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 4;
          wVar4 = (word)contact_index;
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
          event_stack[event_cursor].a = wVar4;
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
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 5;
          event_stack[event_cursor].a = wVar4;
          event_stack[event_cursor].b = 0xb7;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a =
               (ushort)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                                original_hero.y * 0xb + original_hero.x);
          event_stack[event_cursor].b = 0xb8;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 9;
          event_stack[event_cursor].a = wVar4;
          event_stack[event_cursor].b = 0xb7;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a = 0;
          event_stack[event_cursor].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 1;
          event_stack[event_cursor].a = 3;
          event_stack[event_cursor].b = 0;
          local_c = local_c + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
    }
    else {
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
        FUN_00450288();
        break;
      case 0xc:
      case 0xd:
        if (original_hero.cross == 0) {
          FUN_00450288();
        }
        else {
          FUN_004502d0();
        }
        break;
      case 0xe:
      case 0xf:
      case 0x10:
        FUN_00450288();
        break;
      case 0x11:
        if (original_hero.cross == 0) {
          FUN_00450288();
        }
        else {
          FUN_004502d0();
        }
        break;
      case 0x12:
        FUN_00450288();
        break;
      case 0x13:
        if (original_hero.dragon_slayer == 0) {
          FUN_00450288();
        }
        else {
          FUN_004502d0();
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
        FUN_00450288();
      }
      if (0 < DAT_0048c56c) {
        local_c = 1;
        iVar5 = DAT_0048c56c;
        do {
          scratch_index = local_c;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 4;
          wVar4 = (word)contact_index;
          event_stack[event_cursor].a = (word)contact_index;
          if (scratch_index == 1) {
            event_stack[event_cursor].b =
                 (ushort)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                                  original_hero.y * 0xb + original_hero.x);
          }
          else {
            event_stack[event_cursor].b = 0xb8;
          }
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a =
               (ushort)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                                original_hero.y * 0xb + original_hero.x);
          event_stack[event_cursor].b = (original_hero._352_2_ + -1) * 8 + 0xbf;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 9;
          event_stack[event_cursor].a = wVar4;
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
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 5;
          event_stack[event_cursor].a = wVar4;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 0;
          event_stack[event_cursor].a =
               (ushort)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                                original_hero.y * 0xb + original_hero.x);
          event_stack[event_cursor].b = 0xb8;
          event_cursor = event_cursor + 1;
          event_stack[event_cursor].opcode = 9;
          event_stack[event_cursor].a = wVar4;
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
          local_c = local_c + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
    }
  }
  else {
    tile_class_or_message = 1;
    piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    (**(code **)(*piVar3 + 0xc))(piVar3,0xd9,&local_10);
    FUN_0040352c(&DAT_004b8684,local_10);
    FUN_0044cb34(local_8);
  }
  start_event_timer(local_8);
  *in_FS_OFFSET = iStack_34;
  puStack_2c = &LAB_0044b6d4;
  puStack_30 = (undefined *)0x44b6cc;
  FUN_004034fc(&local_1c,4);
  return;
}

