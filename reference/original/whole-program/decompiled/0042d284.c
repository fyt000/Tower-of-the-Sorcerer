/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042d284.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042d284(void)

{
  byte *lpString;
  undefined4 uVar1;
  byte local_30 [32];
  undefined4 local_10;
  undefined local_c;
  DWORD local_8;
  undefined local_4;
  
  _DAT_0048a72c = RegisterWindowMessageA("commdlg_help");
  _DAT_0048a730 = RegisterWindowMessageA("commdlg_FindReplace");
  uVar1 = 1;
  local_10 = DAT_0048a014;
  local_c = 0;
  local_8 = GetCurrentThreadId();
  local_4 = 0;
  lpString = FUN_004065e8(local_30,(byte *)"WndProcPtr%.8X%.8X",&local_10,uVar1);
  _DAT_00489740 = GlobalAddAtomA((LPCSTR)lpString);
  return;
}

