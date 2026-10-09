/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004237dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004237dc(int *param_1)

{
  undefined4 uVar1;
  HWND pHVar2;
  undefined4 extraout_ECX;
  uint extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_3c;
  undefined *puStack_38;
  undefined *puVar3;
  UINT UVar4;
  WPARAM WVar5;
  LPARAM LVar6;
  
  puVar3 = &stack0xfffffffc;
  FUN_00412b9c();
  if ((((*(char *)((int)param_1 + 0x37) != '\0') || (*(char *)(param_1 + 0xe) == '\0')) ||
      ((*(byte *)((int)param_1 + 0x11d) & 8) != 0)) || (*(char *)((int)param_1 + 0x11a) == '\x01'))
  {
    uVar1 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf032);
    FUN_004031f8(uVar1);
  }
  pHVar2 = GetCapture();
  if (pHVar2 != (HWND)0x0) {
    LVar6 = 0;
    WVar5 = 0;
    UVar4 = 0x1f;
    pHVar2 = GetCapture();
    puStack_38 = (undefined *)0x42384a;
    SendMessageA(pHVar2,UVar4,WVar5,LVar6);
  }
  ReleaseCapture();
  *(byte *)((int)param_1 + 0x11d) = *(byte *)((int)param_1 + 0x11d) | 8;
  GetActiveWindow();
  *(int **)(DAT_0048a6fc + 0x4c) = param_1;
  FUN_00423d4c(DAT_0048a6fc,0);
  FUN_0041f860(0);
  *in_FS_OFFSET = &stack0xffffffd0;
  FUN_00423790(param_1,0,extraout_ECX);
  puStack_38 = &LAB_0042396f;
  uStack_3c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_3c;
  LVar6 = 0;
  WVar5 = 0;
  UVar4 = 0xb000;
  pHVar2 = (HWND)FUN_00416cbc(param_1);
  SendMessageA(pHVar2,UVar4,WVar5,LVar6);
  param_1[0x4b] = 0;
  do {
    FUN_00424e1c(DAT_0048a6f8);
    if (*(char *)(DAT_0048a6f8 + 0x7c) == '\0') {
      if (param_1[0x4b] != 0) {
        FUN_004236e0(param_1,extraout_EDX_00,extraout_ECX_00);
      }
    }
    else {
      param_1[0x4b] = 2;
    }
  } while (param_1[0x4b] == 0);
  LVar6 = 0;
  WVar5 = 0;
  UVar4 = 0xb001;
  pHVar2 = (HWND)FUN_00416cbc(param_1);
  SendMessageA(pHVar2,UVar4,WVar5,LVar6);
  FUN_00416cbc(param_1);
  GetActiveWindow();
  *in_FS_OFFSET = uStack_3c;
  puStack_38 = (undefined *)0x42396e;
  FUN_00423788(param_1,uStack_3c,puVar3);
  return;
}

