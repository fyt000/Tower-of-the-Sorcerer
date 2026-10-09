/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0047beac.
 * Inferred types and shared tails require assembly review. */

void doorcheck(void)

{
  dword dVar1;
  
  if (original_hero.floor == 0x27) {
    if ((((uint)original_maps[39][14] + (uint)original_maps[39][18] + (uint)original_maps[39][36] +
          (uint)original_maps[39][38] + (uint)original_maps[39][58] + (uint)original_maps[39][60] +
          (uint)original_maps[39][62] == 7) && (original_maps[39][16] == 6)) &&
       (contact_index == 0x26)) {
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 6;
      event_stack[dVar1].a = 0x24;
      event_stack[dVar1].b = 0x2b;
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 1;
      event_stack[dVar1].a = 2;
      event_stack[dVar1].b = 0;
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
    }
    if ((((uint)original_maps[original_hero.floor][0xe] +
          (uint)original_maps[original_hero.floor][0x12] +
          (uint)original_maps[original_hero.floor][0x24] +
          (uint)original_maps[original_hero.floor][0x26] +
          (uint)original_maps[original_hero.floor][0x3a] +
          (uint)original_maps[original_hero.floor][0x3c] +
          (uint)original_maps[original_hero.floor][0x3e] == 7) && (original_maps[39][40] == 6)) &&
       (contact_index == 0xe)) {
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 6;
      event_stack[dVar1].a = 0x24;
      event_stack[dVar1].b = 0x2b;
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 1;
      event_stack[dVar1].a = 2;
      event_stack[dVar1].b = 0;
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      event_cursor = event_cursor + 1;
      dVar1 = event_cursor;
      event_stack[event_cursor].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      return;
    }
  }
  else if (((original_hero.floor == 0x2b) && (contact_index == 7)) &&
          (original_maps[43][10] == 0x5d)) {
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 6;
    event_stack[dVar1].a = 7;
    event_stack[dVar1].b = 7;
  }
  return;
}

