/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e704.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e704(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((*(byte *)(param_1 + 0x1c) & 8) == 0) {
    *(byte *)(param_1 + 0x1c) = *(byte *)(param_1 + 0x1c) | 8;
    if ((*(int *)(param_1 + 0x10) != 0) &&
       (iVar2 = *(int *)(*(int *)(param_1 + 0x10) + 8), -1 < iVar2 + -1)) {
      iVar3 = 0;
      do {
        iVar1 = FUN_00409a40(*(undefined4 **)(param_1 + 0x10),iVar3);
        FUN_0040e704(iVar1);
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return;
}

