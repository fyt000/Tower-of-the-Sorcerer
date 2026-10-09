/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406090.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00406090(undefined *param_1)

{
  LPCSTR lpPathName;
  BOOL BVar1;
  LPSECURITY_ATTRIBUTES lpSecurityAttributes;
  
  lpSecurityAttributes = (LPSECURITY_ATTRIBUTES)0x0;
  lpPathName = FUN_00403814(param_1);
  BVar1 = CreateDirectoryA(lpPathName,lpSecurityAttributes);
  return BVar1 != 0;
}

