/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042181c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042181c(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  LRESULT LVar1;
  
  LVar1 = CallWindowProcA(*(WNDPROC *)(*(int *)(param_4 + -4) + 0x154),
                          *(HWND *)(*(int *)(param_4 + -4) + 0x134),**(UINT **)(param_4 + -8),
                          *(WPARAM *)(*(int *)(param_4 + -8) + 4),
                          *(LPARAM *)(*(int *)(param_4 + -8) + 8));
  *(LRESULT *)(*(int *)(param_4 + -8) + 0xc) = LVar1;
  return;
}

