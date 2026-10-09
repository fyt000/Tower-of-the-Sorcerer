/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041add0.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0041add0(int param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  HWND hWnd;
  HDC hdc;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar6;
  undefined4 uStack_34;
  undefined *puStack_30;
  undefined *puStack_2c;
  
  iVar5 = *(int *)(param_1 + 0x20);
  if (iVar5 == 0) {
    puStack_2c = (undefined *)0x41adfe;
    iVar5 = FUN_0041adb0(*(short *)(param_1 + 0xe));
  }
  if (iVar5 < 3) {
    return 0;
  }
  uVar1 = (iVar5 + -1) * 4 + 8;
  puStack_2c = (undefined *)0x41ae1d;
  puVar2 = FUN_00405950(uVar1);
  puStack_30 = &LAB_0041af20;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  puStack_2c = &stack0xfffffffc;
  FUN_004029b8(puVar2,uVar1,0);
  *(short *)((int)puVar2 + 2) = (short)iVar5;
  *(undefined2 *)puVar2 = 0x300;
  hWnd = GetFocus();
  hdc = GetDC(hWnd);
  uVar6 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffc0;
  iVar3 = GetDeviceCaps(hdc,0x68);
  if ((iVar5 == 0x10) && (0xf < iVar3)) {
    GetSystemPaletteEntries(hdc,0,8,(LPPALETTEENTRY)(puVar2 + 1));
    GetSystemPaletteEntries(hdc,iVar3 - 8,8,(LPPALETTEENTRY)(puVar2 + 9));
  }
  else if (-1 < iVar5 + -1) {
    iVar3 = 0;
    puVar4 = (undefined *)(param_1 + 0x2a);
    do {
      *(undefined *)(puVar2 + iVar3 + 1) = *puVar4;
      *(undefined *)((int)puVar2 + iVar3 * 4 + 5) = puVar4[-1];
      *(undefined *)((int)puVar2 + iVar3 * 4 + 6) = puVar4[-2];
      *(undefined *)((int)puVar2 + iVar3 * 4 + 7) = 0;
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 4;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  *in_FS_OFFSET = uVar6;
  iVar5 = ReleaseDC(hWnd,hdc);
  return iVar5;
}

