/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00451d3c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void crystal_lava(void)

{
  dword dVar1;
  word wVar2;
  
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0x11;
  wVar2 = (word)neighbor_index;
  event_stack[dVar1].a = (word)neighbor_index;
  event_stack[dVar1].b = 6;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0xd;
  event_stack[dVar1].a = wVar2;
  event_stack[dVar1].b = (word)DAT_0048c564;
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
  return;
}

