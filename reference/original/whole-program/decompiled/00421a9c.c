/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421a9c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_00421a9c(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_00421a94(param_1);
  if ((char)uVar1 != '\0') {
    iVar2 = FUN_0041e4b8(*(int *)(param_1 + 0x124));
    if (iVar2 != 0) {
      return 1;
    }
  }
  return 0;
}

