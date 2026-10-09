/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00404c54.
 * Inferred types, shared tails and runtime effects require assembly review. */

DWORD __stdcall WNetGetConnectionA(LPCSTR lpLocalName,LPSTR lpRemoteName,LPDWORD lpnLength)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00404c54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = WNetGetConnectionA(lpLocalName,lpRemoteName,lpnLength);
  return DVar1;
}

