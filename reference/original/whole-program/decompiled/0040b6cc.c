/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b6cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040b6cc(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  iVar1 = FUN_00409a88(*(int *)(param_4 + -4),param_1);
  if (iVar1 != -1) {
    FUN_004099e4(*(undefined4 **)(param_4 + -4),iVar1);
  }
  iVar1 = FUN_00409a88(*(int *)(param_4 + -8),param_1);
  if (iVar1 < 0) {
    FUN_004099a4(*(int **)(param_4 + -8),param_1);
  }
  return;
}

