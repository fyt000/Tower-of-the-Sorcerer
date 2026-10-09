/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403ef0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void thunk_FUN_00403c5c(VARIANTARG *param_1)

{
  ushort uVar1;
  
  uVar1 = (param_1->n1).n2.vt;
  if (((uVar1 & 0x4000) == 0) && (7 < uVar1)) {
    if (uVar1 == 0x100) {
      (param_1->n1).n2.vt = 0;
      FUN_004034dc((int *)((int)&param_1->n1 + 8));
      return;
    }
    VariantClear(param_1);
    return;
  }
  (param_1->n1).n2.vt = 0;
  return;
}

