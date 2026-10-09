/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428174.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_00428174(int *param_1,undefined4 param_2,int *param_3)

{
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
  FUN_00417128((int)param_1,0,param_3);
  *(ushort *)(param_1 + 0xd) = DAT_004281d8 | *(ushort *)(param_1 + 0xd);
  FUN_004130d8(param_1,0x41);
  FUN_004130f8(param_1,0x11);
  *(undefined *)((int)param_1 + 0xb1) = 1;
  *(undefined *)((int)param_1 + 0xb3) = 1;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe8;
  }
  return param_1;
}

