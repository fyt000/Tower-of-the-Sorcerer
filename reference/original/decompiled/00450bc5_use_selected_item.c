/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00450bc5. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void use_selected_item(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int *unaff_EBX;
  int unaff_EBP;
  int unaff_ESI;
  int iVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_00000000;
  undefined *puVar6;
  undefined4 uVar7;
  undefined4 *puVar8;

  FUN_00413500(*(int **)(unaff_ESI + 0x2cc),0,param_3);
  FUN_00413500(*(int **)(unaff_ESI + 0x2d0),0,extraout_ECX);
  switch(selected_item) {
  case 5:
    tile_class_or_message = 1;
    start_event_timer(unaff_ESI);
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 0;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 2;
    event_stack[iVar5].a = (word)tile_class_or_message;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 0;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 8;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 0;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 1;
    event_stack[iVar5].a = 2;
    event_stack[iVar5].b = 0;
    scratch_index = original_hero.attack * 10 + original_hero.defense * 5;
    piVar2 = *(int **)(*(int *)(unaff_ESI + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xba,unaff_EBP + -8);
    uVar7 = *(undefined4 *)(unaff_EBP + -8);
    puVar6 = &UNK_00451b74;
    FUN_00405b6c(scratch_index,(int *)(unaff_EBP + -0xc));
    piVar2 = *(int **)(*(int *)(unaff_ESI + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))
              (piVar2,0xa6,unaff_EBP + -0x10,*(undefined4 *)(unaff_EBP + -0xc),puVar6,uVar7);
    in_stack_00000000 = *(undefined4 *)(unaff_EBP + -0x10);
    FUN_00403710(&DAT_004b8684,4);
    original_hero.hp = original_hero.hp + scratch_index;
    original_hero.elixir = 0;
    _DAT_0048c5c0 = 0;
    break;
  case 6:
    start_event_timer(unaff_ESI);
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 2;
    event_stack[iVar5].a = 0x3c;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 8;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    tile_class_or_message = 0;
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index + 0xb;
    if (((uint)original_hero.y < 10) &&
       (contact_index = neighbor_index, classify_neighbor(), tile_class_or_message == 1)) {
      func_0x00451b98();
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index + 1;
    if (((uint)original_hero.x < 10) &&
       (contact_index = neighbor_index, classify_neighbor(), tile_class_or_message == 1)) {
      func_0x00451b98();
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index - 1;
    if ((original_hero.x - 1U < 10) &&
       (contact_index = neighbor_index, classify_neighbor(), tile_class_or_message == 1)) {
      func_0x00451b98();
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index - 0xb;
    contact_index = neighbor_index;
    if ((original_hero.y - 1U < 10) && (classify_neighbor(), tile_class_or_message == 1)) {
      func_0x00451b98();
    }
    original_hero.mattock = 0;
    break;
  case 7:
    start_event_timer(unaff_ESI);
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 0;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 0xb;
    event_stack[iVar5].a = 5;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 2;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 8;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    bomb_gold = 0;
    tile_class_or_message = 0;
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index + 0xb;
    if (((uint)original_hero.y < 10) &&
       (contact_index = neighbor_index, classify_neighbor(), tile_class_or_message == 2)) {
      bomb_gold = bomb_gold + original_monsters[monster_index].gold;
      toroad2();
    }
    neighbor_index = scratch_index + 1;
    if (((uint)original_hero.x < 10) &&
       (contact_index = neighbor_index, classify_neighbor(), tile_class_or_message == 2)) {
      bomb_gold = bomb_gold + original_monsters[monster_index].gold;
      toroad2();
    }
    neighbor_index = scratch_index - 1;
    if ((original_hero.x - 1U < 10) &&
       (contact_index = neighbor_index, classify_neighbor(), tile_class_or_message == 2)) {
      bomb_gold = bomb_gold + original_monsters[monster_index].gold;
      toroad2();
    }
    neighbor_index = scratch_index - 0xb;
    contact_index = neighbor_index;
    if ((original_hero.y - 1U < 10) && (classify_neighbor(), tile_class_or_message == 2)) {
      bomb_gold = bomb_gold + original_monsters[monster_index].gold;
      toroad2();
    }
    original_hero.gold = original_hero.gold + bomb_gold;
    original_hero.bomb = 0;
    tile_class_or_message = 1;
    piVar2 = *(int **)(*(int *)(unaff_ESI + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xbc,unaff_EBP + -8);
    piVar2 = *(int **)(*(int *)(unaff_ESI + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,200,unaff_EBP + -0xc,*(undefined4 *)(unaff_EBP + -8));
    uVar7 = *(undefined4 *)(unaff_EBP + -0xc);
    puVar6 = &UNK_00451b74;
    FUN_00405b6c(bomb_gold,(int *)(unaff_EBP + -0x10));
    piVar2 = *(int **)(*(int *)(unaff_ESI + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))
              (piVar2,0xc9,unaff_EBP + -0x14,*(undefined4 *)(unaff_EBP + -0x10),puVar6,uVar7);
    in_stack_00000000 = *(undefined4 *)(unaff_EBP + -0x14);
    FUN_00403710(&DAT_004b8684,5);
    break;
  case 8:
    original_hero.warp_staff = original_hero.warp_staff + -1;
    tile_class_or_message = 0x3e;
    DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
    contact_index = 0x78 - DAT_0048c580;
    if (*(char *)(original_hero.floor * 0x7b + 0x4b8936 + contact_index) == '\x06') {
      DAT_0048c54c = (*(int *)(*(int *)(unaff_ESI + 0x254) + 0x2c) * DAT_0048c580) %
                     (*(int *)(*(int *)(unaff_ESI + 0x254) + 0x2c) * 0xb);
      DAT_0048c550 = ((*(int *)(*(int *)(unaff_ESI + 0x254) + 0x30) * DAT_0048c580) /
                     (*(int *)(*(int *)(unaff_ESI + 0x254) + 0x30) * 0xb)) *
                     *(int *)(*(int *)(unaff_ESI + 0x254) + 0x30);
      iVar4 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 + DAT_0048c580) - 1;
      iVar5 = DAT_0048c550;
      piVar2 = (int *)FUN_0041dad8((int)DAT_0048c514);
      FUN_00417e44(*(int **)(unaff_ESI + 0x1b0),piVar2,DAT_0048c54c,iVar4,iVar5);
      DAT_0048c5a8 = (uint)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + DAT_0048c580);
      FUN_00454c10();
      iVar4 = (*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + DAT_0048c580) - 1) + door_opened;
      iVar5 = DAT_0048c550;
      piVar2 = (int *)FUN_0041dad8(DAT_0048c518);
      FUN_00417e44(*(int **)(unaff_ESI + 0x1b0),piVar2,DAT_0048c54c,iVar4,iVar5);
      original_hero.x = (int)contact_index % 0xb;
      original_hero.y = (int)contact_index / 0xb;
      DAT_0048c54c = (int)(*(int *)(*(int *)(unaff_ESI + 0x254) + 0x2c) * contact_index) %
                     (*(int *)(*(int *)(unaff_ESI + 0x254) + 0x2c) * 0xb);
      DAT_0048c550 = ((int)(*(int *)(*(int *)(unaff_ESI + 0x254) + 0x30) * contact_index) /
                     (*(int *)(*(int *)(unaff_ESI + 0x254) + 0x30) * 0xb)) *
                     *(int *)(*(int *)(unaff_ESI + 0x254) + 0x30);
      FUN_004433a4(unaff_ESI);
      piVar2 = DAT_0048c514;
      piVar3 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a5b8(piVar3,DAT_0048c578,DAT_0048c57c,piVar2);
      start_event_timer(unaff_ESI);
      *unaff_EBX = *unaff_EBX + 1;
      event_stack[*unaff_EBX].opcode = 1;
      event_stack[*unaff_EBX].a = 2;
      event_stack[*unaff_EBX].b = 0;
    }
    else {
      tile_class_or_message = 0x44;
    }
    FUN_00450880(unaff_ESI);
    FUN_0044cb34(unaff_ESI);
    break;
  case 9:
    if ((original_hero.floor == 0x32) ||
       (*(char *)(original_hero.floor * 0x7b + 0x4b89b1 + original_hero.y * 0xb + original_hero.x)
        != '\x06')) {
      tile_class_or_message = 0x45;
      FUN_0044cb34(unaff_ESI);
      FUN_00450880(unaff_ESI);
    }
    else {
      original_hero.ascent_wing = 0;
      tile_class_or_message = 0x3f;
      original_hero.floor = original_hero.floor + 1;
      if (original_hero._360_4_ != 0) {
        FUN_0047c8f8();
        FUN_0047c2bc(unaff_ESI,extraout_EDX,extraout_ECX_00);
      }
      FUN_00442c38(unaff_ESI);
      start_event_timer(unaff_ESI);
      *unaff_EBX = *unaff_EBX + 1;
      event_stack[*unaff_EBX].opcode = 2;
      event_stack[*unaff_EBX].a = (word)tile_class_or_message;
      event_stack[*unaff_EBX].b = 0;
      *unaff_EBX = *unaff_EBX + 1;
      event_stack[*unaff_EBX].opcode = 8;
      event_stack[*unaff_EBX].a = 0;
      event_stack[*unaff_EBX].b = 0;
      *unaff_EBX = *unaff_EBX + 1;
      event_stack[*unaff_EBX].opcode = 0;
      event_stack[*unaff_EBX].a = 0;
      event_stack[*unaff_EBX].b = 0;
      *unaff_EBX = *unaff_EBX + 1;
      event_stack[*unaff_EBX].opcode = 1;
      event_stack[*unaff_EBX].a = 2;
      event_stack[*unaff_EBX].b = 0;
      FUN_00450880(unaff_ESI);
      FUN_0044cb34(unaff_ESI);
    }
    break;
  case 10:
    if (original_hero.floor == 0) {
      tile_class_or_message = 0x46;
      FUN_0044cb34(unaff_ESI);
      FUN_00450880(unaff_ESI);
    }
    else {
      if (*(char *)(original_hero.floor * 0x7b + 0x4b88bb + original_hero.y * 0xb + original_hero.x)
          == '\x06') {
        original_hero.descent_wing = 0;
        tile_class_or_message = 0x40;
        original_hero.floor = original_hero.floor + -1;
        if (original_hero._360_4_ != 0) {
          FUN_0047c8f8();
          FUN_0047c2bc(unaff_ESI,extraout_EDX_00,extraout_ECX_01);
        }
        FUN_00442c38(unaff_ESI);
        start_event_timer(unaff_ESI);
        *unaff_EBX = *unaff_EBX + 1;
        event_stack[*unaff_EBX].opcode = 2;
        event_stack[*unaff_EBX].a = (word)tile_class_or_message;
        event_stack[*unaff_EBX].b = 0;
        *unaff_EBX = *unaff_EBX + 1;
        event_stack[*unaff_EBX].opcode = 8;
        event_stack[*unaff_EBX].a = 0;
        event_stack[*unaff_EBX].b = 0;
        *unaff_EBX = *unaff_EBX + 1;
        event_stack[*unaff_EBX].opcode = 0;
        event_stack[*unaff_EBX].a = 0;
        event_stack[*unaff_EBX].b = 0;
        *unaff_EBX = *unaff_EBX + 1;
        event_stack[*unaff_EBX].opcode = 1;
        event_stack[*unaff_EBX].a = 2;
        event_stack[*unaff_EBX].b = 0;
      }
      else {
        tile_class_or_message = 0x46;
      }
      FUN_0044cb34(unaff_ESI);
      FUN_00450880(unaff_ESI);
    }
    break;
  case 0xc:
    start_event_timer(unaff_ESI);
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 8;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    DAT_0048c560 = 0;
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index + 0xb;
    if (((uint)original_hero.y < 10) &&
       (contact_index = neighbor_index, classify_neighbor(), tile_class_or_message == 3)) {
      DAT_0048c560 = 1;
      DAT_0048c564 = 0xb;
      func_0x00451d3c();
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index + 1;
    if (((uint)original_hero.x < 10) &&
       (contact_index = neighbor_index, classify_neighbor(), tile_class_or_message == 3)) {
      DAT_0048c560 = 1;
      DAT_0048c564 = 10;
      func_0x00451d3c();
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index - 1;
    if ((original_hero.x - 1U < 10) &&
       (contact_index = neighbor_index, classify_neighbor(), tile_class_or_message == 3)) {
      DAT_0048c560 = 1;
      DAT_0048c564 = 9;
      func_0x00451d3c();
    }
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index - 0xb;
    contact_index = neighbor_index;
    if ((original_hero.y - 1U < 10) && (classify_neighbor(), tile_class_or_message == 3)) {
      DAT_0048c560 = 1;
      DAT_0048c564 = 0xc;
      func_0x00451d3c();
    }
    if (DAT_0048c560 == 1) {
      tile_class_or_message = 1;
      piVar2 = *(int **)(*(int *)(unaff_ESI + 0x44c) + 0x100);
      (**(code **)(*piVar2 + 0xc))(piVar2,0xc6,unaff_EBP + -8);
      puVar8 = *(undefined4 **)(unaff_EBP + -8);
      piVar2 = *(int **)(*(int *)(unaff_ESI + 0x44c) + 0x100);
      (**(code **)(*piVar2 + 0xc))(piVar2,0xc0,unaff_EBP + -0xc);
      FUN_0040369c(&DAT_004b8684,*(undefined4 **)(unaff_EBP + -0xc),puVar8);
    }
    else {
      tile_class_or_message = 0x41;
    }
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 2;
    event_stack[iVar5].a = (word)tile_class_or_message;
    event_stack[iVar5].b = 0;
    break;
  case 0xd:
    original_hero.magic_key = 0;
    tile_class_or_message = 0x42;
    start_event_timer(unaff_ESI);
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 2;
    event_stack[iVar5].a = (word)tile_class_or_message;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 8;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    iVar5 = 0x78;
    do {
      DAT_0048c570 = iVar5;
      if (*(char *)(original_hero.floor * 0x7b + 0x4b8936 + iVar5) == '\x01') {
        *unaff_EBX = *unaff_EBX + 1;
        iVar4 = *unaff_EBX;
        event_stack[iVar4].opcode = 0xd;
        event_stack[iVar4].a = (word)DAT_0048c570;
        event_stack[iVar4].b = 1;
        doorstackin();
        *unaff_EBX = *unaff_EBX + 1;
        iVar4 = *unaff_EBX;
        event_stack[iVar4].opcode = 0;
        event_stack[iVar4].a = 0;
        event_stack[iVar4].b = 0;
        *unaff_EBX = *unaff_EBX + 1;
        iVar4 = *unaff_EBX;
        event_stack[iVar4].opcode = 1;
        event_stack[iVar4].a = 1;
        event_stack[iVar4].b = 0;
      }
      iVar5 = iVar5 + -1;
    } while (iVar5 != -1);
    break;
  case 0xe:
    original_hero.super_mattock = 0;
    tile_class_or_message = 0x43;
    start_event_timer(unaff_ESI);
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 2;
    event_stack[iVar5].a = (word)tile_class_or_message;
    event_stack[iVar5].b = 0;
    *unaff_EBX = *unaff_EBX + 1;
    iVar5 = *unaff_EBX;
    event_stack[iVar5].opcode = 8;
    event_stack[iVar5].a = 0;
    event_stack[iVar5].b = 0;
    iVar5 = 10;
    do {
      iVar4 = 10;
      do {
        DAT_0048c570 = iVar4 * 0xb + iVar5;
        if (*(char *)(original_hero.floor * 0x7b + 0x4b8936 + DAT_0048c570) == '\b') {
          *unaff_EBX = *unaff_EBX + 1;
          iVar1 = *unaff_EBX;
          event_stack[iVar1].opcode = 0;
          event_stack[iVar1].a = 0;
          event_stack[iVar1].b = 0;
          *unaff_EBX = *unaff_EBX + 1;
          iVar1 = *unaff_EBX;
          event_stack[iVar1].opcode = 6;
          event_stack[iVar1].a = (word)DAT_0048c570;
          event_stack[iVar1].b = 6;
          *unaff_EBX = *unaff_EBX + 1;
          iVar1 = *unaff_EBX;
          event_stack[iVar1].opcode = 0;
          event_stack[iVar1].a = 0;
          event_stack[iVar1].b = 0;
          *unaff_EBX = *unaff_EBX + 1;
          iVar1 = *unaff_EBX;
          event_stack[iVar1].opcode = 1;
          event_stack[iVar1].a = 2;
          event_stack[iVar1].b = 0;
        }
        iVar4 = iVar4 + -1;
      } while (iVar4 != -1);
      iVar5 = iVar5 + -1;
    } while (iVar5 != -1);
  }
  *in_FS_OFFSET = in_stack_00000000;
  FUN_004034fc((int *)(unaff_EBP + -0x14),4);
  return;
}
