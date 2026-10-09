/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424530.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00424530(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  HDC hDC;
  HICON hIcon;
  tagPAINTSTRUCT local_44;
  
  hDC = BeginPaint(*(HWND *)(*(int *)(param_4 + -4) + 0x20),&local_44);
  hIcon = (HICON)FUN_00424ae8(*(int *)(param_4 + -4));
  DrawIcon(hDC,0,0,hIcon);
  EndPaint(*(HWND *)(*(int *)(param_4 + -4) + 0x20),&local_44);
  return;
}

