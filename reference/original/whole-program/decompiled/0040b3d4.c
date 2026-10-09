/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b3d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0040b3d4(int param_1,undefined4 param_2,HMODULE param_3,LPCSTR param_4,undefined *param_5)

{
  LPCSTR pCVar1;
  HMODULE extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffe0,in_stack_ffffffe4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_00402c0c(param_1,0,param_3);
  pCVar1 = FUN_00403814(param_5);
  FUN_0040b498(param_1,param_3,pCVar1,param_4);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe0;
  }
  return param_1;
}

