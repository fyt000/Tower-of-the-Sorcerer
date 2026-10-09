/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d9ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0040d9ac(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(*(int *)(param_4 + -4) + 0x1c) != 0) {
    iVar1 = FUN_00402b78(*(undefined4 **)(param_4 + -8));
    iVar2 = FUN_00402b78(*(undefined4 **)(*(int *)(param_4 + -4) + 0x1c));
    if ((iVar1 == iVar2) ||
       (iVar2 = *(int *)(param_4 + -8), iVar2 == *(int *)(*(int *)(param_4 + -4) + 0x18))) {
      return CONCAT31((int3)((uint)iVar2 >> 8),1);
    }
  }
  return 0;
}

