/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00429154.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00429154(int param_1,LPARAM *param_2)

{
  HWND hWnd;
  
  hWnd = CreateWindowExA(param_2[2],(LPCSTR)(param_2 + 0x13),"",param_2[1],param_2[3],param_2[4],
                         param_2[5],param_2[6],(HWND)param_2[7],(HMENU)0x0,DAT_0048a014,
                         (LPVOID)param_2[8]);
  *(HWND *)(param_1 + 0xc0) = hWnd;
  SendMessageA(hWnd,0xc,0,*param_2);
  return;
}

