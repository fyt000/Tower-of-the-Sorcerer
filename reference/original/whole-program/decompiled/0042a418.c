/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a418.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042a418(int *param_1,int *param_2)

{
  FUN_00414d88(param_1,param_2);
  FUN_00414d4c(param_1,(int)param_2,"BUTTON");
  param_2[1] = param_2[1] | *(uint *)(&DAT_004896ec + (uint)*(byte *)(param_1 + 0x41) * 4);
  return;
}

