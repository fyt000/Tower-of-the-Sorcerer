/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ac80.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_0040ac80(int *param_1,undefined *param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uStack_c;
  
  uStack_c = param_3;
  if (*(char *)(param_1 + 5) == '\0') {
    uStack_c = FUN_0040a4b4(param_1,param_2);
  }
  else {
    cVar1 = (**(code **)(*param_1 + 0x70))(param_1,param_2,&uStack_c);
    if (cVar1 == '\0') {
      uStack_c = 0xffffffff;
    }
  }
  return uStack_c;
}

