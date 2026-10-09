/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416d80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416d80(int param_1,short param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = FUN_00416d5c(param_1);
  iVar3 = (int)(short)iVar3;
  if (-1 < iVar3) {
    puVar1 = *(undefined4 **)(*(int *)(param_1 + 0x20) + 0xb8);
    iVar2 = puVar1[2];
    if (param_2 < 0) {
      param_2 = 0;
    }
    if (iVar2 <= param_2) {
      param_2 = (short)iVar2 + -1;
    }
    if (iVar3 != param_2) {
      FUN_004099e4(puVar1,iVar3);
      FUN_00409aa8(*(int **)(*(int *)(param_1 + 0x20) + 0xb8),(int)param_2,param_1);
    }
  }
  return;
}

