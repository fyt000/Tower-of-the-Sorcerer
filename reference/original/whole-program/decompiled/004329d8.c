/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004329d8.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_004329d8(int param_1,int param_2,int param_3)

{
  int iVar1;
  int extraout_EDX;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(param_1 + 4) + 8) + -1;
  iVar1 = param_2;
  if (-1 < iVar2) {
    do {
      iVar1 = FUN_00409a40(*(undefined4 **)(param_1 + 4),iVar2);
      if ((param_2 == *(int *)(iVar1 + 0x24)) && (param_3 == *(int *)(iVar1 + 0x20))) {
        return iVar1;
      }
      iVar2 = iVar2 + -1;
      iVar1 = extraout_EDX;
    } while (iVar2 != -1);
  }
  iVar1 = FUN_004327f0(0x432718,CONCAT31((int3)((uint)iVar1 >> 8),1),param_2,param_3);
  FUN_004099a4(*(int **)(param_1 + 4),iVar1);
  return iVar1;
}

