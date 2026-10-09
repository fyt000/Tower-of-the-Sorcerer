/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00404cdc.
 * Inferred types, shared tails and runtime effects require assembly review. */

int __stdcall EnumFontsA(HDC hdc,LPCSTR lpLogfont,FONTENUMPROCA lpProc,LPARAM lParam)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00404cdc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = EnumFontsA(hdc,lpLogfont,lpProc,lParam);
  return iVar1;
}

