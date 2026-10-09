/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414d4c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414d4c(undefined4 param_1,int param_2,LPCSTR param_3)

{
  BOOL BVar1;
  
  if (param_3 != (LPCSTR)0x0) {
    BVar1 = GetClassInfoA(DAT_0048a014,param_3,(LPWNDCLASSA)(param_2 + 0x24));
    if (BVar1 == 0) {
      GetClassInfoA((HINSTANCE)0x0,param_3,(LPWNDCLASSA)(param_2 + 0x24));
    }
    *(uint *)(param_2 + 0x24) = *(uint *)(param_2 + 0x24) & 0xffffbf1f | 3;
  }
  return;
}

