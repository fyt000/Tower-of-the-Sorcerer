/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004292d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004292d0(int param_1,WPARAM param_2)

{
  HWND hWnd;
  UINT Msg;
  LPARAM lParam;
  
  lParam = 0;
  Msg = 0x150;
  hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  SendMessageA(hWnd,Msg,param_2,lParam);
  return;
}

