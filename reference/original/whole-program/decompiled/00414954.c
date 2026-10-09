/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414954.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00414954(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 unaff_EBX;
  
  iVar1 = FUN_00414ccc(*(int *)(param_4 + -0x10));
  iVar1 = iVar1 + -1;
  if (-1 < iVar1) {
    do {
      iVar2 = FUN_00414c9c(*(int *)(param_4 + -0x10),iVar1);
      if (*(char *)(iVar2 + 0x3b) != '\0') {
        return CONCAT31((int3)((uint)unaff_EBX >> 8),1);
      }
      iVar1 = iVar1 + -1;
    } while (iVar1 != -1);
  }
  return 0;
}

