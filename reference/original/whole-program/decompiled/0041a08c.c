/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a08c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0041a08c(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe8;
  undefined4 in_stack_ffffffec;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffe8,in_stack_ffffffec);
    param_2 = extraout_EDX;
  }
  puVar1 = FUN_00419604(DAT_0048a6f0,(undefined4 *)&DAT_004894e8);
  *(undefined4 **)(param_1 + 0xc) = puVar1;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe8;
  }
  return param_1;
}

