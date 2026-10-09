/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421d90.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00421d90(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_00421d7c(param_1);
  if (((param_2 != iVar1) && ((param_2 == 0 || (0x23 < param_2)))) &&
     (((*(byte *)(param_1 + 0x1c) & 1) == 0 || (*(int *)(param_1 + 0x13c) != 0)))) {
    *(int *)(param_1 + 0x13c) = param_2;
  }
  return;
}

