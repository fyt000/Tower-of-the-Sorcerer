/* Original Delphi callback at 0044ed1c; review assembly for inferred types. */

void preview_flight_down(int param_1)

{
  if (1 < original_hero.floor) {
    original_hero._632_4_ = 2;
    if (original_hero.floor == 0x2d) {
      original_hero.floor = 0x2b;
    }
    else {
      original_hero.floor = original_hero.floor + -1;
    }
    FUN_00442c38(param_1);
    FUN_0044cb34(param_1);
    if (*(char *)(*(int **)(param_1 + 0x1e0) + 0xe) == '\0') {
      FUN_0041353c(*(int **)(param_1 + 0x1e0),'\x01');
    }
    if (original_hero.floor == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x1e4),'\0');
      (**(code **)(**(int **)(param_1 + 0x1e8) + 0x80))();
    }
  }
  return;
}
