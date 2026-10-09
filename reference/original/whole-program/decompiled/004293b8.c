/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004293b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004293b8(int param_1)

{
  HWND hWnd;
  undefined4 *in_FS_OFFSET;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  puStack_1c = &LAB_0042941b;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_004135a4(*(int **)(param_1 + 8),(int *)&local_8);
  lParam = 0;
  wParam = 0;
  Msg = 0x14b;
  hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  SendMessageA(hWnd,Msg,wParam,lParam);
  FUN_004135d4(*(int **)(param_1 + 8),local_8);
  (**(code **)(**(int **)(param_1 + 8) + 0x50))();
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_00429422;
  puStack_1c = (undefined *)0x42941a;
  FUN_004034dc((int *)&local_8);
  return;
}

