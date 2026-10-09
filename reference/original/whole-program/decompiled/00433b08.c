/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00433b08.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00433b08(int *param_1,int *param_2)

{
  FUN_00432bc0(param_1[0x44],param_2);
  *(undefined *)((int)param_1 + 0x121) = 1;
  (**(code **)(*param_1 + 0x44))();
  return;
}

