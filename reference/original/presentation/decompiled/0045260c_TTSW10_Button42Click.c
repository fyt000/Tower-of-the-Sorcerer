/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0045260c.
 * Inferred types and shared tails require assembly review. */

void TTSW10_Button42Click(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  
  FUN_00413500(*(int **)(param_1 + 0x2dc),0,param_3);
  FUN_00413500(*(int **)(param_1 + 0x2e0),0,extraout_ECX);
  FUN_00413500(*(int **)(param_1 + 0x2e4),0,extraout_ECX_00);
  FUN_00413500(*(int **)(param_1 + 0x2e8),0,extraout_ECX_01);
  FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_02);
  FUN_00450880(param_1);
  return;
}

