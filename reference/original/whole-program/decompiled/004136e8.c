/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004136e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004136e8(int *param_1,int param_2)

{
  if (param_2 != param_1[0x12]) {
    param_1[0x12] = param_2;
    *(undefined *)((int)param_1 + 0x3a) = 0;
    FUN_00413cb8(param_1,0xb00d,0,0);
  }
  return;
}

