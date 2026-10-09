/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004289f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004289f4(int *param_1)

{
  undefined uVar1;
  
  uVar1 = FUN_004286f4(param_1);
  *(undefined *)((int)param_1 + 0x10d) = uVar1;
  FUN_00415014(param_1);
  return;
}

