/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431bf8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00431bf8(int param_1,undefined4 param_2)

{
  undefined auStack_c [8];
  
  FUN_00430e1c(param_1,param_2);
  mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x807,0x102,(DWORD_PTR)auStack_c);
  return;
}

