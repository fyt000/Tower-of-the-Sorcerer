/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041761c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0041761c(uint param_1)

{
  int iVar1;
  
  iVar1 = FUN_00419b00(param_1);
  if (iVar1 == 0x1fffffff) {
    return -1;
  }
  if (iVar1 == 0x20000000) {
    iVar1 = -0x1000000;
  }
  return iVar1;
}

