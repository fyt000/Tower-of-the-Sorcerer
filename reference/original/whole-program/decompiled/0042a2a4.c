/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a2a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042a2a4(int **param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  HWND hWnd;
  
  iVar1 = *param_2;
  if ((iVar1 == 0x201) || (iVar1 == 0x203)) {
    if (((*(byte *)(param_1 + 7) & 0x10) == 0) &&
       (uVar2 = FUN_00416c74((int)param_1), (char)uVar2 == '\0')) {
      *(undefined *)(param_1 + 0x40) = 1;
      hWnd = (HWND)FUN_00416cbc((int *)param_1);
      SetFocus(hWnd);
      *(undefined *)(param_1 + 0x40) = 0;
      uVar2 = FUN_00416c74((int)param_1);
      if ((char)uVar2 == '\0') {
        return;
      }
    }
  }
  else if ((iVar1 == 0xbd11) && (*(char *)(param_1 + 0x40) != '\0')) {
    return;
  }
  FUN_0041549c(param_1,param_2);
  return;
}

