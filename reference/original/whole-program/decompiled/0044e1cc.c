/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044e1cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void accept_merchant_or_altar(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int *piVar2;
  dword dVar3;
  int iVar4;
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
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined4 *puStack_c;
  uint *puStack_8;
  
  puStack_1c = &stack0xfffffffc;
  puStack_8 = (uint *)0x0;
  puStack_c = (undefined4 *)0x0;
  puStack_20 = &UNK_0044ea74;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  FUN_00413500(*(int **)(param_1 + 0x1d4),0,param_3);
  FUN_00413500(*(int **)(param_1 + 0x1d8),0,extraout_ECX);
  if (*(char *)(*(int **)(param_1 + 0x1d8) + 0xe) == '\0') {
    FUN_0041353c(*(int **)(param_1 + 0x1d8),'\x01');
  }
  FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
  if (_DAT_0048c5cc == 0) {
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_00);
  }
  FUN_0044cb34(param_1);
  if (_DAT_0048c5cc == 0) {
    if (original_hero.floor == 0x1c) {
      if (original_hero.yellow_keys == 0) {
        piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
        (**(code **)(*piVar2 + 0xc))(piVar2,0x106,&puStack_8);
        FUN_004135d4(*(int **)(param_1 + 0x1cc),puStack_8);
        FUN_00413500(*(int **)(param_1 + 0x1cc),CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                     extraout_ECX_05);
        FUN_00413500(*(int **)(param_1 + 0x1d0),CONCAT31((int3)((uint)extraout_EDX_04 >> 8),1),
                     extraout_ECX_06);
        (**(code **)(**(int **)(param_1 + 0x1d0) + 0x80))();
        dialogue_continue_stage = 0;
      }
      else {
        original_hero.yellow_keys = original_hero.yellow_keys + -1;
        original_hero.gold = original_hero.gold + 100;
        dialogue_continue_stage = 0;
        piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
        (**(code **)(*piVar2 + 0xc))(piVar2,0x103,&puStack_8);
        FUN_004135d4(*(int **)(param_1 + 0x1cc),puStack_8);
        FUN_00413500(*(int **)(param_1 + 0x1cc),CONCAT31((int3)((uint)extraout_EDX_05 >> 8),1),
                     extraout_ECX_07);
        FUN_00413500(*(int **)(param_1 + 0x1d0),CONCAT31((int3)((uint)extraout_EDX_06 >> 8),1),
                     extraout_ECX_08);
        (**(code **)(**(int **)(param_1 + 0x1d0) + 0x80))();
        event_cursor = event_cursor + 1;
        dVar3 = event_cursor;
        event_stack[event_cursor].opcode = 2;
        event_stack[dVar3].a = 0;
        event_stack[dVar3].b = 0;
        event_cursor = event_cursor + 1;
        dVar3 = event_cursor;
        event_stack[event_cursor].opcode = 8;
        event_stack[dVar3].a = 0;
        event_stack[dVar3].b = 0;
        event_cursor = event_cursor + 1;
        dVar3 = event_cursor;
        event_stack[event_cursor].opcode = 0;
        event_stack[dVar3].a = 0;
        event_stack[dVar3].b = 0;
        event_cursor = event_cursor + 1;
        dVar3 = event_cursor;
        event_stack[event_cursor].opcode = 1;
        event_stack[dVar3].a = 2;
        event_stack[dVar3].b = 0;
        start_event_timer(param_1);
      }
    }
    else if (original_hero.gold < (int)bomb_gold) {
      piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar2 + 0xc))(piVar2,0x102,&puStack_8);
      FUN_004135d4(*(int **)(param_1 + 0x1cc),puStack_8);
      FUN_00413500(*(int **)(param_1 + 0x1cc),CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                   extraout_ECX_01);
      FUN_00413500(*(int **)(param_1 + 0x1d0),CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                   extraout_ECX_02);
      (**(code **)(**(int **)(param_1 + 0x1d0) + 0x80))();
      dialogue_continue_stage = 0;
    }
    else {
      original_hero.gold = original_hero.gold - bomb_gold;
      dialogue_continue_stage = 0;
      if (DAT_0048c598 - 0x2aU < 4) {
        (&original_hero.hp)[DAT_0048c598] = 1;
      }
      else if (DAT_0048c598 == 0x2f) {
        original_hero._188_4_ = 1;
      }
      else if (DAT_0048c598 - 0x31U < 5) {
        (&original_hero.hp)[DAT_0048c598] = 1;
      }
      switch(DAT_0048c598) {
      case 0x2a:
        original_hero.gold = original_hero.gold + 1000;
        break;
      case 0x2b:
        original_hero.blue_keys = original_hero.blue_keys + 1;
        break;
      case 0x2c:
        original_hero.yellow_keys = original_hero.yellow_keys + 5;
        break;
      case 0x2d:
        original_hero.red_keys = original_hero.red_keys + 1;
        break;
      case 0x2e:
        original_hero.yellow_keys = original_hero.yellow_keys + 1;
        break;
      case 0x2f:
        original_hero.blue_keys = original_hero.blue_keys + 1;
        break;
      case 0x30:
        original_hero.yellow_keys = original_hero.yellow_keys + -1;
        original_hero.gold = original_hero.gold + 100;
        break;
      case 0x31:
        original_hero.yellow_keys = original_hero.yellow_keys + 4;
        original_hero.blue_keys = original_hero.blue_keys + 1;
        break;
      case 0x32:
        original_hero.yellow_keys = original_hero.yellow_keys + 3;
        break;
      case 0x33:
        original_hero.blue_keys = original_hero.blue_keys + 3;
        break;
      case 0x34:
        original_hero.hp = original_hero.hp + 2000;
        break;
      case 0x35:
        original_hero.super_mattock = 1;
      }
      piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar2 + 0xc))(piVar2,0x103,&puStack_8);
      FUN_004135d4(*(int **)(param_1 + 0x1cc),puStack_8);
      FUN_00413500(*(int **)(param_1 + 0x1cc),CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                   extraout_ECX_03);
      FUN_00413500(*(int **)(param_1 + 0x1d0),CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                   extraout_ECX_04);
      (**(code **)(**(int **)(param_1 + 0x1d0) + 0x80))();
      event_cursor = event_cursor + 1;
      dVar3 = event_cursor;
      event_stack[event_cursor].opcode = 2;
      event_stack[dVar3].a = 0;
      event_stack[dVar3].b = 0;
      event_cursor = event_cursor + 1;
      dVar3 = event_cursor;
      event_stack[event_cursor].opcode = 8;
      event_stack[dVar3].a = 0;
      event_stack[dVar3].b = 0;
      event_cursor = event_cursor + 1;
      dVar3 = event_cursor;
      event_stack[event_cursor].opcode = 0;
      event_stack[dVar3].a = 0;
      event_stack[dVar3].b = 0;
      event_cursor = event_cursor + 1;
      dVar3 = event_cursor;
      event_stack[event_cursor].opcode = 1;
      event_stack[dVar3].a = 2;
      event_stack[dVar3].b = 0;
      start_event_timer(param_1);
    }
  }
  else if (_DAT_0048c5cc == 1) {
    FUN_004130f8(*(int **)(param_1 + 0x2dc),*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    FUN_004130d8(*(int **)(param_1 + 0x2dc),
                 *(int *)(*(int *)(param_1 + 0x1cc) + 0x2c) -
                 *(int *)(*(int *)(param_1 + 0x254) + 0x2c));
    iVar4 = *(int *)(*(int *)(param_1 + 0x1cc) + 0x2c);
    if (iVar4 < (*(int **)(param_1 + 0x2dc))[0xb]) {
      FUN_004130d8(*(int **)(param_1 + 0x2dc),iVar4);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar4 = (int)uVar1 >> 1;
    if (iVar4 < 0) {
      iVar4 = iVar4 + (uint)((uVar1 & 1) != 0);
    }
    FUN_004130b8(*(int **)(param_1 + 0x2dc),
                 *(int *)(*(int *)(param_1 + 0x1cc) + 0x28) + uVar1 + iVar4);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar4 = (int)uVar1 >> 1;
    if (iVar4 < 0) {
      iVar4 = iVar4 + (uint)((uVar1 & 1) != 0);
    }
    FUN_00413098(*(int **)(param_1 + 0x2dc),*(int *)(*(int *)(param_1 + 0x1cc) + 0x24) + iVar4);
    FUN_004130f8(*(int **)(param_1 + 0x2e0),*(undefined4 *)(*(int *)(param_1 + 0x2dc) + 0x30));
    FUN_004130d8(*(int **)(param_1 + 0x2e0),*(undefined4 *)(*(int *)(param_1 + 0x2dc) + 0x2c));
    FUN_004130b8(*(int **)(param_1 + 0x2e0),
                 *(int *)(*(int *)(param_1 + 0x2dc) + 0x28) +
                 *(int *)(*(int *)(param_1 + 0x2dc) + 0x30));
    FUN_00413098(*(int **)(param_1 + 0x2e0),*(undefined4 *)(*(int *)(param_1 + 0x2dc) + 0x24));
    FUN_004130f8(*(int **)(param_1 + 0x2e4),*(undefined4 *)(*(int *)(param_1 + 0x2dc) + 0x30));
    FUN_004130d8(*(int **)(param_1 + 0x2e4),*(undefined4 *)(*(int *)(param_1 + 0x2dc) + 0x2c));
    FUN_004130b8(*(int **)(param_1 + 0x2e4),
                 *(int *)(*(int *)(param_1 + 0x2e0) + 0x28) +
                 *(int *)(*(int *)(param_1 + 0x2e0) + 0x30));
    FUN_00413098(*(int **)(param_1 + 0x2e4),*(undefined4 *)(*(int *)(param_1 + 0x2dc) + 0x24));
    FUN_004130f8(*(int **)(param_1 + 0x2e8),*(undefined4 *)(*(int *)(param_1 + 0x2dc) + 0x30));
    FUN_004130d8(*(int **)(param_1 + 0x2e8),*(undefined4 *)(*(int *)(param_1 + 0x2dc) + 0x2c));
    FUN_004130b8(*(int **)(param_1 + 0x2e8),
                 *(int *)(*(int *)(param_1 + 0x2e4) + 0x28) +
                 *(int *)(*(int *)(param_1 + 0x2e4) + 0x30));
    FUN_00413098(*(int **)(param_1 + 0x2e8),*(undefined4 *)(*(int *)(param_1 + 0x2dc) + 0x24));
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xcc,&puStack_8);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),puStack_8);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xcd,&puStack_8);
    FUN_00403658((int *)&puStack_8,(undefined4 *)&UNK_0044ea8c);
    FUN_00405b6c((original_hero._44_4_ + 1) * 100 * (original_hero.cycle_factor_minus_one + 1),
                 (int *)&puStack_c);
    FUN_00403658((int *)&puStack_8,puStack_c);
    FUN_00403658((int *)&puStack_8,(undefined4 *)&UNK_0044ea8c);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xce,&puStack_c);
    FUN_00403658((int *)&puStack_8,puStack_c);
    FUN_004135d4(*(int **)(param_1 + 0x2dc),puStack_8);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xcf,&puStack_8);
    FUN_00403658((int *)&puStack_8,(undefined4 *)&UNK_0044ea8c);
    FUN_00405b6c(((original_hero.floor + 10) / 10) * 2 * (original_hero.cycle_factor_minus_one + 1),
                 (int *)&puStack_c);
    FUN_00403658((int *)&puStack_8,puStack_c);
    FUN_00403658((int *)&puStack_8,(undefined4 *)&UNK_0044ea8c);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xd0,&puStack_c);
    FUN_00403658((int *)&puStack_8,puStack_c);
    FUN_004135d4(*(int **)(param_1 + 0x2e0),puStack_8);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xd1,&puStack_8);
    FUN_00403658((int *)&puStack_8,(undefined4 *)&UNK_0044ea8c);
    FUN_00405b6c(((original_hero.floor + 10) / 10) * 4 * (original_hero.cycle_factor_minus_one + 1),
                 (int *)&puStack_c);
    FUN_00403658((int *)&puStack_8,puStack_c);
    FUN_00403658((int *)&puStack_8,(undefined4 *)&UNK_0044ea8c);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xd0,&puStack_c);
    FUN_00403658((int *)&puStack_8,puStack_c);
    FUN_004135d4(*(int **)(param_1 + 0x2e4),puStack_8);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xd2,&puStack_8);
    FUN_004135d4(*(int **)(param_1 + 0x2e8),puStack_8);
    FUN_00413500(*(int **)(param_1 + 0x2dc),CONCAT31((int3)((uint)extraout_EDX_07 >> 8),1),
                 extraout_ECX_09);
    FUN_00413500(*(int **)(param_1 + 0x2e0),CONCAT31((int3)((uint)extraout_EDX_08 >> 8),1),
                 extraout_ECX_10);
    FUN_00413500(*(int **)(param_1 + 0x2e4),CONCAT31((int3)((uint)extraout_EDX_09 >> 8),1),
                 extraout_ECX_11);
    FUN_00413500(*(int **)(param_1 + 0x2e8),CONCAT31((int3)((uint)extraout_EDX_10 >> 8),1),
                 extraout_ECX_12);
    (**(code **)(**(int **)(param_1 + 0x2e8) + 0x80))();
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &UNK_0044ea7b;
  puStack_20 = (undefined *)0x44ea73;
  FUN_004034fc((int *)&puStack_c,2);
  return;
}

