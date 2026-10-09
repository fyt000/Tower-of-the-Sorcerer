/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416a0c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416a0c(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  HWND hWndInsertAfter;
  int *piVar4;
  
  iVar3 = *(int *)(param_1 + 0x20);
  if (iVar3 != 0) {
    if (*(int *)(iVar3 + 0xb0) != 0) {
      param_2 = param_2 - *(int *)(*(int *)(iVar3 + 0xb0) + 8);
    }
    iVar3 = FUN_00409a88(*(int *)(iVar3 + 0xb4),param_1);
    if (-1 < iVar3) {
      puVar1 = *(undefined4 **)(*(int *)(param_1 + 0x20) + 0xb4);
      iVar2 = puVar1[2];
      if (param_2 < 0) {
        param_2 = 0;
      }
      if (iVar2 <= param_2) {
        param_2 = iVar2 + -1;
      }
      if (iVar3 != param_2) {
        FUN_004099e4(puVar1,iVar3);
        FUN_00409aa8(*(int **)(*(int *)(param_1 + 0x20) + 0xb4),param_2,param_1);
      }
    }
    if (*(int *)(param_1 + 0xc0) != 0) {
      if (param_2 == 0) {
        hWndInsertAfter = (HWND)0x1;
      }
      else {
        puVar1 = *(undefined4 **)(*(int *)(param_1 + 0x20) + 0xb4);
        if (param_2 == puVar1[2] + -1) {
          hWndInsertAfter = (HWND)0x0;
        }
        else if (iVar3 < param_2) {
          piVar4 = (int *)FUN_00409a40(puVar1,param_2 + 1);
          hWndInsertAfter = (HWND)FUN_00416cbc(piVar4);
        }
        else {
          if (iVar3 <= param_2) {
            return;
          }
          piVar4 = (int *)FUN_00409a40(puVar1,param_2);
          hWndInsertAfter = (HWND)FUN_00416cbc(piVar4);
        }
      }
      SetWindowPos(*(HWND *)(param_1 + 0xc0),hWndInsertAfter,0,0,0,0,3);
    }
  }
  return;
}

