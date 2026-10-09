/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420424.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00420424(int param_1,int param_2)

{
  int iVar1;
  int **ppiVar2;
  HWND pHVar3;
  int iVar4;
  uint nBar;
  uint nBar_00;
  BOOL bRedraw;
  
  if ((*(byte *)(*(int *)(param_1 + 4) + 0x1c) & 2) == 0) {
    iVar4 = *(int *)(param_1 + 0x14);
    if ((param_2 <= iVar4) && (iVar4 = param_2, param_2 < 0)) {
      iVar4 = 0;
    }
    nBar = (uint)(*(char *)(param_1 + 0x18) != '\0');
    iVar1 = *(int *)(param_1 + 0xc);
    if (iVar4 != iVar1) {
      *(int *)(param_1 + 0xc) = iVar4;
      if (*(char *)(param_1 + 0x18) == '\0') {
        FUN_00416924(*(int *)(param_1 + 4),iVar1 - iVar4,0);
      }
      else {
        FUN_00416924(*(int *)(param_1 + 4),0,iVar1 - iVar4);
      }
      if ((((*(byte *)(*(int ***)(param_1 + 4) + 7) & 0x10) != 0) &&
          (ppiVar2 = FUN_0041fffc(*(int ***)(param_1 + 4)), ppiVar2 != (int **)0x0)) &&
         (ppiVar2[0x4c] != (int *)0x0)) {
        (**(code **)(*ppiVar2[0x4c] + 4))();
      }
    }
    nBar_00 = nBar;
    pHVar3 = (HWND)FUN_00416cbc(*(int **)(param_1 + 4));
    iVar4 = GetScrollPos(pHVar3,nBar_00);
    if (iVar4 != *(int *)(param_1 + 0xc)) {
      bRedraw = 1;
      iVar4 = *(int *)(param_1 + 0xc);
      pHVar3 = (HWND)FUN_00416cbc(*(int **)(param_1 + 4));
      SetScrollPos(pHVar3,nBar,iVar4,bRedraw);
    }
  }
  else {
    *(int *)(param_1 + 0xc) = param_2;
  }
  return;
}

