/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004340e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004340e0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  
  if (*(char *)((int)*(int **)(param_1 + 0x1b8) + 0x37) == '\x01') {
    FUN_00413500(*(int **)(param_1 + 0x1d8),CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
    FUN_00413500(*(int **)(param_1 + 0x1b8),0,extraout_ECX);
    return;
  }
  if (*(char *)(*(int *)(param_1 + 0x1d8) + 0x37) == '\x01') {
    FUN_00413500(*(int **)(param_1 + 0x1b8),CONCAT31((int3)((uint)*(int *)(param_1 + 0x1d8) >> 8),1)
                 ,param_3);
    FUN_00413500(*(int **)(param_1 + 0x1d8),0,extraout_ECX_00);
  }
  return;
}

