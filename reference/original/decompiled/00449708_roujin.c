/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00449708. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void roujin(int param_1)

{
  dword dVar1;
  int iVar2;

  FUN_004135d4(*(int **)(param_1 + 0x1d0),(uint *)&DAT_00449e14);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1cc) + 0x44),(uint)DAT_00489b9d);
  FUN_00450758(param_1);
  dialogue_continue_stage = 0;
  DAT_0048c564 = 0;
  switch(original_hero.floor) {
  case 2:
    DAT_0048c5a0 = 0x19;
    neighbor_index = 0x42;
    if (original_hero._392_4_ == 0) {
      original_hero._392_4_ = 1;
      original_hero.attack = original_hero.attack + (original_hero.attack * 3) / 100;
      original_hero.defense = original_hero.defense + (original_hero.defense * 3) / 100;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 2;
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
      start_event_timer(param_1);
    }
    break;
  case 3:
    DAT_0048c5a0 = 0x1a;
    neighbor_index = 0x43;
    break;
  case 4:
    DAT_0048c5a0 = 0;
    neighbor_index = 0x44;
    break;
  case 6:
    DAT_0048c5a0 = 1;
    neighbor_index = 0x45;
    break;
  case 0x10:
    if (original_hero.x == 9) {
      DAT_0048c5a0 = 0x1b;
      neighbor_index = 0x47;
    }
    else {
      DAT_0048c5a0 = 6;
      neighbor_index = 0x46;
    }
    break;
  case 0x12:
    DAT_0048c5a0 = 7;
    neighbor_index = 0x48;
    break;
  case 0x15:
    DAT_0048c5a0 = 8;
    neighbor_index = 0x49;
    break;
  case 0x17:
    DAT_0048c564 = 1;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 10;
    event_stack[dVar1].a = 0x3d;
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
    start_event_timer(param_1);
    break;
  case 0x1b:
    DAT_0048c5a0 = 9;
    neighbor_index = 0x4a;
    break;
  case 0x1f:
    DAT_0048c5a0 = 10;
    neighbor_index = 0x4b;
    break;
  case 0x21:
    DAT_0048c5a0 = 0xc;
    neighbor_index = 0x4c;
    break;
  case 0x24:
    DAT_0048c5a0 = 0xd;
    neighbor_index = 0x4d;
    break;
  case 0x25:
    DAT_0048c5a0 = 0xe;
    neighbor_index = 0x4e;
    break;
  case 0x27:
    DAT_0048c5a0 = 0x10;
    neighbor_index = 0x4f;
    break;
  case 0x2a:
    DAT_0048c5a0 = 0x12;
    neighbor_index = 0x50;
    break;
  case 0x2d:
    DAT_0048c5a0 = 0x13;
    neighbor_index = 0x51;
    break;
  case 0x2e:
    DAT_0048c5a0 = 0x15;
    neighbor_index = 0x52;
    break;
  case 0x30:
    DAT_0048c5a0 = 0x17;
    neighbor_index = 0x53;
  }
  if (DAT_0048c564 != 1) {
    if ((DAT_0048c5a0 == 0x1b) && (original_hero._436_4_ == 0)) {
      original_hero.elixir = 1;
      original_hero._436_4_ = 1;
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
      start_event_timer(param_1);
    }
    iVar2 = (&original_hero.hp)[neighbor_index];
    if (iVar2 == 0) {
      if (original_hero.wisdom_orb == 0) {
        (&original_hero.hp)[neighbor_index] = 1;
      }
      else if (original_hero.wisdom_orb == 1) {
        (&original_hero.hp)[neighbor_index] = 2;
      }
      FUN_00449e18(param_1);
      if (original_hero.floor == 3) {
        original_hero.hero_orb = 2;
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
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 2;
        event_stack[dVar1].a = 0xb;
        event_stack[dVar1].b = 0;
        start_event_timer(param_1);
      }
    }
    else if (iVar2 == 1) {
      DAT_0048c5a0 = 0x18;
      FUN_00449e18(param_1);
    }
    else if (iVar2 == 2) {
      DAT_0048c5a0 = 0x18;
      FUN_00449e18(param_1);
    }
  }
  return;
}
