/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c220.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042c220(int param_1,char param_2)

{
  if (param_2 != *(char *)(param_1 + 0xb2)) {
    *(char *)(param_1 + 0xb2) = param_2;
    root_0042c260(param_1,param_1);
  }
  return;
}

