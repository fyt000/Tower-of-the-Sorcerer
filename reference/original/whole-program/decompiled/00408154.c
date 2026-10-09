/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00408154.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00408154(undefined4 param_1,undefined4 param_2)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_1c;
  undefined *puStack_18;
  undefined *puStack_14;
  
  puStack_14 = &stack0xfffffffc;
  puStack_18 = &LAB_00408194;
  uStack_1c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_1c;
  FUN_00407834(0,param_2);
  FUN_00406850();
  FUN_00406d28();
  FUN_00406fb4();
  FUN_004070e4();
  FUN_00407880();
  *in_FS_OFFSET = uStack_1c;
  return;
}

