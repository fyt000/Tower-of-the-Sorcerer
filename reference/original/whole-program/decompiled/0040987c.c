/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040987c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0040987c(undefined4 *param_1,undefined4 *param_2)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_34;
  undefined *puStack_30;
  undefined *puStack_2c;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  
  puStack_20 = (undefined *)0x409894;
  uVar1 = FUN_00402b78(param_1);
  puStack_20 = (undefined *)0x40989d;
  uVar2 = FUN_00402b78(param_2);
  if (uVar1 == uVar2) {
    puStack_20 = (undefined *)0x4098ac;
    uVar1 = FUN_00409fc4((int)param_1);
    puStack_20 = (undefined *)0x4098b5;
    uVar2 = FUN_00409fc4((int)param_2);
    if (uVar1 == uVar2) {
      puStack_20 = (undefined *)0x4098c9;
      piVar3 = (int *)FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX
                                  );
      puStack_24 = &LAB_0040994c;
      uStack_28 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_28;
      puStack_2c = (undefined *)0x4098e4;
      puStack_20 = &stack0xfffffffc;
      FUN_00409824(piVar3,(int)param_1);
      puStack_2c = (undefined *)0x4098f0;
      piVar4 = (int *)FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                                   extraout_ECX_00);
      puStack_30 = &LAB_0040992f;
      uStack_34 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_34;
      puStack_2c = &stack0xfffffffc;
      FUN_00409824(piVar4,(int)param_2);
      FUN_004097e4(piVar3,piVar4);
      *in_FS_OFFSET = uStack_34;
      puStack_2c = &LAB_00409936;
      puStack_30 = (undefined *)0x40992e;
      uVar5 = FUN_00402c34(piVar4);
      return uVar5;
    }
  }
  return uVar2 & 0xffffff00;
}

