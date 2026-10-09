/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409438.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409438(undefined **param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_128;
  undefined *puStack_124;
  undefined *puStack_120;
  int local_110;
  undefined local_10c;
  byte local_108 [256];
  int local_8;
  
  puStack_120 = &stack0xfffffffc;
  local_8 = 0;
  puStack_124 = &LAB_004094f2;
  uStack_128 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_128;
  while( true ) {
    iVar2 = FUN_00409a88((int)DAT_004891c0,(int)param_1);
    if (iVar2 != -1) break;
    FUN_00402b7c((int)param_1,local_108);
    FUN_004035fc(&local_8,local_108);
    iVar2 = FUN_004092f0(local_8);
    if (iVar2 != 0) {
      local_110 = local_8;
      local_10c = 0xb;
      uVar1 = FUN_0040753c(0x408874,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf012,0,&local_110)
      ;
      FUN_004031f8(uVar1);
    }
    FUN_004099a4(DAT_004891c0,param_1);
    if (param_1 == &PTR_FUN_00408b48) break;
    param_1 = (undefined **)FUN_00402bb8((int)param_1);
  }
  *in_FS_OFFSET = uStack_128;
  puStack_120 = &LAB_004094f9;
  puStack_124 = (undefined *)0x4094f1;
  FUN_004034dc(&local_8);
  return;
}

