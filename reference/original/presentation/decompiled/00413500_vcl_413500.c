/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00413500.
 * Inferred types and shared tails require assembly review. */

void FUN_00413500(int *param_1,undefined4 param_2,undefined4 param_3)

{
  if (*(char *)((int)param_1 + 0x37) != (char)param_2) {
    FUN_00402cdc(param_1,param_2,param_3);
    *(char *)((int)param_1 + 0x37) = (char)param_2;
    FUN_00413cb8(param_1,0xb00b,0,0);
    FUN_00412f1c((int)param_1);
  }
  return;
}

