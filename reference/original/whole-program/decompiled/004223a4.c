/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004223a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004223a4(int **param_1,int **param_2,undefined4 param_3)

{
  int **ppiVar1;
  undefined4 uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  int **extraout_EDX;
  int **extraout_EDX_00;
  int **extraout_EDX_01;
  int **ppiVar3;
  int **extraout_EDX_02;
  
  if (param_2 != (int **)param_1[0x43]) {
    ppiVar3 = param_2;
    if ((param_2 != (int **)0x0) &&
       (((param_1 == param_2 ||
         (ppiVar1 = FUN_0041fffc(param_2), ppiVar3 = extraout_EDX, param_1 != ppiVar1)) ||
        (uVar2 = FUN_00416c2c(param_2), param_3 = extraout_ECX, ppiVar3 = extraout_EDX_00,
        (char)uVar2 == '\0')))) {
      uVar2 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)ppiVar3 >> 8),1),0xf02e);
      FUN_004031f8(uVar2);
      param_3 = extraout_ECX_00;
      ppiVar3 = extraout_EDX_01;
    }
    param_1[0x43] = (int *)param_2;
    if (*(char *)((int)param_1 + 0x119) != '\0') {
      FUN_004226b4((int *)param_1);
      param_3 = extraout_ECX_01;
      ppiVar3 = extraout_EDX_02;
    }
    FUN_00402cdc((int *)param_1,ppiVar3,param_3);
    return;
  }
  return;
}

