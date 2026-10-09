/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00450880.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00450880(int param_1)

{
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
  undefined4 extraout_ECX_27;
  undefined4 extraout_ECX_28;
  undefined4 extraout_ECX_29;
  undefined4 extraout_ECX_30;
  undefined4 extraout_ECX_31;
  undefined4 uVar1;
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
  undefined4 uVar2;
  
  if (original_hero.hero_orb != 2) {
    if ((*(char *)(*(int *)(param_1 + 0x350) + 0x28) == '\x01') &&
       (*(char *)(*(int *)(param_1 + 0x41c) + 0x20) == '\0')) {
      FUN_0041353c(*(int **)(param_1 + 0x450),'\x01');
      FUN_00413500(*(int **)(param_1 + 0x450),CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                   extraout_ECX);
      FUN_0041353c(*(int **)(param_1 + 0x454),'\x01');
      FUN_00413500(*(int **)(param_1 + 0x454),CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                   extraout_ECX_00);
      FUN_0041353c(*(int **)(param_1 + 0x458),'\x01');
      FUN_00413500(*(int **)(param_1 + 0x458),CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                   extraout_ECX_01);
      FUN_0041353c(*(int **)(param_1 + 0x45c),'\x01');
      FUN_00413500(*(int **)(param_1 + 0x45c),CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                   extraout_ECX_02);
    }
    if (*(char *)(*(int *)(param_1 + 0x354) + 0x28) == '\x01') {
      *(undefined *)(DAT_0048c510 + 0x118) = 1;
    }
    if (original_hero.hero_orb == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x254),'\x01');
      FUN_00410378(*(int **)(param_1 + 0x338),1);
      uVar1 = extraout_ECX_03;
    }
    else {
      FUN_00410378(*(int **)(param_1 + 0x338),0);
      FUN_00413500(*(int **)(param_1 + 0x254),0,extraout_ECX_04);
      uVar1 = extraout_ECX_05;
    }
    if (original_hero.wisdom_orb == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x1ec),'\x01');
      uVar1 = extraout_ECX_06;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x1ec),0,uVar1);
      uVar1 = extraout_ECX_07;
    }
    if (original_hero.flight_orb == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x1dc),'\x01');
      uVar1 = extraout_ECX_08;
      uVar2 = extraout_EDX_03;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x1dc),0,uVar1);
      uVar1 = extraout_ECX_09;
      uVar2 = extraout_EDX_04;
    }
    if (original_hero.cross == 1) {
      FUN_00413500(*(int **)(param_1 + 600),CONCAT31((int3)((uint)uVar2 >> 8),1),uVar1);
      uVar1 = extraout_ECX_10;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 600),0,uVar1);
      uVar1 = extraout_ECX_11;
    }
    if (original_hero.elixir == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x25c),'\x01');
      uVar1 = extraout_ECX_12;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x25c),0,uVar1);
      uVar1 = extraout_ECX_13;
    }
    if (original_hero.mattock == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x260),'\x01');
      uVar1 = extraout_ECX_14;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x260),0,uVar1);
      uVar1 = extraout_ECX_15;
    }
    if (original_hero.bomb == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x264),'\x01');
      uVar1 = extraout_ECX_16;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x264),0,uVar1);
      uVar1 = extraout_ECX_17;
    }
    if (original_hero.warp_staff < 1) {
      FUN_00413500(*(int **)(param_1 + 0x268),0,uVar1);
      uVar1 = extraout_ECX_19;
    }
    else {
      FUN_0041353c(*(int **)(param_1 + 0x268),'\x01');
      uVar1 = extraout_ECX_18;
    }
    if (original_hero.ascent_wing == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x26c),'\x01');
      uVar1 = extraout_ECX_20;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x26c),0,uVar1);
      uVar1 = extraout_ECX_21;
    }
    if (original_hero.descent_wing == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x270),'\x01');
      uVar1 = extraout_ECX_22;
      uVar2 = extraout_EDX_05;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x270),0,uVar1);
      uVar1 = extraout_ECX_23;
      uVar2 = extraout_EDX_06;
    }
    if (original_hero.dragon_slayer == 1) {
      FUN_00413500(*(int **)(param_1 + 0x274),CONCAT31((int3)((uint)uVar2 >> 8),1),uVar1);
      uVar1 = extraout_ECX_24;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x274),0,uVar1);
      uVar1 = extraout_ECX_25;
    }
    if (original_hero.snow_crystal == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x278),'\x01');
      uVar1 = extraout_ECX_26;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x278),0,uVar1);
      uVar1 = extraout_ECX_27;
    }
    if (original_hero.magic_key == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x27c),'\x01');
      uVar1 = extraout_ECX_28;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x27c),0,uVar1);
      uVar1 = extraout_ECX_29;
    }
    if (original_hero.super_mattock == 1) {
      FUN_0041353c(*(int **)(param_1 + 0x280),'\x01');
      uVar1 = extraout_ECX_30;
      uVar2 = extraout_EDX_07;
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x280),0,uVar1);
      uVar1 = extraout_ECX_31;
      uVar2 = extraout_EDX_08;
    }
    if (original_hero.lucky_gold == 1) {
      FUN_00413500(*(int **)(param_1 + 0x284),CONCAT31((int3)((uint)uVar2 >> 8),1),uVar1);
    }
    else {
      FUN_00413500(*(int **)(param_1 + 0x284),0,uVar1);
    }
    _DAT_0048c5ca = 1;
    FUN_00410378(*(int **)(param_1 + 0x400),1);
    FUN_00410378(*(int **)(param_1 + 0x334),1);
    FUN_00410378(*(int **)(param_1 + 0x328),1);
  }
  return;
}

