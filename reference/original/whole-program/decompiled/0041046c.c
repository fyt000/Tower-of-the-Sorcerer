/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041046c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041046c(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x44) != 0) {
    iVar2 = FUN_0041040c(*(int *)(param_1 + 0x44));
    if (param_2 < 0) {
      param_2 = 0;
    }
    if (iVar2 <= param_2) {
      param_2 = iVar2 + -1;
    }
    iVar2 = root_00410454(param_1);
    if (param_2 != iVar2) {
      piVar1 = *(int **)(param_1 + 0x44);
      FUN_004106d8(piVar1,param_1);
      FUN_00410564(piVar1,param_2,param_1);
    }
  }
  return;
}

