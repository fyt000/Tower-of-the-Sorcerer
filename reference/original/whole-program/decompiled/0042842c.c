/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042842c.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_0042842c(int param_1)

{
  return CONCAT31((int3)((uint)param_1 >> 8),(*(byte *)(param_1 + 0x34) & 0x40) != 0) ^ 1;
}

