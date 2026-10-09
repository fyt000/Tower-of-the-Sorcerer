/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042bf20.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042bf20(int param_1,LPRECT param_2,undefined4 param_3,int param_4)

{
  LPRECT ptVar1;
  undefined4 extraout_ECX;
  undefined4 uVar2;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 uVar3;
  undefined4 extraout_EDX_00;
  
  FUN_0041a060(*(int **)(param_1 + 0x10),1);
  param_2->bottom = param_2->bottom + -1;
  param_2->right = param_2->right + -1;
  ptVar1 = param_2;
  uVar2 = extraout_ECX;
  uVar3 = extraout_EDX;
  if (0 < param_4) {
    do {
      param_4 = param_4 + -1;
      FUN_0042be5c((char)ptVar1,(char)uVar3,(char)uVar2,&stack0xfffffffc);
      ptVar1 = (LPRECT)InflateRect(param_2,-1,-1);
      uVar2 = extraout_ECX_00;
      uVar3 = extraout_EDX_00;
    } while (0 < param_4);
  }
  param_2->bottom = param_2->bottom + 1;
  param_2->right = param_2->right + 1;
  return;
}

