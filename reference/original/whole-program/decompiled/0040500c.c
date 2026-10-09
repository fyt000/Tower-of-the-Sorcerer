/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040500c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int __stdcall GetScrollPos(HWND hWnd,int nBar)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0040500c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetScrollPos(hWnd,nBar);
  return iVar1;
}

