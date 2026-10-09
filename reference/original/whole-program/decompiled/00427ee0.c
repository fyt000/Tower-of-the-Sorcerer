/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00427ee0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00427ee0(int param_1)

{
  undefined4 in_EDX;
  
  if (param_1 != 0) {
    do {
      if (*(int *)(param_1 + 0x50) != 0) {
        return CONCAT31((int3)((uint)in_EDX >> 8),1);
      }
      param_1 = *(int *)(param_1 + 0x20);
    } while (param_1 != 0);
  }
  return 0;
}

