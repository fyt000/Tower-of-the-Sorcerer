/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041ccd4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041ccd4(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 extraout_ECX;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    FUN_0041c954(param_1);
    param_3 = extraout_ECX;
  }
  iVar1 = *(int *)(param_1 + 0x10);
  *(undefined4 *)(iVar1 + 0x20) = 0;
  if (param_2 != *(int *)(iVar1 + 0x10)) {
    FUN_0041ce20(param_1,0,param_3);
    *(int *)(*(int *)(param_1 + 0x10) + 0x10) = param_2;
    FUN_0041bd8c(param_1);
  }
  return;
}

