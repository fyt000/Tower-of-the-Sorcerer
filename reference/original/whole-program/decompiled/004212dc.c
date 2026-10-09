/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004212dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_004212dc(int param_1)

{
  if (((*(char *)(param_1 + 0x108) == '\0') && (*(int *)(*(int *)(param_1 + 0x100) + 0x10) == 0)) &&
     (param_1 = *(int *)(param_1 + 0x104), *(int *)(param_1 + 0x10) == 0)) {
    return 0;
  }
  return CONCAT31((int3)((uint)param_1 >> 8),1);
}

