/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412e20.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_00412e20(int *param_1,char param_2)

{
  FUN_0042431c(DAT_0048a6f8,(int)param_1);
  FUN_00402c34((int *)param_1[0x11]);
  FUN_0040626c(param_1[0x10]);
  (**(code **)(*param_1 + 0x3c))(param_1,0);
  FUN_0040e4fc(param_1,'\0');
  if (param_2 != '\0') {
    FUN_00402e48(param_1);
  }
  return param_1;
}

