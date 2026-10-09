/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412488.
 * Inferred types, shared tails and runtime effects require assembly review. */

HANDLE FUN_00412488(void)

{
  HWND pHVar1;
  HANDLE pvVar2;
  
  pHVar1 = GetCapture();
  pvVar2 = FUN_004121e4(pHVar1);
  if (((pvVar2 != (HANDLE)0x0) && (DAT_00489320 != (HANDLE)0x0)) &&
     (pvVar2 == *(HANDLE *)((int)DAT_00489320 + 0x20))) {
    pvVar2 = DAT_00489320;
  }
  return pvVar2;
}

