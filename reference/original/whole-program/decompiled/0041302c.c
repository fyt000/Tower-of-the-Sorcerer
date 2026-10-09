/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041302c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041302c(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  if ((((param_2 != param_1[9]) || (param_3 != param_1[10])) || (param_5 != param_1[0xb])) ||
     (param_4 != param_1[0xc])) {
    FUN_00413924((int)param_1,*(char *)((int)param_1 + 0x37),'\0');
    param_1[9] = param_2;
    param_1[10] = param_3;
    param_1[0xb] = param_5;
    param_1[0xc] = param_4;
    (**(code **)(*param_1 + 0x44))();
    FUN_00413cb8(param_1,0x47,0,0);
    FUN_00412f1c((int)param_1);
  }
  return;
}

