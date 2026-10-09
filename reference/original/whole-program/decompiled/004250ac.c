/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004250ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004250ac(int param_1,LPCSTR param_2,LPCSTR param_3,ushort param_4)

{
  HWND hWnd;
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  
  hWnd = GetActiveWindow();
  piVar1 = (int *)FUN_0041f860(0);
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  MessageBoxA(*(HWND *)(param_1 + 0x20),param_2,param_3,(uint)param_4);
  *in_FS_OFFSET = uStack_28;
  FUN_0041f914(piVar1);
  uStack_28 = 0x42510c;
  SetActiveWindow(hWnd);
  return;
}

