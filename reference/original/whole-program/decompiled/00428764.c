/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428764.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00428764(int *param_1,char param_2)

{
  bool bVar1;
  uint wParam;
  HWND hWnd;
  undefined *puVar2;
  undefined4 *in_FS_OFFSET;
  UINT Msg;
  LPARAM lParam;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined *puStack_8;
  
  puStack_18 = &stack0xfffffffc;
  puStack_8 = (undefined *)0x0;
  puStack_1c = &UNK_004287e3;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  if (param_2 != *(char *)((int)param_1 + 0x105)) {
    *(char *)((int)param_1 + 0x105) = param_2;
    bVar1 = FUN_00416e54((int)param_1);
    if (bVar1) {
      lParam = 0;
      wParam = (uint)*(byte *)((int)param_1 + 0x105);
      Msg = 0xcc;
      hWnd = (HWND)FUN_00416cbc(param_1);
      SendMessageA(hWnd,Msg,wParam,lParam);
      FUN_004135a4(param_1,(int *)&puStack_8);
      puVar2 = FUN_00403814(puStack_8);
      FUN_00413580(param_1,puVar2);
    }
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &UNK_004287ea;
  puStack_1c = (undefined *)0x4287e2;
  FUN_004034dc((int *)&puStack_8);
  return;
}

