/* Original Delphi callback at 0044ed94; review assembly for inferred types. */

void preview_flight_up(int param_1)

{
  if (original_hero.floor < (int)original_hero._20_4_) {
    original_hero._632_4_ = 1;
    if (original_hero.floor == 0x2b) {
      original_hero.floor = 0x2d;
    }
    else {
      original_hero.floor = original_hero.floor + 1;
    }
    FUN_00442c38(param_1);
    FUN_0044cb34(param_1);
    if ((original_hero.floor == 0x23) &&
       ((uint)original_maps[35][93] + (uint)original_maps[2][122] == 0x1b)) {
      original_maps[2][122] = 6;
    }
    if ((*(char *)(*(int **)(param_1 + 0x1e4) + 0xe) == '\0') && (1 < original_hero.floor)) {
      FUN_0041353c(*(int **)(param_1 + 0x1e4),'\x01');
    }
    if (original_hero._20_4_ == original_hero.floor) {
      FUN_0041353c(*(int **)(param_1 + 0x1e0),'\0');
      (**(code **)(**(int **)(param_1 + 0x1e8) + 0x80))();
    }
  }
  return;
}
