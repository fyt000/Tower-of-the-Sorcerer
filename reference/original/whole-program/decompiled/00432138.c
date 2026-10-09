/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00432138.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00432138(int param_1,int *param_2)

{
  BOOL BVar1;
  uint uVar2;
  int local_1008 [1024];
  
  local_1008[0] = param_1;
  BVar1 = mciGetErrorStringA(*(MCIERROR *)(param_1 + 0x1f8),(LPSTR)local_1008,0x1000);
  if (BVar1 == 0) {
    FUN_00405bf0(0xf0df,param_2);
  }
  else {
    uVar2 = FUN_004060ac((char *)local_1008);
    FUN_004035bc(param_2,local_1008,uVar2);
  }
  return;
}

