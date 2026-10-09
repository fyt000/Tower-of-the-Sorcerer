/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428bd4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00428bd4(int *param_1)

{
  FUN_004163ac(param_1);
  if (((*(byte *)((int)param_1 + 0x35) & 2) != 0) &&
     (((*(byte *)(param_1 + 7) & 0x10) == 0 || ((*(byte *)(param_1 + 7) & 1) == 0)))) {
    FUN_00428a54(param_1);
  }
  return;
}

