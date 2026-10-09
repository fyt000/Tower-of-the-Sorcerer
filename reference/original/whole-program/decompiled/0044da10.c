/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044da10.
 * Inferred types, shared tails and runtime effects require assembly review. */

void dialogue_continue(int param_1,undefined4 param_2,undefined4 param_3)

{
  dword dVar1;
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
  
  if ((10 < (int)dialogue_continue_stage) && ((int)dialogue_continue_stage < 0x44)) {
    *(undefined4 *)(&original_hero.field_0x140 + dialogue_continue_stage * 4) = 1;
  }
  switch(dialogue_continue_stage) {
  case 0:
    if (original_hero.hero_orb == 2) {
      original_hero.hero_orb = 1;
    }
    FUN_00450880(param_1);
    param_3 = extraout_ECX;
    if (*(char *)(*(int *)(param_1 + 0x350) + 0x28) == '\x01') {
      TTSW10_buttonfocus(param_1);
      param_3 = extraout_ECX_00;
    }
    break;
  case 1:
    FUN_0041353c(*(int **)(param_1 + 0x250),'\x01');
    (**(code **)(**(int **)(param_1 + 0x250) + 0x80))();
    param_3 = extraout_ECX_01;
    break;
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0x16:
    break;
  case 0xb:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_0042c454(*(int *)(param_1 + 0x2ec),'\x01');
    param_3 = extraout_ECX_04;
    break;
  case 0xc:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_0042c454(*(int *)(param_1 + 0x2ec),'\x01');
    param_3 = extraout_ECX_05;
    break;
  case 0xd:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_0042c454(*(int *)(param_1 + 0x2ec),'\0');
    FUN_0042c454(*(int *)(param_1 + 0x1b4),'\x01');
    original_hero._48_4_ = 0;
    event_cursor = 0;
    FUN_00442c38(param_1);
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_06);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
    FUN_00450880(param_1);
    param_3 = extraout_ECX_07;
    break;
  case 0xe:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_08);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
    FUN_0042c454(*(int *)(param_1 + 0x2ec),'\0');
    start_event_timer(param_1);
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 0xc;
    event_stack[dVar1].a = 0x42;
    event_stack[dVar1].b = 0x4d;
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 0xc;
    event_stack[dVar1].a = 0x43;
    event_stack[dVar1].b = 0x42;
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 0xc;
    event_stack[dVar1].a = 0x44;
    event_stack[dVar1].b = 0x43;
    param_3 = extraout_ECX_09;
    break;
  case 0xf:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_10);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
    FUN_0042c454(*(int *)(param_1 + 0x2ec),'\0');
    start_event_timer(param_1);
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 6;
    event_stack[dVar1].a = 99;
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
    event_stack[event_cursor].opcode = 0xc;
    event_stack[dVar1].a = 0x58;
    event_stack[dVar1].b = 99;
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    event_cursor = event_cursor + 1;
    dVar1 = event_cursor;
    event_stack[event_cursor].opcode = 0xc;
    event_stack[dVar1].a = 0x4d;
    event_stack[dVar1].b = 0x58;
    param_3 = extraout_ECX_11;
    break;
  case 0x10:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_12);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
    FUN_0042c454(*(int *)(param_1 + 0x2ec),'\0');
    original_maps[35][105] = 0x15;
    original_maps[35][93] = 6;
    FUN_00450880(param_1);
    param_3 = extraout_ECX_13;
    break;
  case 0x11:
  case 0x12:
  case 0x13:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_14);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
    FUN_0042c454(*(int *)(param_1 + 0x2ec),'\0');
    FUN_00450880(param_1);
    param_3 = extraout_ECX_15;
    break;
  case 0x14:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_16);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
    opening_capture(param_1);
    param_3 = extraout_ECX_17;
    break;
  case 0x15:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_18);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
    FUN_0042c454(*(int *)(param_1 + 0x2ec),'\x01');
    param_3 = extraout_ECX_19;
    break;
  case 0x17:
  case 0x18:
  case 0x19:
LAB_0044e08e:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_20);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
    FUN_0042c454(*(int *)(param_1 + 0x2ec),'\x01');
    param_3 = extraout_ECX_21;
    break;
  case 0x1a:
LAB_0044e107:
    FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_24);
    FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
    tile_class_or_message = 0;
    if (original_hero.cycle_factor_minus_one == 0) {
      FUN_004237dc(DAT_0048a764);
      param_3 = extraout_ECX_25;
    }
    else {
      FUN_0042c454(*(int *)(param_1 + 0x2ec),'\x01');
      param_3 = extraout_ECX_26;
    }
    break;
  default:
    if (0x32 < (int)dialogue_continue_stage) {
      if ((int)dialogue_continue_stage < 0x48) {
        if (dialogue_continue_stage != 0x47) {
          if (5 < dialogue_continue_stage - 0x33) {
            if (dialogue_continue_stage == 0x39) goto LAB_0044e107;
            if (9 < dialogue_continue_stage - 0x3a) break;
          }
          goto LAB_0044e08e;
        }
      }
      else {
        if (dialogue_continue_stage == 0x48) {
          FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
          FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_27);
          FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
          FUN_0042c454(*(int *)(param_1 + 0x2ec),'\x01');
          param_3 = extraout_ECX_28;
          break;
        }
        if (dialogue_continue_stage == 0x67) {
          FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
          FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_02);
          FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
          FUN_0042c454(*(int *)(param_1 + 0x2ec),'\x01');
          param_3 = extraout_ECX_03;
          break;
        }
        if (dialogue_continue_stage != 0x112) break;
      }
      FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
      FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_22);
      FUN_004135d4(*(int **)(param_1 + 0x1cc),(uint *)0x0);
      FUN_0042c454(*(int *)(param_1 + 0x2ec),'\0');
      FUN_00450880(param_1);
      param_3 = extraout_ECX_23;
      break;
    }
    switch(dialogue_continue_stage) {
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x21:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
      goto LAB_0044e08e;
    case 0x20:
    case 0x22:
    case 0x32:
      goto LAB_0044e107;
    default:
      break;
    }
  }
  FUN_00413500(*(int **)(param_1 + 0x1d0),0,param_3);
  if ((int)dialogue_continue_stage < 2) {
    (**(code **)(**(int **)(*(int *)(param_1 + 0x1cc) + 0x140) + 0x38))();
    FUN_00413500(*(int **)(param_1 + 0x1cc),0,extraout_ECX_29);
  }
  FUN_0044cb34(param_1);
  return;
}

