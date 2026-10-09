/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040aa30.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0040aa30(int *param_1,undefined4 *param_2,int param_3)

{
  char cVar1;
  undefined4 extraout_EDX;
  int local_10;
  
  if (*(char *)(param_1 + 5) == '\0') {
    local_10 = param_1[3];
  }
  else {
    local_10 = param_3;
    cVar1 = (**(code **)(*param_1 + 0x70))(param_1,param_2,&local_10);
    if (cVar1 != '\0') {
      if (*(char *)((int)param_1 + 0x15) == '\0') {
        return local_10;
      }
      if (*(char *)((int)param_1 + 0x15) == '\x02') {
        FUN_00409960(0xf00e,extraout_EDX);
      }
    }
  }
  FUN_0040acf0(param_1,local_10,param_2);
  return local_10;
}

