/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004172d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004172d0(int *param_1,int *param_2)

{
  FUN_00414d88(param_1,param_2);
  param_2[1] = -0x77800000;
  param_2[9] = param_2[9] | 0x800;
  if (DAT_0048a694 != '\0') {
    param_2[2] = 0x80;
  }
  return;
}

