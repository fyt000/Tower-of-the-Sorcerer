/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004107dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004107dc(int *param_1,char param_2)

{
  if (param_2 != *(char *)((int)param_1 + 0x2b)) {
    *(char *)((int)param_1 + 0x2b) = param_2;
    (**(code **)(*param_1 + 0x28))(param_1,1);
  }
  return;
}

