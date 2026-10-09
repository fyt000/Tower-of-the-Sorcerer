/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c404.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042c404(int param_1)

{
  UINT_PTR UVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  
  KillTimer(*(HWND *)(param_1 + 0x28),1);
  if (((*(UINT *)(param_1 + 0x24) != 0) && (*(char *)(param_1 + 0x20) != '\0')) &&
     (*(short *)(param_1 + 0x2e) != 0)) {
    UVar1 = SetTimer(*(HWND *)(param_1 + 0x28),1,*(UINT *)(param_1 + 0x24),(TIMERPROC)0x0);
    if (UVar1 == 0) {
      uVar2 = FUN_004074cc(0x411138,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf038);
      FUN_004031f8(uVar2);
    }
  }
  return;
}

