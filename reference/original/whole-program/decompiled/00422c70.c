/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422c70.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422c70(int *param_1)

{
  undefined extraout_CL;
  undefined4 extraout_ECX;
  undefined extraout_DL;
  
  (**(code **)(*param_1 + -0x10))();
  FUN_00421bfc(param_1,(int *)param_1[0x4a],extraout_ECX);
  if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
    FUN_00422b74((char)param_1,extraout_DL,extraout_CL,&stack0xfffffffc);
  }
  return;
}

