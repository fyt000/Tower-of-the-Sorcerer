/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409d8c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409d8c(int *param_1,int *param_2)

{
  undefined4 uVar1;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar2;
  undefined *puStack_130;
  undefined *puStack_12c;
  undefined *puStack_128;
  int local_118;
  undefined local_114;
  byte *local_110;
  undefined local_10c;
  byte local_108 [256];
  int local_8;
  
  puStack_128 = &stack0xfffffffc;
  local_8 = 0;
  puStack_12c = &LAB_00409e42;
  puStack_130 = (undefined *)*in_FS_OFFSET;
  *in_FS_OFFSET = &puStack_130;
  if (param_2 == (int *)0x0) {
    FUN_00403570(&local_8,0x409e58);
  }
  else {
    puStack_128 = &stack0xfffffffc;
    FUN_00402b7c(*param_2,local_108);
    FUN_004035fc(&local_8,local_108);
  }
  local_118 = local_8;
  local_114 = 0xb;
  FUN_00402b7c(*param_1,local_108);
  local_110 = local_108;
  local_10c = 4;
  uVar2 = 1;
  uVar1 = FUN_0040753c(0x40576c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf000,1,&local_118);
  FUN_004031f8(uVar1);
  *in_FS_OFFSET = uVar2;
  puStack_130 = &LAB_00409e49;
  FUN_004034dc(&local_8);
  return;
}

