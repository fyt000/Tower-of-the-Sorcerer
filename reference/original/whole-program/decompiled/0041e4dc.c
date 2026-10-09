/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e4dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041e4dc(int param_1)

{
  int iVar1;
  undefined2 extraout_var;
  undefined4 extraout_EDX;
  undefined auStack_10 [2];
  short local_e;
  uint local_c;
  undefined local_8 [4];
  
  iVar1 = *(int *)(param_1 + 0x10);
  if ((*(int *)(iVar1 + 0xc) == 0) && (*(int **)(iVar1 + 8) != (int *)0x0)) {
    FUN_0040af10(*(int **)(iVar1 + 8),0);
    FUN_0040af50(*(undefined4 **)(iVar1 + 8),auStack_10,6);
    if (local_e != 0) {
      if ((short)(local_e + -1) == 0) {
        FUN_0041b654(*(undefined4 **)(iVar1 + 8),local_8,local_c & 0xffff);
      }
      else {
        FUN_0041ac44(CONCAT22(extraout_var,local_e + -1),extraout_EDX);
      }
    }
    *(uint *)(iVar1 + 0xc) = local_c;
  }
  return;
}

