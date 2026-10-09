/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004121e4.
 * Inferred types, shared tails and runtime effects require assembly review. */

HANDLE FUN_004121e4(HWND param_1)

{
  HANDLE pvVar1;
  
  pvVar1 = (HANDLE)0x0;
  if (param_1 != (HWND)0x0) {
    pvVar1 = GetPropA(param_1,(LPCSTR)(uint)DAT_0048a698);
  }
  return pvVar1;
}

