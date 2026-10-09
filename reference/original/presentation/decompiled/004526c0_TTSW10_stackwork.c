/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 004526c0.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004526c0(int *param_1)

{
  longlong lVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  int extraout_ECX_08;
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
  undefined4 extraout_ECX_32;
  undefined4 extraout_ECX_33;
  undefined4 extraout_ECX_34;
  undefined4 extraout_ECX_35;
  undefined4 extraout_ECX_36;
  undefined4 extraout_ECX_37;
  undefined4 extraout_ECX_38;
  undefined4 extraout_ECX_39;
  undefined4 extraout_ECX_40;
  undefined4 extraout_ECX_41;
  undefined4 extraout_ECX_42;
  int extraout_ECX_43;
  int extraout_ECX_44;
  int extraout_ECX_45;
  int extraout_ECX_46;
  int extraout_ECX_47;
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
  undefined4 *puVar7;
  undefined4 *puVar8;
  uint uVar9;
  undefined4 *in_FS_OFFSET;
  byte bVar10;
  int *piVar11;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined4 local_18 [4];
  uint *local_8;
  
  bVar10 = 0;
  puStack_28 = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  puStack_2c = &LAB_00454804;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  _DAT_0048c5c0 = 0;
  iVar6 = event_cursor * 3;
  switch(event_stack[event_cursor].opcode) {
  case 1:
    switch(event_stack[event_cursor].a) {
    case 1:
      if (original_hero._356_4_ == 0) {
        puStack_28 = &stack0xfffffffc;
        FUN_00431250((int *)param_1[0xb5],0);
      }
      break;
    case 2:
      if (original_hero._356_4_ == 0) {
        puStack_28 = &stack0xfffffffc;
        FUN_00431250((int *)param_1[0x118],0);
      }
      break;
    case 3:
      if (original_hero._356_4_ == 0) {
        puStack_28 = &stack0xfffffffc;
        FUN_00431250((int *)param_1[0x119],0);
      }
      break;
    case 4:
      if (original_hero._356_4_ == 0) {
        puStack_28 = &stack0xfffffffc;
        FUN_00431250((int *)param_1[0x11a],0);
      }
      break;
    case 5:
      if (original_hero._360_4_ != 0) {
        puStack_28 = &stack0xfffffffc;
        FUN_0047c2bc((int)param_1,0,iVar6);
      }
      break;
    case 6:
      if (original_hero._360_4_ != 0) {
        puStack_28 = &stack0xfffffffc;
        FUN_00431188((int *)param_1[0xb6],0,iVar6);
      }
      break;
    case 7:
      if (original_hero._356_4_ == 0) {
        puStack_28 = &stack0xfffffffc;
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_8);
        FUN_0040369c((int *)(param_1[0x11b] + 0x20c),local_8,(undefined4 *)"\\wav\\3f.wav");
        FUN_00430f20((int *)param_1[0x11b],extraout_EDX,extraout_ECX);
        FUN_00431250((int *)param_1[0x11b],extraout_EDX_00);
      }
      break;
    case 8:
      if (original_hero._356_4_ == 0) {
        puStack_28 = &stack0xfffffffc;
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_8);
        FUN_0040369c((int *)(param_1[0x11b] + 0x20c),local_8,(undefined4 *)"\\wav\\20f.wav");
        FUN_00430f20((int *)param_1[0x11b],extraout_EDX_01,extraout_ECX_00);
        FUN_00431250((int *)param_1[0x11b],extraout_EDX_02);
      }
      break;
    case 9:
      if (original_hero._356_4_ == 0) {
        puStack_28 = &stack0xfffffffc;
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_8);
        FUN_0040369c((int *)(param_1[0x11b] + 0x20c),local_8,(undefined4 *)"\\wav\\kai.wav");
        FUN_00430f20((int *)param_1[0x11b],extraout_EDX_03,extraout_ECX_01);
        FUN_00431250((int *)param_1[0x11b],extraout_EDX_04);
      }
      break;
    case 10:
      if (original_hero._356_4_ == 0) {
        puStack_28 = &stack0xfffffffc;
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_8);
        FUN_0040369c((int *)(param_1[0x11b] + 0x20c),local_8,(undefined4 *)"\\wav\\kai2.wav");
        FUN_00430f20((int *)param_1[0x11b],extraout_EDX_05,extraout_ECX_02);
        FUN_00431250((int *)param_1[0x11b],extraout_EDX_06);
      }
    }
    break;
  case 2:
    if (event_stack[event_cursor].a != 0) {
      tile_class_or_message = (dword)(short)event_stack[event_cursor].a;
    }
    puStack_28 = &stack0xfffffffc;
    FUN_0044cb34((int)param_1);
    break;
  case 3:
    iVar4 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                     original_hero.y * 0xb + original_hero.x) - 1;
    iVar6 = DAT_0048c550;
    puStack_28 = &stack0xfffffffc;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
    DAT_0048c5a8 = (uint)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                                  original_hero.y * 0xb + original_hero.x);
    FUN_00454c10();
    iVar4 = (*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                      original_hero.y * 0xb + original_hero.x) - 1) + door_opened;
    iVar6 = DAT_0048c550;
    piVar5 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
    if (original_hero._360_4_ != 0) {
      FUN_00431188((int *)param_1[0xb6],extraout_EDX_07,extraout_ECX_03);
      original_hero._360_4_ = 0xe;
      FUN_0047c2bc((int)param_1,extraout_EDX_08,extraout_ECX_04);
    }
    FUN_0042c454(param_1[0xbb],'\0');
    _DAT_0048c5c0 = 1;
    original_hero._48_4_ = 1;
    dialogue_continue_stage = 9;
    DAT_0048c5a0 = 0x1e;
    FUN_00449e18((int)param_1);
    break;
  case 4:
    scratch_index =
         original_hero.defense -
         original_monsters[monster_index].attack * (original_hero.cycle_factor_minus_one + 1);
    if (0 < (int)scratch_index) {
      scratch_index = 0;
    }
    original_hero.hp = original_hero.hp + scratch_index;
    if (original_hero.hp < 0) {
      original_hero.hp = 0;
    }
    puStack_28 = &stack0xfffffffc;
    FUN_00405b6c(original_hero.hp,(int *)&local_8);
    FUN_004135d4((int *)param_1[0xf2],local_8);
    break;
  case 5:
    neighbor_index = 0;
    if (monster_index - 0xc < 2) {
      if (original_hero.cross == 1) {
        neighbor_index = 1;
      }
    }
    else if (monster_index == 0x11) {
      if (original_hero.cross == 1) {
        neighbor_index = 1;
      }
    }
    else if ((monster_index == 0x13) && (original_hero.dragon_slayer == 1)) {
      neighbor_index = 1;
    }
    if (neighbor_index == 0) {
      scratch_index =
           original_monsters[monster_index].defense * (original_hero.cycle_factor_minus_one + 1) -
           original_hero.attack;
    }
    else if (neighbor_index == 1) {
      scratch_index =
           original_monsters[monster_index].defense * (original_hero.cycle_factor_minus_one + 1) +
           original_hero.attack * -2;
    }
    if (0 < (int)scratch_index) {
      scratch_index = 0;
    }
    DAT_0048c5bc = DAT_0048c5bc + scratch_index;
    if (DAT_0048c5bc < 0) {
      DAT_0048c5bc = 0;
    }
    puStack_28 = &stack0xfffffffc;
    FUN_00405b6c(DAT_0048c5bc,(int *)&local_8);
    FUN_004135d4((int *)param_1[0xf6],local_8);
    break;
  case 6:
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = *(undefined *)&event_stack[event_cursor].b;
    iVar4 = (int)(short)event_stack[event_cursor].a % 0xb +
            ((int)(short)event_stack[event_cursor].a / 0xb) * 0xb;
    DAT_0048c54c = (iVar4 * *(int *)(param_1[0x95] + 0x2c)) % (*(int *)(param_1[0x95] + 0x2c) * 0xb)
    ;
    iVar6 = *(int *)(param_1[0x95] + 0x30);
    DAT_0048c550 = ((iVar4 * iVar6) / (iVar6 * 0xb)) * iVar6;
    iVar4 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                     (int)(short)event_stack[event_cursor].a) - 1;
    iVar6 = DAT_0048c550;
    puStack_28 = &stack0xfffffffc;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
    DAT_0048c5a8 = (uint)(short)event_stack[event_cursor].b;
    FUN_00454c10();
    iVar4 = (*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                      (int)(short)event_stack[event_cursor].a) - 1) + door_opened;
    iVar6 = DAT_0048c550;
    piVar5 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
    piVar5 = DAT_0048c514;
    piVar3 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar3,DAT_0048c578,DAT_0048c57c,piVar5);
    break;
  case 7:
    original_hero.gold =
         original_hero.gold +
         (int)(short)event_stack[event_cursor].a * (original_hero.lucky_gold + 1);
    puStack_28 = &stack0xfffffffc;
    FUN_0044cb34((int)param_1);
    break;
  case 8:
    puStack_28 = &stack0xfffffffc;
    FUN_00413500((int *)param_1[0x6f],1,iVar6);
    FUN_00413500((int *)param_1[0x70],CONCAT31((int3)((uint)extraout_EDX_09 >> 8),1),extraout_ECX_05
                );
    FUN_0044bed8((int)param_1,extraout_EDX_10,extraout_ECX_06);
    FUN_0044ccd8((int)param_1);
    break;
  case 9:
    puStack_28 = &stack0xfffffffc;
    FUN_0040923c(0,0,*(undefined4 *)(param_1[0x95] + 0x2c),local_18,
                 *(undefined4 *)(param_1[0x95] + 0x30));
    puVar7 = local_18;
    puVar8 = &DAT_0048c53c;
    for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar10 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
    }
    puVar7 = &DAT_0048c53c;
    puVar8 = &DAT_0048c52c;
    for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar10 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
    }
    (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,*(undefined4 *)(param_1[0x95] + 0x30));
    (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,*(undefined4 *)(param_1[0x95] + 0x2c));
    uVar2 = (**(code **)(*DAT_0048c51c + 0x1c))();
    (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,uVar2);
    uVar2 = (**(code **)(*DAT_0048c51c + 0x20))();
    (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar2);
    uVar2 = (**(code **)(*DAT_0048c51c + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar2);
    uVar2 = (**(code **)(*DAT_0048c51c + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar2);
    iVar6 = FUN_0041dad8((int)DAT_0048c51c);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    iVar6 = FUN_0041dad8((int)DAT_0048c520);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    iVar6 = FUN_0041dad8((int)DAT_0048c524);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    iVar4 = 0;
    iVar6 = (short)event_stack[event_cursor].b + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    iVar4 = 0;
    iVar6 = *(short *)(&DAT_0048c748 + event_cursor * 6) + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    iVar4 = 0;
    iVar6 = *(short *)(&DAT_0048c74a + event_cursor * 6) + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    FUN_0044439c();
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) * *(int *)(param_1[0x95] + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) * *(int *)(param_1[0x95] + 0x30);
    piVar5 = DAT_0048c51c;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar3,DAT_0048c54c,DAT_0048c550,piVar5);
    iVar4 = 0;
    iVar6 = (short)event_stack[event_cursor].b + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    DAT_0048c5a8 = (uint)*(short *)(&DAT_0048c748 + event_cursor * 6);
    FUN_00454c10();
    iVar4 = 0;
    iVar6 = *(short *)(&DAT_0048c748 + event_cursor * 6) + -1 + door_opened;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    DAT_0048c5a8 = (uint)*(short *)(&DAT_0048c74a + event_cursor * 6);
    FUN_00454c10();
    iVar4 = 0;
    iVar6 = *(short *)(&DAT_0048c74a + event_cursor * 6) + -1 + door_opened;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    FUN_0044439c();
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) * *(int *)(param_1[0x95] + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) * *(int *)(param_1[0x95] + 0x30);
    piVar5 = DAT_0048c51c;
    piVar3 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar3,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar3 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar3,DAT_0048c578,DAT_0048c57c,piVar5);
    break;
  case 10:
    puStack_28 = &stack0xfffffffc;
    FUN_0042c454(param_1[0xbb],'\0');
    _DAT_0048c5c0 = 1;
    DAT_0048c5c8 = event_stack[event_cursor].a;
    dialogue_continue_stage = (int)(short)DAT_0048c5c8 + 10;
    FUN_00449e18((int)param_1);
    break;
  case 0xb:
    switch(event_stack[event_cursor].a) {
    case 1:
      event_cursor = event_cursor - 1;
      puStack_28 = &stack0xfffffffc;
      FUN_004653b8((int)param_1,0,iVar6);
      event_cursor = event_cursor + 1;
      break;
    case 2:
      event_cursor = event_cursor - 1;
      scratch_index = 0x1b;
      original_maps[original_hero.floor][0x1d] = 0x5b;
      puStack_28 = &stack0xfffffffc;
      FUN_00461a0c((int)param_1);
      event_cursor = event_cursor + 1;
      break;
    case 3:
      event_cursor = event_cursor - 1;
      puStack_28 = &stack0xfffffffc;
      FUN_00462560((int)param_1);
      event_cursor = event_cursor + 1;
      break;
    case 4:
      scratch_index = (dword)(short)event_stack[event_cursor].b;
      if (DAT_00489ba4 == '\x01') {
        iVar6 = scratch_index * 5;
        if (iVar6 < 0) {
          iVar6 = iVar6 + 3;
        }
        scratch_index = iVar6 >> 2;
      }
      door_opened = 0;
      puStack_28 = &stack0xfffffffc;
      FUN_0047c978((int)param_1);
      DAT_0048c54c = *(int *)(param_1[0x95] + 0x2c) << 2;
      DAT_0048c550 = *(int *)(param_1[0x95] + 0x30) << 2;
      piVar5 = DAT_0048c51c;
      piVar3 = (int *)FUN_0041dad8((int)DAT_0048c514);
      FUN_0041a5b8(piVar3,DAT_0048c54c,DAT_0048c550,piVar5);
      door_opened = 1;
      FUN_0047c978((int)param_1);
      DAT_0048c54c = *(int *)(param_1[0x95] + 0x2c) << 2;
      DAT_0048c550 = *(int *)(param_1[0x95] + 0x30) << 2;
      piVar5 = DAT_0048c51c;
      piVar3 = (int *)FUN_0041dad8(DAT_0048c518);
      FUN_0041a5b8(piVar3,DAT_0048c54c,DAT_0048c550,piVar5);
      piVar5 = DAT_0048c514;
      piVar3 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a5b8(piVar3,DAT_0048c578,DAT_0048c57c,piVar5);
      (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,*(undefined4 *)(param_1[0x95] + 0x30));
      (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,*(undefined4 *)(param_1[0x95] + 0x2c));
      iVar6 = FUN_0041dad8((int)DAT_0048c51c);
      *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
      iVar6 = FUN_0041dad8((int)DAT_0048c520);
      *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
      iVar6 = FUN_0041dad8((int)DAT_0048c524);
      *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
      break;
    case 5:
      event_cursor = event_cursor - 1;
      puStack_28 = &stack0xfffffffc;
      moncheck(param_1);
      event_cursor = event_cursor + 1;
      break;
    case 6:
      puStack_28 = &stack0xfffffffc;
      FUN_004136ac((int *)param_1[0x106],'\0');
      FUN_00413500((int *)param_1[0x106],0,extraout_ECX_07);
      event_cursor = event_cursor - 1;
      if (original_hero.cycle_factor_minus_one == 0) {
        original_hero.cycle_factor_minus_one = 0x2b;
        FUN_00454da0((int)param_1);
        event_cursor = event_cursor + 1;
      }
      else {
        original_hero.later_cycle = 1;
        FUN_00454da0((int)param_1);
        event_cursor = event_cursor + 1;
      }
      break;
    case 7:
      puStack_28 = &stack0xfffffffc;
      if (original_hero._360_4_ != 0) {
        puStack_28 = &stack0xfffffffc;
        FUN_00431188((int *)param_1[0xb6],0,iVar6);
        original_hero._360_4_ = 0xb;
        FUN_0047c2bc((int)param_1,extraout_EDX_11,extraout_ECX_08);
      }
      FUN_0042c454(param_1[0x6d],'\0');
      (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,*(int *)(param_1[0x95] + 0x30) * 0xb);
      (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,*(int *)(param_1[0x95] + 0x2c) * 0xb);
      uVar2 = (**(code **)(*DAT_0048c51c + 0x1c))();
      (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,uVar2);
      uVar2 = (**(code **)(*DAT_0048c51c + 0x20))();
      (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar2);
      uVar2 = (**(code **)(*DAT_0048c51c + 0x1c))();
      (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar2);
      uVar2 = (**(code **)(*DAT_0048c51c + 0x20))();
      (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar2);
      iVar6 = FUN_0041dad8((int)DAT_0048c51c);
      *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
      iVar6 = FUN_0041dad8((int)DAT_0048c520);
      *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
      iVar6 = FUN_0041dad8((int)DAT_0048c524);
      *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
      if (original_hero.cycle_factor_minus_one == 0) {
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_8);
        FUN_00403658((int *)&local_8,DAT_0048c5fc);
        FUN_00403658((int *)&local_8,(undefined4 *)"\\title05.bmp");
        FUN_0041c1e8(*(int *)(param_1[0x6e] + 0xac),(int)local_8);
      }
      else {
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_8);
        FUN_00403658((int *)&local_8,DAT_0048c5fc);
        FUN_00403658((int *)&local_8,(undefined4 *)"\\title05R.bmp");
        FUN_0041c1e8(*(int *)(param_1[0x6e] + 0xac),(int)local_8);
      }
      FUN_004136ac((int *)param_1[0xa2],'\0');
      FUN_004136ac((int *)param_1[0xa3],'\0');
      break;
    case 8:
      puStack_28 = &stack0xfffffffc;
      FUN_00443648((int)param_1);
      break;
    case 9:
      puStack_28 = &stack0xfffffffc;
      FUN_004433a4((int)param_1);
      break;
    case 10:
      event_cursor = event_cursor - 1;
      puStack_28 = &stack0xfffffffc;
      FUN_0047f7d4((int)param_1);
      event_cursor = event_cursor + 1;
      break;
    case 0xb:
      DAT_0048c56c = 0;
      original_hero.floor = (int)(short)event_stack[event_cursor].b;
      puStack_28 = &stack0xfffffffc;
      FUN_00442c38((int)param_1);
      FUN_0044cb34((int)param_1);
      if (original_hero.floor == 0x32) {
        original_hero._48_4_ = 0;
        original_hero.x = (uint)original_maps[50][0] % 0xb;
        original_hero.y = original_maps[50][0] / 0xb;
        DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
        DAT_0048c54c = (*(int *)(param_1[0x95] + 0x2c) * DAT_0048c580) %
                       (*(int *)(param_1[0x95] + 0x2c) * 0xb);
        iVar6 = *(int *)(param_1[0x95] + 0x30);
        DAT_0048c550 = ((iVar6 * DAT_0048c580) / (iVar6 * 0xb)) * iVar6;
        original_hero._352_4_ = 4;
        FUN_004433a4((int)param_1);
      }
      break;
    case 0xc:
      puStack_28 = &stack0xfffffffc;
      FUN_00482e60(param_1);
      break;
    case 0xd:
      puStack_28 = &stack0xfffffffc;
      FUN_0042c454(param_1[0x6d],'\0');
      break;
    case 0xe:
      puStack_28 = &stack0xfffffffc;
      FUN_00413500((int *)param_1[0x114],0,iVar6);
      FUN_00413500((int *)param_1[0x115],0,extraout_ECX_09);
      FUN_00413500((int *)param_1[0x116],0,extraout_ECX_10);
      FUN_00413500((int *)param_1[0x117],0,extraout_ECX_11);
      FUN_00413500((int *)param_1[0xf2],0,extraout_ECX_12);
      FUN_00413500((int *)param_1[0xf3],0,extraout_ECX_13);
      FUN_00413500((int *)param_1[0xf4],0,extraout_ECX_14);
      FUN_00413500((int *)param_1[0xf5],0,extraout_ECX_15);
      FUN_00413500((int *)param_1[0xf6],0,extraout_ECX_16);
      FUN_00413500((int *)param_1[0xf7],0,extraout_ECX_17);
      FUN_00413500((int *)param_1[0xf8],0,extraout_ECX_18);
      FUN_00413500((int *)param_1[0xf9],0,extraout_ECX_19);
      FUN_00413500((int *)param_1[0xfa],0,extraout_ECX_20);
      FUN_00413500((int *)param_1[0xfb],0,extraout_ECX_21);
      FUN_00413500((int *)param_1[0xfc],0,extraout_ECX_22);
      FUN_00413500((int *)param_1[0x111],0,extraout_ECX_23);
      uVar2 = extraout_ECX_24;
      if (*(char *)((int)(int *)param_1[0x77] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x77],0,extraout_ECX_24);
        uVar2 = extraout_ECX_25;
      }
      if (*(char *)((int)(int *)param_1[0x7b] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x7b],0,uVar2);
        uVar2 = extraout_ECX_26;
      }
      if (*(char *)((int)(int *)param_1[0x95] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x95],0,uVar2);
        uVar2 = extraout_ECX_27;
      }
      if (*(char *)(param_1[0x96] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x96],0,uVar2);
        uVar2 = extraout_ECX_28;
      }
      if (*(char *)(param_1[0x97] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x97],0,uVar2);
        uVar2 = extraout_ECX_29;
      }
      if (*(char *)(param_1[0x98] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x98],0,uVar2);
        uVar2 = extraout_ECX_30;
      }
      if (*(char *)(param_1[0x99] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x99],0,uVar2);
        uVar2 = extraout_ECX_31;
      }
      if (*(char *)(param_1[0x9a] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x9a],0,uVar2);
        uVar2 = extraout_ECX_32;
      }
      if (*(char *)(param_1[0x9b] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x9b],0,uVar2);
        uVar2 = extraout_ECX_33;
      }
      if (*(char *)(param_1[0x9c] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x9c],0,uVar2);
        uVar2 = extraout_ECX_34;
      }
      if (*(char *)(param_1[0x9d] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x9d],0,uVar2);
        uVar2 = extraout_ECX_35;
      }
      if (*(char *)(param_1[0x9e] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x9e],0,uVar2);
        uVar2 = extraout_ECX_36;
      }
      if (*(char *)(param_1[0x9f] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x9f],0,uVar2);
        uVar2 = extraout_ECX_37;
      }
      if (*(char *)(param_1[0xa0] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0xa0],0,uVar2);
        uVar2 = extraout_ECX_38;
      }
      if (*(char *)(param_1[0xa1] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0xa1],0,uVar2);
        uVar2 = extraout_ECX_39;
      }
      if (*(char *)(param_1[0xa2] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0xa2],0,uVar2);
        uVar2 = extraout_ECX_40;
      }
      if (*(char *)(param_1[0xa3] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0xa3],0,uVar2);
        uVar2 = extraout_ECX_41;
      }
      if (*(char *)(param_1[0x101] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x101],0,uVar2);
        uVar2 = extraout_ECX_42;
      }
      if (*(char *)(param_1[0x102] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x102],0,uVar2);
      }
      break;
    case 0xf:
      puStack_28 = &stack0xfffffffc;
      iVar6 = FUN_004131bc(param_1);
      iVar6 = iVar6 - *(int *)(param_1[0x72] + 0x30);
      puVar7 = local_18;
      uVar2 = FUN_00413178(param_1);
      FUN_0040923c(0,0,uVar2,puVar7,iVar6);
      puVar7 = local_18;
      puVar8 = &DAT_0048c53c;
      for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + (uint)bVar10 * -2 + 1;
        puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      }
      piVar11 = &DAT_0048c53c;
      piVar5 = (int *)FUN_00421a54(DAT_0048c510);
      piVar3 = (int *)FUN_0041dad8(DAT_0048c528);
      FUN_0041a530(piVar3,&DAT_0048c53c,piVar5,piVar11);
    }
    break;
  case 0xc:
    puStack_28 = &stack0xfffffffc;
    FUN_00480384((int)param_1);
    break;
  case 0xd:
    puStack_28 = &stack0xfffffffc;
    FUN_004770e0((int)param_1);
    break;
  case 0xe:
    puStack_28 = &stack0xfffffffc;
    FUN_0040923c(0,0,*(undefined4 *)(param_1[0x95] + 0x2c),local_18,
                 *(undefined4 *)(param_1[0x95] + 0x30));
    puVar7 = local_18;
    puVar8 = &DAT_0048c53c;
    for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar10 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
    }
    (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,*(undefined4 *)(param_1[0x95] + 0x30));
    (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,*(undefined4 *)(param_1[0x95] + 0x2c));
    uVar2 = (**(code **)(*DAT_0048c51c + 0x1c))();
    (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,uVar2);
    uVar2 = (**(code **)(*DAT_0048c51c + 0x20))();
    (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar2);
    uVar2 = (**(code **)(*DAT_0048c51c + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar2);
    uVar2 = (**(code **)(*DAT_0048c51c + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar2);
    iVar6 = FUN_0041dad8((int)DAT_0048c51c);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    iVar6 = FUN_0041dad8((int)DAT_0048c520);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    iVar6 = FUN_0041dad8((int)DAT_0048c524);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    iVar4 = 0;
    iVar6 = (short)event_stack[event_cursor].b + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    iVar4 = 0;
    iVar6 = *(short *)(&DAT_0048c748 + event_cursor * 6) + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    iVar4 = 0;
    iVar6 = *(short *)(&DAT_0048c74a + event_cursor * 6) + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    iVar6 = FUN_0041dad8((int)DAT_0048c520);
    *(undefined4 *)(iVar6 + 0x20) = 0xee0086;
    piVar11 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_0041a530(piVar3,&DAT_0048c53c,piVar5,piVar11);
    iVar6 = FUN_0041dad8((int)DAT_0048c520);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    iVar4 = 0;
    iVar6 = (short)event_stack[event_cursor].b + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    iVar6 = FUN_0041dad8((int)DAT_0048c524);
    *(undefined4 *)(iVar6 + 0x20) = 0x330008;
    piVar11 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar3,&DAT_0048c53c,piVar5,piVar11);
    iVar6 = FUN_0041dad8((int)DAT_0048c524);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    iVar6 = FUN_0041dad8((int)DAT_0048c51c);
    *(undefined4 *)(iVar6 + 0x20) = 0xee0086;
    piVar11 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_0041a530(piVar3,&DAT_0048c53c,piVar5,piVar11);
    iVar6 = FUN_0041dad8((int)DAT_0048c51c);
    *(undefined4 *)(iVar6 + 0x20) = 0x8800c6;
    piVar11 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_0041a530(piVar3,&DAT_0048c53c,piVar5,piVar11);
    iVar6 = FUN_0041dad8((int)DAT_0048c51c);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) * *(int *)(param_1[0x95] + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) * *(int *)(param_1[0x95] + 0x30);
    piVar5 = DAT_0048c51c;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar3,DAT_0048c54c,DAT_0048c550,piVar5);
    iVar4 = 0;
    iVar6 = (short)event_stack[event_cursor].b + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    DAT_0048c5a8 = (uint)*(short *)(&DAT_0048c748 + event_cursor * 6);
    FUN_00454c10();
    iVar4 = 0;
    iVar6 = *(short *)(&DAT_0048c748 + event_cursor * 6) + -1 + door_opened;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    DAT_0048c5a8 = (uint)*(short *)(&DAT_0048c74a + event_cursor * 6);
    FUN_00454c10();
    iVar4 = 0;
    iVar6 = *(short *)(&DAT_0048c74a + event_cursor * 6) + -1 + door_opened;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    iVar6 = FUN_0041dad8((int)DAT_0048c520);
    *(undefined4 *)(iVar6 + 0x20) = 0xee0086;
    piVar11 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_0041a530(piVar3,&DAT_0048c53c,piVar5,piVar11);
    iVar6 = FUN_0041dad8((int)DAT_0048c520);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    iVar4 = 0;
    iVar6 = (short)event_stack[event_cursor].b + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44((int *)param_1[0x6c],piVar5,0,iVar6,iVar4);
    iVar6 = FUN_0041dad8((int)DAT_0048c524);
    *(undefined4 *)(iVar6 + 0x20) = 0x330008;
    piVar11 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar3,&DAT_0048c53c,piVar5,piVar11);
    iVar6 = FUN_0041dad8((int)DAT_0048c524);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    iVar6 = FUN_0041dad8((int)DAT_0048c51c);
    *(undefined4 *)(iVar6 + 0x20) = 0xee0086;
    piVar11 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_0041a530(piVar3,&DAT_0048c53c,piVar5,piVar11);
    iVar6 = FUN_0041dad8((int)DAT_0048c51c);
    *(undefined4 *)(iVar6 + 0x20) = 0x8800c6;
    piVar11 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_0041a530(piVar3,&DAT_0048c53c,piVar5,piVar11);
    iVar6 = FUN_0041dad8((int)DAT_0048c51c);
    *(undefined4 *)(iVar6 + 0x20) = 0xcc0020;
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) * *(int *)(param_1[0x95] + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) * *(int *)(param_1[0x95] + 0x30);
    piVar5 = DAT_0048c51c;
    piVar3 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar3,DAT_0048c54c,DAT_0048c550,piVar5);
    scratch_index =
         original_monsters[monster_index].defense * (original_hero.cycle_factor_minus_one + 1) -
         original_hero.attack;
    if (0 < (int)scratch_index) {
      scratch_index = 0;
    }
    DAT_0048c5bc = DAT_0048c5bc + scratch_index;
    if (DAT_0048c5bc < 0) {
      DAT_0048c5bc = 0;
    }
    FUN_00405b6c(DAT_0048c5bc,(int *)&local_8);
    FUN_004135d4((int *)param_1[0xf6],local_8);
    piVar5 = DAT_0048c514;
    piVar3 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar3,DAT_0048c578,DAT_0048c57c,piVar5);
    break;
  case 0xf:
    puStack_28 = &stack0xfffffffc;
    FUN_00431188((int *)param_1[0xb6],0,iVar6);
    FUN_0047c8f8();
    FUN_0047c2bc((int)param_1,extraout_EDX_12,extraout_ECX_43);
    break;
  case 0x10:
    original_hero.hp = original_hero.hp + (short)event_stack[event_cursor].a;
    if (original_hero.hp < 0) {
      original_hero.hp = 0;
    }
    puStack_28 = &stack0xfffffffc;
    FUN_00405b6c(original_hero.hp,(int *)&local_8);
    FUN_004135d4((int *)param_1[0xf2],local_8);
    if (original_hero.hp == 0) {
      if (original_hero._360_4_ != 0) {
        FUN_00431188((int *)param_1[0xb6],extraout_EDX_13,extraout_ECX_44);
        original_hero._360_4_ = 0xe;
        FUN_0047c2bc((int)param_1,extraout_EDX_14,extraout_ECX_45);
      }
      iVar4 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                       original_hero.y * 0xb + original_hero.x) - 1;
      iVar6 = DAT_0048c550;
      piVar5 = (int *)FUN_0041dad8((int)DAT_0048c514);
      FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
      DAT_0048c5a8 = (uint)(short)event_stack[event_cursor].b;
      FUN_00454c10();
      iVar4 = (*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                        original_hero.y * 0xb + original_hero.x) - 1) + door_opened;
      iVar6 = DAT_0048c550;
      piVar5 = (int *)FUN_0041dad8(DAT_0048c518);
      FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
      _DAT_0048c5c0 = 1;
      original_hero._48_4_ = 1;
      dialogue_continue_stage = 9;
      event_cursor = 1;
      DAT_0048c5a0 = 0x1e;
      FUN_00449e18((int)param_1);
    }
    break;
  case 0x11:
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = *(undefined *)&event_stack[event_cursor].b;
    break;
  case 0x13:
    uVar9 = original_hero.hp & 1;
    original_hero.hp = original_hero.hp >> 1;
    if (original_hero.hp < 0) {
      original_hero.hp = original_hero.hp + (uint)(uVar9 != 0);
    }
    if (original_hero.hp < 0) {
      original_hero.hp = 0;
    }
    puStack_28 = &stack0xfffffffc;
    FUN_00405b6c(original_hero.hp,(int *)&local_8);
    FUN_004135d4((int *)param_1[0xf2],local_8);
    if (original_hero.hp == 0) {
      if (original_hero._360_4_ != 0) {
        FUN_00431188((int *)param_1[0xb6],extraout_EDX_15,extraout_ECX_46);
        original_hero._360_4_ = 0xe;
        FUN_0047c2bc((int)param_1,extraout_EDX_16,extraout_ECX_47);
      }
      iVar4 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                       original_hero.y * 0xb + original_hero.x) - 1;
      iVar6 = DAT_0048c550;
      piVar5 = (int *)FUN_0041dad8((int)DAT_0048c514);
      FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
      DAT_0048c5a8 = (uint)(short)event_stack[event_cursor].b;
      FUN_00454c10();
      iVar4 = (*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                        original_hero.y * 0xb + original_hero.x) - 1) + door_opened;
      iVar6 = DAT_0048c550;
      piVar5 = (int *)FUN_0041dad8(DAT_0048c518);
      FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
      _DAT_0048c5c0 = 1;
      original_hero._48_4_ = 1;
      dialogue_continue_stage = 9;
      event_cursor = 1;
      DAT_0048c5a0 = 0x1e;
      FUN_00449e18((int)param_1);
    }
    break;
  case 0x14:
    (&original_hero.hp)[(short)event_stack[event_cursor].a] =
         (int)(short)event_stack[event_cursor].b;
    break;
  case 0x15:
    DAT_0048c570 = (int)(short)event_stack[event_cursor].b;
    uVar9 = (uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3);
    DAT_0048c54c = (int)(uVar9 * *(int *)(param_1[0x95] + 0x2c)) %
                   (*(int *)(param_1[0x95] + 0x2c) * 0xb);
    iVar6 = *(int *)(param_1[0x95] + 0x30);
    lVar1 = (longlong)((int)(uVar9 * iVar6) / (iVar6 * 0xb)) * (longlong)iVar6;
    DAT_0048c550 = (int)lVar1;
    if (event_stack[event_cursor].a == 0) {
      puStack_28 = &stack0xfffffffc;
      if ((original_hero._356_4_ == 0) && (puStack_28 = &stack0xfffffffc, DAT_0048c570 == 1)) {
        puStack_28 = &stack0xfffffffc;
        FUN_00431250((int *)param_1[0xb5],(int)((ulonglong)lVar1 >> 0x20));
      }
      iVar6 = DAT_0048c57c + DAT_0048c550;
      iVar4 = 0x9e;
      piVar5 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c578 + DAT_0048c54c,iVar4,iVar6);
      if ((*(short *)(&DAT_0048c746 + event_cursor * 6) == 0x15) &&
         (*(short *)(&DAT_0048c748 + event_cursor * 6) == 0)) {
        event_cursor = event_cursor - 1;
        DAT_0048c570 = (int)(short)event_stack[event_cursor].b;
        uVar9 = (uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3);
        DAT_0048c54c = (int)(uVar9 * *(int *)(param_1[0x95] + 0x2c)) %
                       (*(int *)(param_1[0x95] + 0x2c) * 0xb);
        iVar6 = *(int *)(param_1[0x95] + 0x30);
        lVar1 = (longlong)((int)(uVar9 * iVar6) / (iVar6 * 0xb)) * (longlong)iVar6;
        DAT_0048c550 = (int)lVar1;
        if ((original_hero._356_4_ == 0) && (DAT_0048c570 == 1)) {
          FUN_00431250((int *)param_1[0xb5],(int)((ulonglong)lVar1 >> 0x20));
        }
        iVar6 = DAT_0048c57c + DAT_0048c550;
        iVar4 = 0x9e;
        piVar5 = (int *)FUN_00421a54(DAT_0048c510);
        FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c578 + DAT_0048c54c,iVar4,iVar6);
      }
    }
    else if (event_stack[event_cursor].a == 1) {
      iVar4 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                       (uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3)) - 1;
      iVar6 = DAT_0048c550;
      puStack_28 = &stack0xfffffffc;
      piVar5 = (int *)FUN_0041dad8((int)DAT_0048c514);
      FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
      DAT_0048c5a8 = (uint)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                                    (uint)*(byte *)((int)&original_monsters[0x20].gold +
                                                   DAT_0048c570 + 3));
      FUN_00454c10();
      iVar4 = (*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                        (uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3)) - 1)
              + door_opened;
      iVar6 = DAT_0048c550;
      piVar5 = (int *)FUN_0041dad8(DAT_0048c518);
      FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
      if ((uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3) ==
          original_hero.y * 0xb + original_hero.x) {
        FUN_004433a4((int)param_1);
      }
      iVar6 = DAT_0048c57c + DAT_0048c550;
      iVar4 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                       (uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3)) - 1;
      piVar5 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c578 + DAT_0048c54c,iVar4,iVar6);
      if ((*(short *)(&DAT_0048c746 + event_cursor * 6) == 0x15) &&
         (*(short *)(&DAT_0048c748 + event_cursor * 6) == 1)) {
        event_cursor = event_cursor - 1;
        DAT_0048c570 = (int)(short)event_stack[event_cursor].b;
        uVar9 = (uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3);
        DAT_0048c54c = (int)(uVar9 * *(int *)(param_1[0x95] + 0x2c)) %
                       (*(int *)(param_1[0x95] + 0x2c) * 0xb);
        iVar6 = *(int *)(param_1[0x95] + 0x30);
        DAT_0048c550 = ((int)(uVar9 * iVar6) / (iVar6 * 0xb)) * iVar6;
        iVar4 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                         (uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3)) - 1
        ;
        iVar6 = DAT_0048c550;
        piVar5 = (int *)FUN_0041dad8((int)DAT_0048c514);
        FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
        DAT_0048c5a8 = (uint)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                                      (uint)*(byte *)((int)&original_monsters[0x20].gold +
                                                     DAT_0048c570 + 3));
        FUN_00454c10();
        iVar4 = (*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                          (uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3)) -
                1) + door_opened;
        iVar6 = DAT_0048c550;
        piVar5 = (int *)FUN_0041dad8(DAT_0048c518);
        FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c54c,iVar4,iVar6);
        if ((uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3) ==
            original_hero.y * 0xb + original_hero.x) {
          FUN_004433a4((int)param_1);
        }
        iVar6 = DAT_0048c57c + DAT_0048c550;
        iVar4 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                         (uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3)) - 1
        ;
        piVar5 = (int *)FUN_00421a54(DAT_0048c510);
        FUN_00417e44((int *)param_1[0x6c],piVar5,DAT_0048c578 + DAT_0048c54c,iVar4,iVar6);
      }
      if (DAT_0048c570 == 0x79) {
        FUN_0047f5a8((int)param_1);
        FUN_0042c454(param_1[0x6d],'\x01');
      }
    }
    break;
  case 0x16:
    original_hero.cycle_factor_minus_one = 0;
    original_hero.later_cycle = 0;
    FUN_00454da0((int)param_1);
  }
  event_cursor = event_cursor - 1;
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_0045480b;
  puStack_2c = (undefined *)0x454803;
  FUN_004034dc((int *)&local_8);
  return;
}

