/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423c3c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423c3c(int param_1)

{
  HCURSOR pHVar1;
  int iVar2;
  LPCSTR *ppCVar3;
  HINSTANCE hInstance;
  
  pHVar1 = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
  *(HCURSOR *)(param_1 + 0x38) = pHVar1;
  iVar2 = -0x14;
  ppCVar3 = (LPCSTR *)&DAT_004895f0;
  do {
    if ((iVar2 < -0x11) || (hInstance = DAT_0048a014, -0xc < iVar2)) {
      hInstance = (HINSTANCE)0x0;
    }
    pHVar1 = LoadCursorA(hInstance,*ppCVar3);
    FUN_00423ce8(param_1,iVar2,pHVar1);
    iVar2 = iVar2 + 1;
    ppCVar3 = ppCVar3 + 1;
  } while (iVar2 != -1);
  return;
}

