/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403d04.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403d04(VARIANTARG *param_1,VARIANTARG *param_2,VARTYPE param_3)

{
  uint uVar1;
  VARIANTARG local_14;
  
  if ((param_1->n1).n2.vt == 0x100) {
    local_14.n1._0_4_ = local_14.n1._0_4_ & 0xffff0000;
    uVar1 = VariantChangeTypeEx(&local_14,param_2,0x400,0,param_3);
    if (uVar1 != 0) {
      thunk_FUN_004026d0(uVar1);
    }
    FUN_00403c5c(param_1);
    *(undefined4 *)&param_1->n1 = local_14.n1._0_4_;
    *(undefined4 *)((int)&param_1->n1 + 8) = local_14.n1._8_4_;
    *(undefined4 *)((int)&param_1->n1 + 0xc) = local_14.n1._12_4_;
  }
  else {
    uVar1 = VariantChangeTypeEx(param_1,param_2,0x400,0,param_3);
    if (uVar1 != 0) {
      thunk_FUN_004026d0(uVar1);
    }
  }
  return;
}

