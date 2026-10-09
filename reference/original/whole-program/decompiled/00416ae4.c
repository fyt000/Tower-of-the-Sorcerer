/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416ae4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416ae4(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x20);
  if (iVar1 != 0) {
    if ((char)param_2 == '\0') {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(*(int *)(iVar1 + 0xb4) + 8) + -1;
    }
    iVar3 = 0;
    if (*(int *)(iVar1 + 0xb0) != 0) {
      iVar3 = *(int *)(*(int *)(iVar1 + 0xb0) + 8);
    }
    FUN_00416a0c(param_1,iVar2 + iVar3);
    return;
  }
  if (*(HWND *)(param_1 + 0xc0) != (HWND)0x0) {
    SetWindowPos(*(HWND *)(param_1 + 0xc0),(HWND)(uint)*(ushort *)((param_2 & 0x7f) * 2 + 0x489328),
                 0,0,0,0,3);
  }
  return;
}

