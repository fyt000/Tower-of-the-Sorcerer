/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004161ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004161ac(int *param_1,int param_2)

{
  if (((*(byte *)(param_1 + 7) & 0x10) != 0) && (param_1[8] != 0)) {
    *(undefined4 *)(param_2 + 0xc) = 1;
    return;
  }
  (**(code **)(*param_1 + -0x10))();
  return;
}

