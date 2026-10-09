/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c614.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042c614(int param_1,undefined4 param_2,LPRECT param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10c);
  if (*(char *)(param_1 + 0x105) != '\0') {
    iVar1 = iVar1 + *(int *)(param_1 + 0x108);
  }
  if (*(char *)(param_1 + 0x104) != '\0') {
    iVar1 = iVar1 + *(int *)(param_1 + 0x108);
  }
  InflateRect(param_3,-iVar1,-iVar1);
  FUN_00414990(param_1,param_2,param_3);
  return;
}

