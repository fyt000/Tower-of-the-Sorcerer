/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424d6c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00424d6c(int param_1)

{
  bool bVar1;
  BOOL BVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char local_28 [4];
  tagMSG local_24;
  
  uVar4 = 0;
  BVar2 = PeekMessageA(&local_24,(HWND)0x0,0,0,1);
  if (BVar2 != 0) {
    uVar4 = 1;
    if (local_24.message == 0x12) {
      *(undefined *)(param_1 + 0x7c) = 1;
    }
    else {
      local_28[0] = '\0';
      if (*(short *)(param_1 + 0x96) != 0) {
        (**(code **)(param_1 + 0x94))(*(undefined4 *)(param_1 + 0x98),&local_24,local_28);
      }
      uVar3 = FUN_00424d3c(param_1,&local_24);
      if (((char)uVar3 == '\0') && (local_28[0] == '\0')) {
        bVar1 = FUN_00424c88(param_1,&local_24);
        if (!bVar1) {
          uVar3 = FUN_00424cd8(param_1,&local_24.hwnd);
          if ((char)uVar3 == '\0') {
            bVar1 = FUN_00424c64(param_1,&local_24);
            if (!bVar1) {
              TranslateMessage(&local_24);
              DispatchMessageA(&local_24);
            }
          }
        }
      }
    }
  }
  return uVar4;
}

