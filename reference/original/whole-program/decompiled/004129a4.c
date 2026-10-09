/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004129a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004129a4(int *param_1,char param_2,undefined4 param_3)

{
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  code *pcStack_20;
  undefined *puStack_1c;
  undefined4 *local_c;
  char local_5;
  
  puStack_1c = &stack0xfffffffc;
  pcStack_20 = thunk_FUN_00402f4c;
  uStack_24 = *in_FS_OFFSET;
  DAT_0048a69c = param_1;
  *in_FS_OFFSET = &uStack_24;
  local_c = (undefined4 *)0x0;
  DAT_0048a6a4 = 0;
  local_5 = param_2;
  FUN_00402cdc(param_1,&local_c,param_3);
  if (local_c == (undefined4 *)0x0) {
    local_c = (undefined4 *)
              FUN_00412600(0x411234,CONCAT31((int3)((uint)extraout_EDX >> 8),1),param_1);
    DAT_0048a6a4 = 1;
  }
  FUN_00412918(local_c,local_5);
  *in_FS_OFFSET = uStack_24;
  return;
}

