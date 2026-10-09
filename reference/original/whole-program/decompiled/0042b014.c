/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042b014.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042b014(int *param_1)

{
  tagPOINT tStack_24;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  int aiStack_c [2];
  
  uStack_1c = 0x201;
  GetCursorPos(&tStack_24);
  FUN_00413278(param_1,&tStack_24.x,aiStack_c);
  uStack_14 = FUN_004052f4((undefined2 *)aiStack_c);
  uStack_18 = 0;
  uStack_10 = 0;
  (**(code **)(*param_1 + -0x10))(param_1,&uStack_1c);
  uStack_1c = 0x202;
  (**(code **)(*param_1 + -0x10))(param_1,&uStack_1c);
  return;
}

