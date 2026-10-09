/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00488d50.
 * Inferred types, shared tails and runtime effects require assembly review. */

void entry(void)

{
  undefined4 uVar1;
  HWND hWnd;
  undefined4 extraout_EDX;
  
  FUN_00403420();
  uVar1 = FUN_00404a10();
  FUN_00408154(uVar1,extraout_EDX);
  FUN_0040ebd0();
  FUN_0040ed0c();
  FUN_0040f140();
  FUN_00411098();
  FUN_0041898c();
  FUN_004258a0();
  FUN_0042d338();
  FUN_00433e20();
  hWnd = FindWindowA("TTSW10",(LPCSTR)0x0);
  if (hWnd == (HWND)0x0) {
    FUN_00424f08();
    FUN_00424c34(DAT_0048a6f8,(undefined4 *)"Tower of the Sorcerer Ver1.2");
    FUN_00424f18(DAT_0048a6f8,0x440f60,&DAT_0048c510);
    FUN_00424f18(DAT_0048a6f8,0x433e70,&DAT_0048a760);
    FUN_00424f18(DAT_0048a6f8,0x43463c,&DAT_0048a764);
    FUN_00424f18(DAT_0048a6f8,0x4400a4,(undefined4 *)&DAT_0048c50c);
    FUN_00424fa8(DAT_0048a6f8);
  }
  else {
    FUN_0042cf78((uint *)"Sorry, cannot execute plural \'Tower of the Sorcerer\'.");
    SetForegroundWindow(hWnd);
  }
  FUN_0040441c();
  return;
}

