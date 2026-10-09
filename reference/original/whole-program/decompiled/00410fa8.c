/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410fa8.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * root_00410fa8(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int *extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe8;
  undefined4 in_stack_ffffffec;
  
  if ((char)param_2 != '\0') {
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_ffffffe8,in_stack_ffffffec);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_004107ec(param_1,0,param_3);
  iVar1 = param_1[8];
  *(int **)(iVar1 + 0x94) = param_1;
  *(code **)(iVar1 + 0x90) = FUN_00411030;
  param_1[9] = *(int *)(DAT_0048a6f8 + 0x20);
  *(undefined *)((int)param_1 + 0x2d) = 1;
  FUN_00410f64(DAT_0048a690,param_1);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe8;
  }
  return param_1;
}

