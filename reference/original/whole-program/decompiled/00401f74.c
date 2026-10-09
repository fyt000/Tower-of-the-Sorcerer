/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401f74.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00401f74(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_1 >> 2;
  if (uVar2 < 0x401) {
    do {
      iVar1 = *(int *)(DAT_0048a478 + -0xc + uVar2 * 4);
      if (iVar1 != 0) {
        return iVar1;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 != 0x401);
  }
  return 0;
}

