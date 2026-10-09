/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d7fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041d7fc(int param_1,HGDIOBJ param_2,HPALETTE param_3,char param_4,int param_5,int param_6)

{
  BOOL BVar1;
  undefined4 uVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_3c;
  code *pcStack_38;
  undefined *puStack_34;
  undefined4 local_30;
  code *pcStack_2c;
  undefined *puStack_28;
  
  FUN_0041db9c(param_1);
  puStack_28 = (undefined *)0x41d830;
  BVar1 = FUN_0041d400(param_2,param_3,param_6,param_4,*(int *)(param_1 + 0x14),param_5);
  pcStack_2c = thunk_FUN_00402f4c;
  local_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &local_30;
  puStack_34 = (undefined *)0x41d849;
  puStack_28 = &stack0xfffffffc;
  uVar2 = FUN_0041d66c(param_3);
  pcStack_38 = thunk_FUN_00402f4c;
  uStack_3c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_3c;
  puStack_34 = &stack0xfffffffc;
  FUN_0041de0c(param_1,BVar1,uVar2,0,0,0,0,param_4,param_5,param_6);
  *in_FS_OFFSET = uStack_3c;
  *in_FS_OFFSET = local_30;
  return;
}

