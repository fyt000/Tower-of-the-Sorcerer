/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0044ed1c.
 * Inferred types and shared tails require assembly review. */

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

