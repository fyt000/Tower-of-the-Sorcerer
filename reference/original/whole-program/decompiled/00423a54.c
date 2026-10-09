/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423a54.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00423a54(int param_1,undefined4 param_2,int *param_3)

{
  undefined4 uVar1;
  HDC hdc;
  DWORD DVar2;
  HMODULE hModule;
  FARPROC pFVar3;
  int iVar4;
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 *in_FS_OFFSET;
  char *lpProcName;
  undefined4 in_stack_ffffffa0;
  undefined4 in_stack_ffffffa4;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffa0,in_stack_ffffffa4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_0040e4b8(param_1,0,param_3);
  FUN_00423c3c(param_1);
  uVar1 = FUN_00402c0c(0x408d3c,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  *(undefined4 *)(param_1 + 0x20) = uVar1;
  uVar1 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),extraout_ECX_01);
  *(undefined4 *)(param_1 + 0x2c) = uVar1;
  uVar1 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),extraout_ECX_02);
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  hdc = GetDC((HWND)0x0);
  FUN_0040aea8(*(int **)(param_1 + 0x20),'\x01');
  *(undefined *)(*(int *)(param_1 + 0x20) + 0x15) = 0;
  DVar2 = GetVersion();
  if (((ushort)DVar2 & 0xff) < 4) {
    EnumFontsA(hdc,(LPCSTR)0x0,FUN_004239f4,*(LPARAM *)(param_1 + 0x20));
  }
  else {
    lpProcName = "EnumFontFamiliesExA";
    hModule = GetModuleHandleA("GDI32");
    pFVar3 = GetProcAddress(hModule,lpProcName);
    (*pFVar3)();
  }
  iVar4 = GetDeviceCaps(hdc,0x5a);
  *(int *)(param_1 + 0x24) = iVar4;
  ReleaseDC((HWND)0x0,hdc);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffa0;
  }
  return param_1;
}

