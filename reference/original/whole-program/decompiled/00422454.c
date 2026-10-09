/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422454.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00422454(int **param_1,int **param_2,undefined4 param_3)

{
  char cVar1;
  
  cVar1 = *(char *)((int)param_1 + 0x119);
  FUN_004223a4(param_1,param_2,param_3);
  if (cVar1 == '\0') {
    (*(code *)(*param_1)[0x20])();
  }
  return;
}

