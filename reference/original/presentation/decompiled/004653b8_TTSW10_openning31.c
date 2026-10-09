/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 004653b8.
 * Inferred types and shared tails require assembly review. */

void FUN_004653b8(int param_1,undefined4 param_2,int param_3)

{
  dword dVar1;
  int *piVar2;
  undefined *puVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar4;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar5;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  int local_c;
  int local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_c = 0;
  puStack_20 = &LAB_00465882;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  puVar3 = &stack0xfffffffc;
  local_8 = param_1;
  if (original_hero._360_4_ != 0) {
    FUN_00431188(*(int **)(param_1 + 0x2d8),0,param_3);
    puVar3 = puStack_1c;
  }
  puStack_1c = puVar3;
  piVar2 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
  (**(code **)(*piVar2 + 0xc))(piVar2,1,&local_c);
  FUN_00403658(&local_c,DAT_0048c5fc);
  FUN_00403658(&local_c,(undefined4 *)"\\center.bmp");
  FUN_0041c1e8(*(int *)(*(int *)(local_8 + 0x1b8) + 0xac),local_c);
  if (original_hero.cycle_factor_minus_one == 0) {
    piVar2 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
    (**(code **)(*piVar2 + 0xc))(piVar2,1,&local_c);
    FUN_00403658(&local_c,DAT_0048c5fc);
    FUN_00403658(&local_c,(undefined4 *)"\\left.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(local_8 + 0x1bc) + 0xac),local_c);
  }
  else {
    piVar2 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
    (**(code **)(*piVar2 + 0xc))(piVar2,1,&local_c);
    FUN_00403658(&local_c,DAT_0048c5fc);
    FUN_00403658(&local_c,(undefined4 *)"\\leftr.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(local_8 + 0x1bc) + 0xac),local_c);
  }
  if (original_hero.cycle_factor_minus_one == 0) {
    piVar2 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
    (**(code **)(*piVar2 + 0xc))(piVar2,1,&local_c);
    FUN_00403658(&local_c,DAT_0048c5fc);
    FUN_00403658(&local_c,(undefined4 *)"\\right.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(local_8 + 0x1c0) + 0xac),local_c);
    uVar4 = extraout_ECX;
    uVar5 = extraout_EDX;
  }
  else {
    piVar2 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
    (**(code **)(*piVar2 + 0xc))(piVar2,1,&local_c);
    FUN_00403658(&local_c,DAT_0048c5fc);
    FUN_00403658(&local_c,(undefined4 *)"\\rightr.bmp");
    FUN_0041c1e8(*(int *)(*(int *)(local_8 + 0x1c0) + 0xac),local_c);
    uVar4 = extraout_ECX_00;
    uVar5 = extraout_EDX_00;
  }
  FUN_00413500(*(int **)(local_8 + 0x1b8),CONCAT31((int3)((uint)uVar5 >> 8),1),uVar4);
  FUN_00413500(*(int **)(local_8 + 0x1bc),CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
               extraout_ECX_01);
  FUN_00413500(*(int **)(local_8 + 0x1c0),CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
               extraout_ECX_02);
  FUN_004135d4(*(int **)(local_8 + 0x1d0),(uint *)&LAB_004658fc);
  if (original_hero.cycle_factor_minus_one == 0) {
    original_hero.hp = 400;
    original_hero.attack = 10;
    original_hero.defense = 10;
  }
  else {
    original_hero.hero_orb = 0;
    original_hero.wisdom_orb = 0;
    original_hero.flight_orb = 0;
    original_hero.cross = 0;
    original_hero.elixir = 0;
    original_hero.mattock = 0;
    original_hero.bomb = 0;
    original_hero.warp_staff = 0;
    original_hero.ascent_wing = 0;
    original_hero.descent_wing = 0;
    original_hero.dragon_slayer = 0;
    original_hero.snow_crystal = 0;
    original_hero.magic_key = 0;
    original_hero.super_mattock = 0;
    original_hero.lucky_gold = 0;
  }
  original_hero._164_4_ = 0;
  original_hero._144_4_ = 0;
  original_hero.shield = 0;
  original_hero.sword = 0;
  original_hero._48_4_ = 1;
  original_hero.y = 7;
  original_hero.x = 2;
  original_hero._20_4_ = 2;
  original_hero.floor = 2;
  start_event_timer(local_8);
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0xb;
  event_stack[dVar1].a = 8;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 10;
  event_stack[dVar1].a = 3;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 10;
  event_stack[dVar1].a = 2;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 10;
  event_stack[dVar1].a = 1;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 10;
  event_stack[dVar1].a = 1;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 8;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 2;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  FUN_0044cb34(local_8);
  FUN_0042c454(*(int *)(local_8 + 0x1b4),'\0');
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_00465889;
  puStack_20 = (undefined *)0x465881;
  FUN_004034dc(&local_c);
  return;
}

