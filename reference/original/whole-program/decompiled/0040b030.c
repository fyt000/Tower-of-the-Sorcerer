/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b030.
 * Inferred types, shared tails and runtime effects require assembly review. */

DWORD root_0040b030(int param_1,LPCVOID param_2,DWORD param_3)

{
  DWORD DVar1;
  
  DVar1 = FUN_00405d14(*(HANDLE *)(param_1 + 4),param_2,param_3);
  if (DVar1 == 0xffffffff) {
    DVar1 = 0;
  }
  return DVar1;
}

