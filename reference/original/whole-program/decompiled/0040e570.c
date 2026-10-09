/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e570.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e570(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 extraout_ECX;
  
  if ((*(int *)(param_1 + 4) == 0) || (*(int *)(param_1 + 4) != *(int *)(param_2 + 4))) {
    if (*(int *)(param_1 + 0x14) == 0) {
      uVar1 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
      *(undefined4 *)(param_1 + 0x14) = uVar1;
    }
    iVar2 = FUN_00409a88(*(int *)(param_1 + 0x14),param_2);
    if (iVar2 < 0) {
      FUN_004099a4(*(int **)(param_1 + 0x14),param_2);
      FUN_0040e570(param_2,param_1,extraout_ECX);
    }
  }
  return;
}

