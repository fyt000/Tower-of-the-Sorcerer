/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0044c5c4.
 * Inferred types and shared tails require assembly review. */

void mazyutu1(int param_1)

{
  dword dVar1;
  undefined4 uVar2;
  int iVar3;
  short sVar4;
  
  if (tile_class_or_message == 0x6e) {
    if ((((original_hero.floor == 0x2f) && (original_hero.y - 1U < 9)) &&
        (original_hero.y * 0xb + original_hero.x + DAT_0048c568 < 0x7a)) &&
       (original_maps[0x2f][original_hero.y * 0xb + original_hero.x + DAT_0048c568 + 2] == 6)) {
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0xc;
      sVar4 = (short)original_hero.y * 0xb + (short)original_hero.x;
      iVar3 = (int)DAT_0048c568 >> 1;
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((DAT_0048c568 & 1) != 0);
      }
      event_stack[dVar1].a = sVar4 + (short)iVar3;
      event_stack[dVar1].b = sVar4 + (short)DAT_0048c568;
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
    if (original_hero._164_4_ == 0) {
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0x10;
      event_stack[dVar1].a = ((short)original_hero.cycle_factor_minus_one + 1) * -200;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 2;
      if (original_hero.cycle_factor_minus_one == 0) {
        event_stack[dVar1].a = (word)tile_class_or_message;
      }
      else {
        event_stack[dVar1].a = (word)tile_class_or_message + 0x1c;
      }
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 6;
      uVar2 = original_hero._352_4_;
      if (original_hero._352_4_ == 1) {
        event_stack[dVar1].b = 0xbf;
      }
      else if (original_hero._352_4_ == 2) {
        event_stack[dVar1].b = 199;
      }
      else if (original_hero._352_4_ == 3) {
        event_stack[dVar1].b = 0xcf;
      }
      else if (original_hero._352_4_ == 4) {
        event_stack[dVar1].b = 0xd7;
      }
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 9;
      event_stack[dVar1].a = (word)scratch_index;
      if (uVar2 == 1) {
        event_stack[dVar1].b = 0xc0;
      }
      else if (uVar2 == 2) {
        event_stack[dVar1].b = 200;
      }
      else if (uVar2 == 3) {
        event_stack[dVar1].b = 0xd0;
      }
      else if (uVar2 == 4) {
        event_stack[dVar1].b = 0xd8;
      }
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
    start_event_timer(param_1);
    tile_class_or_message = 0;
    DAT_0048c560 = 1;
  }
  else if (tile_class_or_message == 0x6f) {
    if (original_hero._164_4_ == 0) {
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0x10;
      event_stack[dVar1].a = ((short)original_hero.cycle_factor_minus_one + 1) * -100;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 2;
      if (original_hero.cycle_factor_minus_one == 0) {
        event_stack[dVar1].a = (word)tile_class_or_message;
      }
      else {
        event_stack[dVar1].a = (word)tile_class_or_message + 0x1c;
      }
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 6;
      uVar2 = original_hero._352_4_;
      if (original_hero._352_4_ == 1) {
        event_stack[dVar1].b = 0xbf;
      }
      else if (original_hero._352_4_ == 2) {
        event_stack[dVar1].b = 199;
      }
      else if (original_hero._352_4_ == 3) {
        event_stack[dVar1].b = 0xcf;
      }
      else if (original_hero._352_4_ == 4) {
        event_stack[dVar1].b = 0xd7;
      }
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 9;
      event_stack[dVar1].a = (word)scratch_index;
      if (uVar2 == 1) {
        event_stack[dVar1].b = 0xc0;
      }
      else if (uVar2 == 2) {
        event_stack[dVar1].b = 200;
      }
      else if (uVar2 == 3) {
        event_stack[dVar1].b = 0xd0;
      }
      else if (uVar2 == 4) {
        event_stack[dVar1].b = 0xd8;
      }
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
    start_event_timer(param_1);
    tile_class_or_message = 0;
    DAT_0048c560 = 1;
  }
  return;
}

