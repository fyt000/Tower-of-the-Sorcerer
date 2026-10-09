/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419ea4.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00419ea4(int param_1)

{
  return CONCAT31((int3)((uint)*(int *)(param_1 + 0xc) >> 8),
                  *(undefined *)(*(int *)(param_1 + 0xc) + 0x18));
}

