/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00478f0c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00478f0c(int param_1)

{
  dword dVar1;
  int iVar2;
  int extraout_ECX;
  int extraout_ECX_00;
  int *piVar3;
  int *piVar4;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  uint uVar5;
  int iVar6;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_164;
  code *pcStack_160;
  uint **ppuVar7;
  undefined4 uStack_158;
  code *pcStack_154;
  undefined *puStack_150;
  uint *local_140;
  undefined4 *local_13c;
  uint *local_138;
  int local_134;
  int local_130;
  int local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  int local_11c;
  int local_118;
  int local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  int local_104;
  int local_100;
  int local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  int local_ec;
  int local_e8;
  int local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  int local_d4;
  int local_d0;
  int local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  int local_8c;
  int local_88;
  int local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  int local_74;
  int local_70;
  int local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  int local_5c;
  int local_58;
  int local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  int local_44 [4];
  undefined4 local_34;
  undefined4 local_30;
  int local_2c [4];
  undefined4 local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  puStack_150 = &stack0xfffffffc;
  local_140 = (uint *)0x0;
  local_138 = (uint *)0x0;
  local_13c = (undefined4 *)0x0;
  pcStack_154 = thunk_FUN_00403140;
  uStack_158 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_158;
  local_8 = param_1;
  FUN_004135d4(*(int **)(param_1 + 0x1d0),(uint *)&DAT_0047bd48);
  FUN_00419e4c(*(int **)(*(int *)(local_8 + 0x1cc) + 0x44),(uint)DAT_00489b9d);
  if (original_hero._360_4_ != 0) {
    FUN_00431188(*(int **)(local_8 + 0x2d8),extraout_EDX,extraout_ECX);
    original_hero._360_4_ = 0xc;
    FUN_0047c2bc(local_8,extraout_EDX_00,extraout_ECX_00);
  }
  original_hero._56_4_ = original_hero._56_4_ + 1;
  scratch_index = 0;
  if (original_hero.floor < 0x1a) {
    if (original_hero.floor == 0x19) {
      iVar2 = original_hero.cycle_factor_minus_one + 1;
      uVar5 = original_hero.attack + iVar2 * -0xf0;
      iVar6 = (int)uVar5 >> 1;
      if (iVar6 < 0) {
        iVar6 = iVar6 + (uint)((uVar5 & 1) != 0);
      }
      scratch_index =
           (original_hero.hp + iVar2 * -3000) / 400 + 0x3c + iVar6 +
           (original_hero.defense + iVar2 * -300) / 3 + original_hero.yellow_keys +
           original_hero.blue_keys * 2 + original_hero.red_keys * 3;
    }
    else if (original_hero.floor == 10) {
      scratch_index =
           (original_hero.hp + (original_hero.cycle_factor_minus_one + 1) * -400) / 0x32 + 0x3c +
           original_hero.attack * 3 + (original_hero.cycle_factor_minus_one + 1) * -0x9d +
           original_hero.defense * 2 + original_hero.yellow_keys + original_hero.blue_keys * 2 +
           original_hero.red_keys * 3;
    }
    else if (original_hero.floor == 0x14) {
      scratch_index =
           (original_hero.hp + (original_hero.cycle_factor_minus_one + 1) * -800) / 100 + 0x3c +
           original_hero.attack * 2 + (original_hero.cycle_factor_minus_one + 1) * -0xe4 +
           original_hero.defense + original_hero.yellow_keys + original_hero.blue_keys * 2 +
           original_hero.red_keys * 3;
    }
  }
  else if (original_hero.floor == 0x28) {
    iVar2 = original_hero.cycle_factor_minus_one + 1;
    uVar5 = original_hero.defense + iVar2 * -0xc6;
    iVar6 = (int)uVar5 >> 1;
    if (iVar6 < 0) {
      iVar6 = iVar6 + (uint)((uVar5 & 1) != 0);
    }
    scratch_index =
         (original_hero.hp + iVar2 * -0x640) / 200 + 0x3c + original_hero.attack + iVar2 * -0x98 +
         iVar6 + original_hero.yellow_keys + original_hero.blue_keys * 2 +
         original_hero.red_keys * 3;
  }
  else if (original_hero.floor == 0x31) {
    uVar5 = original_hero.attack + (original_hero.cycle_factor_minus_one + 1) * -0xf0;
    iVar2 = (int)uVar5 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar5 & 1) != 0);
    }
    scratch_index =
         (original_hero.hp + (original_hero.cycle_factor_minus_one + 1) * -3000) / 400 + 0x3c +
         iVar2 + (original_hero.defense + (original_hero.cycle_factor_minus_one + 1) * -300) / 3 +
         original_hero.yellow_keys + original_hero.blue_keys * 2 + original_hero.red_keys * 3;
  }
  if ((int)scratch_index < 0) {
    scratch_index = 0;
  }
  original_hero._340_4_ = scratch_index;
  original_hero._344_4_ = 0;
  local_14 = 0;
  if (original_hero.floor < 0x1a) {
    if (original_hero.floor == 0x19) {
      local_14 = 3;
      piVar4 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
      (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_138);
      FUN_0040369c((int *)&DAT_0048c5d4,local_138,(undefined4 *)"\\option3.dat");
    }
    else if (original_hero.floor == 10) {
      local_14 = 1;
      piVar4 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
      (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_138);
      FUN_0040369c((int *)&DAT_0048c5d4,local_138,(undefined4 *)"\\option1.dat");
    }
    else if (original_hero.floor == 0x14) {
      local_14 = 2;
      piVar4 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
      (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_138);
      FUN_0040369c((int *)&DAT_0048c5d4,local_138,(undefined4 *)"\\option2.dat");
    }
  }
  else if (original_hero.floor == 0x28) {
    local_14 = 4;
    piVar4 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_138);
    FUN_0040369c((int *)&DAT_0048c5d4,local_138,(undefined4 *)"\\option4.dat");
  }
  else if (original_hero.floor == 0x31) {
    local_14 = 5;
    piVar4 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_138);
    FUN_0040369c((int *)&DAT_0048c5d4,local_138,(undefined4 *)"\\option5.dat");
  }
  pcStack_160 = thunk_FUN_00402f4c;
  uStack_164 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_164;
  FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
  FUN_0040458d((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
  FUN_00402710();
  FUN_004041f0((HANDLE *)&DAT_0048c600,&local_134,0x120,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048c600);
  FUN_00402710();
  local_10 = 0;
  local_c = 10;
  piVar4 = &local_134;
  do {
    iVar6 = 0;
    iVar2 = 4;
    piVar3 = piVar4;
    do {
      iVar6 = iVar6 + *piVar3;
      piVar3 = piVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (iVar6 != piVar4[4]) {
      local_10 = 1;
    }
    iVar6 = 0;
    iVar2 = 1;
    piVar3 = piVar4;
    do {
      switch(iVar2) {
      case 1:
      case 3:
      case 5:
        iVar6 = iVar6 + *piVar3;
        break;
      case 2:
      case 4:
        iVar6 = iVar6 - *piVar3;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar2 != 6);
    if (iVar6 != piVar4[5]) {
      local_10 = 1;
    }
    piVar4 = piVar4 + 6;
    local_c = local_c + -1;
  } while (local_c != 0);
  local_c = 1;
  piVar4 = &local_134;
  do {
    iVar6 = 0;
    iVar2 = 10;
    piVar3 = piVar4;
    do {
      iVar6 = iVar6 + *piVar3;
      piVar3 = piVar3 + 6;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (iVar6 != piVar4[0x3c]) {
      local_10 = 1;
    }
    iVar6 = 0;
    iVar2 = 1;
    piVar3 = piVar4;
    do {
      switch(iVar2) {
      case 1:
      case 3:
      case 5:
      case 7:
      case 9:
      case 0xb:
        iVar6 = iVar6 + *piVar3;
        break;
      case 2:
      case 4:
      case 6:
      case 8:
      case 10:
        iVar6 = iVar6 - *piVar3;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 6;
    } while (iVar2 != 0xc);
    if ((local_c != 6) && (iVar6 != piVar4[0x42])) {
      local_10 = 1;
    }
    local_c = local_c + 1;
    piVar4 = piVar4 + 1;
  } while (local_c != 7);
  if ((local_10 == 0) && (local_18 / 100 != original_hero._628_4_)) {
    local_10 = 2;
  }
  if ((local_10 == 0) && (original_hero._628_4_ * -100 + local_18 != -local_14)) {
    local_10 = 2;
  }
  if ((local_10 == 1) || (local_10 == 2)) {
    if (local_10 == 1) {
      FUN_0042cf78((uint *)"Ranking data is abnormal. Use a temporary Ranking.");
    }
    else if (local_10 == 2) {
      FUN_0042cf78((uint *)"Version of Ranking data is abnormal. Use a temporary Ranking.");
    }
    switch(local_14) {
    case 1:
      local_134 = 100;
      local_130 = 500;
      local_12c = 0x19;
      local_128 = 0x19;
      local_124 = 0;
      local_120 = 0;
      local_11c = 0x5a;
      local_118 = 0x1c2;
      local_114 = 0x18;
      local_110 = 0x18;
      local_10c = 0;
      local_108 = 0;
      local_104 = 0x50;
      local_100 = 400;
      local_fc = 0x17;
      local_f8 = 0x17;
      local_f4 = 0;
      local_f0 = 0;
      local_ec = 0x46;
      local_e8 = 0x15e;
      local_e4 = 0x16;
      local_e0 = 0x16;
      local_dc = 0;
      local_d8 = 0;
      local_d4 = 0x3c;
      local_d0 = 300;
      local_cc = 0x15;
      local_c8 = 0x15;
      local_c4 = 0;
      local_c0 = 0;
      local_bc = 0x32;
      local_b8 = 0xfa;
      local_b4 = 0x14;
      local_b0 = 0x14;
      local_ac = 0;
      local_a8 = 0;
      local_a4 = 0x28;
      local_a0 = 200;
      local_9c = 0x13;
      local_98 = 0x13;
      local_94 = 0;
      local_90 = 0;
      local_8c = 0x1e;
      local_88 = 0x96;
      local_84 = 0x12;
      local_80 = 0x12;
      local_7c = 0;
      local_78 = 0;
      local_74 = 0x14;
      local_70 = 100;
      local_6c = 0x11;
      local_68 = 0x11;
      local_64 = 0;
      local_60 = 0;
      local_5c = 10;
      local_58 = 0x32;
      local_54 = 0x10;
      local_50 = 0x10;
      local_4c = 0;
      local_48 = 0;
      local_44[0] = 0;
      local_44[1] = 0;
      local_44[2] = 0;
      local_44[3] = 0;
      local_34 = 0;
      local_30 = 0;
      local_2c[0] = 0;
      local_2c[1] = 0;
      local_2c[2] = 0;
      local_2c[3] = 0;
      local_1c = 0;
      local_18 = 0;
      break;
    case 2:
      local_134 = 100;
      local_130 = 1000;
      local_12c = 0x32;
      local_128 = 0x32;
      local_124 = 0;
      local_120 = 0;
      local_11c = 0x5a;
      local_118 = 900;
      local_114 = 0x2d;
      local_110 = 0x2d;
      local_10c = 0;
      local_108 = 0;
      local_104 = 0x50;
      local_100 = 800;
      local_fc = 0x28;
      local_f8 = 0x28;
      local_f4 = 0;
      local_f0 = 0;
      local_ec = 0x46;
      local_e8 = 700;
      local_e4 = 0x23;
      local_e0 = 0x23;
      local_dc = 0;
      local_d8 = 0;
      local_d4 = 0x3c;
      local_d0 = 600;
      local_cc = 0x1e;
      local_c8 = 0x1e;
      local_c4 = 0;
      local_c0 = 0;
      local_bc = 0x32;
      local_b8 = 500;
      local_b4 = 0x19;
      local_b0 = 0x19;
      local_ac = 0;
      local_a8 = 0;
      local_a4 = 0x28;
      local_a0 = 400;
      local_9c = 0x14;
      local_98 = 0x14;
      local_94 = 0;
      local_90 = 0;
      local_8c = 0x1e;
      local_88 = 300;
      local_84 = 0xf;
      local_80 = 0xf;
      local_7c = 0;
      local_78 = 0;
      local_74 = 0x14;
      local_70 = 200;
      local_6c = 10;
      local_68 = 10;
      local_64 = 0;
      local_60 = 0;
      local_5c = 10;
      local_58 = 100;
      local_54 = 5;
      local_50 = 5;
      local_4c = 0;
      local_48 = 0;
      local_44[0] = 0;
      local_44[1] = 0;
      local_44[2] = 0;
      local_44[3] = 0;
      local_34 = 0;
      local_30 = 0;
      local_2c[0] = 0;
      local_2c[1] = 0;
      local_2c[2] = 0;
      local_2c[3] = 0;
      local_1c = 0;
      local_18 = 0;
      break;
    case 3:
    case 5:
      local_134 = 100;
      local_130 = 10000;
      local_12c = 500;
      local_128 = 500;
      local_124 = 0;
      local_120 = 0;
      local_11c = 0x5a;
      local_118 = 9000;
      local_114 = 0x1c2;
      local_110 = 0x1c2;
      local_10c = 0;
      local_108 = 0;
      local_104 = 0x50;
      local_100 = 8000;
      local_fc = 400;
      local_f8 = 400;
      local_f4 = 0;
      local_f0 = 0;
      local_ec = 0x46;
      local_e8 = 7000;
      local_e4 = 0x15e;
      local_e0 = 0x15e;
      local_dc = 0;
      local_d8 = 0;
      local_d4 = 0x3c;
      local_d0 = 6000;
      local_cc = 300;
      local_c8 = 300;
      local_c4 = 0;
      local_c0 = 0;
      local_bc = 0x32;
      local_b8 = 5000;
      local_b4 = 0xfa;
      local_b0 = 0xfa;
      local_ac = 0;
      local_a8 = 0;
      local_a4 = 0x28;
      local_a0 = 4000;
      local_9c = 200;
      local_98 = 200;
      local_94 = 0;
      local_90 = 0;
      local_8c = 0x1e;
      local_88 = 3000;
      local_84 = 0x96;
      local_80 = 0x96;
      local_7c = 0;
      local_78 = 0;
      local_74 = 0x14;
      local_70 = 2000;
      local_6c = 100;
      local_68 = 100;
      local_64 = 0;
      local_60 = 0;
      local_5c = 10;
      local_58 = 1000;
      local_54 = 0x32;
      local_50 = 0x32;
      local_4c = 0;
      local_48 = 0;
      local_44[0] = 0;
      local_44[1] = 0;
      local_44[2] = 0;
      local_44[3] = 0;
      local_34 = 0;
      local_30 = 0;
      local_2c[0] = 0;
      local_2c[1] = 0;
      local_2c[2] = 0;
      local_2c[3] = 0;
      local_1c = 0;
      local_18 = 0;
      break;
    case 4:
      local_134 = 100;
      local_130 = 5000;
      local_12c = 200;
      local_128 = 200;
      local_124 = 0;
      local_120 = 0;
      local_11c = 0x5a;
      local_118 = 0x1194;
      local_114 = 0xbe;
      local_110 = 0xbe;
      local_10c = 0;
      local_108 = 0;
      local_104 = 0x50;
      local_100 = 4000;
      local_fc = 0xb4;
      local_f8 = 0xb4;
      local_f4 = 0;
      local_f0 = 0;
      local_ec = 0x46;
      local_e8 = 0xdac;
      local_e4 = 0xaa;
      local_e0 = 0xaa;
      local_dc = 0;
      local_d8 = 0;
      local_d4 = 0x3c;
      local_d0 = 3000;
      local_cc = 0xa0;
      local_c8 = 0xa0;
      local_c4 = 0;
      local_c0 = 0;
      local_bc = 0x32;
      local_b8 = 0x9c4;
      local_b4 = 0x96;
      local_b0 = 0x96;
      local_ac = 0;
      local_a8 = 0;
      local_a4 = 0x28;
      local_a0 = 2000;
      local_9c = 0x8c;
      local_98 = 0x8c;
      local_94 = 0;
      local_90 = 0;
      local_8c = 0x1e;
      local_88 = 0x5dc;
      local_84 = 0x82;
      local_80 = 0x82;
      local_7c = 0;
      local_78 = 0;
      local_74 = 0x14;
      local_70 = 1000;
      local_6c = 0x78;
      local_68 = 0x78;
      local_64 = 0;
      local_60 = 0;
      local_5c = 10;
      local_58 = 500;
      local_54 = 0x6e;
      local_50 = 0x6e;
      local_4c = 0;
      local_48 = 0;
      local_44[0] = 0;
      local_44[1] = 0;
      local_44[2] = 0;
      local_44[3] = 0;
      local_34 = 0;
      local_30 = 0;
      local_2c[0] = 0;
      local_2c[1] = 0;
      local_2c[2] = 0;
      local_2c[3] = 0;
      local_1c = 0;
      local_18 = 0;
    }
  }
  *in_FS_OFFSET = uStack_164;
  if (original_hero._340_4_ == local_134 || original_hero._340_4_ - local_134 < 0) {
    if ((original_hero._340_4_ == local_134) &&
       (original_hero.hp != local_130 && -1 < original_hero.hp - local_130)) {
      original_hero._344_4_ = 1;
    }
    else if ((original_hero._340_4_ == local_134) &&
            ((original_hero.hp == local_130 &&
             (iVar2 = (original_hero.attack + original_hero.defense) - local_130,
             iVar2 != local_12c && -1 < iVar2 - local_12c)))) {
      original_hero._344_4_ = 1;
    }
    else if (original_hero._340_4_ == local_11c || original_hero._340_4_ - local_11c < 0) {
      if ((original_hero._340_4_ == local_11c) &&
         (original_hero.hp != local_118 && -1 < original_hero.hp - local_118)) {
        original_hero._344_4_ = 2;
      }
      else if ((original_hero._340_4_ == local_11c) &&
              ((original_hero.hp == local_118 &&
               (iVar2 = (original_hero.attack + original_hero.defense) - local_118,
               iVar2 != local_114 && -1 < iVar2 - local_114)))) {
        original_hero._344_4_ = 2;
      }
      else if (original_hero._340_4_ == local_104 || original_hero._340_4_ - local_104 < 0) {
        if ((original_hero._340_4_ == local_104) &&
           (original_hero.hp != local_100 && -1 < original_hero.hp - local_100)) {
          original_hero._344_4_ = 3;
        }
        else if ((original_hero._340_4_ == local_104) &&
                ((original_hero.hp == local_100 &&
                 (iVar2 = (original_hero.attack + original_hero.defense) - local_100,
                 iVar2 != local_fc && -1 < iVar2 - local_fc)))) {
          original_hero._344_4_ = 3;
        }
        else if (original_hero._340_4_ == local_ec || original_hero._340_4_ - local_ec < 0) {
          if ((original_hero._340_4_ == local_ec) &&
             (original_hero.hp != local_e8 && -1 < original_hero.hp - local_e8)) {
            original_hero._344_4_ = 4;
          }
          else if ((original_hero._340_4_ == local_ec) &&
                  ((original_hero.hp == local_e8 &&
                   (iVar2 = (original_hero.attack + original_hero.defense) - local_e8,
                   iVar2 != local_e4 && -1 < iVar2 - local_e4)))) {
            original_hero._344_4_ = 4;
          }
          else if (original_hero._340_4_ == local_d4 || original_hero._340_4_ - local_d4 < 0) {
            if ((original_hero._340_4_ == local_d4) &&
               (original_hero.hp != local_d0 && -1 < original_hero.hp - local_d0)) {
              original_hero._344_4_ = 5;
            }
            else if ((original_hero._340_4_ == local_d4) &&
                    ((original_hero.hp == local_d0 &&
                     (iVar2 = (original_hero.attack + original_hero.defense) - local_d0,
                     iVar2 != local_cc && -1 < iVar2 - local_cc)))) {
              original_hero._344_4_ = 5;
            }
            else if (original_hero._340_4_ == local_bc || original_hero._340_4_ - local_bc < 0) {
              if ((original_hero._340_4_ == local_bc) &&
                 (original_hero.hp != local_b8 && -1 < original_hero.hp - local_b8)) {
                original_hero._344_4_ = 6;
              }
              else if ((original_hero._340_4_ == local_bc) &&
                      ((original_hero.hp == local_b8 &&
                       (iVar2 = (original_hero.attack + original_hero.defense) - local_b8,
                       iVar2 != local_b4 && -1 < iVar2 - local_b4)))) {
                original_hero._344_4_ = 6;
              }
              else if (original_hero._340_4_ == local_a4 || original_hero._340_4_ - local_a4 < 0) {
                if ((original_hero._340_4_ == local_a4) &&
                   (original_hero.hp != local_a0 && -1 < original_hero.hp - local_a0)) {
                  original_hero._344_4_ = 7;
                }
                else if ((original_hero._340_4_ == local_a4) &&
                        ((original_hero.hp == local_a0 &&
                         (iVar2 = (original_hero.attack + original_hero.defense) - local_a0,
                         iVar2 != local_9c && -1 < iVar2 - local_9c)))) {
                  original_hero._344_4_ = 7;
                }
                else if (original_hero._340_4_ == local_8c || original_hero._340_4_ - local_8c < 0)
                {
                  if ((original_hero._340_4_ == local_8c) &&
                     (original_hero.hp != local_88 && -1 < original_hero.hp - local_88)) {
                    original_hero._344_4_ = 8;
                  }
                  else if ((original_hero._340_4_ == local_8c) &&
                          ((original_hero.hp == local_88 &&
                           (iVar2 = (original_hero.attack + original_hero.defense) - local_88,
                           iVar2 != local_84 && -1 < iVar2 - local_84)))) {
                    original_hero._344_4_ = 8;
                  }
                  else if (original_hero._340_4_ == local_74 || original_hero._340_4_ - local_74 < 0
                          ) {
                    if ((original_hero._340_4_ == local_74) &&
                       (original_hero.hp != local_70 && -1 < original_hero.hp - local_70)) {
                      original_hero._344_4_ = 9;
                    }
                    else if ((original_hero._340_4_ == local_74) &&
                            ((original_hero.hp == local_70 &&
                             (iVar2 = (original_hero.attack + original_hero.defense) - local_70,
                             iVar2 != local_6c && -1 < iVar2 - local_6c)))) {
                      original_hero._344_4_ = 9;
                    }
                    else if (original_hero._340_4_ == local_5c ||
                             original_hero._340_4_ - local_5c < 0) {
                      if ((original_hero._340_4_ == local_5c) &&
                         (original_hero.hp != local_58 && -1 < original_hero.hp - local_58)) {
                        original_hero._344_4_ = 10;
                      }
                      else if ((original_hero._340_4_ == local_5c) &&
                              ((original_hero.hp == local_58 &&
                               (iVar2 = (original_hero.attack + original_hero.defense) - local_58,
                               iVar2 != local_54 && -1 < iVar2 - local_54)))) {
                        original_hero._344_4_ = 10;
                      }
                    }
                    else {
                      original_hero._344_4_ = 10;
                    }
                  }
                  else {
                    original_hero._344_4_ = 9;
                  }
                }
                else {
                  original_hero._344_4_ = 8;
                }
              }
              else {
                original_hero._344_4_ = 7;
              }
            }
            else {
              original_hero._344_4_ = 6;
            }
          }
          else {
            original_hero._344_4_ = 5;
          }
        }
        else {
          original_hero._344_4_ = 4;
        }
      }
      else {
        original_hero._344_4_ = 3;
      }
    }
    else {
      original_hero._344_4_ = 2;
    }
  }
  else {
    original_hero._344_4_ = 1;
  }
  if (original_hero.floor < 0x1a) {
    if (original_hero.floor == 0x19) {
      original_hero._348_4_ = 3;
    }
    else if (original_hero.floor == 10) {
      original_hero._348_4_ = 1;
    }
    else if (original_hero.floor == 0x14) {
      original_hero._348_4_ = 2;
    }
  }
  else if (original_hero.floor == 0x28) {
    original_hero._348_4_ = 4;
  }
  else if (original_hero.floor == 0x31) {
    original_hero._348_4_ = 5;
  }
  piVar4 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
  (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_138);
  FUN_0040369c((int *)&DAT_0048c5d4,local_138,(undefined4 *)"\\save0.dat");
  FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
  FUN_004045a4((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
  FUN_00402710();
  pcStack_160 = (code *)0x47adf7;
  FUN_00404254((HANDLE *)&DAT_0048c600,original_maps,0x1881,(uint *)0x0);
  FUN_00402710();
  pcStack_160 = (code *)0x47ae12;
  FUN_00404254((HANDLE *)&DAT_0048c600,&original_hero,0x2ac,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048c600);
  FUN_00402710();
  tile_class_or_message = 1;
  if ((int)original_hero._344_4_ < 1) {
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    (**(code **)(*piVar4 + 0xc))(piVar4,0xdc,&local_138);
    FUN_00403658((int *)&local_138,(undefined4 *)&LAB_0047bea8);
    ppuVar7 = &local_138;
    pcStack_160 = (code *)0x47afd7;
    FUN_00405b6c(scratch_index,(int *)&local_13c);
    FUN_00403658((int *)ppuVar7,local_13c);
    FUN_00403658((int *)&local_138,(undefined4 *)&LAB_0047bea8);
    ppuVar7 = &local_138;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b019;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xdd,&local_13c);
    FUN_00403658((int *)ppuVar7,local_13c);
    FUN_004135d4(*(int **)(local_8 + 0x1cc),local_138);
  }
  else {
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    (**(code **)(*piVar4 + 0xc))(piVar4,0xf4,&local_138);
    FUN_00403658((int *)&local_138,(undefined4 *)&LAB_0047bea8);
    ppuVar7 = &local_138;
    pcStack_160 = (code *)0x47ae83;
    FUN_00405b6c(original_hero._344_4_,(int *)&local_13c);
    FUN_00403658((int *)ppuVar7,local_13c);
    FUN_00403658((int *)&local_138,(undefined4 *)&LAB_0047bea8);
    ppuVar7 = &local_138;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47aec5;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xf5,&local_13c);
    FUN_00403658((int *)ppuVar7,local_13c);
    ppuVar7 = &local_138;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47aef7;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xdc,&local_13c);
    FUN_00403658((int *)ppuVar7,local_13c);
    FUN_00403658((int *)&local_138,(undefined4 *)&LAB_0047bea8);
    ppuVar7 = &local_138;
    pcStack_160 = (code *)0x47af2a;
    FUN_00405b6c(original_hero._340_4_,(int *)&local_13c);
    FUN_00403658((int *)ppuVar7,local_13c);
    FUN_00403658((int *)&local_138,(undefined4 *)&LAB_0047bea8);
    ppuVar7 = &local_138;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47af6c;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xdd,&local_13c);
    FUN_00403658((int *)ppuVar7,local_13c);
    FUN_004135d4(*(int **)(local_8 + 0x1cc),local_138);
  }
  if ((int)scratch_index < 100) {
    if (scratch_index < 0x32) {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b0ea;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xde,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    }
    else if (scratch_index - 0x32 < 10) {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b149;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xdf,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    }
    else if (scratch_index - 0x3c < 0x14) {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b1a8;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xe0,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    }
    else if (scratch_index - 0x50 < 0x14) {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b207;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xe1,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    }
  }
  else if ((int)scratch_index < 0x8d) {
    if (scratch_index - 100 < 0x15) {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b266;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xe2,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b298;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xe4,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b2ca;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xe5,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b2fc;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xea,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
      if ((int)original_hero._56_4_ < 4) {
        FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
        ppuVar7 = &local_140;
        piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
        pcStack_160 = (code *)0x47b35f;
        (**(code **)(*piVar4 + 0xc))(piVar4,0xeb,&local_138);
        FUN_00403658((int *)ppuVar7,local_138);
        FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
      }
      else {
        FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
        ppuVar7 = &local_140;
        piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
        pcStack_160 = (code *)0x47b3be;
        (**(code **)(*piVar4 + 0xc))(piVar4,0xec,&local_138);
        FUN_00403658((int *)ppuVar7,local_138);
        FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
      }
    }
    else if (scratch_index - 0x79 < 0x14) {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b41d;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xe2,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b44f;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xe4,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b481;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xe6,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b4b3;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xea,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
      if ((int)original_hero._56_4_ < 4) {
        FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
        ppuVar7 = &local_140;
        piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
        pcStack_160 = (code *)0x47b516;
        (**(code **)(*piVar4 + 0xc))(piVar4,0xeb,&local_138);
        FUN_00403658((int *)ppuVar7,local_138);
        FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
      }
      else {
        FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
        ppuVar7 = &local_140;
        piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
        pcStack_160 = (code *)0x47b575;
        (**(code **)(*piVar4 + 0xc))(piVar4,0xec,&local_138);
        FUN_00403658((int *)ppuVar7,local_138);
        FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
      }
    }
  }
  else if (scratch_index - 0x8d < 0x14) {
    FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b5d4;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xe3,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b606;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xe4,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b638;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xe7,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b66a;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xea,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    if ((int)original_hero._56_4_ < 4) {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b6cd;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xeb,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    }
    else {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b72c;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xec,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    }
  }
  else if (scratch_index - 0xa1 < 0x28) {
    FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b78b;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xe3,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b7bd;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xe4,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b7ef;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xe8,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b821;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xea,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    if ((int)original_hero._56_4_ < 4) {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b884;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xeb,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    }
    else {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47b8e3;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xec,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    }
  }
  else if (scratch_index - 0xc9 < 0x2647) {
    FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b942;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xe3,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b974;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xe4,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b9a6;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xe9,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    ppuVar7 = &local_140;
    piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
    pcStack_160 = (code *)0x47b9d8;
    (**(code **)(*piVar4 + 0xc))(piVar4,0xea,&local_138);
    FUN_00403658((int *)ppuVar7,local_138);
    FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    if ((int)original_hero._56_4_ < 4) {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47ba3b;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xeb,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    }
    else {
      FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_140);
      ppuVar7 = &local_140;
      piVar4 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      pcStack_160 = (code *)0x47ba97;
      (**(code **)(*piVar4 + 0xc))(piVar4,0xec,&local_138);
      FUN_00403658((int *)ppuVar7,local_138);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_140);
    }
  }
  if (original_hero._360_4_ != 0) {
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 0xf;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
  }
  event_cursor = event_cursor + 1;
  dVar1 = event_cursor;
  event_stack[event_cursor].opcode = 6;
  if (original_hero.floor < 0x1a) {
    if (original_hero.floor == 0x19) {
      event_stack[dVar1].a = 0x47;
      DAT_0048c5c8 = 0x18;
    }
    else if (original_hero.floor == 10) {
      event_stack[dVar1].a = 0x1b;
      DAT_0048c5c8 = 0x10;
    }
    else if (original_hero.floor == 0x14) {
      event_stack[dVar1].a = 0x31;
      DAT_0048c5c8 = 0x16;
    }
  }
  else if (original_hero.floor == 0x28) {
    event_stack[dVar1].a = 0x3c;
    DAT_0048c5c8 = 0x28;
  }
  else if (original_hero.floor == 0x31) {
    event_stack[dVar1].a = 0x10;
    DAT_0048c5c8 = 0x2f;
  }
  event_stack[dVar1].b = 6;
  event_cursor = event_cursor + 1;
  dVar1 = event_cursor;
  event_stack[event_cursor].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  event_cursor = event_cursor + 1;
  dVar1 = event_cursor;
  event_stack[event_cursor].opcode = 1;
  event_stack[dVar1].a = 2;
  event_stack[dVar1].b = 0;
  event_cursor = event_cursor + 1;
  dVar1 = event_cursor;
  event_stack[event_cursor].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  event_cursor = event_cursor + 1;
  dVar1 = event_cursor;
  event_stack[event_cursor].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  event_cursor = event_cursor + 1;
  dVar1 = event_cursor;
  event_stack[event_cursor].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  event_cursor = event_cursor + 1;
  dVar1 = event_cursor;
  event_stack[event_cursor].opcode = 10;
  event_stack[dVar1].a = DAT_0048c5c8;
  event_stack[dVar1].b = 0;
  event_cursor = event_cursor + 1;
  dVar1 = event_cursor;
  event_stack[event_cursor].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  event_cursor = event_cursor + 1;
  dVar1 = event_cursor;
  event_stack[event_cursor].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  start_event_timer(local_8);
  *in_FS_OFFSET = uStack_158;
  puStack_150 = &LAB_0047bd37;
  pcStack_154 = (code *)0x47bd1f;
  FUN_004034dc((int *)&local_140);
  pcStack_154 = (code *)0x47bd2f;
  FUN_004034fc((int *)&local_13c,2);
  return;
}

