/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004340b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004340b4(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  
  FUN_00413500(*(int **)(param_1 + 0x1d0),CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  FUN_00413500(*(int **)(param_1 + 0x1b8),0,extraout_ECX);
  FUN_00413500(*(int **)(param_1 + 0x1d8),0,extraout_ECX_00);
  return;
}

