/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421984.
 * Inferred types, shared tails and runtime effects require assembly review. */

HANDLE FUN_00421984(int param_1)

{
  HANDLE pvVar1;
  HWND pHVar2;
  
  pvVar1 = (HANDLE)0x0;
  if ((*(char *)(param_1 + 0x11a) == '\x02') && (*(int *)(param_1 + 0x134) != 0)) {
    pHVar2 = (HWND)SendMessageA(*(HWND *)(param_1 + 0x134),0x229,0,0);
    pvVar1 = FUN_004121e4(pHVar2);
  }
  return pvVar1;
}

