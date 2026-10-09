/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00451b98.
 * Inferred types and shared tails require assembly review. */

void mattock_wall(void)

{
  dword dVar1;
  
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0xd;
  event_stack[dVar1].a = (word)neighbor_index;
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
  return;
}

