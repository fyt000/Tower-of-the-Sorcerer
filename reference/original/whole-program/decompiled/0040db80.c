/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040db80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040db80(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStackY_2c;
  undefined *puStackY_28;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_1c = &LAB_0040dc18;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  puStackY_28 = (undefined *)0x40dba1;
  FUN_0040d9f8((char)param_4,(undefined)param_2,(undefined)param_3,param_4);
  FUN_00403570((int *)&local_8,*(int *)(*(int *)(param_4 + -4) + 0x28));
  puStackY_28 = &LAB_0040dbfb;
  uStackY_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStackY_2c;
  FUN_004034dc((int *)(*(int *)(param_4 + -4) + 0x28));
  FUN_0040d3b4(*(int *)(param_4 + -4),param_1,extraout_ECX);
  *in_FS_OFFSET = uStackY_2c;
  puStackY_28 = (undefined *)0x40dbfa;
  FUN_0040352c((int *)(*(int *)(param_4 + -4) + 0x28),local_8);
  return;
}

