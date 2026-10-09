/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 004610c4.
 * Inferred types and shared tails require assembly review. */

void FUN_004610c4(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int *piVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  int iVar8;
  int *piVar9;
  undefined4 auStack_1c [4];
  
  bVar7 = 0;
  if (DAT_0048c5d0 < 0) {
    DAT_0048c5d0 = DAT_0048c5d0 + 0xf;
  }
  if (0xe < DAT_0048c5d0) {
    DAT_0048c5d0 = DAT_0048c5d0 + -0xf;
  }
  if ((&original_hero.hero_orb)[DAT_0048c5d0] == 0) {
    if (param_2 == 0) {
      DAT_0048c5d0 = DAT_0048c5d0 + -3;
    }
    else if (param_2 == 1) {
      DAT_0048c5d0 = DAT_0048c5d0 + 3;
    }
    else if (param_2 == 2) {
      DAT_0048c5d0 = DAT_0048c5d0 + 1;
    }
    else if (param_2 == 3) {
      DAT_0048c5d0 = DAT_0048c5d0 + -1;
    }
    if (DAT_0048c5d0 < 0) {
      DAT_0048c5d0 = DAT_0048c5d0 + 0xf;
    }
    if (0xe < DAT_0048c5d0) {
      DAT_0048c5d0 = DAT_0048c5d0 + -0xf;
    }
    if ((&original_hero.hero_orb)[DAT_0048c5d0] == 0) {
      if (param_2 == 0) {
        DAT_0048c5d0 = DAT_0048c5d0 + -3;
      }
      else if (param_2 == 1) {
        DAT_0048c5d0 = DAT_0048c5d0 + 3;
      }
      else if (param_2 == 2) {
        DAT_0048c5d0 = DAT_0048c5d0 + 1;
      }
      else if (param_2 == 3) {
        DAT_0048c5d0 = DAT_0048c5d0 + -1;
      }
      if (DAT_0048c5d0 < 0) {
        DAT_0048c5d0 = DAT_0048c5d0 + 0xf;
      }
      if (0xe < DAT_0048c5d0) {
        DAT_0048c5d0 = DAT_0048c5d0 + -0xf;
      }
      if ((&original_hero.hero_orb)[DAT_0048c5d0] == 0) {
        if (param_2 == 0) {
          DAT_0048c5d0 = DAT_0048c5d0 + -3;
        }
        else if (param_2 == 1) {
          DAT_0048c5d0 = DAT_0048c5d0 + 3;
        }
        else if (param_2 == 2) {
          DAT_0048c5d0 = DAT_0048c5d0 + 1;
        }
        else if (param_2 == 3) {
          DAT_0048c5d0 = DAT_0048c5d0 + -1;
        }
        if (DAT_0048c5d0 < 0) {
          DAT_0048c5d0 = DAT_0048c5d0 + 0xf;
        }
        if (0xe < DAT_0048c5d0) {
          DAT_0048c5d0 = DAT_0048c5d0 + -0xf;
        }
        if ((&original_hero.hero_orb)[DAT_0048c5d0] == 0) {
          if (param_2 == 0) {
            DAT_0048c5d0 = DAT_0048c5d0 + -3;
          }
          else if (param_2 == 1) {
            DAT_0048c5d0 = DAT_0048c5d0 + 3;
          }
          else if (param_2 == 2) {
            DAT_0048c5d0 = DAT_0048c5d0 + 1;
          }
          else if (param_2 == 3) {
            DAT_0048c5d0 = DAT_0048c5d0 + -1;
          }
          if (DAT_0048c5d0 < 0) {
            DAT_0048c5d0 = DAT_0048c5d0 + 0xf;
          }
          if (0xe < DAT_0048c5d0) {
            DAT_0048c5d0 = DAT_0048c5d0 + -0xf;
          }
        }
      }
    }
  }
  if (original_hero.hero_orb + original_hero.wisdom_orb + original_hero.flight_orb +
      original_hero.cross + original_hero.elixir + original_hero.mattock + original_hero.bomb +
      original_hero.warp_staff + original_hero.ascent_wing + original_hero.descent_wing +
      original_hero.dragon_slayer + original_hero.snow_crystal + original_hero.magic_key +
      original_hero.super_mattock + original_hero.lucky_gold != 0) {
    FUN_0046171c();
    switch(DAT_0048c5d0) {
    case 0:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x24));
      break;
    case 1:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x1ec) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x1ec) + 0x24));
      break;
    case 2:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x1dc) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x1dc) + 0x24));
      break;
    case 3:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 600) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 600) + 0x24));
      break;
    case 4:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x25c) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x25c) + 0x24));
      break;
    case 5:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x260) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x260) + 0x24));
      break;
    case 6:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x264) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x264) + 0x24));
      break;
    case 7:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x268) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x268) + 0x24));
      break;
    case 8:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x26c) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x26c) + 0x24));
      break;
    case 9:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x270) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x270) + 0x24));
      break;
    case 10:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x274) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x274) + 0x24));
      break;
    case 0xb:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x278) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x278) + 0x24));
      break;
    case 0xc:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x27c) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x27c) + 0x24));
      break;
    case 0xd:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x280) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x280) + 0x24));
      break;
    case 0xe:
      FUN_004130b8(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x284) + 0x28));
      FUN_00413098(*(int **)(param_1 + 0x3f8),*(undefined4 *)(*(int *)(param_1 + 0x284) + 0x24));
    }
    (**(code **)(*DAT_0048c524 + 0x28))
              (DAT_0048c524,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c524 + 0x2c))
              (DAT_0048c524,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    iVar1 = FUN_0041dad8((int)DAT_0048c524);
    *(undefined4 *)(iVar1 + 0x20) = 0xcc0020;
    uVar2 = (**(code **)(*DAT_0048c524 + 0x1c))();
    (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,uVar2);
    uVar2 = (**(code **)(*DAT_0048c524 + 0x20))();
    (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar2);
    iVar1 = FUN_0041dad8((int)DAT_0048c520);
    *(undefined4 *)(iVar1 + 0x20) = 0xcc0020;
    uVar2 = (**(code **)(*DAT_0048c524 + 0x1c))();
    (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,uVar2);
    uVar2 = (**(code **)(*DAT_0048c524 + 0x20))();
    (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,uVar2);
    iVar1 = FUN_0041dad8((int)DAT_0048c51c);
    *(undefined4 *)(iVar1 + 0x20) = 0xcc0020;
    iVar8 = 0;
    iVar1 = 0xa2;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar1,iVar8);
    iVar8 = 0;
    iVar1 = DAT_0048c5d0 + 0x23;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar1,iVar8);
    iVar8 = 0;
    iVar1 = DAT_0048c5d0 + 0x23;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,iVar1,iVar8);
    FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_1c,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar5 = auStack_1c;
    puVar6 = &DAT_0048c53c;
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
      puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
    }
    puVar5 = &DAT_0048c53c;
    puVar6 = &DAT_0048c52c;
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
      puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
    }
    FUN_0044439c();
    piVar9 = &DAT_0048c53c;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    piVar4 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_0041a530(piVar4,&DAT_0048c53c,piVar3,piVar9);
    iVar8 = 0;
    iVar1 = 0xa4;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar1,iVar8);
    iVar8 = 0;
    iVar1 = 0x9e;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,iVar1,iVar8);
    FUN_0044439c();
    FUN_0041c160(*(int *)(*(int *)(param_1 + 0x3f8) + 0xac),DAT_0048c51c);
    FUN_00413500(*(int **)(param_1 + 0x3f8),CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX
                );
    FUN_00410378(*(int **)(param_1 + 0x474),0);
  }
  return;
}

