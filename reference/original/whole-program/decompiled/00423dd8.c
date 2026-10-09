/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423dd8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423dd8(int param_1,int *param_2)

{
  if (param_1 != 0) {
    do {
      if (*(int *)(param_1 + 0x54) != 0) {
        FUN_00403570(param_2,*(int *)(param_1 + 0x54));
        return;
      }
      param_1 = *(int *)(param_1 + 0x20);
    } while (param_1 != 0);
  }
  FUN_004034dc(param_2);
  return;
}

