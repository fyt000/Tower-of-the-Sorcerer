/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431fdc.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00431fdc(int param_1,undefined4 param_2)

{
  MCIERROR MVar1;
  undefined auStack_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  
  FUN_00430e1c(param_1,param_2);
  *(undefined4 *)(param_1 + 0x1dc) = 0x102;
  local_10 = 1;
  MVar1 = mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x814,0x102,(DWORD_PTR)auStack_18);
  *(MCIERROR *)(param_1 + 0x1f8) = MVar1;
  return local_14;
}

