/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431c24.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00431c24(int param_1,undefined4 param_2)

{
  undefined auStack_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  *(undefined4 *)(param_1 + 0x1dc) = 0x112;
  local_8 = 2;
  local_4 = param_2;
  mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x814,0x112,(DWORD_PTR)auStack_10);
  return local_c;
}

