/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0044eaf4.
 * Inferred types and shared tails require assembly review. */

void confirm_flight(int param_1,undefined4 param_2,undefined4 param_3)

{
  dword dVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int extraout_ECX_01;
  undefined4 extraout_EDX;
  
  FUN_00413500(*(int **)(param_1 + 0x1e0),0,param_3);
  FUN_00413500(*(int **)(param_1 + 0x1e4),0,extraout_ECX);
  FUN_00413500(*(int **)(param_1 + 0x1e8),0,extraout_ECX_00);
  if (((original_hero._632_4_ != 0) && (original_hero.floor != 0x19)) &&
     (original_maps[25][73] == 0x17)) {
    original_maps[25][73] = 6;
  }
  if (((original_hero._632_4_ != 0) && (original_hero.floor != 0x31)) &&
     (original_maps[49][18] == 0x17)) {
    original_maps[49][18] = 6;
  }
  original_hero._48_4_ = 0;
  if (original_hero._632_4_ == 1) {
    if ((original_hero.floor == original_hero._20_4_) && (original_hero._664_4_ == 1)) {
      original_hero._632_4_ = 2;
    }
  }
  else if (((original_hero._632_4_ == 2) && (original_hero.floor == original_hero._20_4_)) &&
          (original_hero._664_4_ != 1)) {
    original_hero._632_4_ = 1;
  }
  if (original_hero._632_4_ - 1 < 2) {
    original_hero.x =
         (uint)*(byte *)(original_hero.floor * 0x7b + 0x4b8933 + original_hero._632_4_) % 0xb;
    original_hero.y = *(byte *)(original_hero.floor * 0x7b + 0x4b8933 + original_hero._632_4_) / 0xb
    ;
  }
  if (((original_hero._632_4_ != 0) && (original_hero._20_4_ == 0x1d)) &&
     (original_hero.floor < 0x1d)) {
    original_maps[29][40] = 6;
    original_maps[29][29] = 6;
    original_maps[29][19] = 0x15;
  }
  DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
  DAT_0048c54c = (iVar2 * DAT_0048c580) % (iVar2 * 0xb);
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  DAT_0048c550 = ((iVar2 * DAT_0048c580) / (iVar2 * 0xb)) * iVar2;
  if (original_hero._632_4_ == 1) {
    FUN_00442f80();
  }
  else if (original_hero._632_4_ == 2) {
    FUN_00443050();
  }
  start_event_timer(param_1);
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 1;
  event_stack[dVar1].a = 2;
  event_stack[dVar1].b = 0;
  FUN_004433a4(param_1);
  tile_class_or_message = 0x17;
  FUN_0044cb34(param_1);
  if (original_hero._360_4_ != 0) {
    FUN_0047c8f8();
    FUN_0047c2bc(param_1,extraout_EDX,extraout_ECX_01);
  }
  FUN_00450880(param_1);
  return;
}

