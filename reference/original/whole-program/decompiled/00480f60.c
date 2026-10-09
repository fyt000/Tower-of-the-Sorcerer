/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00480f60.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00480f60(int param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 uVar5;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  undefined4 extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_ECX_11;
  undefined4 extraout_ECX_12;
  undefined4 extraout_ECX_13;
  undefined4 extraout_ECX_14;
  undefined4 extraout_ECX_15;
  undefined4 extraout_ECX_16;
  undefined4 extraout_ECX_17;
  undefined4 extraout_ECX_18;
  undefined4 extraout_ECX_19;
  undefined4 extraout_ECX_20;
  undefined4 extraout_ECX_21;
  undefined4 extraout_ECX_22;
  undefined4 extraout_ECX_23;
  undefined4 extraout_ECX_24;
  undefined4 extraout_ECX_25;
  undefined4 extraout_ECX_26;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint extraout_EDX_01;
  uint extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 extraout_EDX_06;
  undefined4 extraout_EDX_07;
  undefined4 extraout_EDX_08;
  undefined4 extraout_EDX_09;
  undefined4 extraout_EDX_10;
  undefined4 extraout_EDX_11;
  undefined4 extraout_EDX_12;
  undefined4 extraout_EDX_13;
  undefined4 extraout_EDX_14;
  undefined4 extraout_EDX_15;
  undefined4 extraout_EDX_16;
  undefined4 extraout_EDX_17;
  undefined4 extraout_EDX_18;
  undefined4 extraout_EDX_19;
  undefined4 extraout_EDX_20;
  undefined4 extraout_EDX_21;
  undefined4 extraout_EDX_22;
  undefined4 extraout_EDX_23;
  undefined4 extraout_EDX_24;
  undefined4 extraout_EDX_25;
  undefined4 *in_FS_OFFSET;
  int iVar6;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  puStack_1c = &LAB_0048197f;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1cc) + 0x44),(uint)DAT_00489b9d);
  if (DAT_00489ba4 == '\0') {
    FUN_004130f8(*(int **)(param_1 + 0x1cc),0x38);
    FUN_004130d8(*(int **)(param_1 + 0x1cc),0x166);
    FUN_004130b8(*(int **)(param_1 + 0x1cc),0x10);
    FUN_00413098(*(int **)(param_1 + 0x1cc),0x8d);
    FUN_004130b8(*(int **)(param_1 + 0x418),0x18);
    FUN_00413098(*(int **)(param_1 + 0x418),0x90);
  }
  else if (DAT_00489ba4 == '\x01') {
    FUN_004130f8(*(int **)(param_1 + 0x1cc),0x46);
    FUN_004130d8(*(int **)(param_1 + 0x1cc),0x1c0);
    FUN_004130b8(*(int **)(param_1 + 0x1cc),0x14);
    FUN_00413098(*(int **)(param_1 + 0x1cc),0xb0);
    FUN_004130b8(*(int **)(param_1 + 0x418),0x1e);
    FUN_00413098(*(int **)(param_1 + 0x418),0xb4);
  }
  FUN_004130f8(*(int **)(param_1 + 0x418),*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 0xb);
  FUN_004130d8(*(int **)(param_1 + 0x418),*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 0xb);
  if (original_hero.hero_orb == 1) {
    FUN_0042c454(*(int *)(param_1 + 0x1b4),'\0');
    FUN_00450758(param_1);
    if (DAT_00489ba4 == '\0') {
      FUN_00413098(*(int **)(param_1 + 0x294),*(int *)(*(int *)(param_1 + 0x1cc) + 0x24) + 0x28);
    }
    else if (DAT_00489ba4 == '\x01') {
      FUN_00413098(*(int **)(param_1 + 0x294),*(int *)(*(int *)(param_1 + 0x1cc) + 0x24) + 0x32);
    }
    FUN_00413098(*(int **)(param_1 + 0x298),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x29c),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2a0),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2a4),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2a8),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2ac),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2b0),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2b4),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2b8),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 700),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2c0),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2c4),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2c8),*(undefined4 *)(*(int *)(param_1 + 0x294) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x2f0),
                 *(int *)(*(int *)(param_1 + 0x294) + 0x24) +
                 *(int *)(*(int *)(param_1 + 0x294) + 0x2c));
    FUN_00413098(*(int **)(param_1 + 0x2f4),
                 *(int *)(*(int *)(param_1 + 0x29c) + 0x24) +
                 *(int *)(*(int *)(param_1 + 0x29c) + 0x2c));
    FUN_00413098(*(int **)(param_1 + 0x2f8),
                 *(int *)(*(int *)(param_1 + 0x2a4) + 0x24) +
                 *(int *)(*(int *)(param_1 + 0x2a4) + 0x2c));
    FUN_00413098(*(int **)(param_1 + 0x2fc),
                 *(int *)(*(int *)(param_1 + 0x2ac) + 0x24) +
                 *(int *)(*(int *)(param_1 + 0x2ac) + 0x2c));
    FUN_00413098(*(int **)(param_1 + 0x300),
                 *(int *)(*(int *)(param_1 + 0x2b4) + 0x24) +
                 *(int *)(*(int *)(param_1 + 0x2b4) + 0x2c));
    FUN_00413098(*(int **)(param_1 + 0x304),
                 *(int *)(*(int *)(param_1 + 700) + 0x24) + *(int *)(*(int *)(param_1 + 700) + 0x2c)
                );
    FUN_00413098(*(int **)(param_1 + 0x308),
                 *(int *)(*(int *)(param_1 + 0x2c4) + 0x24) +
                 *(int *)(*(int *)(param_1 + 0x2c4) + 0x2c));
    FUN_004130d8(*(int **)(param_1 + 0x424),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x2c));
    FUN_004130f8(*(int **)(param_1 + 0x424),*(int *)(*(int *)(param_1 + 0x1b8) + 0x30) + -3);
    FUN_004130b8(*(int **)(param_1 + 0x424),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x28));
    FUN_00413098(*(int **)(param_1 + 0x424),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x24));
    uVar2 = (*(int *)(*(int *)(param_1 + 0x294) + 0x30) + *(int *)(*(int *)(param_1 + 0x298) + 0x30)
            ) - (*(int **)(param_1 + 0x428))[0xc];
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    FUN_004130b8(*(int **)(param_1 + 0x428),
                 (*(int *)(*(int *)(param_1 + 0x294) + 0x28) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x28)) + iVar3);
    FUN_00413098(*(int **)(param_1 + 0x428),
                 *(int *)(*(int *)(param_1 + 0x1cc) + 0x24) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x24));
    uVar2 = (*(int *)(*(int *)(param_1 + 0x294) + 0x30) + *(int *)(*(int *)(param_1 + 0x298) + 0x30)
            ) - *(int *)(*(int *)(param_1 + 0x428) + 0x30);
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    FUN_004130b8(*(int **)(param_1 + 0x42c),
                 (*(int *)(*(int *)(param_1 + 0x29c) + 0x28) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x28)) + iVar3);
    FUN_00413098(*(int **)(param_1 + 0x42c),
                 *(int *)(*(int *)(param_1 + 0x1cc) + 0x24) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x24));
    uVar2 = (*(int *)(*(int *)(param_1 + 0x294) + 0x30) + *(int *)(*(int *)(param_1 + 0x298) + 0x30)
            ) - *(int *)(*(int *)(param_1 + 0x428) + 0x30);
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    FUN_004130b8(*(int **)(param_1 + 0x430),
                 (*(int *)(*(int *)(param_1 + 0x2a4) + 0x28) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x28)) + iVar3);
    FUN_00413098(*(int **)(param_1 + 0x430),
                 *(int *)(*(int *)(param_1 + 0x1cc) + 0x24) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x24));
    uVar2 = (*(int *)(*(int *)(param_1 + 0x294) + 0x30) + *(int *)(*(int *)(param_1 + 0x298) + 0x30)
            ) - *(int *)(*(int *)(param_1 + 0x428) + 0x30);
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    FUN_004130b8(*(int **)(param_1 + 0x434),
                 (*(int *)(*(int *)(param_1 + 0x2ac) + 0x28) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x28)) + iVar3);
    FUN_00413098(*(int **)(param_1 + 0x434),
                 *(int *)(*(int *)(param_1 + 0x1cc) + 0x24) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x24));
    uVar2 = (*(int *)(*(int *)(param_1 + 0x294) + 0x30) + *(int *)(*(int *)(param_1 + 0x298) + 0x30)
            ) - *(int *)(*(int *)(param_1 + 0x428) + 0x30);
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    FUN_004130b8(*(int **)(param_1 + 0x438),
                 (*(int *)(*(int *)(param_1 + 0x2b4) + 0x28) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x28)) + iVar3);
    FUN_00413098(*(int **)(param_1 + 0x438),
                 *(int *)(*(int *)(param_1 + 0x1cc) + 0x24) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x24));
    uVar2 = (*(int *)(*(int *)(param_1 + 0x294) + 0x30) + *(int *)(*(int *)(param_1 + 0x298) + 0x30)
            ) - *(int *)(*(int *)(param_1 + 0x428) + 0x30);
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    FUN_004130b8(*(int **)(param_1 + 0x43c),
                 (*(int *)(*(int *)(param_1 + 700) + 0x28) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x28)) + iVar3);
    FUN_00413098(*(int **)(param_1 + 0x43c),
                 *(int *)(*(int *)(param_1 + 0x1cc) + 0x24) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x24));
    uVar2 = (*(int *)(*(int *)(param_1 + 0x294) + 0x30) + *(int *)(*(int *)(param_1 + 0x298) + 0x30)
            ) - *(int *)(*(int *)(param_1 + 0x428) + 0x30);
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    FUN_004130b8(*(int **)(param_1 + 0x440),
                 (*(int *)(*(int *)(param_1 + 0x2c4) + 0x28) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x28)) + iVar3);
    FUN_00413098(*(int **)(param_1 + 0x440),
                 *(int *)(*(int *)(param_1 + 0x1cc) + 0x24) -
                 *(int *)(*(int *)(param_1 + 0x424) + 0x24));
    FUN_00413098(*(int **)(param_1 + 0x290),
                 (*(int *)(*(int *)(param_1 + 0x2c8) + 0x24) +
                 *(int *)(*(int *)(param_1 + 0x2c8) + 0x2c)) - (*(int **)(param_1 + 0x290))[0xb]);
    uVar2 = ((*(int *)(*(int *)(param_1 + 0x424) + 0x28) +
             *(int *)(*(int *)(param_1 + 0x424) + 0x30)) -
            (*(int *)(*(int *)(param_1 + 0x2c8) + 0x28) + *(int *)(*(int *)(param_1 + 0x2c8) + 0x30)
            )) - *(int *)(*(int *)(param_1 + 0x290) + 0x30);
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    FUN_004130b8(*(int **)(param_1 + 0x290),
                 iVar3 + *(int *)(*(int *)(param_1 + 0x2c8) + 0x28) +
                         *(int *)(*(int *)(param_1 + 0x2c8) + 0x30));
    (**(code **)(*DAT_0048c524 + 0x2c))
              (DAT_0048c524,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    (**(code **)(*DAT_0048c524 + 0x28))
              (DAT_0048c524,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    iVar6 = 0;
    iVar3 = 0xa2;
    piVar4 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar4,0,iVar3,iVar6);
    iVar3 = 1;
    do {
      DAT_0048c564 = iVar3;
      (&DAT_00489907)[iVar3] = 0;
      switch(DAT_0048c564) {
      case 1:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x428) + 0xac),DAT_0048c524);
        break;
      case 2:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x42c) + 0xac),DAT_0048c524);
        break;
      case 3:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x430) + 0xac),DAT_0048c524);
        break;
      case 4:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x434) + 0xac),DAT_0048c524);
        break;
      case 5:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x438) + 0xac),DAT_0048c524);
        break;
      case 6:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x43c) + 0xac),DAT_0048c524);
        break;
      case 7:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x440) + 0xac),DAT_0048c524);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 != 8);
    piVar4 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar4 + 0xc))(piVar4,0xb4,&local_8);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),local_8);
    DAT_0048c5b0 = 1;
    iVar3 = 1;
    uVar5 = extraout_ECX;
    do {
      bVar1 = *(byte *)(original_hero.floor * 0x7b + 0x4b8935 + iVar3);
      DAT_0048c570 = iVar3;
      if ((byte)(bVar1 - 0x3d) < 0x23) {
        neighbor_index = (int)(bVar1 - 0x3d) >> 1;
        if ((int)neighbor_index < 0) {
          neighbor_index = neighbor_index + ((bVar1 - 0x3d & 1) != 0);
        }
        FUN_0044f26c(param_1);
        uVar5 = extraout_ECX_00;
        uVar2 = extraout_EDX;
      }
      else if (bVar1 == 0x68) {
        neighbor_index = 0x12;
        FUN_0044f26c(param_1);
        uVar5 = extraout_ECX_01;
        uVar2 = extraout_EDX_00;
      }
      else if (bVar1 == 0x7a) {
        neighbor_index = 0x13;
        FUN_0044f26c(param_1);
        uVar5 = extraout_ECX_02;
        uVar2 = extraout_EDX_01;
      }
      else {
        uVar2 = (uint)(original_maps + original_hero.floor) & 0xffffff00;
        if ((byte)(bVar1 + 0x7b) < 0x19) {
          iVar6 = (int)(bVar1 - 0x85) >> 1;
          if (iVar6 < 0) {
            iVar6 = iVar6 + (uint)((bVar1 - 0x85 & 1) != 0);
          }
          neighbor_index = iVar6 + 0x14;
          FUN_0044f26c(param_1);
          uVar5 = extraout_ECX_03;
          uVar2 = extraout_EDX_02;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 != 0x7a);
    FUN_00413500(*(int **)(param_1 + 0x424),CONCAT31((int3)(uVar2 >> 8),1),uVar5);
    FUN_00413500(*(int **)(param_1 + 0x1cc),CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                 extraout_ECX_04);
    FUN_00413500(*(int **)(param_1 + 0x294),CONCAT31((int3)((uint)extraout_EDX_04 >> 8),1),
                 extraout_ECX_05);
    FUN_00413500(*(int **)(param_1 + 0x298),CONCAT31((int3)((uint)extraout_EDX_05 >> 8),1),
                 extraout_ECX_06);
    FUN_00413500(*(int **)(param_1 + 0x29c),CONCAT31((int3)((uint)extraout_EDX_06 >> 8),1),
                 extraout_ECX_07);
    FUN_00413500(*(int **)(param_1 + 0x2a0),CONCAT31((int3)((uint)extraout_EDX_07 >> 8),1),
                 extraout_ECX_08);
    FUN_00413500(*(int **)(param_1 + 0x2a4),CONCAT31((int3)((uint)extraout_EDX_08 >> 8),1),
                 extraout_ECX_09);
    FUN_00413500(*(int **)(param_1 + 0x2a8),CONCAT31((int3)((uint)extraout_EDX_09 >> 8),1),
                 extraout_ECX_10);
    FUN_00413500(*(int **)(param_1 + 0x2ac),CONCAT31((int3)((uint)extraout_EDX_10 >> 8),1),
                 extraout_ECX_11);
    FUN_00413500(*(int **)(param_1 + 0x2b0),CONCAT31((int3)((uint)extraout_EDX_11 >> 8),1),
                 extraout_ECX_12);
    FUN_00413500(*(int **)(param_1 + 0x2b4),CONCAT31((int3)((uint)extraout_EDX_12 >> 8),1),
                 extraout_ECX_13);
    FUN_00413500(*(int **)(param_1 + 0x2b8),CONCAT31((int3)((uint)extraout_EDX_13 >> 8),1),
                 extraout_ECX_14);
    FUN_00413500(*(int **)(param_1 + 700),CONCAT31((int3)((uint)extraout_EDX_14 >> 8),1),
                 extraout_ECX_15);
    FUN_00413500(*(int **)(param_1 + 0x2c0),CONCAT31((int3)((uint)extraout_EDX_15 >> 8),1),
                 extraout_ECX_16);
    FUN_00413500(*(int **)(param_1 + 0x2c4),CONCAT31((int3)((uint)extraout_EDX_16 >> 8),1),
                 extraout_ECX_17);
    FUN_00413500(*(int **)(param_1 + 0x2c8),CONCAT31((int3)((uint)extraout_EDX_17 >> 8),1),
                 extraout_ECX_18);
    FUN_00413500(*(int **)(param_1 + 0x2f0),CONCAT31((int3)((uint)extraout_EDX_18 >> 8),1),
                 extraout_ECX_19);
    FUN_00413500(*(int **)(param_1 + 0x2f4),CONCAT31((int3)((uint)extraout_EDX_19 >> 8),1),
                 extraout_ECX_20);
    FUN_00413500(*(int **)(param_1 + 0x2f8),CONCAT31((int3)((uint)extraout_EDX_20 >> 8),1),
                 extraout_ECX_21);
    FUN_00413500(*(int **)(param_1 + 0x2fc),CONCAT31((int3)((uint)extraout_EDX_21 >> 8),1),
                 extraout_ECX_22);
    FUN_00413500(*(int **)(param_1 + 0x300),CONCAT31((int3)((uint)extraout_EDX_22 >> 8),1),
                 extraout_ECX_23);
    FUN_00413500(*(int **)(param_1 + 0x304),CONCAT31((int3)((uint)extraout_EDX_23 >> 8),1),
                 extraout_ECX_24);
    FUN_00413500(*(int **)(param_1 + 0x308),CONCAT31((int3)((uint)extraout_EDX_24 >> 8),1),
                 extraout_ECX_25);
    FUN_00413500(*(int **)(param_1 + 0x290),CONCAT31((int3)((uint)extraout_EDX_25 >> 8),1),
                 extraout_ECX_26);
    (**(code **)(**(int **)(param_1 + 0x290) + 0x80))();
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_00481986;
  puStack_1c = (undefined *)0x48197e;
  FUN_004034dc((int *)&local_8);
  return;
}

