/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004070e4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004070e4(void)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  int extraout_ECX;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  float10 in_ST0;
  float10 in_ST1;
  float10 in_ST2;
  float10 in_ST3;
  float10 in_ST4;
  float10 in_ST5;
  float10 in_ST6;
  float10 in_ST7;
  undefined4 uStack_12c;
  undefined *puStack_128;
  undefined *puStack_124;
  undefined4 local_114 [64];
  undefined4 *local_14;
  ushort local_e;
  ushort local_c;
  undefined2 local_a;
  char *local_8;
  
  puStack_124 = &stack0xfffffffc;
  local_14 = (undefined4 *)0x0;
  local_8 = (char *)0x0;
  puStack_128 = &LAB_00407287;
  uStack_12c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_12c;
  FUN_00405bf0(0xfe8e,(int *)&local_14);
  uVar2 = FUN_00405bd8((byte *)local_14,0,extraout_ECX);
  DAT_0048a540 = (ushort)uVar2;
  DAT_0048a544 = 0;
  if (DAT_0048a540 != 0) {
    DAT_0048a544 = FUN_00402650((uVar2 & 0xffff) * 0x24);
    uVar2 = (uint)DAT_0048a540;
    if (uVar2 != 0) {
      iVar4 = 1;
      do {
        puVar1 = (undefined4 *)(DAT_0048a544 + -0x24 + iVar4 * 0x24);
        FUN_00405bf0(iVar4 + 0xfe8e,(int *)&local_8);
        FUN_00407084(&local_8,(int *)&local_14);
        FUN_00403988((undefined *)local_114,local_14,0xff);
        FUN_00402918(puVar1,local_114,4);
        FUN_00407084(&local_8,(int *)&local_14);
        FUN_00403988((undefined *)local_114,local_14,0xff);
        FUN_00402918((undefined4 *)((int)puVar1 + 5),local_114,4);
        FUN_00407084(&local_8,(int *)&local_14);
        FUN_00403988((undefined *)local_114,local_14,0xff);
        FUN_00402918((undefined4 *)((int)puVar1 + 10),local_114,0x10);
        FUN_00407084(&local_8,(int *)&local_14);
        uVar3 = FUN_00405b9c((byte *)local_14);
        local_a = (undefined2)uVar3;
        FUN_00407084(&local_8,(int *)&local_14);
        uVar3 = FUN_00405b9c((byte *)local_14);
        local_c = (ushort)uVar3;
        FUN_00407084(&local_8,(int *)&local_14);
        uVar3 = FUN_00405b9c((byte *)local_14);
        local_e = (ushort)uVar3;
        FUN_004067ac(CONCAT22((short)((uint)uVar3 >> 0x10),local_a),local_c,local_e);
        *(double *)(puVar1 + 7) = (double)in_ST0;
        iVar4 = iVar4 + 1;
        uVar2 = uVar2 - 1;
        in_ST0 = in_ST1;
        in_ST1 = in_ST2;
        in_ST2 = in_ST3;
        in_ST3 = in_ST4;
        in_ST4 = in_ST5;
        in_ST5 = in_ST6;
        in_ST6 = in_ST7;
      } while (uVar2 != 0);
    }
  }
  *in_FS_OFFSET = uStack_12c;
  puStack_124 = &LAB_0040728e;
  puStack_128 = (undefined *)0x40727e;
  FUN_004034dc((int *)&local_14);
  puStack_128 = (undefined *)0x407286;
  FUN_004034dc((int *)&local_8);
  return;
}

