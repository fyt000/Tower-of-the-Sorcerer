/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00425618.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00425618(int param_1)

{
  if (*(int *)(param_1 + 0x40) != 0) {
    FUN_004255dc(param_1);
    *(undefined4 *)(param_1 + 0x40) = 0;
    *(undefined *)(param_1 + 0x38) = 0;
    FUN_00423f2c();
    FUN_004254d0(param_1);
  }
  return;
}

