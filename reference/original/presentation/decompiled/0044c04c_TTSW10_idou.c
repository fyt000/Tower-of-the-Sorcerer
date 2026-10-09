/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0044c04c.
 * Inferred types and shared tails require assembly review. */

void FUN_0044c04c(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  dword dVar7;
  int *piVar8;
  
  DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
  DAT_0048c54c = (DAT_0048c580 * iVar2) % (iVar2 * 0xb);
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  DAT_0048c550 = ((DAT_0048c580 * iVar2) / (iVar2 * 0xb)) * iVar2;
  if (original_hero._352_4_ == 2) {
    DAT_0048c54c = DAT_0048c54c - *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
  }
  else if (original_hero._352_4_ == 4) {
    DAT_0048c550 = DAT_0048c550 - *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  }
  uVar6 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
  if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
    if ((int)uVar6 < 0) {
      uVar6 = uVar6 + 3;
    }
    uVar6 = (int)uVar6 >> 2;
  }
  if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
    uVar5 = uVar6 & 1;
    uVar6 = (int)uVar6 >> 1;
    if ((int)uVar6 < 0) {
      uVar6 = uVar6 + (uVar5 != 0);
    }
  }
  if (0 < (int)uVar6) {
    dVar7 = 1;
    uVar5 = uVar6;
    do {
      iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      neighbor_index = dVar7;
      if (uVar6 == iVar2 >> 2) {
        neighbor_index = dVar7 << 2;
      }
      uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
      uVar3 = (int)uVar1 >> 1;
      if ((int)uVar3 < 0) {
        uVar3 = uVar3 + ((uVar1 & 1) != 0);
      }
      if (uVar6 == uVar3) {
        neighbor_index = neighbor_index * 2;
      }
      DAT_0048c56c = dVar7;
      FUN_00443808(param_1);
      piVar8 = DAT_0048c514;
      piVar4 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a5b8(piVar4,DAT_0048c578,DAT_0048c57c,piVar8);
      dVar7 = dVar7 + 1;
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
  }
  original_hero.x = (int)contact_index % 0xb;
  original_hero.y = (int)contact_index / 0xb;
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
  DAT_0048c54c = (int)(iVar2 * contact_index) % (iVar2 * 0xb);
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  DAT_0048c550 = ((int)(iVar2 * contact_index) / (iVar2 * 0xb)) * iVar2;
  FUN_004433a4(param_1);
  DAT_0048c560 = 0;
  DAT_0048c568 = 0;
  tile_class_or_message = 0;
  scratch_index = original_hero.y * 0xb + original_hero.x;
  neighbor_index = scratch_index - 0xb;
  if ((original_hero.y - 1U < 10) &&
     ((FUN_0044c9f0(), tile_class_or_message == 0x6e || (tile_class_or_message == 0x6f)))) {
    DAT_0048c568 = 0xffffffea;
    mazyutu1(param_1);
  }
  neighbor_index = scratch_index - 1;
  if ((original_hero.x - 1U < 10) &&
     ((FUN_0044c9f0(), tile_class_or_message == 0x6e || (tile_class_or_message == 0x6f)))) {
    DAT_0048c568 = 0xfffffffe;
    mazyutu1(param_1);
  }
  neighbor_index = scratch_index + 1;
  if (((uint)original_hero.x < 10) &&
     ((FUN_0044c9f0(), tile_class_or_message == 0x6e || (tile_class_or_message == 0x6f)))) {
    DAT_0048c568 = 2;
    mazyutu1(param_1);
  }
  neighbor_index = scratch_index + 0xb;
  if (((uint)original_hero.y < 10) &&
     ((FUN_0044c9f0(), tile_class_or_message == 0x6e || (tile_class_or_message == 0x6f)))) {
    DAT_0048c568 = 0x16;
    mazyutu1(param_1);
  }
  if (original_hero._164_4_ == 0) {
    if (((original_hero.x - 1U < 9) &&
        (*(char *)(original_hero.floor * 0x7b + scratch_index + 0x4b8935) == ']')) &&
       (*(char *)(original_hero.floor * 0x7b + scratch_index + 0x4b8937) == ']')) {
      FUN_0044c464(param_1);
    }
    if (((original_hero.y - 1U < 9) &&
        (*(char *)(original_hero.floor * 0x7b + scratch_index + 0x4b892b) == ']')) &&
       (*(char *)(original_hero.floor * 0x7b + scratch_index + 0x4b8941) == ']')) {
      FUN_0044c464(param_1);
    }
  }
  if (DAT_0048c560 == 0) {
    tile_class_or_message = 0;
    scratch_index = original_hero.y * 0xb + original_hero.x;
    neighbor_index = scratch_index - 0xb;
    if (original_hero.y - 1U < 10) {
      FUN_0044c9f0();
    }
    neighbor_index = scratch_index - 1;
    if (original_hero.x - 1U < 10) {
      FUN_0044c9f0();
    }
    neighbor_index = scratch_index + 1;
    if ((uint)original_hero.x < 10) {
      FUN_0044c9f0();
    }
    neighbor_index = scratch_index + 0xb;
    if ((uint)original_hero.y < 10) {
      FUN_0044c9f0();
    }
    FUN_0044cb34(param_1);
  }
  return;
}

