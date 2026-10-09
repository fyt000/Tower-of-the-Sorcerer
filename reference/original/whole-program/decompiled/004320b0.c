/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004320b0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_004320b0(int param_1)

{
  MCIERROR MVar1;
  undefined auStack_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  
  *(undefined4 *)(param_1 + 0x1dc) = 0x102;
  local_10 = 2;
  MVar1 = mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x814,0x102,(DWORD_PTR)auStack_18);
  *(MCIERROR *)(param_1 + 0x1f8) = MVar1;
  return local_14;
}

