/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041372c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041372c(int *param_1,short param_2)

{
  if (param_2 != *(short *)(param_1 + 0x13)) {
    *(short *)(param_1 + 0x13) = param_2;
    FUN_00413cb8(param_1,0xb00f,0,0);
  }
  return;
}

