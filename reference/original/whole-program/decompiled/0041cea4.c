/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041cea4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041cea4(int param_1,int *param_2)

{
  int iVar1;
  undefined2 extraout_var;
  int local_10;
  
  if (*(int *)(param_1 + 0x10) != 0) {
    local_10 = 0;
    (**(code **)(*param_2 + 4))(param_2,&local_10,4);
    local_10 = FUN_0040af00(param_2);
    local_10 = local_10 + -4;
    if (*(char *)(param_1 + 0x14) == '\0') {
      FUN_0041cfac(param_1,param_2);
    }
    else {
      FUN_0041cf28(param_1,param_2);
    }
    (**(code **)(*param_2 + 8))(param_2,local_10,0);
    iVar1 = FUN_0040af1c(param_2);
    local_10 = iVar1 - local_10;
    (**(code **)(*param_2 + 4))(param_2,&local_10,4);
    (**(code **)(*param_2 + 8))(param_2,0,CONCAT22(extraout_var,2));
  }
  return;
}

