/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00450ba0.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TTSW10_Button38Click(int param_1,undefined4 param_2)

{
  dword dVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int iVar5;
  int *in_FS_OFFSET;
  undefined *puVar6;
  undefined4 *puVar7;
  int iStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  int iStack_18;
  int iStack_14;
  undefined4 *puStack_10;
  undefined4 *puStack_c;
  undefined4 uStack_8;
  
  puStack_28 = &stack0xfffffffc;
  puStack_c = (undefined4 *)0x0;
  puStack_10 = (undefined4 *)0x0;
  iStack_14 = 0;
  iStack_18 = 0;
  puStack_2c = &UNK_00451b5d;
  iStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_30;
  uStack_8 = param_2;
  FUN_00413500(*(int **)(param_1 + 0x2cc),0,0);
  FUN_00413500(*(int **)(param_1 + 0x2d0),0,extraout_ECX);
  switch(selected_item) {
  case 5:
    tile_class_or_message = 1;
    start_event_timer(param_1);
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 2;
    event_stack[dVar1].a = (word)tile_class_or_message;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
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
    scratch_index = original_hero.attack * 10 + original_hero.defense * 5;
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xba,&puStack_c);
    puVar6 = &UNK_00451b74;
    puVar7 = puStack_c;
    FUN_00405b6c(scratch_index,(int *)&puStack_10);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xa6,&iStack_14,puStack_10,puVar6,puVar7);
    iStack_30 = iStack_14;
    FUN_00403710(&DAT_004b8684,4);
    original_hero.hp = original_hero.hp + scratch_index;
    original_hero.elixir = 0;
    _DAT_0048c5c0 = 0;
    break;
  case 6:
    start_event_timer(param_1);
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 2;
    event_stack[dVar1].a = 0x3c;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 8;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    tile_class_or_message = 0;
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index + 0xb;
    if (((uint)original_hero.y < 10) &&
       (contact_index = neighbor_index, classify_neighbor(param_1), tile_class_or_message == 1)) {
      mattock_wall(param_1);
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index + 1;
    if (((uint)original_hero.x < 10) &&
       (contact_index = neighbor_index, classify_neighbor(param_1), tile_class_or_message == 1)) {
      mattock_wall(param_1);
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index - 1;
    if ((original_hero.x - 1U < 10) &&
       (contact_index = neighbor_index, classify_neighbor(param_1), tile_class_or_message == 1)) {
      mattock_wall(param_1);
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index - 0xb;
    contact_index = neighbor_index;
    if ((original_hero.y - 1U < 10) && (classify_neighbor(param_1), tile_class_or_message == 1)) {
      mattock_wall(param_1);
    }
    original_hero.mattock = 0;
    break;
  case 7:
    start_event_timer(param_1);
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0xb;
    event_stack[dVar1].a = 5;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 2;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 8;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    bomb_gold = 0;
    tile_class_or_message = 0;
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index + 0xb;
    if (((uint)original_hero.y < 10) &&
       (contact_index = neighbor_index, classify_neighbor(param_1), tile_class_or_message == 2)) {
      bomb_gold = bomb_gold + original_monsters[monster_index].gold;
      toroad2(param_1);
    }
    neighbor_index = scratch_index + 1;
    if (((uint)original_hero.x < 10) &&
       (contact_index = neighbor_index, classify_neighbor(param_1), tile_class_or_message == 2)) {
      bomb_gold = bomb_gold + original_monsters[monster_index].gold;
      toroad2(param_1);
    }
    neighbor_index = scratch_index - 1;
    if ((original_hero.x - 1U < 10) &&
       (contact_index = neighbor_index, classify_neighbor(param_1), tile_class_or_message == 2)) {
      bomb_gold = bomb_gold + original_monsters[monster_index].gold;
      toroad2(param_1);
    }
    neighbor_index = scratch_index - 0xb;
    contact_index = neighbor_index;
    if ((original_hero.y - 1U < 10) && (classify_neighbor(param_1), tile_class_or_message == 2)) {
      bomb_gold = bomb_gold + original_monsters[monster_index].gold;
      toroad2(param_1);
    }
    original_hero.gold = original_hero.gold + bomb_gold;
    original_hero.bomb = 0;
    tile_class_or_message = 1;
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xbc,&puStack_c);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,200,&puStack_10,puStack_c);
    puVar6 = &UNK_00451b74;
    puVar7 = puStack_10;
    FUN_00405b6c(bomb_gold,&iStack_14);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xc9,&iStack_18,iStack_14,puVar6,puVar7);
    iStack_30 = iStack_18;
    FUN_00403710(&DAT_004b8684,5);
    break;
  case 8:
    original_hero.warp_staff = original_hero.warp_staff + -1;
    tile_class_or_message = 0x3e;
    DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
    contact_index = 0x78 - DAT_0048c580;
    if (*(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) == '\x06') {
      DAT_0048c54c = (*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * DAT_0048c580) %
                     (*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 0xb);
      DAT_0048c550 = ((*(int *)(*(int *)(param_1 + 0x254) + 0x30) * DAT_0048c580) /
                     (*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 0xb)) *
                     *(int *)(*(int *)(param_1 + 0x254) + 0x30);
      iVar4 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 + DAT_0048c580) - 1;
      iVar5 = DAT_0048c550;
      piVar2 = (int *)FUN_0041dad8((int)DAT_0048c514);
      FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,DAT_0048c54c,iVar4,iVar5);
      DAT_0048c5a8 = (uint)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + DAT_0048c580);
      FUN_00454c10();
      iVar4 = (*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + DAT_0048c580) - 1) + door_opened;
      iVar5 = DAT_0048c550;
      piVar2 = (int *)FUN_0041dad8(DAT_0048c518);
      FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,DAT_0048c54c,iVar4,iVar5);
      original_hero.x = (int)contact_index % 0xb;
      original_hero.y = (int)contact_index / 0xb;
      DAT_0048c54c = (int)(*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * contact_index) %
                     (*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 0xb);
      DAT_0048c550 = ((int)(*(int *)(*(int *)(param_1 + 0x254) + 0x30) * contact_index) /
                     (*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 0xb)) *
                     *(int *)(*(int *)(param_1 + 0x254) + 0x30);
      FUN_004433a4(param_1);
      piVar2 = DAT_0048c514;
      piVar3 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a5b8(piVar3,DAT_0048c578,DAT_0048c57c,piVar2);
      start_event_timer(param_1);
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 1;
      event_stack[event_cursor].a = 2;
      event_stack[event_cursor].b = 0;
    }
    else {
      tile_class_or_message = 0x44;
    }
    FUN_00450880(param_1);
    FUN_0044cb34(param_1);
    break;
  case 9:
    if ((original_hero.floor == 0x32) ||
       (*(char *)(original_hero.floor * 0x7b + 0x4b89b1 + original_hero.y * 0xb + original_hero.x)
        != '\x06')) {
      tile_class_or_message = 0x45;
      FUN_0044cb34(param_1);
      FUN_00450880(param_1);
    }
    else {
      original_hero.ascent_wing = 0;
      tile_class_or_message = 0x3f;
      original_hero.floor = original_hero.floor + 1;
      if (original_hero._360_4_ != 0) {
        FUN_0047c8f8();
        FUN_0047c2bc(param_1,extraout_EDX,extraout_ECX_00);
      }
      FUN_00442c38(param_1);
      start_event_timer(param_1);
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 2;
      event_stack[event_cursor].a = (word)tile_class_or_message;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 8;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 0;
      event_stack[event_cursor].a = 0;
      event_stack[event_cursor].b = 0;
      event_cursor = event_cursor + 1;
      event_stack[event_cursor].opcode = 1;
      event_stack[event_cursor].a = 2;
      event_stack[event_cursor].b = 0;
      FUN_00450880(param_1);
      FUN_0044cb34(param_1);
    }
    break;
  case 10:
    if (original_hero.floor == 0) {
      tile_class_or_message = 0x46;
      FUN_0044cb34(param_1);
      FUN_00450880(param_1);
    }
    else {
      if (*(char *)(original_hero.floor * 0x7b + 0x4b88bb + original_hero.y * 0xb + original_hero.x)
          == '\x06') {
        original_hero.descent_wing = 0;
        tile_class_or_message = 0x40;
        original_hero.floor = original_hero.floor + -1;
        if (original_hero._360_4_ != 0) {
          FUN_0047c8f8();
          FUN_0047c2bc(param_1,extraout_EDX_00,extraout_ECX_01);
        }
        FUN_00442c38(param_1);
        start_event_timer(param_1);
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 2;
        event_stack[event_cursor].a = (word)tile_class_or_message;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 8;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 1;
        event_stack[event_cursor].a = 2;
        event_stack[event_cursor].b = 0;
      }
      else {
        tile_class_or_message = 0x46;
      }
      FUN_0044cb34(param_1);
      FUN_00450880(param_1);
    }
    break;
  case 0xc:
    start_event_timer(param_1);
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 8;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    DAT_0048c560 = 0;
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index + 0xb;
    if (((uint)original_hero.y < 10) &&
       (contact_index = neighbor_index, classify_neighbor(param_1), tile_class_or_message == 3)) {
      DAT_0048c560 = 1;
      DAT_0048c564 = 0xb;
      crystal_lava(param_1);
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index + 1;
    if (((uint)original_hero.x < 10) &&
       (contact_index = neighbor_index, classify_neighbor(param_1), tile_class_or_message == 3)) {
      DAT_0048c560 = 1;
      DAT_0048c564 = 10;
      crystal_lava(param_1);
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index - 1;
    if ((original_hero.x - 1U < 10) &&
       (contact_index = neighbor_index, classify_neighbor(param_1), tile_class_or_message == 3)) {
      DAT_0048c560 = 1;
      DAT_0048c564 = 9;
      crystal_lava(param_1);
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index - 0xb;
    contact_index = neighbor_index;
    if ((original_hero.y - 1U < 10) && (classify_neighbor(param_1), tile_class_or_message == 3)) {
      DAT_0048c560 = 1;
      DAT_0048c564 = 0xc;
      crystal_lava(param_1);
    }
    if (DAT_0048c560 == 1) {
      tile_class_or_message = 1;
      piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar2 + 0xc))(piVar2,0xc6,&puStack_c);
      piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      puVar7 = puStack_c;
      (**(code **)(*piVar2 + 0xc))(piVar2,0xc0,&puStack_10);
      FUN_0040369c(&DAT_004b8684,puStack_10,puVar7);
    }
    else {
      tile_class_or_message = 0x41;
    }
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 2;
    event_stack[dVar1].a = (word)tile_class_or_message;
    event_stack[dVar1].b = 0;
    break;
  case 0xd:
    original_hero.magic_key = 0;
    tile_class_or_message = 0x42;
    start_event_timer(param_1);
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
    iVar5 = 0x78;
    do {
      DAT_0048c570 = iVar5;
      if (*(char *)(original_hero.floor * 0x7b + 0x4b8936 + iVar5) == '\x01') {
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0xd;
        event_stack[dVar1].a = (word)DAT_0048c570;
        event_stack[dVar1].b = 1;
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
      }
      iVar5 = iVar5 + -1;
    } while (iVar5 != -1);
    break;
  case 0xe:
    original_hero.super_mattock = 0;
    tile_class_or_message = 0x43;
    start_event_timer(param_1);
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
    iVar5 = 10;
    do {
      iVar4 = 10;
      do {
        DAT_0048c570 = iVar4 * 0xb + iVar5;
        if (*(char *)(original_hero.floor * 0x7b + 0x4b8936 + DAT_0048c570) == '\b') {
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 0;
          event_stack[dVar1].a = 0;
          event_stack[dVar1].b = 0;
          dVar1 = event_cursor + 1;
          event_cursor = dVar1;
          event_stack[dVar1].opcode = 6;
          event_stack[dVar1].a = (word)DAT_0048c570;
          event_stack[dVar1].b = 6;
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
        }
        iVar4 = iVar4 + -1;
      } while (iVar4 != -1);
      iVar5 = iVar5 + -1;
    } while (iVar5 != -1);
  }
  *in_FS_OFFSET = iStack_30;
  puStack_28 = &UNK_00451b64;
  puStack_2c = (undefined *)0x451b5c;
  FUN_004034fc(&iStack_18,4);
  return;
}

