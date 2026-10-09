/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00432af0.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * root_00432af0(int *param_1,char param_2)

{
  undefined4 uVar1;
  
  FUN_00402c34((int *)param_1[1]);
  FUN_00432b48((int)param_1);
  if (DAT_004898d4 != (int *)0x0) {
    uVar1 = FUN_00432a58((int)DAT_004898d4);
    if ((char)uVar1 != '\0') {
      FUN_00402c34(DAT_004898d4);
      DAT_004898d4 = (int *)0x0;
    }
  }
  FUN_00402c28(param_1,'\0');
  if (param_2 != '\0') {
    FUN_00402e48(param_1);
  }
  return param_1;
}

