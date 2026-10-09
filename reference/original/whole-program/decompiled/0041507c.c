/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041507c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0041507c(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_00409a88(*(int *)(param_1 + 0xb4),param_2);
  iVar1 = iVar1 + 1;
  iVar3 = *(int *)(*(int *)(param_1 + 0xb4) + 8) + -1;
  if (iVar1 <= iVar3) {
    iVar3 = (iVar3 - iVar1) + 1;
    do {
      iVar2 = FUN_00409a40(*(undefined4 **)(param_1 + 0xb4),iVar1);
      if (*(int *)(iVar2 + 0xc0) != 0) {
        return *(int *)(iVar2 + 0xc0);
      }
      iVar1 = iVar1 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return 0;
}

