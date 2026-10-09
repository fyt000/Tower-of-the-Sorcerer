/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0047c258.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0047c258(int param_1,undefined4 param_2,int param_3)

{
  int extraout_ECX;
  undefined4 extraout_EDX;
  
  if (original_hero._360_4_ != 0) {
    FUN_00431188(*(int **)(param_1 + 0x2d8),param_2,param_3);
    original_hero._360_4_ = 0;
    DAT_00489ba2 = 0;
    FUN_004102f0(*(int *)(param_1 + 0x330),0);
    return;
  }
  FUN_004102f0(*(int *)(param_1 + 0x330),1);
  if (*(char *)(*(int *)(param_1 + 0x41c) + 0x20) == '\0') {
    FUN_0047c8f8();
    FUN_0047c2bc(param_1,extraout_EDX,extraout_ECX);
  }
  DAT_00489ba2 = 1;
  return;
}

