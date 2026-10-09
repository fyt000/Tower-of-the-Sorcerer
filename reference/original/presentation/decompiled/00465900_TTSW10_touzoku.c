/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00465900.
 * Inferred types and shared tails require assembly review. */

void touzoku(int param_1)

{
  dword dVar1;
  int *piVar2;
  int extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_1c = &LAB_004660b6;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00450758(param_1);
  FUN_004135d4(*(int **)(param_1 + 0x1d0),(uint *)&DAT_004660cc);
  if (original_hero.floor < 0x1e) {
    if (original_hero.floor == 0x1d) {
      if (original_hero.y * 0xb + original_hero.x == 0x1b) {
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 10;
        event_stack[dVar1].a = 0x1b;
        event_stack[dVar1].b = 0;
        start_event_timer(param_1);
      }
      else if (original_hero.floor29_thief_heard == 0) {
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 10;
        event_stack[event_cursor].a = 0x1c;
        event_stack[event_cursor].b = 0;
        start_event_timer(param_1);
      }
      else if (original_hero.floor29_thief_heard == 1) {
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 10;
        event_stack[event_cursor].a = 0x1d;
        event_stack[event_cursor].b = 0;
        start_event_timer(param_1);
      }
    }
    else if (original_hero.floor == 2) {
      if (original_hero.x == 0) {
        start_event_timer(param_1);
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 10;
        event_stack[event_cursor].a = 5;
        event_stack[event_cursor].b = 0;
      }
      else if (original_hero.x - 2U < 2) {
        tile_class_or_message = 1;
        piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
        (**(code **)(*piVar2 + 0xc))(piVar2,0x89,&local_8);
        FUN_0040352c(&DAT_004b8684,local_8);
        start_event_timer(param_1);
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 0;
        event_stack[dVar1].a = 0;
        event_stack[dVar1].b = 0;
        dVar1 = event_cursor + 1;
        event_cursor = dVar1;
        event_stack[dVar1].opcode = 10;
        event_stack[dVar1].a = 4;
        event_stack[dVar1].b = 0;
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
        event_stack[dVar1].a = 0x43;
        event_stack[dVar1].b = 7;
        doorstackin();
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 1;
        event_stack[event_cursor].a = 1;
        event_stack[event_cursor].b = 0;
        if (original_hero._360_4_ != 0) {
          FUN_0047c8f8();
          FUN_0047c2bc(param_1,extraout_EDX,extraout_ECX);
        }
      }
      else if (original_hero.x - 9U < 2) {
        scratch_index = 6;
        if (original_hero.floor2_thief_tunnel_started == 1) {
          scratch_index = 7;
        }
        start_event_timer(param_1);
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 0;
        event_stack[event_cursor].a = 0;
        event_stack[event_cursor].b = 0;
        event_cursor = event_cursor + 1;
        event_stack[event_cursor].opcode = 10;
        event_stack[event_cursor].a = (word)scratch_index;
        event_stack[event_cursor].b = 0;
      }
    }
    else if (original_hero.floor == 0xf) {
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 6;
      event_stack[dVar1].a = 6;
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
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0xc;
      event_stack[dVar1].a = 7;
      event_stack[dVar1].b = 6;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0xc;
      event_stack[dVar1].a = 8;
      event_stack[dVar1].b = 7;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 10;
      event_stack[dVar1].a = 0x12;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0xd;
      event_stack[dVar1].a = 7;
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
  }
  else if (original_hero.floor == 0x23) {
    original_maps[2][122] = 6;
    scratch_index = 0x20;
    if (original_hero.floor35_thief_heard == 1) {
      scratch_index = 0x21;
    }
    start_event_timer(param_1);
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 10;
    event_stack[dVar1].a = (word)scratch_index;
    event_stack[dVar1].b = 0;
  }
  else if (original_hero.floor == 0x32) {
    start_event_timer(param_1);
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 10;
    event_stack[dVar1].a = 0x108;
    event_stack[dVar1].b = 0;
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_004660bd;
  puStack_1c = (undefined *)0x4660b5;
  FUN_004034dc((int *)&local_8);
  return;
}

