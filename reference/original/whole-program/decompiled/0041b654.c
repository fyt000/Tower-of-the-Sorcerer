/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041b654.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041b654(undefined4 *param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  HDC hdc;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar2;
  undefined4 uStack_90;
  undefined *puStack_8c;
  undefined *puStack_88;
  
  puStack_88 = (undefined *)0x41b677;
  puVar1 = FUN_00405950(param_3 << 4);
  puStack_8c = &LAB_0041b900;
  uStack_90 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_90;
  puStack_88 = &stack0xfffffffc;
  (**(code **)*param_1)(param_1,puVar1,param_3 << 4);
  GetSystemMetrics(0xb);
  GetSystemMetrics(0xc);
  hdc = GetDC((HWND)0x0);
  if (hdc == (HDC)0x0) {
    FUN_0041ac5c(0,extraout_EDX);
  }
  uVar2 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffff64;
  GetDeviceCaps(hdc,0xe);
  GetDeviceCaps(hdc,0xc);
  *in_FS_OFFSET = uVar2;
  ReleaseDC((HWND)0x0,hdc);
  return;
}

