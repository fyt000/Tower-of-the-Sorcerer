/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00480e64.
 * Inferred types, shared tails and runtime effects require assembly review. */

void TTSW10_KeyboardControl1Click(int param_1)

{
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  
  FUN_00450758(param_1);
  FUN_00413500(*(int **)(param_1 + 0x450),0,extraout_ECX);
  FUN_00413500(*(int **)(param_1 + 0x454),0,extraout_ECX_00);
  FUN_00413500(*(int **)(param_1 + 0x458),0,extraout_ECX_01);
  FUN_00413500(*(int **)(param_1 + 0x45c),0,extraout_ECX_02);
  DAT_00489ba0 = 1;
  FUN_004102f0(*(int *)(param_1 + 0x350),0);
  FUN_004102f0(*(int *)(param_1 + 0x354),1);
  FUN_00450758(param_1);
  *(undefined *)(DAT_0048c510 + 0x118) = 1;
  FUN_00450880(param_1);
  return;
}

