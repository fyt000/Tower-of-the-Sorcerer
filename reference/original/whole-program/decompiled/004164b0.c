/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004164b0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004164b0(int *param_1,int param_2)

{
  int *piVar1;
  int aiStack_18 [2];
  
  piVar1 = *(int **)(param_2 + 8);
  if (*(byte *)(param_2 + 4) < 4) {
    if (piVar1[3] != 0) {
      root_00413c24(piVar1[3],param_2);
    }
  }
  else if (*(byte *)(param_2 + 4) == 5) {
    FUN_00413278(param_1,piVar1,aiStack_18);
    piVar1 = FUN_00415350((int)param_1,aiStack_18,0);
    *(int **)(param_2 + 0xc) = piVar1;
    if (piVar1 == (int *)0x0) {
      *(int **)(param_2 + 0xc) = param_1;
    }
  }
  return;
}

