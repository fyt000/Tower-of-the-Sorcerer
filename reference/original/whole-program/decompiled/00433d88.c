/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00433d88.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_00433d88(int param_1)

{
  return CONCAT31((int3)((uint)*(int *)(param_1 + 0x110) >> 8),
                  *(undefined *)(*(int *)(param_1 + 0x110) + 0x20));
}

