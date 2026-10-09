/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044c464.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0044c464(int param_1)

{
  dword dVar1;
  undefined4 uVar2;
  
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0x13;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 2;
  event_stack[dVar1].a = 0x70;
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
  start_event_timer(param_1);
  tile_class_or_message = 0;
  DAT_0048c560 = 1;
  return;
}

