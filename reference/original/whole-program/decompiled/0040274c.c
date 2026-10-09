/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040274c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040274c(undefined *param_1)

{
  LPCSTR lpPathName;
  BOOL BVar1;
  
  lpPathName = FUN_00403814(param_1);
  BVar1 = SetCurrentDirectoryA(lpPathName);
  if ((short)BVar1 == 0) {
    FUN_00402740();
  }
  return;
}

