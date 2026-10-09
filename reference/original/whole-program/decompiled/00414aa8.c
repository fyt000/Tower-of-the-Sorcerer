/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414aa8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414aa8(int param_1)

{
  *(short *)(param_1 + 0xcc) = *(short *)(param_1 + 0xcc) + -1;
  if ((*(short *)(param_1 + 0xcc) == 0) && ((*(byte *)(param_1 + 0x36) & 0x10) != 0)) {
    FUN_00414ac8(param_1);
  }
  return;
}

