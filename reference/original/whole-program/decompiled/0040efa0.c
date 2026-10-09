/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040efa0.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040efa0(void)

{
  UINT uMode;
  HMODULE hModule;
  
  DAT_0048a628 = (FARPROC)0x0;
  DAT_0048a630 = (FARPROC)0x0;
  DAT_0048a634 = (FARPROC)0x0;
  DAT_0048a638 = (FARPROC)0x0;
  DAT_0048a63c = (FARPROC)0x0;
  DAT_0048a640 = (FARPROC)0x0;
  uMode = SetErrorMode(0x8000);
  DAT_0048a624 = LoadLibraryA("imm32.dll");
  if (DAT_0048a624 != (HMODULE)0x0) {
    DAT_0048a630 = GetProcAddress(DAT_0048a624,"ImmGetContext");
    DAT_0048a634 = GetProcAddress(DAT_0048a624,"ImmGetConversionStatus");
    DAT_0048a638 = GetProcAddress(DAT_0048a624,"ImmReleaseContext");
    DAT_0048a63c = GetProcAddress(DAT_0048a624,"ImmSetOpenStatus");
    DAT_0048a640 = GetProcAddress(DAT_0048a624,"ImmSetConversionStatus");
    hModule = GetModuleHandleA("USER32");
    DAT_0048a628 = GetProcAddress(hModule,"WINNLSEnableIME");
    _DAT_0048a62c = GetProcAddress(hModule,"WINNLSGetEnableStatus");
  }
  SetErrorMode(uMode);
  return;
}

