/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423f68.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00423f68(void)

{
  BOOL BVar1;
  undefined4 local_8;
  int local_4;
  
  local_8 = 8;
  BVar1 = SystemParametersInfoA(0x48,0,&local_8,0);
  if (BVar1 != 0) {
    return local_4 != 0;
  }
  return false;
}

