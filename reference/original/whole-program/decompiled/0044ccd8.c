/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044ccd8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0044ccd8(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
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
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
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
  undefined4 *puVar3;
  undefined4 *puVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 auStack_20 [4];
  
  bVar5 = 0;
  FUN_00402c34(DAT_0048c51c);
  DAT_0048c51c = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                                     extraout_ECX);
  FUN_00402c34(DAT_0048c520);
  DAT_0048c520 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                                     extraout_ECX_00);
  FUN_00402c34(DAT_0048c524);
  DAT_0048c524 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                                     extraout_ECX_01);
  (**(code **)(*DAT_0048c51c + 0x28))
            (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  (**(code **)(*DAT_0048c51c + 0x2c))
            (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  uVar1 = (**(code **)(*DAT_0048c51c + 0x1c))();
  (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,uVar1);
  uVar1 = (**(code **)(*DAT_0048c51c + 0x20))();
  (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar1);
  uVar1 = (**(code **)(*DAT_0048c51c + 0x1c))();
  (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar1);
  uVar1 = (**(code **)(*DAT_0048c51c + 0x20))();
  (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar1);
  DAT_0048c54c = 0;
  DAT_0048c550 = 0;
  door_opened = 0xa2;
  iVar8 = 0;
  iVar6 = 0xa2;
  piVar2 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,DAT_0048c54c,iVar6,iVar8);
  if (original_hero.sword != 0) {
    iVar8 = original_hero.sword + 0x31;
    iVar6 = DAT_0048c550;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,DAT_0048c54c,iVar8,iVar6);
    iVar8 = original_hero.sword + 0x31;
    iVar6 = DAT_0048c550;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x40c),piVar2,DAT_0048c54c,iVar8,iVar6);
    FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar3 = auStack_20;
    puVar4 = &DAT_0048c53c;
    for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
      puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    }
    puVar3 = &DAT_0048c53c;
    puVar4 = &DAT_0048c52c;
    for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
      puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    }
    FUN_0044439c();
  }
  FUN_0041c160(*(int *)(*(int *)(param_1 + 0x288) + 0xac),DAT_0048c51c);
  switch(original_hero.sword) {
  case 0:
    FUN_004135d4(*(int **)(param_1 + 1000),(uint *)"      ");
    FUN_004136ac(*(int **)(param_1 + 0x288),'\0');
    break;
  case 1:
    FUN_004135d4(*(int **)(param_1 + 1000),(uint *)&DAT_0044d8e8);
    FUN_0040352c((int *)(*(int *)(param_1 + 0x288) + 0x54),(undefined4 *)"Iron Sword");
    FUN_004136ac(*(int **)(param_1 + 0x288),'\x01');
    break;
  case 2:
    FUN_004135d4(*(int **)(param_1 + 1000),(uint *)"Silver");
    FUN_0040352c((int *)(*(int *)(param_1 + 0x288) + 0x54),(undefined4 *)"Silver Sword");
    FUN_004136ac(*(int **)(param_1 + 0x288),'\x01');
    break;
  case 3:
    FUN_004135d4(*(int **)(param_1 + 1000),(uint *)"Knight");
    FUN_0040352c((int *)(*(int *)(param_1 + 0x288) + 0x54),(undefined4 *)"Knight Sword");
    FUN_004136ac(*(int **)(param_1 + 0x288),'\x01');
    break;
  case 4:
    FUN_004135d4(*(int **)(param_1 + 1000),(uint *)&DAT_0044d95c);
    FUN_0040352c((int *)(*(int *)(param_1 + 0x288) + 0x54),(undefined4 *)"Holy Sword");
    FUN_004136ac(*(int **)(param_1 + 0x288),'\x01');
    break;
  case 5:
    FUN_004135d4(*(int **)(param_1 + 1000),(uint *)"Sacred");
    FUN_0040352c((int *)(*(int *)(param_1 + 0x288) + 0x54),(undefined4 *)"Sacred Sword");
    FUN_004136ac(*(int **)(param_1 + 0x288),'\x01');
  }
  door_opened = 0xa2;
  iVar8 = 0xa2;
  iVar6 = DAT_0048c550;
  piVar2 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,DAT_0048c54c,iVar8,iVar6);
  if (original_hero.shield != 0) {
    iVar8 = original_hero.shield + 0x36;
    iVar6 = DAT_0048c550;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,DAT_0048c54c,iVar8,iVar6);
    iVar8 = original_hero.shield + 0x36;
    iVar6 = DAT_0048c550;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x40c),piVar2,DAT_0048c54c,iVar8,iVar6);
    FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar3 = auStack_20;
    puVar4 = &DAT_0048c53c;
    for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
      puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    }
    puVar3 = &DAT_0048c53c;
    puVar4 = &DAT_0048c52c;
    for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
      puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    }
    FUN_0044439c();
  }
  FUN_0041c160(*(int *)(*(int *)(param_1 + 0x28c) + 0xac),DAT_0048c51c);
  switch(original_hero.shield) {
  case 0:
    FUN_004135d4(*(int **)(param_1 + 0x3ec),(uint *)"      ");
    FUN_004136ac(*(int **)(param_1 + 0x28c),'\0');
    break;
  case 1:
    FUN_004135d4(*(int **)(param_1 + 0x3ec),(uint *)&DAT_0044d8e8);
    FUN_0040352c((int *)(*(int *)(param_1 + 0x28c) + 0x54),(undefined4 *)"Iron Shield");
    FUN_004136ac(*(int **)(param_1 + 0x28c),'\x01');
    break;
  case 2:
    FUN_004135d4(*(int **)(param_1 + 0x3ec),(uint *)"Silver");
    FUN_0040352c((int *)(*(int *)(param_1 + 0x28c) + 0x54),(undefined4 *)"Silver Shield");
    FUN_004136ac(*(int **)(param_1 + 0x28c),'\x01');
    break;
  case 3:
    FUN_004135d4(*(int **)(param_1 + 0x3ec),(uint *)"Knight");
    FUN_0040352c((int *)(*(int *)(param_1 + 0x28c) + 0x54),(undefined4 *)"Knight Shield");
    FUN_004136ac(*(int **)(param_1 + 0x28c),'\x01');
    break;
  case 4:
    FUN_004135d4(*(int **)(param_1 + 0x3ec),(uint *)&DAT_0044d95c);
    FUN_0040352c((int *)(*(int *)(param_1 + 0x28c) + 0x54),(undefined4 *)"Holy Shield");
    FUN_004136ac(*(int **)(param_1 + 0x28c),'\x01');
    break;
  case 5:
    FUN_004135d4(*(int **)(param_1 + 0x3ec),(uint *)"Sacred");
    FUN_0040352c((int *)(*(int *)(param_1 + 0x28c) + 0x54),(undefined4 *)"Sacred Shield");
    FUN_004136ac(*(int **)(param_1 + 0x28c),'\x01');
  }
  iVar6 = 0;
  do {
    iVar8 = 0;
    do {
      door_opened = iVar6 + iVar8 * 3 + 0x24;
      iVar9 = 0;
      iVar7 = 0xa2;
      piVar2 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar7,iVar9);
      if ((&original_hero.hero_orb)[iVar8 * 3 + iVar6] != 0) {
        iVar9 = 0;
        iVar7 = door_opened - 1;
        piVar2 = (int *)FUN_0041dad8((int)DAT_0048c520);
        FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar7,iVar9);
        iVar9 = 0;
        iVar7 = door_opened - 1;
        piVar2 = (int *)FUN_0041dad8((int)DAT_0048c524);
        FUN_00417e44(*(int **)(param_1 + 0x40c),piVar2,0,iVar7,iVar9);
        FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
                     *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
        puVar3 = auStack_20;
        puVar4 = &DAT_0048c53c;
        for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
          puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
        }
        puVar3 = &DAT_0048c53c;
        puVar4 = &DAT_0048c52c;
        for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
          puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
        }
        FUN_0044439c();
      }
      switch(iVar8) {
      case 0:
        if (iVar6 == 0) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x254) + 0xac),DAT_0048c51c);
          if ((&original_hero.hero_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x254),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x254),CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                         extraout_ECX_02);
            FUN_004136ac(*(int **)(param_1 + 0x254),'\x01');
          }
        }
        else if (iVar6 == 1) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x1ec) + 0xac),DAT_0048c51c);
          if ((&original_hero.wisdom_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x1ec),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x1ec),CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                         extraout_ECX_03);
            FUN_004136ac(*(int **)(param_1 + 0x1ec),'\x01');
          }
        }
        else if (iVar6 == 2) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x1dc) + 0xac),DAT_0048c51c);
          if ((&original_hero.flight_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x1dc),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x1dc),CONCAT31((int3)((uint)extraout_EDX_04 >> 8),1),
                         extraout_ECX_04);
            FUN_004136ac(*(int **)(param_1 + 0x1dc),'\x01');
          }
        }
        break;
      case 1:
        if (iVar6 == 0) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 600) + 0xac),DAT_0048c51c);
          if ((&original_hero.hero_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 600),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 600),CONCAT31((int3)((uint)extraout_EDX_05 >> 8),1),
                         extraout_ECX_05);
            FUN_004136ac(*(int **)(param_1 + 600),'\x01');
          }
        }
        else if (iVar6 == 1) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x25c) + 0xac),DAT_0048c51c);
          if ((&original_hero.wisdom_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x25c),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x25c),CONCAT31((int3)((uint)extraout_EDX_06 >> 8),1),
                         extraout_ECX_06);
            FUN_004136ac(*(int **)(param_1 + 0x25c),'\x01');
          }
        }
        else if (iVar6 == 2) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x260) + 0xac),DAT_0048c51c);
          if ((&original_hero.flight_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x260),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x260),CONCAT31((int3)((uint)extraout_EDX_07 >> 8),1),
                         extraout_ECX_07);
            FUN_004136ac(*(int **)(param_1 + 0x260),'\x01');
          }
        }
        break;
      case 2:
        if (iVar6 == 0) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x264) + 0xac),DAT_0048c51c);
          if ((&original_hero.hero_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x264),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x264),CONCAT31((int3)((uint)extraout_EDX_08 >> 8),1),
                         extraout_ECX_08);
            FUN_004136ac(*(int **)(param_1 + 0x264),'\x01');
          }
        }
        else if (iVar6 == 1) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x268) + 0xac),DAT_0048c51c);
          if ((&original_hero.wisdom_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x268),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x268),CONCAT31((int3)((uint)extraout_EDX_09 >> 8),1),
                         extraout_ECX_09);
            FUN_004136ac(*(int **)(param_1 + 0x268),'\x01');
          }
        }
        else if (iVar6 == 2) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x26c) + 0xac),DAT_0048c51c);
          if ((&original_hero.flight_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x26c),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x26c),CONCAT31((int3)((uint)extraout_EDX_10 >> 8),1),
                         extraout_ECX_10);
            FUN_004136ac(*(int **)(param_1 + 0x26c),'\x01');
          }
        }
        break;
      case 3:
        if (iVar6 == 0) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x270) + 0xac),DAT_0048c51c);
          if ((&original_hero.hero_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x270),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x270),CONCAT31((int3)((uint)extraout_EDX_11 >> 8),1),
                         extraout_ECX_11);
            FUN_004136ac(*(int **)(param_1 + 0x270),'\x01');
          }
        }
        else if (iVar6 == 1) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x274) + 0xac),DAT_0048c51c);
          if ((&original_hero.wisdom_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x274),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x274),CONCAT31((int3)((uint)extraout_EDX_12 >> 8),1),
                         extraout_ECX_12);
            FUN_004136ac(*(int **)(param_1 + 0x274),'\x01');
          }
        }
        else if (iVar6 == 2) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x278) + 0xac),DAT_0048c51c);
          if ((&original_hero.flight_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x278),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x278),CONCAT31((int3)((uint)extraout_EDX_13 >> 8),1),
                         extraout_ECX_13);
            FUN_004136ac(*(int **)(param_1 + 0x278),'\x01');
          }
        }
        break;
      case 4:
        if (iVar6 == 0) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x27c) + 0xac),DAT_0048c51c);
          if ((&original_hero.hero_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x27c),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x27c),CONCAT31((int3)((uint)extraout_EDX_14 >> 8),1),
                         extraout_ECX_14);
            FUN_004136ac(*(int **)(param_1 + 0x27c),'\x01');
          }
        }
        else if (iVar6 == 1) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x280) + 0xac),DAT_0048c51c);
          if ((&original_hero.wisdom_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x280),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x280),CONCAT31((int3)((uint)extraout_EDX_15 >> 8),1),
                         extraout_ECX_15);
            FUN_004136ac(*(int **)(param_1 + 0x280),'\x01');
          }
        }
        else if (iVar6 == 2) {
          FUN_0041c160(*(int *)(*(int *)(param_1 + 0x284) + 0xac),DAT_0048c51c);
          if ((&original_hero.flight_orb)[iVar8 * 3] == 0) {
            FUN_004136ac(*(int **)(param_1 + 0x284),'\0');
          }
          else {
            FUN_00413500(*(int **)(param_1 + 0x284),CONCAT31((int3)((uint)extraout_EDX_16 >> 8),1),
                         extraout_ECX_16);
            FUN_004136ac(*(int **)(param_1 + 0x284),'\x01');
          }
        }
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 != 5);
    iVar6 = iVar6 + 1;
  } while (iVar6 != 3);
  return;
}

