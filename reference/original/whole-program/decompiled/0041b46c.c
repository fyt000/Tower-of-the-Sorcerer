/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041b46c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0041b46c(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + 0x1f;
  if (iVar1 < 0) {
    iVar1 = param_1 + 0x3e;
  }
  return (iVar1 >> 5) << 2;
}

