/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0047eadc.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void write_original_save(int param_1)

{
  OriginalHero_conflict *pOVar1;
  int iVar2;
  uint uVar3;
  undefined4 extraout_EDX;
  uint uVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  int iStack_c;
  
  puStack_1c = &stack0xfffffffc;
  iStack_c = 0;
  original_hero._660_4_ = 0;
  uVar3 = 0;
  pOVar1 = &original_hero;
  do {
    iVar2 = pOVar1->hp;
    original_hero._656_4_ = iStack_c + iVar2;
    uVar4 = uVar3 & 0x80000001;
    if ((int)uVar4 < 0) {
      uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
    }
    if (uVar4 != 0) {
      iVar2 = -iVar2;
    }
    original_hero._660_4_ = original_hero._660_4_ + iVar2;
    uVar3 = uVar3 + 1;
    pOVar1 = (OriginalHero_conflict *)&pOVar1->attack;
    iStack_c = original_hero._656_4_;
  } while (uVar3 != 0xa4);
  puStack_20 = &UNK_0047ec11;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
  FUN_0040458d((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
  FUN_00402710();
  FUN_004042b8(&DAT_0048c600);
  FUN_00402710();
  iVar2 = FUN_0042cec8((uint *)"Overwrite. Is it true?",CONCAT31((int3)((uint)extraout_EDX >> 8),2),
                       _DAT_0047eca0,0);
  if (iVar2 == 6) {
    FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
    FUN_004045a4((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
    FUN_00402710();
    FUN_00404254((HANDLE *)&DAT_0048c600,original_maps,0x1881,(uint *)0x0);
    FUN_00402710();
    FUN_00404254((HANDLE *)&DAT_0048c600,&original_hero,0x2ac,(uint *)0x0);
    FUN_00402710();
    FUN_004042b8(&DAT_0048c600);
    FUN_00402710();
    tile_class_or_message = 0x86;
    FUN_0044cb34(param_1);
  }
  *in_FS_OFFSET = uStack_24;
  return;
}

