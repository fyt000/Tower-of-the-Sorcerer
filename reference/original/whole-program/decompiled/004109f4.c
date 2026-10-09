/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004109f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

char FUN_004109f4(int *param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStackY_20;
  code *pcStackY_1c;
  char local_5;
  
  local_5 = '\x01';
  if ((int *)param_1[0x11] != (int *)0x0) {
    pcStackY_1c = (code *)0x410a11;
    iVar1 = param_4;
    local_5 = FUN_004109f4((int *)param_1[0x11],param_4,param_3,param_4);
    param_3 = iVar1;
  }
  if (local_5 == '\x01') {
    if (*(char *)((int)param_1 + 0x29) == '\0') {
      local_5 = '\0';
    }
    else {
      pcStackY_1c = thunk_FUN_00402f4c;
      uStackY_20 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStackY_20;
      (**(code **)(*param_1 + 0x2c))(param_1,*param_1,param_3);
      if (*(short *)(*(int *)(param_4 + -4) + 0x40) != *(short *)(param_4 + -6)) {
        local_5 = '\x02';
      }
      *in_FS_OFFSET = uStackY_20;
    }
  }
  return local_5;
}

