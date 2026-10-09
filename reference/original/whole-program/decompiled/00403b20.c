/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403b20.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403b20(LPCWSTR param_1,int param_2,LPSTR *param_3)

{
  uint uVar1;
  undefined4 local_810 [512];
  
  if (param_2 == 0) {
    FUN_004034dc((int *)param_3);
  }
  else if (param_2 < 0x400) {
    uVar1 = WideCharToMultiByte(0,0,param_1,param_2,(LPSTR)local_810,0x800,(LPCSTR)0x0,(LPBOOL)0x0);
    FUN_004035bc((int *)param_3,local_810,uVar1);
  }
  else {
    uVar1 = WideCharToMultiByte(0,0,param_1,param_2,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
    FUN_004035bc((int *)param_3,(undefined4 *)0x0,uVar1);
    WideCharToMultiByte(0,0,param_1,param_2,*param_3,uVar1,(LPCSTR)0x0,(LPBOOL)0x0);
  }
  return;
}

