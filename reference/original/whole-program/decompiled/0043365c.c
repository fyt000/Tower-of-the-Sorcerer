/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043365c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043365c(int param_1,int *param_2,int *param_3,LPRECT param_4,byte param_5,int param_6,
                 int param_7,byte param_8,undefined *param_9)

{
  int local_10;
  int local_c;
  int *local_8;
  
  local_8 = param_3;
  FUN_00433388(param_1,param_2,param_3,param_4,&local_10,param_6,param_7,param_8,param_9);
  FUN_004331fc(param_1,param_2,local_10,param_5,local_c);
  FUN_004332b8(param_1,param_2,param_9,param_5,&param_4->left);
  return;
}

