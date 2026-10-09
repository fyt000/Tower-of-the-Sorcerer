/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a0dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040a0dc(int *param_1,int **param_2)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_18;
  undefined *puStack_14;
  undefined *puStack_10;
  
  puStack_10 = (undefined *)0x40a0f2;
  piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_00408c2c);
  if ((char)piVar1 != '\0') {
    puStack_10 = (undefined *)0x40a0fe;
    FUN_0040a14c(param_1);
    puStack_14 = &LAB_0040a134;
    uStack_18 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_18;
    puStack_10 = &stack0xfffffffc;
    (**(code **)(*param_1 + 0x38))();
    (**(code **)(*param_1 + 0x34))(param_1,param_2);
    *in_FS_OFFSET = uStack_18;
    puStack_10 = (undefined *)0x40a145;
    puStack_14 = (undefined *)0x40a133;
    FUN_0040a204(param_1);
    return;
  }
  puStack_10 = (undefined *)0x40a145;
  FUN_00409d78(param_1,param_2);
  return;
}

