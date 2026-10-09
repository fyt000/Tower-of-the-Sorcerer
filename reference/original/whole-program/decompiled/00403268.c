/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403268.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_00403268(undefined param_1,undefined param_2,undefined param_3,undefined param_4,
                 undefined param_5,undefined param_6,undefined param_7,undefined param_8,
                 undefined param_9,undefined param_10,undefined4 *param_11)

{
  int *piVar1;
  int *piVar2;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 *in_FS_OFFSET;
  ULONG_PTR in_stack_00000000;
  
  piVar2 = (int *)FUN_00403498();
  piVar1 = (int *)*piVar2;
  *piVar2 = *piVar1;
  FUN_00402c34((int *)piVar1[2]);
  *in_FS_OFFSET = *param_11;
  param_11[2] = 0x403295;
  FUN_00402f10(param_11[1],in_stack_00000000);
                    /* WARNING: Could not recover jumptable at 0x00403295. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

