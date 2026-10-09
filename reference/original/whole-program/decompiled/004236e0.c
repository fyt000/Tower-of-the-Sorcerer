/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004236e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004236e0(int *param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  code *pcStack_20;
  undefined *puStack_1c;
  char local_9;
  int *local_8;
  
  puStack_1c = &stack0xfffffffc;
  pcStack_20 = thunk_FUN_00402f4c;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  local_9 = '\0';
  local_8 = param_1;
  uVar1 = FUN_00423680((int)param_1,param_2,param_3);
  if (((char)uVar1 != '\0') && (local_9 = '\x01', *(short *)((int)local_8 + 0x16a) != 0)) {
    (*(code *)local_8[0x5a])(local_8[0x5b],local_8,&local_9);
  }
  if (local_9 == '\0') {
    local_8[0x4b] = 0;
  }
  else if (local_9 == '\x02') {
    FUN_004239d8(local_8);
  }
  *in_FS_OFFSET = uStack_24;
  return;
}

