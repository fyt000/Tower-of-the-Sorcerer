/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042327b.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042327b(void)

{
  byte *pbVar1;
  undefined uVar2;
  int iVar3;
  int iVar4;
  WPARAM wParam;
  HWND pHVar5;
  undefined extraout_CL;
  undefined4 extraout_ECX;
  undefined extraout_DL;
  undefined4 extraout_EDX;
  uint uVar6;
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
  if (*(char *)(*(int *)(unaff_EBP + -4) + 0x11b) == '\x04') {
    if (*(char *)(*(int *)(unaff_EBP + -4) + 0x11a) == '\x01') {
      iVar3 = FUN_00413178(*(int **)(DAT_0048a6f8 + 0x28));
      uVar6 = iVar3 - *(int *)(*(int *)(unaff_EBP + -4) + 0x2c);
      iVar3 = (int)uVar6 >> 1;
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((uVar6 & 1) != 0);
      }
      iVar4 = FUN_004131bc(*(int **)(DAT_0048a6f8 + 0x28));
      uVar6 = iVar4 - *(int *)(*(int *)(unaff_EBP + -4) + 0x30);
      iVar4 = (int)uVar6 >> 1;
      if (iVar4 < 0) {
        iVar4 = iVar4 + (uint)((uVar6 & 1) != 0);
      }
    }
    else {
      iVar3 = FUN_00423ba8();
      uVar6 = iVar3 - *(int *)(*(int *)(unaff_EBP + -4) + 0x2c);
      iVar3 = (int)uVar6 >> 1;
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((uVar6 & 1) != 0);
      }
      iVar4 = FUN_00423ba0();
      uVar6 = iVar4 - *(int *)(*(int *)(unaff_EBP + -4) + 0x30);
      iVar4 = (int)uVar6 >> 1;
      if (iVar4 < 0) {
        iVar4 = iVar4 + (uint)((uVar6 & 1) != 0);
      }
    }
    if (iVar3 < 0) {
      iVar3 = 0;
    }
    if (iVar4 < 0) {
      iVar4 = 0;
    }
    (**(code **)(**(int **)(unaff_EBP + -4) + 0x4c))(*(int **)(unaff_EBP + -4),iVar3,iVar4);
  }
  *(undefined *)(*(int *)(unaff_EBP + -4) + 0x11b) = 0;
  if (*(char *)(*(int *)(unaff_EBP + -4) + 0x11a) == '\x01') {
    if (*(char *)(*(int *)(unaff_EBP + -4) + 0x116) == '\x02') {
      wParam = FUN_00416cbc(*(int **)(unaff_EBP + -4));
      SendMessageA(*(HWND *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x134),0x223,wParam,0);
      pHVar5 = (HWND)FUN_00416cbc(*(int **)(unaff_EBP + -4));
      ShowWindow(pHVar5,3);
    }
    else {
      iVar3 = *(int *)((uint)*(byte *)(*(int *)(unaff_EBP + -4) + 0x116) * 4 + 0x4895e4);
      pHVar5 = (HWND)FUN_00416cbc(*(int **)(unaff_EBP + -4));
      ShowWindow(pHVar5,iVar3);
      iVar3 = *(int *)(*(int *)(unaff_EBP + -4) + 0x30);
      uVar6 = *(uint *)(*(int *)(unaff_EBP + -4) + 0x2c);
      pHVar5 = (HWND)FUN_00416cbc(*(int **)(unaff_EBP + -4));
      CallWindowProcA((WNDPROC)&DAT_00404eac,pHVar5,5,0,iVar3 << 0x10 | uVar6);
      FUN_00413780(*(int **)(unaff_EBP + -4),extraout_EDX,extraout_ECX);
    }
    SendMessageA(*(HWND *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x134),0x234,0,0);
  }
  else {
    iVar3 = *(int *)((uint)*(byte *)(*(int *)(unaff_EBP + -4) + 0x116) * 4 + 0x4895e4);
    pHVar5 = (HWND)FUN_00416cbc(*(int **)(unaff_EBP + -4));
    ShowWindow(pHVar5,iVar3);
  }
  *in_FS_OFFSET = in_stack_00000030;
  pbVar1 = (byte *)(*(int *)(unaff_EBP + -4) + 0x11d);
  *pbVar1 = *pbVar1 & 0xfb;
  return;
}

