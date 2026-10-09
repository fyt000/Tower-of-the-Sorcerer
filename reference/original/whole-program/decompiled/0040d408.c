/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d408.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0040d408(undefined *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(*(int *)(*(int *)(param_4 + -4) + 0x2c) + 8);
  if (-1 < iVar3 + -1) {
    iVar4 = 0;
    do {
      iVar1 = FUN_00409a40(*(undefined4 **)(*(int *)(param_4 + -4) + 0x2c),iVar4);
      iVar2 = FUN_00405a34(*(undefined **)(iVar1 + 8),param_1);
      if (iVar2 == 0) {
        return iVar1;
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return 0;
}

