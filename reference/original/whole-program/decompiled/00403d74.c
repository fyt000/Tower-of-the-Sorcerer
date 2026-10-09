/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403d74.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403d74(VARIANTARG *param_1,int param_2)

{
  LPSTR local_8;
  
  local_8 = (LPSTR)0x0;
  FUN_00403bac(*(LPCWSTR *)(param_2 + 8),&local_8);
  FUN_00403c5c(param_1);
  (param_1->n1).n2.vt = 0x100;
  *(LPSTR *)((int)&param_1->n1 + 8) = local_8;
  return;
}

