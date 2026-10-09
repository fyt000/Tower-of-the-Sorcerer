/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405c28.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00405c28(UINT param_1,undefined4 param_2,undefined4 param_3,int *param_4)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  byte *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (byte *)0x0;
  puStack_1c = &LAB_00405c72;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00405bf0(param_1,(int *)&local_8);
  FUN_00406630(param_4,local_8,param_2,param_3);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_00405c79;
  puStack_1c = (undefined *)0x405c71;
  FUN_004034dc((int *)&local_8);
  return;
}

