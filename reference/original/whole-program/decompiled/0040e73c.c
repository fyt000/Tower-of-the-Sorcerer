/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e73c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e73c(int param_1,int param_2,char param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if ((*(undefined4 **)(param_1 + 0x14) != (undefined4 *)0x0) && (param_3 == '\x01')) {
    FUN_00409b2c(*(undefined4 **)(param_1 + 0x14),param_2);
    if ((*(int **)(param_1 + 0x14))[2] == 0) {
      FUN_00402c34(*(int **)(param_1 + 0x14));
      *(undefined4 *)(param_1 + 0x14) = 0;
    }
  }
  if ((*(int *)(param_1 + 0x10) != 0) &&
     (iVar2 = *(int *)(*(int *)(param_1 + 0x10) + 8), -1 < iVar2 + -1)) {
    iVar3 = 0;
    do {
      piVar1 = (int *)FUN_00409a40(*(undefined4 **)(param_1 + 0x10),iVar3);
      (**(code **)(*piVar1 + 0x10))(piVar1,param_2,param_3);
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

