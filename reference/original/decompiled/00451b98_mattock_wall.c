/* Original Delphi callback at 00451b98; review assembly for inferred types. */

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
