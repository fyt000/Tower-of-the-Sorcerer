/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041772c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_0041772c(int *param_1,char param_2)

{
  int iVar1;
  
  while (0 < (int)((undefined4 *)param_1[0xf])[2]) {
    iVar1 = FUN_00409afc((undefined4 *)param_1[0xf]);
    FUN_00418490((int)param_1,iVar1);
  }
  FUN_00402c34((int *)param_1[0x12]);
  FUN_004179bc(param_1);
  FUN_00402c34((int *)param_1[0xf]);
  FUN_0040e4fc(param_1,'\0');
  if (param_2 != '\0') {
    FUN_00402e48(param_1);
  }
  return param_1;
}

