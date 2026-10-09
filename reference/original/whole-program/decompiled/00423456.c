/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423456.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00423456(void)

{
  byte *pbVar1;
  undefined uVar2;
  HWND pHVar3;
  HWND pHVar4;
  BOOL BVar5;
  int iVar6;
  undefined extraout_CL;
  undefined extraout_DL;
  HWND hWnd;
  int unaff_EBP;
  undefined4 *in_FS_OFFSET;
  undefined in_stack_00000000;
  undefined in_stack_00000004;
  undefined in_stack_00000008;
  undefined in_stack_0000000c;
  undefined in_stack_00000010;
  undefined in_stack_00000014;
  undefined in_stack_00000018;
  undefined4 in_stack_0000002c;
  undefined4 in_stack_00000030;
  
  uVar2 = root_00425020(DAT_0048a6f8,*(undefined4 *)(unaff_EBP + -4));
  FUN_00403268(uVar2,extraout_DL,extraout_CL,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  if (*(int *)(DAT_0048a6fc + 0x40) == *(int *)(unaff_EBP + -4)) {
    FUN_004227b8(*(int **)(unaff_EBP + -4),'\0');
  }
  if (*(char *)(*(int *)(unaff_EBP + -4) + 0x11a) == '\x01') {
    FUN_00415130(*(int **)(unaff_EBP + -4));
  }
  else if ((*(byte *)(*(int *)(unaff_EBP + -4) + 0x11d) & 8) == 0) {
    hWnd = (HWND)0x0;
    pHVar3 = (HWND)FUN_00416cbc(*(int **)(unaff_EBP + -4));
    pHVar4 = GetActiveWindow();
    if (pHVar3 == pHVar4) {
      pHVar3 = (HWND)FUN_00416cbc(*(int **)(unaff_EBP + -4));
      BVar5 = IsIconic(pHVar3);
      if (BVar5 == 0) {
        iVar6 = FUN_00416cbc(*(int **)(unaff_EBP + -4));
        hWnd = (HWND)FUN_0041f9b0(iVar6);
      }
    }
    if (hWnd == (HWND)0x0) {
      pHVar3 = (HWND)FUN_00416cbc(*(int **)(unaff_EBP + -4));
      ShowWindow(pHVar3,0);
    }
    else {
      pHVar3 = (HWND)FUN_00416cbc(*(int **)(unaff_EBP + -4));
      SetWindowPos(pHVar3,(HWND)0x0,0,0,0,0,0x97);
      SetActiveWindow(hWnd);
    }
  }
  else {
    pHVar3 = (HWND)FUN_00416cbc(*(int **)(unaff_EBP + -4));
    SetWindowPos(pHVar3,(HWND)0x0,0,0,0,0,0x97);
  }
  *in_FS_OFFSET = in_stack_00000030;
  pbVar1 = (byte *)(*(int *)(unaff_EBP + -4) + 0x11d);
  *pbVar1 = *pbVar1 & 0xfb;
  return;
}

