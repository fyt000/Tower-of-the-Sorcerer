/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421a94.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_00421a94(int param_1)

{
  return CONCAT31((int3)((uint)param_1 >> 8),*(undefined *)(param_1 + 0x3d)) ^ 1;
}

