/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421bd4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00421bd4(int *param_1,int param_2,undefined4 param_3)

{
  if (param_2 != param_1[0x4e]) {
    param_1[0x4e] = param_2;
    if (param_2 != 0) {
      FUN_0040e570(param_2,(int)param_1,param_3);
    }
    FUN_00421b44(param_1);
  }
  return;
}

