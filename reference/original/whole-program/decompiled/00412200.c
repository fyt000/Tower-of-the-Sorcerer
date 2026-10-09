/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412200.
 * Inferred types, shared tails and runtime effects require assembly review. */

LRESULT FUN_00412200(UINT param_1,WPARAM param_2,LPARAM param_3)

{
  LRESULT LVar1;
  
  if (*(HWND *)(DAT_0048a6f8 + 0x20) != (HWND)0x0) {
    LVar1 = SendMessageA(*(HWND *)(DAT_0048a6f8 + 0x20),param_1,param_2,param_3);
    return LVar1;
  }
  return 0;
}

