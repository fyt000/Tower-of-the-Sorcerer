/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004074cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004074cc(int param_1,undefined4 param_2,UINT param_3)

{
  UINT extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStackY_30;
  undefined *puStackY_2c;
  undefined *puStackY_28;
  undefined4 in_stack_ffffffdc;
  undefined4 in_stack_ffffffe0;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  if ((char)param_2 != '\0') {
    puStackY_28 = (undefined *)0x4074e0;
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffdc,in_stack_ffffffe0);
    param_3 = extraout_ECX;
  }
  puStackY_2c = &LAB_0040751f;
  uStackY_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStackY_30;
  puStackY_28 = &stack0xfffffffc;
  FUN_00405bf0(param_3,(int *)&local_8);
  FUN_0040352c((int *)(param_1 + 4),local_8);
  *in_FS_OFFSET = uStackY_30;
  puStackY_28 = &LAB_00407526;
  puStackY_2c = (undefined *)0x40751e;
  FUN_004034dc((int *)&local_8);
  return;
}

