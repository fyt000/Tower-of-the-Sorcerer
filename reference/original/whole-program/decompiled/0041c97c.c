/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c97c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041c97c(int param_1,int *param_2,int param_3)

{
  undefined4 uVar1;
  int iStack_10;
  
  iStack_10 = param_3;
  (**(code **)*param_2)(param_2,&iStack_10,4);
  uVar1 = FUN_0041cdc0(param_1,param_2);
  if ((char)uVar1 == '\0') {
    FUN_0041ca94(param_1,param_2,iStack_10);
  }
  else {
    FUN_0041c9c4(param_1,param_2);
  }
  FUN_0041bd8c(param_1);
  return;
}

