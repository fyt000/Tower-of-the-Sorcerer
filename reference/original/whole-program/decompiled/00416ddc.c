/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416ddc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416ddc(int param_1,short param_2)

{
  if ((*(byte *)(param_1 + 0x36) & 8) != 0) {
    *(int *)(param_1 + 200) = (int)param_2;
    return;
  }
  FUN_00416d80(param_1,param_2);
  return;
}

