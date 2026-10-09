/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040976c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040976c(undefined4 *param_1,undefined4 param_2)

{
  undefined **ppuVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined *puVar2;
  undefined4 uStack_1c;
  undefined *puStack_18;
  undefined *puStack_14;
  undefined local_d;
  undefined4 local_c;
  undefined4 *local_8;
  
  puVar2 = &stack0xfffffffc;
  puStack_14 = (undefined *)0x40977d;
  local_c = param_2;
  local_8 = param_1;
  FUN_00409654();
  puStack_18 = &LAB_004097b5;
  uStack_1c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_1c;
  puStack_14 = &stack0xfffffffc;
  ppuVar1 = (undefined **)FUN_00402b78(local_8);
  local_d = FUN_004096d4(ppuVar1,extraout_EDX,extraout_ECX,(int)puVar2);
  FUN_00409678();
  *in_FS_OFFSET = uStack_1c;
  puStack_14 = &LAB_004097bc;
  puStack_18 = (undefined *)0x4097b4;
  FUN_004096a4();
  return;
}

