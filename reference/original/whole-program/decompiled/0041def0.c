/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041def0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041def0(int param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  short local_18 [8];
  int *local_8;
  
  FUN_0041db9c(param_1);
  if (param_2 == 0) {
    FUN_0041de0c(param_1,0,0,0,0,0,0,0,0,0);
  }
  else {
    uVar1 = FUN_0040af50(param_3,local_18,0xe);
    uVar2 = extraout_ECX;
    uVar3 = extraout_EDX;
    if (local_18[0] != 0x4d42) {
      FUN_0041ac38(uVar1,extraout_EDX);
      uVar2 = extraout_ECX_00;
      uVar3 = extraout_EDX_00;
    }
    local_8 = (int *)FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)uVar3 >> 8),1),uVar2);
    uVar2 = *in_FS_OFFSET;
    *in_FS_OFFSET = &stack0xffffffd0;
    FUN_0040b2e8(local_8,param_2 + -0xe);
    FUN_0040af50(param_3,local_8[1],param_2 + -0xe);
    FUN_0041dfb4(param_1,local_8);
    *in_FS_OFFSET = uVar2;
  }
  return;
}

