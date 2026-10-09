/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422efc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422efc(int **param_1,int param_2)

{
  if (((*(uint *)(param_2 + 4) & 0xfff0) == 0xf020) && (param_1 == *(int ***)(DAT_0048a6f8 + 0x28)))
  {
    FUN_00424b04(DAT_0048a6f8);
    return;
  }
  FUN_00416074(param_1,param_2);
  return;
}

