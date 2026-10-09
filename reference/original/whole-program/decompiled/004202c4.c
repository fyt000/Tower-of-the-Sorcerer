/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004202c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_004202c4(int param_1)

{
  HWND hWnd;
  int iVar1;
  int extraout_ECX;
  undefined2 extraout_var;
  int iVar2;
  
  iVar2 = -0x10;
  hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 4));
  GetWindowLongA(hWnd,iVar2);
  if (*(char *)(param_1 + 0x18) == '\x01') {
    iVar1 = FUN_00420250(0,CONCAT22(extraout_var,0x15),extraout_ECX,(int)&stack0xfffffffc);
    iVar2 = FUN_004131bc(*(int **)(param_1 + 4));
    iVar1 = iVar1 + iVar2;
  }
  else {
    iVar1 = FUN_00420250(1,CONCAT22(extraout_var,0x14),extraout_ECX,(int)&stack0xfffffffc);
    iVar2 = FUN_00413178(*(int **)(param_1 + 4));
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}

