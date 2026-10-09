/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0046397c.
 * Inferred types and shared tails require assembly review. */

void mevent(int param_1)

{
  int *piVar1;
  dword dVar2;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_ECX_04;
  int extraout_ECX_05;
  int extraout_ECX_06;
  byte (*pabVar3) [123];
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  puStack_1c = &LAB_0046403a;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00450758(param_1);
  switch(original_hero.floor) {
  case 3:
    FUN_0044c04c(param_1);
    start_event_timer(param_1);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar1 + 0xc))(piVar1,0xda,&local_8);
    FUN_004135d4(*(int **)(param_1 + 0x1d0),local_8);
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 10;
    event_stack[dVar2].a = 10;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    scratch_index = 0x46;
    FUN_00461a0c(param_1);
    if (original_hero._360_4_ != 0) {
      event_cursor = event_cursor + 1;
      dVar2 = event_cursor;
      event_stack[event_cursor].opcode = 0;
      event_stack[dVar2].a = 0;
      event_stack[dVar2].b = 0;
      event_cursor = event_cursor + 1;
      dVar2 = event_cursor;
      event_stack[event_cursor].opcode = 1;
      event_stack[dVar2].a = 6;
      event_stack[dVar2].b = 0;
    }
    break;
  case 10:
    FUN_0044c04c(param_1);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    ichicheck(param_1);
    break;
  case 0xf:
    FUN_0044c04c(param_1);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    ichicheck(param_1);
    break;
  case 0x14:
    FUN_0044c04c(param_1);
    if (original_hero.y * 0xb + original_hero.x == 0x52) {
      pabVar3 = original_maps + original_hero.floor;
      original_maps[original_hero.floor][0x54] = 6;
      if (original_hero._360_4_ != 0) {
        FUN_00431188(*(int **)(param_1 + 0x2d8),pabVar3,extraout_ECX);
        original_hero._360_4_ = 0x10;
        FUN_0047c2bc(param_1,extraout_EDX,extraout_ECX_00);
      }
      ichicheck(param_1);
    }
    break;
  case 0x17:
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 2;
    event_stack[dVar2].a = 0x72;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 6;
    event_stack[dVar2].a = (word)contact_index;
    event_stack[dVar2].b = 8;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 1;
    event_stack[dVar2].a = 1;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    start_event_timer(param_1);
    break;
  case 0x18:
    FUN_0044c04c(param_1);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    ichicheck(param_1);
    break;
  case 0x19:
    FUN_0044c04c(param_1);
    pabVar3 = original_maps + original_hero.floor;
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    if (original_hero._360_4_ != 0) {
      FUN_00431188(*(int **)(param_1 + 0x2d8),pabVar3,extraout_ECX_01);
      original_hero._360_4_ = 7;
      FUN_0047c2bc(param_1,extraout_EDX_00,extraout_ECX_02);
    }
    ichicheck(param_1);
    break;
  case 0x1e:
    FUN_0044c04c(param_1);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    ichicheck(param_1);
    break;
  case 0x20:
    ichicheck(param_1);
    break;
  case 0x21:
    FUN_0044c04c(param_1);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    ichicheck(param_1);
    break;
  case 0x26:
    FUN_0044c04c(param_1);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    ichicheck(param_1);
    break;
  case 0x28:
    FUN_0044c04c(param_1);
    pabVar3 = original_maps + original_hero.floor;
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    if (original_hero._360_4_ != 0) {
      FUN_00431188(*(int **)(param_1 + 0x2d8),pabVar3,extraout_ECX_03);
      original_hero._360_4_ = 0x12;
      FUN_0047c2bc(param_1,extraout_EDX_01,extraout_ECX_04);
    }
    ichicheck(param_1);
    break;
  case 0x2a:
    ichicheck(param_1);
    break;
  case 0x2b:
    FUN_0044c04c(param_1);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    ichicheck(param_1);
    break;
  case 0x30:
    ichicheck(param_1);
    break;
  case 0x31:
    FUN_0044c04c(param_1);
    pabVar3 = original_maps + original_hero.floor;
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
         = 6;
    if (original_hero._360_4_ != 0) {
      FUN_00431188(*(int **)(param_1 + 0x2d8),pabVar3,extraout_ECX_05);
      original_hero._360_4_ = 0x13;
      FUN_0047c2bc(param_1,extraout_EDX_02,extraout_ECX_06);
    }
    ichicheck(param_1);
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_00464041;
  puStack_1c = (undefined *)0x464039;
  FUN_004034dc((int *)&local_8);
  return;
}

