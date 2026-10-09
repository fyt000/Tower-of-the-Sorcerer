/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430344.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00430344(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = 0;
  bVar1 = 0;
  do {
    if (*(char *)(param_1 + 0x104 + (uint)bVar1 * 0x10) != '\0') {
      iVar2 = iVar2 + 1;
    }
    bVar1 = bVar1 + 1;
  } while (bVar1 != 9);
  if (iVar2 == 0) {
    iVar2 = 1;
  }
  return iVar2;
}

