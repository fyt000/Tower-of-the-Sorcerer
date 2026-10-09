/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00449e18.
 * Inferred types and shared tails require assembly review. */

void FUN_00449e18(int param_1)

{
  dword dVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 uVar5;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar6;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined3 uVar7;
  undefined4 extraout_EDX_05;
  undefined4 *in_FS_OFFSET;
  uint **ppuVar8;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  uint *local_10;
  uint *local_c;
  int local_8;
  
  puStack_20 = &stack0xfffffffc;
  local_c = (uint *)0x0;
  local_10 = (uint *)0x0;
  puStack_24 = &LAB_0044a437;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  local_8 = param_1;
  if (dialogue_continue_stage == 9) {
    if (original_hero._360_4_ != 0) {
      original_hero._360_4_ = 0xe;
    }
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0x16;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 10;
    event_stack[dVar1].a = 0x5d;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0;
    if (original_hero._360_4_ != 0) {
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 1;
      event_stack[dVar1].a = 5;
      event_stack[dVar1].b = 0;
    }
    puStack_20 = &stack0xfffffffc;
    start_event_timer(param_1);
  }
  else {
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1cc) + 0x44),(uint)DAT_00489b9d);
    if (DAT_00489ba4 == '\0') {
      FUN_004130f8(*(int **)(local_8 + 0x1cc),200);
      FUN_004130d8(*(int **)(local_8 + 0x1cc),0x17e);
      FUN_004130b8(*(int **)(local_8 + 0x1cc),0x2d);
      FUN_00413098(*(int **)(local_8 + 0x1cc),0x81);
    }
    else if (DAT_00489ba4 == '\x01') {
      FUN_004130f8(*(int **)(local_8 + 0x1cc),0xfa);
      FUN_004130d8(*(int **)(local_8 + 0x1cc),0x1de);
      FUN_004130b8(*(int **)(local_8 + 0x1cc),0x38);
      FUN_00413098(*(int **)(local_8 + 0x1cc),0xa1);
    }
    FUN_004130b8(*(int **)(local_8 + 0x1d0),
                 ((*(int *)(*(int *)(local_8 + 0x1cc) + 0x28) +
                  *(int *)(*(int *)(local_8 + 0x1cc) + 0x30)) - (*(int **)(local_8 + 0x1d0))[0xc]) +
                 -0x10);
    FUN_00413098(*(int **)(local_8 + 0x1d0),
                 ((*(int *)(*(int *)(local_8 + 0x1cc) + 0x24) +
                  *(int *)(*(int *)(local_8 + 0x1cc) + 0x2c)) - (*(int **)(local_8 + 0x1d0))[0xb]) +
                 -0x10);
    if ((int)dialogue_continue_stage < 10) {
      piVar2 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
      (**(code **)(*piVar2 + 0xc))(piVar2,DAT_0048c5a0 + 0x3e,&local_c);
      FUN_004135d4(*(int **)(local_8 + 0x1cc),local_c);
      uVar5 = extraout_ECX_00;
      uVar6 = extraout_EDX_00;
    }
    else {
      uVar5 = extraout_ECX;
      uVar6 = extraout_EDX;
      if ((((DAT_0048c5c8 != 0x10) && (DAT_0048c5c8 != 0x16)) && (DAT_0048c5c8 != 0x18)) &&
         ((DAT_0048c5c8 != 0x28 && (DAT_0048c5c8 != 0x2f)))) {
        piVar2 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
        (**(code **)(*piVar2 + 0xc))(piVar2,DAT_0048c5c8 + -1,&local_c);
        FUN_004135d4(*(int **)(local_8 + 0x1cc),local_c);
        uVar5 = extraout_ECX_01;
        uVar6 = extraout_EDX_01;
      }
      if (DAT_0048c5c8 == 5) {
        piVar2 = *(int **)(local_8 + 0x1cc);
        FUN_004135a4(piVar2,(int *)&local_10);
        ppuVar8 = &local_10;
        piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
        (**(code **)(*piVar3 + 0xc))(piVar3,DAT_0048c5c8 + 0x34,&local_c);
        FUN_00403658((int *)ppuVar8,local_c);
        FUN_004135d4(piVar2,local_10);
        uVar5 = extraout_ECX_02;
        uVar6 = extraout_EDX_02;
      }
      else if (DAT_0048c5c8 == 0x11) {
        piVar2 = *(int **)(local_8 + 0x1cc);
        FUN_004135a4(piVar2,(int *)&local_10);
        ppuVar8 = &local_10;
        piVar3 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
        (**(code **)(*piVar3 + 0xc))(piVar3,DAT_0048c5c8 + 0x29,&local_c);
        FUN_00403658((int *)ppuVar8,local_c);
        FUN_004135d4(piVar2,local_10);
        uVar5 = extraout_ECX_03;
        uVar6 = extraout_EDX_03;
      }
      else if (DAT_0048c5c8 == 0x37) {
        FUN_004135a4(*(int **)(local_8 + 0x1cc),(int *)&local_10);
        ppuVar8 = &local_10;
        piVar2 = *(int **)(*(int *)(local_8 + 0x44c) + 0x100);
        (**(code **)(*piVar2 + 0xc))(piVar2,DAT_0048c5c8 + 4,&local_c);
        FUN_00403658((int *)ppuVar8,local_c);
        FUN_004135d4(*(int **)(local_8 + 0x1cc),local_10);
        uVar5 = extraout_ECX_04;
        uVar6 = extraout_EDX_04;
      }
    }
    uVar7 = (undefined3)((uint)uVar6 >> 8);
    if (((original_hero._668_4_ == 1) || (DAT_0048c5c8 != 0x5d)) ||
       ((int)dialogue_continue_stage < 10)) {
      FUN_00413500(*(int **)(local_8 + 0x1cc),CONCAT31(uVar7,1),uVar5);
      if (original_hero._668_4_ == 0) {
        FUN_00413500(*(int **)(local_8 + 0x1d0),CONCAT31((int3)((uint)extraout_EDX_05 >> 8),1),
                     extraout_ECX_05);
        (**(code **)(**(int **)(local_8 + 0x1d0) + 0x80))();
      }
    }
    else {
      iVar4 = FUN_0042cec8((uint *)"You have no life point. Do you try again?",CONCAT31(uVar7,2),
                           DAT_0044a448,0);
      if (iVar4 == 6) {
        start_event_timer(local_8);
      }
      else {
        FUN_00410378(*(int **)(local_8 + 0x334),1);
      }
    }
  }
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_0044a43e;
  puStack_24 = (undefined *)0x44a42e;
  FUN_004034dc((int *)&local_10);
  puStack_24 = (undefined *)0x44a436;
  FUN_004034dc((int *)&local_c);
  return;
}

