/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00451e1c.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void altar_health(int param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  dword dVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int *in_FS_OFFSET;
  int iStackY_38;
  undefined *puVar3;
  uint *puVar4;
  int iStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  int iStack_10;
  int iStack_c;
  uint *puStack_8;
  
  puStack_20 = &stack0xfffffffc;
  puStack_8 = (uint *)0x0;
  iStack_c = 0;
  iStack_10 = 0;
  puStack_24 = &UNK_00452098;
  iStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_28;
  FUN_00413500(*(int **)(param_1 + 0x2dc),0,param_3);
  FUN_00413500(*(int **)(param_1 + 0x2e0),0,extraout_ECX);
  FUN_00413500(*(int **)(param_1 + 0x2e4),0,extraout_ECX_00);
  FUN_00413500(*(int **)(param_1 + 0x2e8),0,extraout_ECX_01);
  FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_02);
  if (original_hero.gold < (int)bomb_gold) {
    piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar1 + 0xc))(piVar1,0xd3,&puStack_8);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),puStack_8);
    dialogue_continue_stage = 0;
    FUN_004130b8(*(int **)(param_1 + 0x1d0),
                 ((*(int *)(*(int *)(param_1 + 0x1cc) + 0x28) +
                  *(int *)(*(int *)(param_1 + 0x1cc) + 0x30)) - (*(int **)(param_1 + 0x1d0))[0xc]) +
                 -0x10);
    FUN_00413098(*(int **)(param_1 + 0x1d0),
                 ((*(int *)(*(int *)(param_1 + 0x1cc) + 0x24) +
                  *(int *)(*(int *)(param_1 + 0x1cc) + 0x2c)) - (*(int **)(param_1 + 0x1d0))[0xb]) +
                 -0x10);
    FUN_00413500(*(int **)(param_1 + 0x1cc),CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                 extraout_ECX_03);
    FUN_00413500(*(int **)(param_1 + 0x1d0),CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                 extraout_ECX_04);
    (**(code **)(**(int **)(param_1 + 0x1d0) + 0x80))();
  }
  else {
    tile_class_or_message = 1;
    piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar1 + 0xc))(piVar1,0xb5,&puStack_8);
    puVar3 = &UNK_004520b0;
    puVar4 = puStack_8;
    FUN_00405b6c((original_hero._44_4_ + 1) * 100 * (original_hero.cycle_factor_minus_one + 1),
                 &iStack_c);
    piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar1 + 0xc))(piVar1,0xa6,&iStack_10,iStack_c,puVar3,puVar4);
    iStackY_38 = iStack_10;
    FUN_00403710(&DAT_004b8684,4);
    original_hero._44_4_ = original_hero._44_4_ + 1;
    original_hero.gold = original_hero.gold - bomb_gold;
    original_hero.hp =
         original_hero.hp + original_hero._44_4_ * 100 * (original_hero.cycle_factor_minus_one + 1);
    start_event_timer(param_1);
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 2;
    event_stack[dVar2].a = 1;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar2].a = 0;
    event_stack[dVar2].b = 0;
    event_cursor = event_cursor + 1;
    dVar2 = event_cursor;
    event_stack[event_cursor].opcode = 1;
    event_stack[dVar2].a = 2;
    event_stack[dVar2].b = 0;
    _DAT_0048c5c0 = 0;
  }
  *in_FS_OFFSET = iStackY_38;
  FUN_004034fc(&iStack_10,3);
  return;
}

