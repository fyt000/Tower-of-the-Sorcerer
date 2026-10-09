/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423ed4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423ed4(undefined4 param_1,undefined4 param_2,DWORD param_3)

{
  DWORD dwThreadId;
  DWORD DStack_4;
  
  if (*(char *)(DAT_0048a6f8 + 0x7f) == '\0') {
    DStack_4 = param_3;
    if (DAT_0048a724 == (HHOOK)0x0) {
      dwThreadId = GetCurrentThreadId();
      DAT_0048a724 = SetWindowsHookExA(3,root_00423e90,(HINSTANCE)0x0,dwThreadId);
    }
    if (DAT_0048a728 == (HANDLE)0x0) {
      DAT_0048a728 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,1000,root_00423e40,(LPVOID)0x0,0,
                                  &DStack_4);
    }
  }
  return;
}

