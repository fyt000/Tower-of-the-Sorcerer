/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405e7c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00405e7c(LPWORD param_1)

{
  BOOL BVar1;
  
  BVar1 = FindNextFileA(*(HANDLE *)(param_1 + 10),(LPWIN32_FIND_DATAA)(param_1 + 0xc));
  if (BVar1 != 0) {
    FUN_00405dcc(param_1);
    return;
  }
  GetLastError();
  return;
}

