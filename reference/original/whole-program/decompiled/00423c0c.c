/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423c0c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423c0c(int param_1,int param_2)

{
  FUN_00409b2c(*(undefined4 **)(param_1 + 0x2c),param_2);
  if ((*(int *)(*(int *)(param_1 + 0x2c) + 8) == 0) && (*(int *)(DAT_0048a6f8 + 0x60) != 0)) {
    FUN_004173f4(*(int **)(DAT_0048a6f8 + 0x60));
  }
  return;
}

