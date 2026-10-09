/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f2d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042f2d4(int *param_1,int *param_2)

{
  UINT uMode;
  HMODULE pHVar1;
  
  uMode = SetErrorMode(0x8000);
  pHVar1 = LoadLibraryA("RICHED32.DLL");
  param_1[0x4a] = (int)pHVar1;
  if ((int)pHVar1 < 0x20) {
    param_1[0x4a] = 0;
  }
  SetErrorMode(uMode);
  FUN_00429108(param_1,param_2);
  FUN_00414d4c(param_1,(int)param_2,"RICHEDIT");
  param_2[1] = param_2[1] | *(uint *)(&DAT_004897ec + (uint)*(byte *)(param_1 + 0x4b) * 4) |
               *(uint *)(&DAT_004897f4 + (uint)*(byte *)(param_1 + 0x54) * 4);
  return;
}

