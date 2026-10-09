/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431c9c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00431c9c(int param_1,byte param_2)

{
  MCIERROR MVar1;
  undefined auStack_14 [4];
  uint local_10;
  
  *(undefined4 *)(param_1 + 0x1dc) = 0x401;
  local_10 = (uint)param_2;
  MVar1 = mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x80d,0x401,(DWORD_PTR)auStack_14);
  *(MCIERROR *)(param_1 + 0x1f8) = MVar1;
  return;
}

