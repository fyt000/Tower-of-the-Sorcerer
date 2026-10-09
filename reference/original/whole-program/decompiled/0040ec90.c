/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ec90.
 * Inferred types, shared tails and runtime effects require assembly review. */

int __stdcall ImageList_AddMasked(HIMAGELIST himl,HBITMAP hbmImage,COLORREF crMask)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0040ec90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = ImageList_AddMasked(himl,hbmImage,crMask);
  return iVar1;
}

