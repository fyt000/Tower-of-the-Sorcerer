/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00408510.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00408510(int *param_1,char **param_2,int *param_3)

{
  byte local_104 [256];
  
  if (**param_2 == '\x05') {
    FUN_004083e8(param_1,(int)param_2,local_104);
    FUN_004035fc(param_3,local_104);
  }
  else {
    FUN_00408490(param_1,(int)param_2,param_3);
  }
  return;
}

