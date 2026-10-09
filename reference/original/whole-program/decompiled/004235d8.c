/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004235d8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004235d8(int *param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  undefined4 local_8;
  
  if ((*(byte *)((int)param_1 + 0x11d) & 8) != 0) {
    param_1[0x4b] = 2;
    return;
  }
  local_8 = param_3;
  uVar1 = FUN_00423680((int)param_1,param_2,param_3);
  if ((char)uVar1 != '\0') {
    if (*(char *)((int)param_1 + 0x11a) == '\x01') {
      if ((*(byte *)(param_1 + 0x45) & 2) == 0) {
        local_8 = (uint)local_8._1_3_ << 8;
      }
      else {
        local_8 = CONCAT31(local_8._1_3_,3);
      }
    }
    else {
      local_8 = CONCAT31(local_8._1_3_,1);
    }
    uVar2 = extraout_ECX;
    uVar3 = extraout_EDX;
    if (*(short *)((int)param_1 + 0x16a) != 0) {
      (*(code *)param_1[0x5a])(param_1[0x5b],param_1,&local_8);
      uVar2 = extraout_ECX_00;
      uVar3 = extraout_EDX_00;
    }
    if ((char)local_8 != '\0') {
      if (param_1 == *(int **)(DAT_0048a6f8 + 0x28)) {
        FUN_00425018();
      }
      else if ((char)local_8 == '\x01') {
        FUN_00423788(param_1,uVar3,uVar2);
      }
      else if ((char)local_8 == '\x03') {
        FUN_00421edc(param_1,1);
      }
      else {
        FUN_004239d8(param_1);
      }
    }
  }
  return;
}

