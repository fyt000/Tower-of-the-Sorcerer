/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004168c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004168c4(int *param_1,int param_2,int param_3)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_1c;
  undefined *puStack_18;
  undefined *puStack_14;
  
  puStack_14 = (undefined *)0x4168d9;
  FUN_00414aa0((int)param_1);
  puStack_18 = &LAB_00416915;
  uStack_1c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_1c;
  puStack_14 = &stack0xfffffffc;
  FUN_0041687c((int)param_1,param_2,param_3);
  FUN_004132bc(param_1,param_2,param_3);
  *in_FS_OFFSET = uStack_1c;
  puStack_14 = &LAB_0041691c;
  puStack_18 = (undefined *)0x416914;
  FUN_00414aa8((int)param_1);
  return;
}

