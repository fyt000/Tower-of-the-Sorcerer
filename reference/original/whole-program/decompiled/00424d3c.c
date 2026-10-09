/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424d3c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00424d3c(int param_1,undefined4 param_2)

{
  int *piVar1;
  char cVar2;
  
  piVar1 = *(int **)(param_1 + 0x60);
  if (piVar1 != (int *)0x0) {
    cVar2 = (**(code **)(*piVar1 + 0x8c))(piVar1,param_2);
    if (cVar2 != '\0') {
      FUN_00425618(param_1);
    }
  }
  return 0;
}

