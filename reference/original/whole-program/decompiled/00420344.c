/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420344.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00420344(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004202c4(param_1);
  return iVar1 < *(int *)(param_1 + 0x10);
}

