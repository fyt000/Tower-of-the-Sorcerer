/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043fab4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043fab4(int *param_1,byte *param_2)

{
  int iVar1;
  undefined *lParam;
  HWND hWnd;
  undefined4 *in_FS_OFFSET;
  UINT Msg;
  WPARAM WVar2;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  byte *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (byte *)0x0;
  puStack_1c = &LAB_0043fb2b;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_0043fa68(param_1,(int *)&local_8);
  iVar1 = FUN_0043c180(param_2,local_8);
  if (iVar1 != 0) {
    lParam = FUN_00403814(param_2);
    WVar2 = 0;
    Msg = 0x1a2;
    hWnd = (HWND)FUN_00416cbc(param_1);
    WVar2 = SendMessageA(hWnd,Msg,WVar2,(LPARAM)lParam);
    FUN_0042a938(param_1,WVar2);
    (**(code **)(*param_1 + 0x90))();
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0043fb32;
  puStack_1c = (undefined *)0x43fb2a;
  FUN_004034dc((int *)&local_8);
  return;
}

