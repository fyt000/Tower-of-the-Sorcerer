/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041f9b0.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0041f9b0(undefined4 param_1)

{
  DWORD dwThreadId;
  code *lpfn;
  LPARAM lParam;
  
  DAT_00489590 = 0;
  DAT_00489594 = 0;
  lParam = 0;
  lpfn = FUN_0041f94c;
  DAT_0048958c = param_1;
  dwThreadId = GetCurrentThreadId();
  EnumThreadWindows(dwThreadId,lpfn,lParam);
  if (DAT_00489590 != 0) {
    return DAT_00489590;
  }
  return DAT_00489594;
}

