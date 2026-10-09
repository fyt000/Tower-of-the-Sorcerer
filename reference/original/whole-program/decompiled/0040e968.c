/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e968.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0040e968(int param_1,undefined *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (((param_2 != (undefined *)0x0) && (*(int *)(param_1 + 0x10) != 0)) &&
     (iVar3 = *(int *)(*(int *)(param_1 + 0x10) + 8), -1 < iVar3 + -1)) {
    iVar4 = 0;
    do {
      iVar1 = FUN_00409a40(*(undefined4 **)(param_1 + 0x10),iVar4);
      iVar2 = FUN_00405a34(*(undefined **)(iVar1 + 8),param_2);
      if (iVar2 == 0) {
        return iVar1;
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return 0;
}

