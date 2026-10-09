/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004051d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

int __stdcall SetScrollPos(HWND hWnd,int nBar,int nPos,BOOL bRedraw)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004051d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = SetScrollPos(hWnd,nBar,nPos,bRedraw);
  return iVar1;
}

