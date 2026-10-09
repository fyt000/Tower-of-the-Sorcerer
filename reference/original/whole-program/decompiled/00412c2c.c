/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412c2c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00412c2c(int **param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  
  if (*param_1 == (int *)0x0) {
    piVar1 = (int *)FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
    *param_1 = piVar1;
  }
  FUN_004099a4(*param_1,param_2);
  return;
}

