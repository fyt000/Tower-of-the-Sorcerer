/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040cf18.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040cf18(uint param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 local_104 [64];
  
  if (0 < (int)param_1) {
    do {
      if ((int)param_1 < 0x101) {
        FUN_0040bc08(*(int *)(param_4 + -4),local_104,param_1);
        param_1 = 0;
      }
      else {
        FUN_0040bc08(*(int *)(param_4 + -4),local_104,0x100);
        param_1 = param_1 - 0x100;
      }
    } while (0 < (int)param_1);
  }
  return;
}

