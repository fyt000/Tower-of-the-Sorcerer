/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004251b0.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_004251b0(int param_1,uint param_2,ULONG_PTR param_3)

{
  LPCSTR lpszHelp;
  BOOL BVar1;
  uint uVar2;
  HWND hWndMain;
  char local_10 [4];
  
  uVar2 = 0;
  local_10[0] = '\x01';
  if (*(short *)(param_1 + 0x9e) != 0) {
    uVar2 = (**(code **)(param_1 + 0x9c))(*(undefined4 *)(param_1 + 0xa0),param_2,param_3,local_10);
  }
  if (local_10[0] != '\0') {
    if (*(int *)(param_1 + 0x30) == 0) {
      if (*(char *)(param_1 + 0x7e) == '\0') {
        PostMessageA(*(HWND *)(param_1 + 0x20),0xb01f,param_2 & 0xffff,param_3);
      }
    }
    else {
      hWndMain = (HWND)0x0;
      if (*(int **)(param_1 + 0x28) != (int *)0x0) {
        hWndMain = (HWND)FUN_00416cbc(*(int **)(param_1 + 0x28));
      }
      uVar2 = param_2 & 0xffff;
      lpszHelp = FUN_00403814(*(undefined **)(param_1 + 0x30));
      BVar1 = WinHelpA(hWndMain,lpszHelp,uVar2,param_3);
      uVar2 = (uint)(BVar1 != 0);
    }
  }
  return uVar2;
}

