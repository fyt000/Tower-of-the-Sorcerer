/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042eed4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042eed4(int param_1,undefined4 param_2,undefined4 param_3)

{
  HWND hWnd;
  undefined4 uVar1;
  undefined4 extraout_EDX;
  WPARAM wParam;
  undefined4 *in_FS_OFFSET;
  UINT Msg;
  int ***lParam;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  int **local_20;
  int local_1c;
  code *local_18;
  int *local_14;
  int *local_10;
  undefined4 local_c;
  int local_8;
  
  local_14 = *(int **)(param_1 + 0x10);
  local_8 = param_1;
  if (local_14 == (int *)0x0) {
    puStack_28 = (undefined *)0x42ef02;
    local_14 = (int *)FUN_00402c0c(*(int *)(*(int *)(param_1 + 8) + 0x154),
                                   CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  }
  local_10 = local_14;
  puStack_2c = &LAB_0042ef9a;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  local_20 = &local_10;
  local_18 = root_0042ec5c;
  local_1c = 0;
  if (*(char *)(local_8 + 0xc) == '\0') {
    wParam = 2;
  }
  else {
    wParam = 1;
  }
  lParam = &local_20;
  Msg = 0x44a;
  puStack_28 = &stack0xfffffffc;
  local_c = param_2;
  hWnd = (HWND)FUN_00416cbc(*(int **)(local_8 + 8));
  SendMessageA(hWnd,Msg,wParam,(LPARAM)lParam);
  if (local_1c != 0) {
    uVar1 = FUN_004074cc(0x411138,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf209);
    FUN_004031f8(uVar1);
  }
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_0042efa1;
  if (*(int *)(local_8 + 0x10) == 0) {
    puStack_2c = (undefined *)0x42ef99;
    FUN_00402c34(local_14);
  }
  return;
}

