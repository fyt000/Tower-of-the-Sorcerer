/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004067dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004067dc(LCID param_1,LCTYPE param_2,int param_3,int *param_4)

{
  int iVar1;
  undefined4 local_104 [64];
  
  iVar1 = GetLocaleInfoA(param_1,param_2,(LPSTR)local_104,0x100);
  if (iVar1 < 1) {
    FUN_00403570(param_4,param_3);
  }
  else {
    FUN_004035bc(param_4,local_104,iVar1 - 1);
  }
  return;
}

