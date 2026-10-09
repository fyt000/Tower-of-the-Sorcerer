/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406068.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00406068(int *param_1)

{
  DWORD DVar1;
  undefined4 auStack_108 [65];
  
  DVar1 = GetCurrentDirectoryA(0x104,(LPSTR)auStack_108);
  FUN_004035bc(param_1,auStack_108,DVar1);
  return;
}

