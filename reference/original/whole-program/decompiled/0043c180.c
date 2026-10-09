/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043c180.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043c180(byte *param_1,byte *param_2)

{
  byte *pbVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  byte *local_c;
  byte *local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_8 = (byte *)0x0;
  local_c = (byte *)0x0;
  puStack_20 = &LAB_0043c1da;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  FUN_0043c124(param_2,&local_8);
  pbVar1 = local_8;
  FUN_0043c124(param_1,&local_c);
  FUN_004059fc(local_c,pbVar1);
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0043c1e1;
  puStack_20 = (undefined *)0x43c1d9;
  FUN_004034fc((int *)&local_c,2);
  return;
}

