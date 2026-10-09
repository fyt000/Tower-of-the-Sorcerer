/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0044ea90.
 * Inferred types and shared tails require assembly review. */

void TTSW10_Button7Click(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  
  FUN_00413500(*(int **)(param_1 + 0x1d4),0,param_3);
  FUN_00413500(*(int **)(param_1 + 0x1d8),0,extraout_ECX);
  FUN_00450880(param_1);
  if (*(char *)(*(int *)(param_1 + 0x350) + 0x28) == '\x01') {
    TTSW10_buttonfocus(param_1);
  }
  FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
  FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_00);
  FUN_0044cb34(param_1);
  return;
}

