/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403da4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403da4(VARIANTARG *param_1,int param_2)

{
  BSTR pOVar1;
  
  pOVar1 = FUN_00403bc8(*(LPCSTR *)(param_2 + 8));
  FUN_00403c5c(param_1);
  (param_1->n1).n2.vt = 8;
  *(BSTR *)((int)&param_1->n1 + 8) = pOVar1;
  return;
}

