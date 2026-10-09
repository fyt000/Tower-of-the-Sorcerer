/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004109bc.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_004109bc(int param_1)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00410958(param_1);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x2c))();
  }
  return piVar1 != (int *)0x0;
}

