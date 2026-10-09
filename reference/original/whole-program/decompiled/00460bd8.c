/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00460bd8.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00460bd8(int param_1,int param_2,short *param_3)

{
  int iVar1;
  short *extraout_ECX;
  short *extraout_ECX_00;
  short *extraout_ECX_01;
  short *extraout_ECX_02;
  short *extraout_ECX_03;
  short *extraout_ECX_04;
  short *extraout_ECX_05;
  short *extraout_ECX_06;
  short *extraout_ECX_07;
  short *extraout_ECX_08;
  short *extraout_ECX_09;
  short *extraout_ECX_10;
  short *extraout_ECX_11;
  short *extraout_ECX_12;
  short *extraout_ECX_13;
  short *extraout_ECX_14;
  short *extraout_ECX_15;
  short *extraout_ECX_16;
  short *extraout_ECX_17;
  short *extraout_ECX_18;
  short *extraout_ECX_19;
  short *extraout_ECX_20;
  short *extraout_ECX_21;
  short *extraout_ECX_22;
  short *extraout_ECX_23;
  short *psVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int extraout_EDX_04;
  int extraout_EDX_05;
  int extraout_EDX_06;
  int extraout_EDX_07;
  int extraout_EDX_08;
  int extraout_EDX_09;
  int extraout_EDX_10;
  int extraout_EDX_11;
  
  if ((int)event_cursor < 0) {
    event_cursor = 0;
  }
  psVar2 = param_3;
  if ((*(char *)(*(int *)(param_1 + 0x328) + 0x29) == '\x01') && (event_cursor == 0)) {
    switch(*param_3) {
    case 0xd:
      if (*(char *)(*(int *)(param_1 + 0x3f8) + 0x37) == '\0') {
        FUN_004610c4(param_1,4);
        psVar2 = extraout_ECX_09;
        param_2 = extraout_EDX_09;
      }
      else {
        switch(DAT_0048c5d0) {
        case 0:
          FUN_00480f60(param_1);
          psVar2 = extraout_ECX_10;
          break;
        case 1:
          FUN_0048198c(param_1);
          psVar2 = extraout_ECX_11;
          break;
        case 2:
          FUN_00481e80(param_1,param_2,param_3);
          psVar2 = extraout_ECX_12;
          break;
        case 4:
          FUN_0048201c(param_1);
          psVar2 = extraout_ECX_13;
          break;
        case 5:
          FUN_00482128(param_1);
          psVar2 = extraout_ECX_14;
          break;
        case 6:
          FUN_00482234(param_1);
          psVar2 = extraout_ECX_15;
          break;
        case 7:
          FUN_00482340(param_1);
          psVar2 = extraout_ECX_16;
          break;
        case 8:
          FUN_0048244c(param_1);
          psVar2 = extraout_ECX_17;
          break;
        case 9:
          FUN_00482558(param_1);
          psVar2 = extraout_ECX_18;
          break;
        case 0xb:
          FUN_00482664(param_1);
          psVar2 = extraout_ECX_19;
          break;
        case 0xc:
          FUN_00482770(param_1);
          psVar2 = extraout_ECX_20;
          break;
        case 0xd:
          FUN_0048287c(param_1);
          psVar2 = extraout_ECX_21;
        }
        FUN_00413500(*(int **)(param_1 + 0x3f8),0,psVar2);
        FUN_00410378(*(int **)(param_1 + 0x474),1);
        psVar2 = extraout_ECX_22;
        param_2 = extraout_EDX_10;
      }
      DAT_0048c5ce = 1 - DAT_0048c5ce;
      break;
    case 0x1b:
      if (DAT_0048c5ce == 1) {
        FUN_00413500(*(int **)(param_1 + 0x3f8),0,param_3);
        FUN_00410378(*(int **)(param_1 + 0x474),1);
        DAT_0048c5ce = 0;
        psVar2 = extraout_ECX_23;
        param_2 = extraout_EDX_11;
      }
      break;
    case 0x25:
      if (*(char *)(*(int *)(param_1 + 0x3f8) + 0x37) == '\0') {
        _DAT_0048c590 = 2;
        DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
        original_hero._352_4_ = 2;
        contact_index = DAT_0048c580 - 1;
        if (original_hero.x != 0) {
          handan(param_1);
          psVar2 = extraout_ECX_03;
          param_2 = extraout_EDX_03;
        }
      }
      else if (DAT_0048c5ce == 1) {
        neighbor_index = 0;
        iVar1 = 1;
        do {
          param_2 = (&original_hero.shield)[iVar1];
          neighbor_index = neighbor_index + param_2;
          iVar1 = iVar1 + 1;
        } while (iVar1 != 0x10);
        if (neighbor_index != 0) {
          DAT_0048c5d0 = DAT_0048c5d0 + -1;
          FUN_004610c4(param_1,3);
          psVar2 = extraout_ECX_04;
          param_2 = extraout_EDX_04;
        }
      }
      break;
    case 0x26:
      if (*(char *)(*(int *)(param_1 + 0x3f8) + 0x37) == '\0') {
        _DAT_0048c590 = 1;
        DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
        original_hero._352_4_ = 4;
        contact_index = DAT_0048c580 - 0xb;
        if (original_hero.y != 0) {
          handan(param_1);
          psVar2 = extraout_ECX;
          param_2 = extraout_EDX;
        }
      }
      else if (DAT_0048c5ce == 0) {
        if ((ushort)(DAT_0048c5d0 - 4U) < 6) {
          if (*(char *)((int)*(int **)(param_1 + 0x2cc) + 0x37) == '\x01') {
            (**(code **)(**(int **)(param_1 + 0x2cc) + 0x80))();
            psVar2 = extraout_ECX_00;
            param_2 = extraout_EDX_00;
          }
        }
        else if (((ushort)(DAT_0048c5d0 - 0xbU) < 3) &&
                (*(char *)((int)*(int **)(param_1 + 0x2cc) + 0x37) == '\x01')) {
          (**(code **)(**(int **)(param_1 + 0x2cc) + 0x80))();
          psVar2 = extraout_ECX_01;
          param_2 = extraout_EDX_01;
        }
      }
      else if (DAT_0048c5ce == 1) {
        neighbor_index = 0;
        iVar1 = 1;
        do {
          param_2 = (&original_hero.shield)[iVar1];
          neighbor_index = neighbor_index + param_2;
          iVar1 = iVar1 + 1;
        } while (iVar1 != 0x10);
        if (neighbor_index != 0) {
          DAT_0048c5d0 = DAT_0048c5d0 + -3;
          FUN_004610c4(param_1,0);
          psVar2 = extraout_ECX_02;
          param_2 = extraout_EDX_02;
        }
      }
      break;
    case 0x27:
      if (*(char *)(*(int *)(param_1 + 0x3f8) + 0x37) == '\0') {
        _DAT_0048c590 = 3;
        DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
        original_hero._352_4_ = 3;
        contact_index = DAT_0048c580 + 1;
        if (original_hero.x != 10) {
          handan(param_1);
          psVar2 = extraout_ECX_05;
          param_2 = extraout_EDX_05;
        }
      }
      else if (DAT_0048c5ce == 1) {
        neighbor_index = 0;
        iVar1 = 1;
        do {
          param_2 = (&original_hero.shield)[iVar1];
          neighbor_index = neighbor_index + param_2;
          iVar1 = iVar1 + 1;
        } while (iVar1 != 0x10);
        if (neighbor_index != 0) {
          DAT_0048c5d0 = DAT_0048c5d0 + 1;
          FUN_004610c4(param_1,2);
          psVar2 = extraout_ECX_06;
          param_2 = extraout_EDX_06;
        }
      }
      break;
    case 0x28:
      if (*(char *)(*(int *)(param_1 + 0x3f8) + 0x37) == '\0') {
        _DAT_0048c590 = 4;
        DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
        original_hero._352_4_ = 1;
        contact_index = DAT_0048c580 + 0xb;
        if (original_hero.y != 10) {
          handan(param_1);
          psVar2 = extraout_ECX_07;
          param_2 = extraout_EDX_07;
        }
      }
      else if (DAT_0048c5ce == 1) {
        neighbor_index = 0;
        iVar1 = 1;
        do {
          param_2 = (&original_hero.shield)[iVar1];
          neighbor_index = neighbor_index + param_2;
          iVar1 = iVar1 + 1;
        } while (iVar1 != 0x10);
        if (neighbor_index != 0) {
          DAT_0048c5d0 = DAT_0048c5d0 + 3;
          FUN_004610c4(param_1,1);
          psVar2 = extraout_ECX_08;
          param_2 = extraout_EDX_08;
        }
      }
    }
  }
  if ((*(char *)(*(int *)(param_1 + 0x484) + 0x37) == '\x01') && (*param_3 == 0xd)) {
    FUN_00484de8(param_1,param_2,(int)psVar2);
  }
  return;
}

