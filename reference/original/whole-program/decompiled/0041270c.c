/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041270c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0041270c(HWND param_1)

{
  HANDLE pvVar1;
  
  if (param_1 != (HWND)0x0) {
    pvVar1 = GetPropA(param_1,(LPCSTR)(uint)DAT_0048a696);
    if (pvVar1 != (HANDLE)0x0) {
      return CONCAT31((int3)((uint)pvVar1 >> 8),1);
    }
  }
  return 0;
}

