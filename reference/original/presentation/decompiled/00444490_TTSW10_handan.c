/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00444490.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void handan(int param_1)

{
  dword dVar1;
  char cVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  int extraout_ECX_05;
  int extraout_ECX_06;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  char **in_FS_OFFSET;
  undefined *puVar7;
  uint **ppuVar8;
  uint *puVar9;
  char *pcStack_2c;
  undefined4 *puStack_28;
  undefined *puStack_24;
  char *local_14;
  undefined4 *local_10;
  uint *local_c;
  int local_8;
  
  puStack_24 = &stack0xfffffffc;
  uVar6 = 0;
  local_c = (uint *)0x0;
  local_10 = (undefined4 *)0x0;
  local_14 = (char *)0x0;
  puStack_28 = (undefined4 *)&LAB_00448fd7;
  pcStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = (char *)&pcStack_2c;
  uVar4 = (uint)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index);
  local_8 = param_1;
  switch(uVar4) {
  case 0:
  case 4:
  case 5:
  case 8:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x11:
  case 0x12:
    break;
  case 1:
  case 2:
  case 3:
    door_opened = 0;
    cVar2 = *(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index);
    if (cVar2 == '\x01') {
      tile_class_or_message = 0x10;
      if (0 < original_hero.yellow_keys) {
        door_opened = 1;
        original_hero.yellow_keys = original_hero.yellow_keys + -1;
        tile_class_or_message = 4;
      }
    }
    else if (cVar2 == '\x02') {
      tile_class_or_message = 0x11;
      if (0 < original_hero.blue_keys) {
        door_opened = 1;
        original_hero.blue_keys = original_hero.blue_keys + -1;
        tile_class_or_message = 5;
      }
    }
    else if ((cVar2 == '\x03') && (tile_class_or_message = 0x12, 0 < original_hero.red_keys)) {
      door_opened = 1;
      original_hero.red_keys = original_hero.red_keys + -1;
      tile_class_or_message = 6;
    }
    puStack_24 = &stack0xfffffffc;
    doorcheck();
    if (door_opened == 1) {
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 2;
      event_stack[event_cursor].a = (word)tile_class_or_message;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 8;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0xd;
      event_stack[event_cursor].a = (word)contact_index;
      event_stack[event_cursor].b =
           (ushort)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index);
      doorstackin();
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 1;
      event_stack[event_cursor].a = 1;
      event_stack[event_cursor].b = 0;
      start_event_timer(local_8);
    }
    else {
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 2;
      event_stack[event_cursor].a = (word)tile_class_or_message;
      event_stack[event_cursor].b = 0;
      start_event_timer(local_8);
    }
    break;
  case 6:
    puStack_24 = &stack0xfffffffc;
    FUN_0044c04c(param_1);
    break;
  case 7:
    puStack_24 = &stack0xfffffffc;
    mevent(param_1);
    break;
  case 9:
    puStack_24 = &stack0xfffffffc;
    start_event_timer(param_1);
    tile_class_or_message = 1;
    piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    (**(code **)(*piVar3 + 0xc))(piVar3,0x89,&local_c);
    FUN_0040352c(&DAT_004b8684,local_c);
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 2;
    event_stack[dVar1].a = 1;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0xd;
    event_stack[dVar1].a = (word)contact_index;
    event_stack[dVar1].b = 7;
    doorstackin();
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 1;
    event_stack[dVar1].a = 1;
    event_stack[dVar1].b = 0;
    break;
  case 10:
    if (original_hero.floor == 0xc) {
      if (contact_index == 10) {
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 6;
        event_stack[event_cursor].a = 10;
        event_stack[event_cursor].b = 0x13;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 1;
        event_stack[event_cursor].a = 2;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        puStack_24 = &stack0xfffffffc;
        start_event_timer(param_1);
      }
    }
    else if (original_hero.floor == 0x10) {
      if (contact_index == 0x78) {
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 6;
        event_stack[event_cursor].a = 0x78;
        event_stack[event_cursor].b = 0x19;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 1;
        event_stack[event_cursor].a = 2;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        puStack_24 = &stack0xfffffffc;
        start_event_timer(param_1);
      }
    }
    else if (original_hero.floor == 0x13) {
      if (contact_index == 0x1b) {
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 6;
        event_stack[event_cursor].a = 0x1b;
        event_stack[event_cursor].b = 0x27;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 1;
        event_stack[event_cursor].a = 2;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        puStack_24 = &stack0xfffffffc;
        start_event_timer(param_1);
      }
    }
    else if ((original_hero.floor == 0x29) && (original_maps[41][14] == 6)) {
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 6;
      event_stack[event_cursor].a = 0x14;
      event_stack[event_cursor].b = 0x97;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 1;
      event_stack[event_cursor].a = 2;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      puStack_24 = &stack0xfffffffc;
      start_event_timer(param_1);
    }
    break;
  case 0xb:
  case 0xc:
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    puStack_24 = &stack0xfffffffc;
    if (original_hero._360_4_ != 0) {
      puStack_24 = &stack0xfffffffc;
      FUN_0042c454(*(int *)(param_1 + 0x1b4),'\0');
      FUN_00431188(*(int **)(local_8 + 0x2d8),extraout_EDX,extraout_ECX);
      uVar6 = extraout_ECX_00;
    }
    cVar2 = *(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index);
    if (cVar2 == '\v') {
      monster_index = 0xffffffff;
      FUN_0044b78c(local_8,contact_index,uVar6);
      tile_class_or_message = 1;
      piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xf3,&local_c);
      FUN_0040352c(&DAT_004b8684,local_c);
      FUN_0044cb34(local_8);
      if ((original_hero.floor == 0x14) && (original_maps[20][51] == 0x17)) {
        original_maps[20][51] = 6;
      }
      if ((original_hero.floor == 0x19) && (original_maps[25][73] == 0x17)) {
        original_maps[25][73] = 6;
      }
      if ((original_hero.floor == 0x28) && (original_maps[40][62] == 0x17)) {
        original_maps[40][62] = 6;
      }
      if (original_hero.floor == 0x2b) {
        original_hero.floor = 0x2d;
      }
      else {
        original_hero.floor = original_hero.floor + 1;
      }
      if ((((int)original_hero._20_4_ < original_hero.floor) &&
          (original_hero._20_4_ = original_hero.floor, original_hero._140_4_ == 0x23)) &&
         ((uint)original_maps[35][93] + (uint)original_maps[2][122] == 0x1b)) {
        original_maps[2][122] = 6;
      }
      original_hero.x = (uint)original_maps[original_hero.floor][0] % 0xb;
      original_hero.y = original_maps[original_hero.floor][0] / 0xb;
      FUN_00442f80();
      if ((original_hero.floor == 0x20) && (original_hero.floor32_arrival_seen == 0)) {
        mevent(local_8);
        original_hero.floor32_arrival_seen = 1;
      }
      if ((original_hero.floor == 0x2a) && (original_hero._524_4_ == 0)) {
        mevent(local_8);
        original_hero._524_4_ = 1;
      }
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 2;
      event_stack[event_cursor].a = 7;
      event_stack[event_cursor].b = 0;
    }
    else if (cVar2 == '\f') {
      monster_index = 0xffffffff;
      FUN_0044b78c(local_8,contact_index,uVar6);
      tile_class_or_message = 1;
      piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xf3,&local_c);
      FUN_0040352c(&DAT_004b8684,local_c);
      FUN_0044cb34(local_8);
      if ((original_hero.floor == 0x19) && (original_maps[25][73] == 0x17)) {
        original_maps[25][73] = 6;
      }
      if ((original_hero.floor == 0x31) && (original_maps[49][18] == 0x17)) {
        original_maps[49][18] = 6;
      }
      if (original_hero.floor == 0x2d) {
        original_hero.floor = 0x2b;
      }
      else {
        original_hero.floor = original_hero.floor + -1;
      }
      if ((original_hero._20_4_ == 0x1d) && (original_hero.floor == 0x1c)) {
        original_maps[29][40] = 6;
        original_maps[29][29] = 6;
        original_maps[29][19] = 0x15;
      }
      original_hero.x = (uint)original_maps[original_hero.floor][1] % 0xb;
      original_hero.y = original_maps[original_hero.floor][1] / 0xb;
      FUN_00443050();
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 2;
      event_stack[event_cursor].a = 8;
      event_stack[event_cursor].b = 0;
    }
    kaidanwork(local_8);
    monster_index = 0xffffffff;
    FUN_0044b78c(local_8,extraout_EDX_00,extraout_ECX_01);
    FUN_00450880(local_8);
    start_event_timer(local_8);
    break;
  case 0x10:
    puStack_24 = &stack0xfffffffc;
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1cc) + 0x44),(uint)DAT_00489b9d);
    _DAT_0048c5cc = 1;
    FUN_00450758(local_8);
    iVar5 = original_hero._44_4_ + 1;
    bomb_gold = ((iVar5 * iVar5 - iVar5) + 2) * 10;
    piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    (**(code **)(*piVar3 + 0xc))(piVar3,0xca,&local_c);
    FUN_00403658((int *)&local_c,(undefined4 *)&DAT_00448ff0);
    ppuVar8 = &local_c;
    FUN_00405b6c(bomb_gold,(int *)&local_10);
    FUN_00403658((int *)ppuVar8,local_10);
    FUN_00403658((int *)&local_c,(undefined4 *)&DAT_00448ff0);
    ppuVar8 = &local_c;
    piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    (**(code **)(*piVar3 + 0xc))(piVar3,0xcb,&local_10);
    FUN_00403658((int *)ppuVar8,local_10);
    FUN_004135d4(*(int **)(local_8 + 0x1cc),local_c);
    dialogue_continue_stage = 2;
    if (DAT_00489ba4 == '\0') {
      FUN_004130f8(*(int **)(local_8 + 0x1cc),200);
      FUN_004130d8(*(int **)(local_8 + 0x1cc),0x17e);
      FUN_004130b8(*(int **)(local_8 + 0x1cc),0x2d);
      FUN_00413098(*(int **)(local_8 + 0x1cc),0x81);
    }
    else if (DAT_00489ba4 == '\x01') {
      FUN_004130f8(*(int **)(local_8 + 0x1cc),0xfa);
      FUN_004130d8(*(int **)(local_8 + 0x1cc),0x1de);
      FUN_004130b8(*(int **)(local_8 + 0x1cc),0x38);
      FUN_00413098(*(int **)(local_8 + 0x1cc),0xa1);
    }
    uVar4 = *(uint *)(*(int *)(local_8 + 0x254) + 0x30);
    iVar5 = (int)uVar4 >> 1;
    if (iVar5 < 0) {
      iVar5 = iVar5 + (uint)((uVar4 & 1) != 0);
    }
    FUN_004130b8(*(int **)(local_8 + 0x1d8),
                 ((*(int *)(*(int *)(local_8 + 0x1cc) + 0x28) +
                  *(int *)(*(int *)(local_8 + 0x1cc) + 0x30)) -
                 *(int *)(*(int *)(local_8 + 0x1d8) + 0x30)) - iVar5);
    uVar4 = *(uint *)(*(int *)(local_8 + 0x254) + 0x30);
    iVar5 = (int)uVar4 >> 1;
    if (iVar5 < 0) {
      iVar5 = iVar5 + (uint)((uVar4 & 1) != 0);
    }
    FUN_00413098(*(int **)(local_8 + 0x1d8),
                 ((*(int *)(*(int *)(local_8 + 0x1cc) + 0x24) +
                  *(int *)(*(int *)(local_8 + 0x1cc) + 0x2c)) -
                 *(int *)(*(int *)(local_8 + 0x1d8) + 0x2c)) - iVar5);
    uVar4 = *(uint *)(*(int *)(local_8 + 0x254) + 0x30);
    iVar5 = (int)uVar4 >> 1;
    if (iVar5 < 0) {
      iVar5 = iVar5 + (uint)((uVar4 & 1) != 0);
    }
    FUN_004130b8(*(int **)(local_8 + 0x1d4),
                 ((*(int *)(*(int *)(local_8 + 0x1cc) + 0x28) +
                  *(int *)(*(int *)(local_8 + 0x1cc) + 0x30)) -
                 *(int *)(*(int *)(local_8 + 0x1d4) + 0x30)) - iVar5);
    FUN_00413098(*(int **)(local_8 + 0x1d4),
                 (*(int *)(*(int *)(local_8 + 0x1d8) + 0x24) -
                 *(int *)(*(int *)(local_8 + 0x1d4) + 0x2c)) + -0x10);
    FUN_00413500(*(int **)(local_8 + 0x1cc),CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                 extraout_ECX_02);
    FUN_00413500(*(int **)(local_8 + 0x1d4),CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                 extraout_ECX_03);
    FUN_00413500(*(int **)(local_8 + 0x1d8),CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                 extraout_ECX_04);
    (**(code **)(**(int **)(local_8 + 0x1d4) + 0x80))();
    break;
  case 0x13:
  case 0x14:
    puStack_24 = &stack0xfffffffc;
    syounin(param_1);
    break;
  case 0x15:
  case 0x16:
    puStack_24 = &stack0xfffffffc;
    touzoku(param_1);
    break;
  case 0x17:
  case 0x18:
    puStack_24 = &stack0xfffffffc;
    FUN_00478f0c(param_1);
    break;
  default:
    if (uVar4 < 0x3d) {
      if (uVar4 < 0x1d) {
        if (uVar4 - 0x19 < 2) {
          puStack_24 = &stack0xfffffffc;
          roujin(param_1);
        }
        else if (uVar4 - 0x1b < 2) {
          puStack_24 = &stack0xfffffffc;
          if ((original_hero._360_4_ != 0) &&
             (puStack_24 = &stack0xfffffffc, original_hero._360_4_ != 0xd)) {
            puStack_24 = &stack0xfffffffc;
            FUN_00431188(*(int **)(param_1 + 0x2d8),contact_index,0);
            original_hero._360_4_ = 0xd;
            FUN_0047c2bc(local_8,extraout_EDX_04,extraout_ECX_05);
          }
          if (original_maps[25][62] == 6) {
            original_maps[24][6] = 8;
            original_maps[24][8] = 8;
            original_maps[24][18] = 6;
            original_maps[24][29] = 6;
            original_maps[24][40] = 6;
            original_maps[24][7] = 7;
          }
          original_maps[50][51] = 0x15;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 6;
          event_stack[dVar1].a = 0x3c;
          event_stack[dVar1].b = 0x1b;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 10;
          event_stack[dVar1].a = 0x1a;
          event_stack[dVar1].b = 0;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 10;
          event_stack[dVar1].a = 0x19;
          event_stack[dVar1].b = 0;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          start_event_timer(local_8);
          FUN_004135d4(*(int **)(local_8 + 0x1d0),(uint *)&DAT_00448ffc);
        }
      }
      else if (uVar4 - 0x1d < 3) {
        cVar2 = *(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index);
        if (cVar2 == '\x1d') {
          original_hero.yellow_keys = original_hero.yellow_keys + 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0x80,&local_c);
          FUN_0040352c(&DAT_004b8684,local_c);
        }
        else if (cVar2 == '\x1e') {
          original_hero.red_keys = original_hero.red_keys + 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0x82,&local_c);
          FUN_0040352c(&DAT_004b8684,local_c);
        }
        else {
          puStack_24 = &stack0xfffffffc;
          if (cVar2 == '\x1f') {
            original_hero.blue_keys = original_hero.blue_keys + 1;
            tile_class_or_message = 1;
            piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
            puStack_24 = &stack0xfffffffc;
            (**(code **)(*piVar3 + 0xc))(piVar3,0x81,&local_c);
            FUN_0040352c(&DAT_004b8684,local_c);
          }
        }
        start_event_timer(local_8);
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 2;
        event_stack[dVar1].a = (word)tile_class_or_message;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 8;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 1;
        event_stack[dVar1].a = 2;
        event_stack[dVar1].b = 0;
        *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) = 6;
        FUN_0044c04c(local_8);
      }
      else if (uVar4 - 0x20 < 0x13) {
        puStack_24 = &stack0xfffffffc;
        switch(*(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index)) {
        case 0x20:
          original_hero.hp =
               original_hero.hp +
               ((original_hero.floor + 9) / 10) * 0x32 * (original_hero.cycle_factor_minus_one + 1);
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa2,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c(((original_hero.floor + 9) / 10) * 0x32 *
                       (original_hero.cycle_factor_minus_one + 1),(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x21:
          original_hero.hp =
               original_hero.hp +
               ((original_hero.floor + 9) / 10) * 200 * (original_hero.cycle_factor_minus_one + 1);
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa3,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c(((original_hero.floor + 9) / 10) * 200 *
                       (original_hero.cycle_factor_minus_one + 1),(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x22:
          original_hero.attack =
               original_hero.attack +
               ((original_hero.floor + 9) / 10) * (original_hero.cycle_factor_minus_one + 1);
          tile_class_or_message = 1;
          if (((original_hero.floor + 9) / 10) * (original_hero.cycle_factor_minus_one + 1) == 1) {
            piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
            puStack_24 = &stack0xfffffffc;
            (**(code **)(*piVar3 + 0xc))(piVar3,0xa4,&local_c);
            puStack_24 = &DAT_00448ff0;
            puStack_28 = (undefined4 *)0x4458c8;
            FUN_00405b6c(((original_hero.floor + 9) / 10) *
                         (original_hero.cycle_factor_minus_one + 1),(int *)&local_10);
            puStack_28 = local_10;
            pcStack_2c = " point up!";
            FUN_00403710(&DAT_004b8684,4);
          }
          else {
            piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
            puStack_24 = &stack0xfffffffc;
            (**(code **)(*piVar3 + 0xc))(piVar3,0xa4,&local_c);
            puVar7 = &DAT_00448ff0;
            puVar9 = local_c;
            FUN_00405b6c(((original_hero.floor + 9) / 10) *
                         (original_hero.cycle_factor_minus_one + 1),(int *)&local_10);
            piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
            (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
            pcStack_2c = local_14;
            FUN_00403710(&DAT_004b8684,4);
          }
          break;
        case 0x23:
          original_hero.defense =
               original_hero.defense +
               ((original_hero.floor + 9) / 10) * (original_hero.cycle_factor_minus_one + 1);
          tile_class_or_message = 1;
          if (((original_hero.floor + 9) / 10) * (original_hero.cycle_factor_minus_one + 1) == 1) {
            piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
            puStack_24 = &stack0xfffffffc;
            (**(code **)(*piVar3 + 0xc))(piVar3,0xa5,&local_c);
            puStack_24 = &DAT_00448ff0;
            puStack_28 = (undefined4 *)0x4459e9;
            FUN_00405b6c(((original_hero.floor + 9) / 10) *
                         (original_hero.cycle_factor_minus_one + 1),(int *)&local_10);
            puStack_28 = local_10;
            pcStack_2c = " point up!";
            FUN_00403710(&DAT_004b8684,4);
          }
          else {
            piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
            puStack_24 = &stack0xfffffffc;
            (**(code **)(*piVar3 + 0xc))(piVar3,0xa5,&local_c);
            puVar7 = &DAT_00448ff0;
            puVar9 = local_c;
            FUN_00405b6c(((original_hero.floor + 9) / 10) *
                         (original_hero.cycle_factor_minus_one + 1),(int *)&local_10);
            piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
            (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
            pcStack_2c = local_14;
            FUN_00403710(&DAT_004b8684,4);
          }
          break;
        case 0x25:
          original_hero.wisdom_orb = 1;
          tile_class_or_message = 0x16;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x26:
          original_hero.flight_orb = 1;
          tile_class_or_message = 0x15;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x27:
          original_hero.cross = 1;
          tile_class_or_message = 0x28;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x28:
          original_hero.elixir = 1;
          tile_class_or_message = 0x29;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x29:
          original_hero.mattock = 1;
          tile_class_or_message = 0x2a;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x2a:
          original_hero.bomb = 1;
          tile_class_or_message = 0x2b;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x2b:
          original_hero.warp_staff = 3;
          tile_class_or_message = 0x2c;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x2c:
          original_hero.ascent_wing = 1;
          tile_class_or_message = 0x2d;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x2d:
          original_hero.descent_wing = 1;
          tile_class_or_message = 0x2e;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x2e:
          original_hero.dragon_slayer = 1;
          tile_class_or_message = 0x2f;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x2f:
          original_hero.snow_crystal = 1;
          tile_class_or_message = 0x30;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x30:
          original_hero.magic_key = 1;
          tile_class_or_message = 0x31;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x31:
          original_hero.super_mattock = 1;
          tile_class_or_message = 0x32;
          puStack_24 = &stack0xfffffffc;
          break;
        case 0x32:
          original_hero.lucky_gold = 1;
          tile_class_or_message = 0x33;
          puStack_24 = &stack0xfffffffc;
        }
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 2;
        event_stack[dVar1].a = (word)tile_class_or_message;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 8;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 1;
        event_stack[dVar1].a = 2;
        event_stack[dVar1].b = 0;
        start_event_timer(local_8);
        *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) = 6;
        FUN_0044c04c(local_8);
      }
      else if (uVar4 - 0x33 < 10) {
        puStack_24 = &stack0xfffffffc;
        switch(*(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index)) {
        case 0x33:
          original_hero.attack =
               original_hero.attack + (original_hero.cycle_factor_minus_one + 1) * 10;
          original_hero.sword = 1;
          original_hero._128_4_ = 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0x98,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c((original_hero.cycle_factor_minus_one + 1) * 10,(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x34:
          original_hero.attack =
               original_hero.attack + (original_hero.cycle_factor_minus_one + 1) * 0x14;
          original_hero.sword = 2;
          original_hero._132_4_ = 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0x99,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c((original_hero.cycle_factor_minus_one + 1) * 0x14,(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x35:
          original_hero.attack =
               original_hero.attack + (original_hero.cycle_factor_minus_one + 1) * 0x28;
          original_hero.sword = 3;
          original_hero._136_4_ = 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0x9a,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c((original_hero.cycle_factor_minus_one + 1) * 0x28,(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x36:
          original_hero.attack =
               original_hero.attack + (original_hero.cycle_factor_minus_one + 1) * 0x32;
          original_hero.sword = 4;
          original_hero._140_4_ = 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0x9b,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c((original_hero.cycle_factor_minus_one + 1) * 0x32,(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x37:
          original_hero.attack =
               original_hero.attack + (original_hero.cycle_factor_minus_one + 1) * 100;
          original_hero.sword = 5;
          original_hero._144_4_ = 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0x9c,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c((original_hero.cycle_factor_minus_one + 1) * 100,(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x38:
          original_hero.defense =
               original_hero.defense + (original_hero.cycle_factor_minus_one + 1) * 10;
          original_hero.shield = 1;
          original_hero._148_4_ = 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0x9d,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c((original_hero.cycle_factor_minus_one + 1) * 10,(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x39:
          original_hero.defense =
               original_hero.defense + (original_hero.cycle_factor_minus_one + 1) * 0x14;
          original_hero.shield = 2;
          original_hero._152_4_ = 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0x9e,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c((original_hero.cycle_factor_minus_one + 1) * 0x14,(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x3a:
          original_hero.defense =
               original_hero.defense + (original_hero.cycle_factor_minus_one + 1) * 0x28;
          original_hero.shield = 3;
          original_hero._156_4_ = 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0x9f,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c((original_hero.cycle_factor_minus_one + 1) * 0x28,(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x3b:
          original_hero.defense =
               original_hero.defense + (original_hero.cycle_factor_minus_one + 1) * 0x32;
          original_hero.shield = 4;
          original_hero._160_4_ = 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa0,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c((original_hero.cycle_factor_minus_one + 1) * 0x32,(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
          break;
        case 0x3c:
          original_hero.defense =
               original_hero.defense + (original_hero.cycle_factor_minus_one + 1) * 100;
          original_hero.shield = 5;
          original_hero._164_4_ = 1;
          tile_class_or_message = 1;
          piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
          puStack_24 = &stack0xfffffffc;
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa1,&local_c);
          puVar7 = &DAT_00448ff0;
          puVar9 = local_c;
          FUN_00405b6c((original_hero.cycle_factor_minus_one + 1) * 100,(int *)&local_10);
          piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
          (**(code **)(*piVar3 + 0xc))(piVar3,0xa6,&local_14,local_10,puVar7,puVar9);
          pcStack_2c = local_14;
          FUN_00403710(&DAT_004b8684,4);
        }
        start_event_timer(local_8);
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 2;
        event_stack[dVar1].a = (word)tile_class_or_message;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 8;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 1;
        event_stack[event_cursor].a = 2;
        event_stack[event_cursor].b = 0;
        *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) = 6;
        FUN_0044c04c(local_8);
      }
    }
    else if (uVar4 < 0x5d) {
      if (uVar4 - 0x3d < 0x1e) {
        puStack_24 = &stack0xfffffffc;
        taisen(param_1);
      }
      else if (uVar4 - 0x5b < 2) {
        if (original_hero.floor == 0x31) {
          puStack_24 = &stack0xfffffffc;
          taisen(param_1);
        }
        else if (original_hero.floor == 0x32) {
          if (original_hero.cycle_factor_minus_one == 0) {
            puStack_24 = &stack0xfffffffc;
            if (original_hero._360_4_ != 0) {
              puStack_24 = &stack0xfffffffc;
              FUN_0042c454(*(int *)(param_1 + 0x1b4),'\0');
              FUN_00431188(*(int **)(local_8 + 0x2d8),extraout_EDX_05,extraout_ECX_06);
            }
            FUN_0042c454(*(int *)(local_8 + 0x1b4),'\0');
            start_event_timer(local_8);
            FUN_004135d4(*(int **)(local_8 + 0x1d0),(uint *)&DAT_00448ffc);
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 8;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 7;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0;
            iVar5 = 1;
            do {
              event_cursor = event_cursor + 1;
              event_stack[event_cursor].opcode = 0;
              event_stack[event_cursor].a = 5;
              event_stack[event_cursor].b = 0;
              event_cursor = event_cursor + 1;
              event_stack[event_cursor].opcode = 0xb;
              event_stack[event_cursor].a = 0xc;
              event_stack[event_cursor].b = 0x191 - (short)iVar5;
              iVar5 = iVar5 + 1;
            } while (iVar5 != 0x191);
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 400;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 399;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x18c;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x189;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x186;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x183;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x180;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x17d;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x17a;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x177;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x174;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x171;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x16e;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x16b;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x168;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x165;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x162;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x15f;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x15c;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x159;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x156;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x153;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x150;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x14d;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x14a;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x147;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x144;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x141;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x13e;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x13b;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x138;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x135;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x132;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x12f;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 300;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x127;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x122;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x11d;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x118;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x113;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x10e;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x109;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x104;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xff;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xfa;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf5;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xeb;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xe6;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xe1;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xdc;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xd7;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xd2;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xcd;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xc5;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xbd;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xb5;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xad;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xa5;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x9d;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x95;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x8d;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x85;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x7d;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x75;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x6d;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x65;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x5b;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x51;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x47;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x3d;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x33;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x29;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x1f;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x15;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xb;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 4;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 1;
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
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x11;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0x10;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xe;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xd;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xc;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xb;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 10;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 9;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 8;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 7;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 6;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 5;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 4;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 3;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 2;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 10;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 6;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 1;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf7;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf6;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf5;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf4;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf3;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf2;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf1;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xf0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xef;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xee;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xed;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xec;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xeb;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xea;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xe9;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 2;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xc;
            event_stack[event_cursor].b = 0xe8;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 1;
            event_stack[event_cursor].a = 1;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xf;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0;
            event_stack[event_cursor].a = 0;
            event_stack[event_cursor].b = 0;
            event_cursor = event_cursor + 1;
            event_stack[event_cursor].opcode = 0xb;
            event_stack[event_cursor].a = 0xe;
            event_stack[event_cursor].b = 0;
          }
          else {
            if (original_hero.later_cycle == 0) {
              original_monsters[15].hp = 1000;
              original_monsters[15].attack = 0x271;
              original_monsters[15].defense = 0x7d;
            }
            puStack_24 = &stack0xfffffffc;
            taisen(param_1);
          }
        }
      }
    }
    else if (uVar4 - 0x5d < 0x16) {
      taisen(param_1);
    }
    else if (uVar4 == 0x7a) {
      puStack_24 = &stack0xfffffffc;
      taisen(param_1);
    }
    else if (uVar4 - 0x85 < 0x19) {
      puStack_24 = &stack0xfffffffc;
      taisen(param_1);
    }
  }
  *in_FS_OFFSET = pcStack_2c;
  puStack_24 = &LAB_00448fde;
  puStack_28 = (undefined4 *)0x448fd6;
  FUN_004034fc((int *)&local_14,3);
  return;
}

