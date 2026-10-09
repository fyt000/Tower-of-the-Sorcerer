/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043f618.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043f618(int param_1)

{
  bool bVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  DWORD DVar5;
  int iVar6;
  ushort *puVar7;
  undefined4 uVar8;
  undefined4 *in_FS_OFFSET;
  undefined uVar9;
  undefined4 uStack_19c;
  undefined *puStack_198;
  undefined *puStack_194;
  undefined4 uStack_190;
  undefined *puStack_18c;
  undefined *puStack_188;
  int iStack_178;
  undefined uStack_174;
  undefined *puStack_170;
  WORD aWStack_16c [4];
  uint uStack_164;
  int iStack_160;
  short sStack_14;
  ushort uStack_12;
  uint *puStack_10;
  int iStack_c;
  int iStack_8;
  
  puStack_170 = (undefined *)0x0;
  puStack_10 = (uint *)0x0;
  puStack_188 = (undefined *)0x43f642;
  iStack_8 = param_1;
  FUN_004039ac((int)aWStack_16c,0x405340);
  puStack_18c = &LAB_0043f8e1;
  uStack_190 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_190;
  uStack_12 = 0;
  puStack_194 = (undefined *)0x43f65e;
  puStack_188 = &stack0xfffffffc;
  bVar1 = FUN_00416e54(iStack_8);
  if (!bVar1) {
    *in_FS_OFFSET = uStack_190;
    puStack_188 = &LAB_0043f8e8;
    puStack_18c = (undefined *)0x43f8c8;
    FUN_004034dc((int *)&puStack_170);
    puStack_18c = (undefined *)0x43f8d8;
    FUN_00403a64((int)aWStack_16c,0x405340);
    puStack_18c = (undefined *)0x43f8e0;
    FUN_004034dc((int *)&puStack_10);
    return;
  }
  uVar2 = 0;
  puVar7 = &DAT_004898f8;
  do {
    bVar1 = (byte)uVar2 < 7;
    if ((byte)uVar2 < 8) {
      bVar1 = (*(byte *)(iStack_8 + 0x144 + ((int)(uVar2 & 0x7f) >> 3)) >> (uVar2 & 7) & 1) != 0;
    }
    if (bVar1) {
      uStack_12 = uStack_12 | *puVar7;
    }
    uVar2 = uVar2 + 1;
    puVar7 = puVar7 + 1;
  } while ((char)uVar2 != '\x06');
  puStack_194 = (undefined *)0x43f6a0;
  FUN_0040274c(*(undefined **)(iStack_8 + 0x13c));
  puStack_194 = (undefined *)0x43f6a5;
  FUN_00402710();
  puStack_194 = (undefined *)0x43f6ad;
  FUN_0042a894(iStack_8);
  iStack_c = 0;
  sStack_14 = *(short *)(DAT_0048a6fc + 0x28);
  puStack_198 = &LAB_0043f89e;
  uStack_19c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_19c;
  puStack_194 = &stack0xfffffffc;
  puVar3 = (undefined4 *)FUN_00403814(*(undefined **)(iStack_8 + 0x140));
  while (puVar3 != (undefined4 *)0x0) {
    puVar4 = (undefined4 *)FUN_00406200((char *)puVar3,';');
    if (puVar4 != (undefined4 *)0x0) {
      *(undefined *)puVar4 = 0;
    }
    FUN_00403608((int *)&puStack_170,puVar3);
    DVar5 = FUN_00405e30(puStack_170,(uint)uStack_12,aWStack_16c);
    if (DVar5 == 0) {
      do {
        if (((*(byte *)(iStack_8 + 0x144) & 0x40) != 0) || ((uStack_12 & uStack_164) != 0)) {
          uVar9 = (uStack_164 & 0x10) == 0;
          if ((bool)uVar9) {
            FUN_00405fec(iStack_160,(int *)&puStack_170);
            FUN_004059cc(puStack_170,(LPSTR *)&puStack_10);
            uVar8 = *(undefined4 *)(iStack_8 + 0x15c);
            FUN_00403760(puStack_10,(uint *)&DAT_0043f908);
            if (((((bool)uVar9) || (FUN_00403760(puStack_10,(uint *)&DAT_0043f918), (bool)uVar9)) ||
                (FUN_00403760(puStack_10,(uint *)&DAT_0043f928), (bool)uVar9)) ||
               (FUN_00403760(puStack_10,(uint *)&DAT_0043f938), (bool)uVar9)) {
              uVar8 = *(undefined4 *)(iStack_8 + 0x154);
            }
            iStack_c = (**(code **)(**(int **)(iStack_8 + 0x100) + 0x30))
                                 (*(int **)(iStack_8 + 0x100),iStack_160,uVar8);
          }
          else {
            iStack_178 = iStack_160;
            uStack_174 = 0xb;
            FUN_0040661c(&DAT_0043f8f8,&iStack_178,0,(int *)&puStack_170);
            iStack_c = (**(code **)(**(int **)(iStack_8 + 0x100) + 0x2c))
                                 (*(int **)(iStack_8 + 0x100),puStack_170);
            if (*(char *)(iStack_8 + 0x16c) != '\0') {
              (**(code **)(**(int **)(iStack_8 + 0x100) + 0x20))
                        (*(int **)(iStack_8 + 0x100),iStack_c,*(undefined4 *)(iStack_8 + 0x158));
            }
          }
        }
        if (iStack_c == 100) {
          FUN_00423d4c(DAT_0048a6fc,-0xb);
        }
        iVar6 = FUN_00405e7c(aWStack_16c);
      } while (iVar6 == 0);
      FUN_00405ea0((int)aWStack_16c);
    }
    puVar3 = puVar4;
    if (puVar4 != (undefined4 *)0x0) {
      *(undefined *)puVar4 = 0x3b;
      puVar3 = (undefined4 *)((int)puVar4 + 1);
    }
  }
  *in_FS_OFFSET = uStack_19c;
  puStack_194 = &DAT_0043f8a5;
  puStack_198 = (undefined *)0x43f89d;
  FUN_00423d4c(DAT_0048a6fc,sStack_14);
  return;
}

