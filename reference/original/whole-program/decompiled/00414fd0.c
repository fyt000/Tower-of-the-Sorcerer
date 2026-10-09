/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414fd0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414fd0(int param_1,LPCSTR *param_2)

{
  HWND pHVar1;
  
  pHVar1 = CreateWindowExA((DWORD)param_2[2],(LPCSTR)(param_2 + 0x13),*param_2,(DWORD)param_2[1],
                           (int)param_2[3],(int)param_2[4],(int)param_2[5],(int)param_2[6],
                           (HWND)param_2[7],(HMENU)0x0,DAT_0048a014,param_2[8]);
  *(HWND *)(param_1 + 0xc0) = pHVar1;
  return;
}

