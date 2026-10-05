/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00451c20. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void classify_neighbor(void)

{
  byte bVar1;
  int iVar2;
  uint uVar3;

  bVar1 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 + neighbor_index);
  uVar3 = (uint)bVar1;
  if (bVar1 < 0x5d) {
    if (uVar3 == 8) {
      tile_class_or_message = 1;
      return;
    }
    if (uVar3 == 0xd) {
      tile_class_or_message = 3;
      return;
    }
    if (0x1d < uVar3 - 0x3d) {
      tile_class_or_message = 0;
      return;
    }
  }
  else if (((3 < uVar3 - 0x5d) && (0xb < uVar3 - 0x85)) && (0xb < uVar3 - 0x93)) {
    tile_class_or_message = 0;
    return;
  }
  tile_class_or_message = 2;
  if ((byte)(bVar1 - 0x3d) < 0x24) {
    monster_index = (int)(bVar1 - 0x3d) >> 1;
    if ((int)monster_index < 0) {
      monster_index = monster_index + ((bVar1 - 0x3d & 1) != 0);
    }
  }
  else if ((byte)(bVar1 + 0x9f) < 0x12) {
    monster_index = 0x12;
  }
  else if ((byte)(bVar1 + 0x8d) < 0x12) {
    monster_index = 0x13;
  }
  else if ((byte)(bVar1 + 0x7b) < 0x1a) {
    iVar2 = (int)(bVar1 - 0x85) >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((bVar1 - 0x85 & 1) != 0);
    }
    monster_index = iVar2 + 0x14;
    return;
  }
  return;
}
