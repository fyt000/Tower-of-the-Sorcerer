/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040f848.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040f848(ushort param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined4 *local_10;
  undefined4 *local_c;
  undefined4 uStack_8;
  
  puStack_20 = &stack0xfffffffc;
  local_c = (undefined4 *)0x0;
  local_10 = (undefined4 *)0x0;
  uStack_8 = (uint)param_1 << 0x10;
  uVar2 = uStack_8;
  puStack_24 = &LAB_0040fa35;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  uStack_8._2_1_ = (byte)param_1;
  uVar1 = (uint)uStack_8._2_1_;
  uStack_8 = uVar2;
  if (uStack_8._2_1_ < 0x2d) {
    if (uVar1 - 8 < 2) {
      uVar2 = (uint)uStack_8._2_1_;
      puStack_20 = &stack0xfffffffc;
      FUN_00403570((int *)&local_c,(&DAT_0048a624)[uVar2]);
      goto LAB_0040f9be;
    }
    if (uVar1 == 0xd) {
      puStack_20 = &stack0xfffffffc;
      FUN_00403570((int *)&local_c,DAT_0048a650);
      goto LAB_0040f9be;
    }
    if (uVar1 == 0x1b) {
      puStack_20 = &stack0xfffffffc;
      FUN_00403570((int *)&local_c,DAT_0048a64c);
      goto LAB_0040f9be;
    }
    if (uVar1 - 0x20 < 9) {
      bVar3 = uStack_8._2_1_ + 4;
      puStack_20 = &stack0xfffffffc;
      FUN_00403570((int *)&local_c,*(int *)(&DAT_0048a5c4 + (uint)bVar3 * 4));
      goto LAB_0040f9be;
    }
  }
  else if (uStack_8._2_1_ < 0x41) {
    if (uVar1 - 0x2d < 2) {
      bVar3 = uStack_8._2_1_ + 0xd;
      puStack_20 = &stack0xfffffffc;
      FUN_00403570((int *)&local_c,*(int *)(&DAT_0048a590 + (uint)bVar3 * 4));
      goto LAB_0040f9be;
    }
    if (uVar1 - 0x30 < 10) {
      uVar2 = (uint)uStack_8._2_1_;
      puStack_20 = &stack0xfffffffc;
      FUN_004035ec((int *)&local_c,uVar2);
      goto LAB_0040f9be;
    }
  }
  else {
    if (uVar1 - 0x41 < 0x1a) {
      uVar2 = (uint)uStack_8._2_1_;
      FUN_004035ec((int *)&local_c,uVar2);
      goto LAB_0040f9be;
    }
    if (uVar1 - 0x60 < 10) {
      uVar2 = (uint)uStack_8._2_1_;
      puStack_20 = &stack0xfffffffc;
      FUN_004035ec((int *)&local_c,uVar2 - 0x30);
      goto LAB_0040f9be;
    }
    if (uVar1 - 0x70 < 0x18) {
      uVar2 = (uint)uStack_8._2_1_;
      puStack_20 = &stack0xfffffffc;
      FUN_00405b6c(uVar2 - 0x6f,(int *)&local_10);
      FUN_0040369c((int *)&local_c,(undefined4 *)&DAT_0040fa4c,local_10);
      goto LAB_0040f9be;
    }
  }
  puStack_20 = &stack0xfffffffc;
  FUN_0040f7e0(param_1,(int *)&local_c);
LAB_0040f9be:
  if (local_c == (undefined4 *)0x0) {
    FUN_004034dc(param_2);
  }
  else {
    FUN_004034dc(param_2);
    if ((uStack_8 & 0x20000000) != 0) {
      FUN_00403658(param_2,DAT_0048a680);
    }
    if ((uStack_8 & 0x40000000) != 0) {
      FUN_00403658(param_2,DAT_0048a684);
    }
    if ((uStack_8 & 0x80000000) != 0) {
      FUN_00403658(param_2,DAT_0048a688);
    }
    FUN_00403658(param_2,local_c);
  }
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_0040fa3c;
  puStack_24 = (undefined *)0x40fa34;
  FUN_004034fc((int *)&local_10,2);
  return;
}

