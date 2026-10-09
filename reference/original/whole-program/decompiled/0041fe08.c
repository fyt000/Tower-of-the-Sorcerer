/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041fe08.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

HWND FUN_0041fe08(undefined param_1,undefined param_2,undefined param_3,undefined4 param_4,
                 undefined4 param_5)

{
  BOOL BVar1;
  HWND hWnd;
  undefined *dwNewLong;
  undefined extraout_CL;
  undefined extraout_DL;
  tagWNDCLASSA local_2c;
  
  _DAT_004895b4 = DAT_0048a014;
  BVar1 = GetClassInfoA(DAT_0048a014,PTR_s_TPUtilWindow_004895c8,&local_2c);
  if ((BVar1 == 0) || (local_2c.lpfnWndProc != DefWindowProcA)) {
    if (BVar1 != 0) {
      UnregisterClassA(PTR_s_TPUtilWindow_004895c8,DAT_0048a014);
    }
    RegisterClassA((WNDCLASSA *)&DAT_004895a4);
  }
  hWnd = (HWND)FUN_0040530c(PTR_s_TPUtilWindow_004895c8,"",0,(LPVOID)0x0,DAT_0048a014,(HMENU)0x0,
                            (HWND)0x0,0,0,0,0);
  dwNewLong = FUN_0041fd4c((char)hWnd,extraout_DL,extraout_CL,param_4,param_5);
  SetWindowLongA(hWnd,-4,(LONG)dwNewLong);
  return hWnd;
}

