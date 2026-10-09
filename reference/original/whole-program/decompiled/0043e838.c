/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043e838.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043e838(int *param_1)

{
  int iVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  int local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = 0;
  puStack_1c = &LAB_0043e886;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  iVar1 = FUN_0042a91c(param_1);
  FUN_0043efa8((int)param_1,iVar1,&local_8);
  (**(code **)(*param_1 + 0x8c))(param_1,local_8);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0043e88d;
  puStack_1c = (undefined *)0x43e885;
  FUN_004034dc(&local_8);
  return;
}

