/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0045265c.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TTSW10_timer2timer(int *param_1)

{
  if ((int)event_cursor < 1) {
    FUN_0042c454(param_1[0xbb],'\0');
    if (_DAT_0048c5c0 == 0) {
      FUN_00450880((int)param_1);
    }
  }
  else {
    FUN_004526c0(param_1);
    if ((int)event_cursor < 1) {
      FUN_0042c454(param_1[0xbb],'\0');
      if (_DAT_0048c5c0 == 0) {
        FUN_00450880((int)param_1);
        return;
      }
    }
    else {
      FUN_004526c0(param_1);
    }
  }
  return;
}

