/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004013a0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_004013a0(int **param_1,int **param_2)

{
  int *piVar1;
  int **ppiVar2;
  
  ppiVar2 = (int **)FUN_00401348();
  if (ppiVar2 == (int **)0x0) {
    return 0;
  }
  ppiVar2[2] = *param_2;
  ppiVar2[3] = param_2[1];
  piVar1 = *param_1;
  *ppiVar2 = piVar1;
  ppiVar2[1] = (int *)param_1;
  piVar1[1] = (int)ppiVar2;
  *param_1 = (int *)ppiVar2;
  return CONCAT31((int3)((uint)ppiVar2 >> 8),1);
}

