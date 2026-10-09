/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040aab0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040aab0(int *param_1)

{
  if (param_1[3] != 0) {
    (**(code **)(*param_1 + 0x6c))();
    FUN_00403a8c((VARIANTARG *)param_1[2],"\x0e\vTStringItem\b",param_1[3]);
    param_1[3] = 0;
    FUN_0040ae8c((int)param_1,0);
    (**(code **)(*param_1 + 0x68))();
  }
  return;
}

