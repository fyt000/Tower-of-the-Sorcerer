/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00482e60. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_00482e60(int *param_1)

{
  dword dVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
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
  undefined4 extraout_ECX_43;
  undefined4 extraout_ECX_44;
  undefined4 extraout_ECX_45;
  undefined4 extraout_ECX_46;
  undefined4 extraout_ECX_47;
  undefined4 extraout_ECX_48;
  undefined4 extraout_ECX_49;
  undefined4 extraout_ECX_50;
  undefined4 extraout_ECX_51;
  undefined4 extraout_ECX_52;
  int extraout_ECX_53;
  undefined4 extraout_ECX_54;
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
  undefined4 extraout_EDX_17;
  undefined4 extraout_EDX_18;
  undefined4 extraout_EDX_19;
  undefined4 extraout_EDX_20;
  undefined4 extraout_EDX_21;
  undefined4 extraout_EDX_22;
  undefined4 extraout_EDX_23;
  undefined4 extraout_EDX_24;
  undefined4 extraout_EDX_25;
  undefined4 uVar10;
  undefined4 extraout_EDX_26;
  undefined4 extraout_EDX_27;
  undefined4 extraout_EDX_28;
  undefined4 extraout_EDX_29;
  undefined4 extraout_EDX_30;
  undefined4 extraout_EDX_31;
  undefined4 extraout_EDX_32;
  undefined4 extraout_EDX_33;
  undefined4 extraout_EDX_34;
  undefined4 extraout_EDX_35;
  undefined4 extraout_EDX_36;
  undefined4 extraout_EDX_37;
  undefined4 extraout_EDX_38;
  undefined4 extraout_EDX_39;
  undefined4 extraout_EDX_40;
  undefined4 extraout_EDX_41;
  undefined4 extraout_EDX_42;
  undefined4 extraout_EDX_43;
  undefined4 extraout_EDX_44;
  undefined4 extraout_EDX_45;
  undefined4 extraout_EDX_46;
  undefined4 extraout_EDX_47;
  undefined4 extraout_EDX_48;
  undefined4 extraout_EDX_49;
  undefined4 extraout_EDX_50;
  undefined4 extraout_EDX_51;
  undefined4 extraout_EDX_52;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *in_FS_OFFSET;
  byte bVar13;
  int *piVar14;
  undefined4 uStack_34;
  undefined *puStack_30;
  undefined *puStack_2c;
  undefined4 *local_1c;
  undefined4 local_18 [4];
  int local_8;

  bVar13 = 0;
  puStack_2c = &stack0xfffffffc;
  local_1c = (undefined4 *)0x0;
  puStack_30 = &LAB_0048473f;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  FUN_0042c454(param_1[0x6d],'\0');
  dVar1 = event_cursor;
  switch(*(undefined2 *)(&DAT_0048c748 + event_cursor * 6)) {
  case 0:
  case 2:
    if (event_stack[event_cursor].b == 0xe8) {
      FUN_004130b8((int *)param_1[0x106],0);
      FUN_00413098((int *)param_1[0x106],0);
      uVar6 = FUN_00413178(param_1);
      FUN_004130d8((int *)param_1[0x106],uVar6);
      iVar7 = FUN_004131bc(param_1);
      FUN_004130f8((int *)param_1[0x106],iVar7 - *(int *)(param_1[0x72] + 0x30));
      uVar6 = extraout_ECX_00;
      if (*(char *)((int)(int *)param_1[0x6e] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x6e],0,extraout_ECX_00);
        uVar6 = extraout_ECX_01;
      }
      if (*(char *)((int)(int *)param_1[0x6f] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x6f],0,uVar6);
        uVar6 = extraout_ECX_02;
      }
      if (*(char *)((int)(int *)param_1[0x70] + 0x37) == '\x01') {
        FUN_00413500((int *)param_1[0x70],0,uVar6);
      }
    }
    iVar7 = FUN_004131bc(param_1);
    iVar7 = iVar7 - *(int *)(param_1[0x72] + 0x30);
    puVar11 = local_18;
    uVar6 = FUN_00413178(param_1);
    FUN_0040923c(0,0,uVar6,puVar11,iVar7);
    puVar11 = local_18;
    puVar12 = &DAT_0048c53c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    puVar11 = &DAT_0048c53c;
    puVar12 = &DAT_0048c52c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    FUN_00402c34(DAT_0048c51c);
    DAT_0048c51c = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                                       extraout_ECX_03);
    FUN_00402c34(DAT_0048c520);
    DAT_0048c520 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                                       extraout_ECX_04);
    FUN_00402c34(DAT_0048c524);
    DAT_0048c524 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                                       extraout_ECX_05);
    uVar6 = FUN_00413178(param_1);
    (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,uVar6);
    iVar7 = FUN_004131bc(param_1);
    (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,iVar7 - *(int *)(param_1[0x72] + 0x30));
    uVar6 = FUN_00413178(param_1);
    (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar6);
    iVar7 = FUN_004131bc(param_1);
    (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,iVar7 - *(int *)(param_1[0x72] + 0x30));
    uVar6 = FUN_00413178(param_1);
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar6);
    iVar7 = FUN_004131bc(param_1);
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,iVar7 - *(int *)(param_1[0x72] + 0x30));
    piVar14 = &DAT_0048c53c;
    piVar8 = (int *)FUN_0041dad8(DAT_0048c528);
    piVar9 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
    if (*(short *)(&DAT_0048c748 + event_cursor * 6) == 0) {
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,DAT_0048c5fc);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\open1.bmp");
      (**(code **)(*DAT_0048c520 + 0x34))(DAT_0048c520,local_1c);
    }
    else if (*(short *)(&DAT_0048c748 + event_cursor * 6) == 2) {
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,DAT_0048c5fc);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\open0.bmp");
      (**(code **)(*DAT_0048c520 + 0x34))(DAT_0048c520,local_1c);
    }
    local_8 = 0;
    do {
      iVar7 = 0;
      do {
        iVar5 = param_1[0x95];
        iVar2 = *(int *)(iVar5 + 0x30) * iVar7;
        iVar3 = (short)event_stack[event_cursor].b + -0x42;
        piVar8 = (int *)FUN_0041dad8((int)DAT_0048c524);
        FUN_00417e44((int *)param_1[0x6c],piVar8,*(int *)(iVar5 + 0x2c) * local_8,iVar3,iVar2);
        iVar7 = iVar7 + 1;
      } while (iVar7 != 0xd);
      local_8 = local_8 + 1;
    } while (local_8 != 0x14);
    FUN_0044439c();
    piVar8 = DAT_0048c51c;
    piVar9 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar9,0,0,piVar8);
    if (((event_stack[event_cursor].b == 0xf7) &&
        (*(short *)(&DAT_0048c748 + event_cursor * 6) == 0)) ||
       ((event_stack[event_cursor].b == 0xf8 && (*(short *)(&DAT_0048c748 + event_cursor * 6) == 2))
       )) {
      if (DAT_00489b9f == '\x01') {
        FUN_0042c464(param_1[0xbb],0x96);
      }
      else if (DAT_00489b9f == '\x02') {
        FUN_0042c464(param_1[0xbb],0xfa);
      }
      else if (DAT_00489b9f == '\x03') {
        FUN_0042c464(param_1[0xbb],0x15e);
      }
      FUN_00402c34(DAT_0048c514);
      DAT_0048c514 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                                         extraout_ECX_06);
      (**(code **)(*DAT_0048c514 + 0x28))(DAT_0048c514,*(int *)(param_1[0x95] + 0x30) * 0xb);
      (**(code **)(*DAT_0048c514 + 0x2c))(DAT_0048c514,*(int *)(param_1[0x95] + 0x2c) * 0xb);
      FUN_00413500((int *)param_1[0x106],0,extraout_ECX_07);
      if (*(short *)(&DAT_0048c748 + event_cursor * 6) == 2) {
        FUN_004130d8((int *)param_1[0x106],
                     *(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
                     *(int *)(param_1[0x70] + 0x2c));
        FUN_004130f8((int *)param_1[0x106],*(undefined4 *)(param_1[0x6e] + 0x30));
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
        FUN_00403658((int *)&local_1c,DAT_0048c5fc);
        FUN_00403658((int *)&local_1c,(undefined4 *)"\\open0.bmp");
        FUN_0041c1e8(*(int *)(param_1[0x106] + 0xac),(int)local_1c);
        FUN_00413500((int *)param_1[0x106],CONCAT31((int3)((uint)extraout_EDX_04 >> 8),1),
                     extraout_ECX_08);
      }
    }
    break;
  case 1:
    if (event_stack[event_cursor].b == 0) {
      uVar6 = FUN_00413178(param_1);
      (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,uVar6);
      iVar7 = FUN_004131bc(param_1);
      (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,iVar7 - *(int *)(param_1[0x72] + 0x30));
      uVar6 = FUN_00413178(param_1);
      (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar6);
      iVar7 = FUN_004131bc(param_1);
      (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,iVar7 - *(int *)(param_1[0x72] + 0x30));
      iVar7 = FUN_004131bc(param_1);
      iVar7 = iVar7 - *(int *)(param_1[0x72] + 0x30);
      puVar11 = local_18;
      uVar6 = FUN_00413178(param_1);
      FUN_0040923c(0,0,uVar6,puVar11,iVar7);
      puVar11 = local_18;
      puVar12 = &DAT_0048c53c;
      for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar12 = *puVar11;
        puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
        puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
      }
      FUN_004130d8((int *)param_1[0x106],
                   *(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
                   *(int *)(param_1[0x70] + 0x2c));
      FUN_004130f8((int *)param_1[0x106],*(undefined4 *)(param_1[0x6e] + 0x30));
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,DAT_0048c5fc);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\open1.bmp");
      FUN_0041c1e8(*(int *)(param_1[0x106] + 0xac),(int)local_1c);
      piVar14 = &DAT_0048c53c;
      piVar8 = (int *)FUN_0042c150(param_1[0x106],extraout_EDX_05,extraout_ECX_09);
      piVar9 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,DAT_0048c5fc);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\open2.bmp");
      FUN_0041c1e8(*(int *)(param_1[0x106] + 0xac),(int)local_1c);
      piVar14 = &DAT_0048c53c;
      piVar8 = (int *)FUN_0042c150(param_1[0x106],extraout_EDX_06,extraout_ECX_10);
      piVar9 = (int *)FUN_0041dad8((int)DAT_0048c520);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      if (DAT_00489b9f == '\x01') {
        FUN_0042c464(param_1[0xbb],0x1e);
      }
      else if (DAT_00489b9f == '\x02') {
        FUN_0042c464(param_1[0xbb],0x32);
      }
      else if (DAT_00489b9f == '\x03') {
        FUN_0042c464(param_1[0xbb],0x46);
      }
    }
    iVar7 = (int)(short)event_stack[event_cursor].b;
    puVar11 = local_18;
    uVar6 = FUN_00413178(param_1);
    FUN_0040923c(0,0,uVar6,puVar11,iVar7);
    puVar11 = local_18;
    puVar12 = &DAT_0048c53c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    piVar14 = &DAT_0048c53c;
    piVar8 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar9 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
    piVar8 = DAT_0048c51c;
    piVar9 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar9,0,0,piVar8);
    if (((event_stack[event_cursor].b == 400) && (*(int *)(param_1[0x95] + 0x2c) == 0x20)) ||
       ((event_stack[event_cursor].b == 500 && (*(int *)(param_1[0x95] + 0x2c) == 0x28)))) {
      FUN_00413500((int *)param_1[0xf2],CONCAT31((int3)((uint)extraout_EDX_07 >> 8),1),
                   extraout_ECX_11);
      FUN_00413500((int *)param_1[0xf3],CONCAT31((int3)((uint)extraout_EDX_08 >> 8),1),
                   extraout_ECX_12);
      FUN_00413500((int *)param_1[0xf4],CONCAT31((int3)((uint)extraout_EDX_09 >> 8),1),
                   extraout_ECX_13);
      FUN_00413500((int *)param_1[0xf5],CONCAT31((int3)((uint)extraout_EDX_10 >> 8),1),
                   extraout_ECX_14);
      FUN_00413500((int *)param_1[0xf6],CONCAT31((int3)((uint)extraout_EDX_11 >> 8),1),
                   extraout_ECX_15);
      FUN_00413500((int *)param_1[0xf7],CONCAT31((int3)((uint)extraout_EDX_12 >> 8),1),
                   extraout_ECX_16);
      FUN_00413500((int *)param_1[0xf8],CONCAT31((int3)((uint)extraout_EDX_13 >> 8),1),
                   extraout_ECX_17);
      FUN_00413500((int *)param_1[0xf9],CONCAT31((int3)((uint)extraout_EDX_14 >> 8),1),
                   extraout_ECX_18);
      FUN_00413500((int *)param_1[0xfa],CONCAT31((int3)((uint)extraout_EDX_15 >> 8),1),
                   extraout_ECX_19);
      FUN_00413500((int *)param_1[0xfb],CONCAT31((int3)((uint)extraout_EDX_16 >> 8),1),
                   extraout_ECX_20);
      FUN_00413500((int *)param_1[0xfc],CONCAT31((int3)((uint)extraout_EDX_17 >> 8),1),
                   extraout_ECX_21);
      uVar6 = extraout_ECX_22;
      uVar10 = extraout_EDX_18;
      if (*(char *)(param_1[0xd4] + 0x28) == '\x01') {
        FUN_00413500((int *)param_1[0x114],CONCAT31((int3)((uint)extraout_EDX_18 >> 8),1),
                     extraout_ECX_22);
        FUN_00413500((int *)param_1[0x115],CONCAT31((int3)((uint)extraout_EDX_19 >> 8),1),
                     extraout_ECX_23);
        FUN_00413500((int *)param_1[0x116],CONCAT31((int3)((uint)extraout_EDX_20 >> 8),1),
                     extraout_ECX_24);
        FUN_00413500((int *)param_1[0x117],CONCAT31((int3)((uint)extraout_EDX_21 >> 8),1),
                     extraout_ECX_25);
        uVar6 = extraout_ECX_26;
        uVar10 = extraout_EDX_22;
      }
      FUN_00413500((int *)param_1[0xa2],CONCAT31((int3)((uint)uVar10 >> 8),1),uVar6);
      FUN_00413500((int *)param_1[0xa3],CONCAT31((int3)((uint)extraout_EDX_23 >> 8),1),
                   extraout_ECX_27);
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,DAT_0048c5fc);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\center.bmp");
      FUN_0041c1e8(*(int *)(param_1[0x6e] + 0xac),(int)local_1c);
      if (original_hero.cycle_factor_minus_one == 0) {
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
        FUN_00403658((int *)&local_1c,DAT_0048c5fc);
        FUN_00403658((int *)&local_1c,(undefined4 *)"\\left.bmp");
        FUN_0041c1e8(*(int *)(param_1[0x6f] + 0xac),(int)local_1c);
      }
      else {
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
        FUN_00403658((int *)&local_1c,DAT_0048c5fc);
        FUN_00403658((int *)&local_1c,(undefined4 *)"\\leftr.bmp");
        FUN_0041c1e8(*(int *)(param_1[0x6f] + 0xac),(int)local_1c);
      }
      if (original_hero.cycle_factor_minus_one == 0) {
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
        FUN_00403658((int *)&local_1c,DAT_0048c5fc);
        FUN_00403658((int *)&local_1c,(undefined4 *)"\\right.bmp");
        FUN_0041c1e8(*(int *)(param_1[0x70] + 0xac),(int)local_1c);
        uVar6 = extraout_ECX_28;
        uVar10 = extraout_EDX_24;
      }
      else {
        (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                  (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
        FUN_00403658((int *)&local_1c,DAT_0048c5fc);
        FUN_00403658((int *)&local_1c,(undefined4 *)"\\rightr.bmp");
        FUN_0041c1e8(*(int *)(param_1[0x70] + 0xac),(int)local_1c);
        uVar6 = extraout_ECX_29;
        uVar10 = extraout_EDX_25;
      }
      FUN_00413500((int *)param_1[0x6e],CONCAT31((int3)((uint)uVar10 >> 8),1),uVar6);
      FUN_00413500((int *)param_1[0x6f],CONCAT31((int3)((uint)extraout_EDX_26 >> 8),1),
                   extraout_ECX_30);
      FUN_00413500((int *)param_1[0x70],CONCAT31((int3)((uint)extraout_EDX_27 >> 8),1),
                   extraout_ECX_31);
      monster_index = 0xffffffff;
      FUN_0044b78c((int)param_1,extraout_EDX_28,extraout_ECX_32);
      FUN_0044bed8((int)param_1,extraout_EDX_29,extraout_ECX_33);
      FUN_0044ccd8((int)param_1);
      FUN_00413500((int *)param_1[0x77],CONCAT31((int3)((uint)extraout_EDX_30 >> 8),1),
                   extraout_ECX_34);
      FUN_00413500((int *)param_1[0x7b],CONCAT31((int3)((uint)extraout_EDX_31 >> 8),1),
                   extraout_ECX_35);
      FUN_00413500((int *)param_1[0x95],CONCAT31((int3)((uint)extraout_EDX_32 >> 8),1),
                   extraout_ECX_36);
      FUN_00413500((int *)param_1[0x96],CONCAT31((int3)((uint)extraout_EDX_33 >> 8),1),
                   extraout_ECX_37);
      FUN_00413500((int *)param_1[0x97],CONCAT31((int3)((uint)extraout_EDX_34 >> 8),1),
                   extraout_ECX_38);
      FUN_00413500((int *)param_1[0x98],CONCAT31((int3)((uint)extraout_EDX_35 >> 8),1),
                   extraout_ECX_39);
      FUN_00413500((int *)param_1[0x99],CONCAT31((int3)((uint)extraout_EDX_36 >> 8),1),
                   extraout_ECX_40);
      FUN_00413500((int *)param_1[0x9a],CONCAT31((int3)((uint)extraout_EDX_37 >> 8),1),
                   extraout_ECX_41);
      FUN_00413500((int *)param_1[0x9b],CONCAT31((int3)((uint)extraout_EDX_38 >> 8),1),
                   extraout_ECX_42);
      FUN_00413500((int *)param_1[0x9c],CONCAT31((int3)((uint)extraout_EDX_39 >> 8),1),
                   extraout_ECX_43);
      FUN_00413500((int *)param_1[0x9d],CONCAT31((int3)((uint)extraout_EDX_40 >> 8),1),
                   extraout_ECX_44);
      FUN_00413500((int *)param_1[0x9e],CONCAT31((int3)((uint)extraout_EDX_41 >> 8),1),
                   extraout_ECX_45);
      FUN_00413500((int *)param_1[0x9f],CONCAT31((int3)((uint)extraout_EDX_42 >> 8),1),
                   extraout_ECX_46);
      FUN_00413500((int *)param_1[0xa0],CONCAT31((int3)((uint)extraout_EDX_43 >> 8),1),
                   extraout_ECX_47);
      FUN_00413500((int *)param_1[0xa1],CONCAT31((int3)((uint)extraout_EDX_44 >> 8),1),
                   extraout_ECX_48);
      if (DAT_00489b9f == '\x01') {
        FUN_0042c464(param_1[0xbb],0x82);
      }
      else if (DAT_00489b9f == '\x02') {
        FUN_0042c464(param_1[0xbb],200);
      }
      else if (DAT_00489b9f == '\x03') {
        FUN_0042c464(param_1[0xbb],300);
      }
    }
    break;
  case 4:
    FUN_0042c464(param_1[0xbb],100);
    iVar7 = FUN_004131bc(param_1);
    FUN_0040923c(0,0,*(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
                     *(int *)(param_1[0x70] + 0x2c),local_18,iVar7 - *(int *)(param_1[0x72] + 0x30))
    ;
    puVar11 = local_18;
    puVar12 = &DAT_0048c53c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    FUN_0040923c(0,0,0x280,local_18,400);
    puVar11 = local_18;
    puVar12 = &DAT_0048c52c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
              (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
    FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End20.bmp");
    (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
    iVar7 = (int)(short)event_stack[event_cursor].b >> 1;
    if (iVar7 < 0) {
      iVar7 = iVar7 + (uint)(((int)(short)event_stack[event_cursor].b & 1U) != 0);
    }
    uVar4 = ((short)event_stack[event_cursor].b * 0x280) / 400;
    iVar5 = (int)uVar4 >> 1;
    if (iVar5 < 0) {
      iVar5 = iVar5 + (uint)((uVar4 & 1) != 0);
    }
    FUN_0040923c(iVar5,iVar7,0x280 - (iVar7 * 0x280) / 400,local_18,400 - iVar7);
    puVar11 = local_18;
    puVar12 = &DAT_0048c53c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    iVar7 = FUN_0041dad8((int)DAT_0048c520);
    *(undefined4 *)(iVar7 + 0x20) = 0xff0062;
    piVar14 = &DAT_0048c52c;
    piVar8 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar9 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_0041a530(piVar9,&DAT_0048c52c,piVar8,piVar14);
    iVar7 = FUN_0041dad8((int)DAT_0048c520);
    *(undefined4 *)(iVar7 + 0x20) = 0xcc0020;
    piVar14 = &DAT_0048c52c;
    piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    piVar9 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
    iVar7 = FUN_004131bc(param_1);
    FUN_0040923c(0,0,*(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
                     *(int *)(param_1[0x70] + 0x2c),local_18,iVar7 - *(int *)(param_1[0x72] + 0x30))
    ;
    puVar11 = local_18;
    puVar12 = &DAT_0048c53c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    piVar14 = &DAT_0048c52c;
    piVar8 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar9 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
    if (event_stack[event_cursor].b == 400) {
      FUN_004130b8((int *)param_1[0x106],0);
      FUN_00413098((int *)param_1[0x106],0);
      uVar6 = FUN_00413178(param_1);
      FUN_004130d8((int *)param_1[0x106],uVar6);
      iVar7 = FUN_004131bc(param_1);
      FUN_004130f8((int *)param_1[0x106],iVar7 - *(int *)(param_1[0x72] + 0x30));
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End26.bmp");
      FUN_0041c1e8(*(int *)(param_1[0x106] + 0xac),(int)local_1c);
    }
    break;
  case 5:
    FUN_0042c464(param_1[0xbb],0x3c);
    iVar7 = FUN_004131bc(param_1);
    FUN_0040923c(0,0,*(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
                     *(int *)(param_1[0x70] + 0x2c),local_18,iVar7 - *(int *)(param_1[0x72] + 0x30))
    ;
    puVar11 = local_18;
    puVar12 = &DAT_0048c53c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    uVar6 = 0;
    uVar10 = extraout_EDX_45;
    if (event_stack[dVar1].b == 1) {
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End26.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      uVar6 = extraout_ECX_49;
      uVar10 = extraout_EDX_46;
    }
    piVar14 = &DAT_0048c53c;
    piVar8 = (int *)FUN_0042c150(param_1[0x122],uVar10,uVar6);
    piVar9 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
    FUN_0040923c(0,0,0x280,local_18,(int)(short)event_stack[event_cursor].b);
    puVar11 = local_18;
    puVar12 = &DAT_0048c53c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    if (399 < (short)event_stack[event_cursor].b) {
      FUN_0040923c(0,0,0x280,local_18,400);
      puVar11 = local_18;
      puVar12 = &DAT_0048c53c;
      for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar12 = *puVar11;
        puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
        puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
      }
    }
    piVar14 = &DAT_0048c53c;
    piVar8 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar9 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
    if (*(int *)(param_1[0x95] + 0x2c) == 0x20) {
      piVar8 = DAT_0048c51c;
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a5b8(piVar9,0,0,piVar8);
    }
    else if (*(int *)(param_1[0x95] + 0x2c) == 0x28) {
      piVar8 = DAT_0048c51c;
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a5b8(piVar9,0x50,0x32,piVar8);
    }
    break;
  case 6:
    FUN_0042c464(param_1[0xbb],0x1c2);
    iVar7 = FUN_004131bc(param_1);
    FUN_0040923c(0,0,*(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
                     *(int *)(param_1[0x70] + 0x2c),local_18,iVar7 - *(int *)(param_1[0x72] + 0x30))
    ;
    puVar11 = local_18;
    puVar12 = &DAT_0048c53c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    FUN_0040923c(0,0,0x280,local_18,400);
    puVar11 = local_18;
    puVar12 = &DAT_0048c52c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    switch(event_stack[event_cursor].b) {
    case 1:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data\\open0.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 2:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End05.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 3:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End06.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 4:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End07.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 5:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End08.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 6:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End09.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 7:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End10.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 8:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End11.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 9:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End12.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 10:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End13.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 0xb:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End14.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 0xc:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End15.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 0xd:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End16.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 0xe:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End17.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 0xf:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End18.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 0x10:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End19.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
      break;
    case 0x11:
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_00403658((int *)&local_1c,(undefined4 *)"\\data2\\End20.bmp");
      (**(code **)(*DAT_0048c51c + 0x34))(DAT_0048c51c,local_1c);
      piVar14 = &DAT_0048c52c;
      piVar8 = (int *)FUN_0041dad8((int)DAT_0048c51c);
      piVar9 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
    }
    break;
  case 7:
    iVar7 = FUN_004131bc(param_1);
    FUN_0040923c(0,0,*(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
                     *(int *)(param_1[0x70] + 0x2c),local_18,iVar7 - *(int *)(param_1[0x72] + 0x30))
    ;
    puVar11 = local_18;
    puVar12 = &DAT_0048c53c;
    for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
      puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
    }
    FUN_004130b8((int *)param_1[0x106],0);
    FUN_00413098((int *)param_1[0x106],0);
    FUN_004130d8((int *)param_1[0x106],
                 *(int *)(param_1[0x6e] + 0x2c) + *(int *)(param_1[0x6f] + 0x2c) +
                 *(int *)(param_1[0x70] + 0x2c));
    iVar7 = FUN_004131bc(param_1);
    FUN_004130f8((int *)param_1[0x106],iVar7 - *(int *)(param_1[0x72] + 0x30));
    piVar14 = &DAT_0048c53c;
    piVar8 = (int *)FUN_0042c150(param_1[0x123],extraout_EDX_47,extraout_ECX_50);
    piVar9 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_0041a530(piVar9,&DAT_0048c53c,piVar8,piVar14);
    piVar8 = (int *)FUN_0042c150(param_1[0x106],extraout_EDX_48,extraout_ECX_51);
    FUN_0041a784(piVar8,&DAT_0048c53c,DAT_0048c520);
    FUN_0040352c((int *)(param_1[0x106] + 0x54),(undefined4 *)"Thank you for playing!");
    FUN_004136ac((int *)param_1[0x106],'\x01');
    FUN_00413500((int *)param_1[0x106],CONCAT31((int3)((uint)extraout_EDX_49 >> 8),1),
                 extraout_ECX_52);
    if (*(char *)(*(int *)(DAT_0048c510 + 0x330) + 0x28) == '\x01') {
      FUN_00431c8c(param_1[0xb6],'\t');
      (**(code **)(**(int **)(param_1[0x111] + 0x118) + 0xc))
                (*(int **)(param_1[0x111] + 0x118),1,&local_1c);
      FUN_0040369c((int *)(param_1[0xb6] + 0x20c),local_1c,(undefined4 *)"\\midi\\b_014xgw.mid");
      FUN_00430f20((int *)param_1[0xb6],extraout_EDX_50,extraout_ECX_53);
      FUN_00431c5c(param_1[0xb6],'\x01');
      FUN_00431250((int *)param_1[0xb6],extraout_EDX_51);
    }
    break;
  case 8:
    FUN_00413500((int *)param_1[0x120],CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
    FUN_00413500((int *)param_1[0x121],CONCAT31((int3)((uint)extraout_EDX_52 >> 8),1),
                 extraout_ECX_54);
    *(undefined *)(DAT_0048c510 + 0x118) = 1;
    FUN_0042c454(param_1[0xbb],'\0');
  }
  *in_FS_OFFSET = uStack_34;
  puStack_2c = &LAB_00484746;
  puStack_30 = (undefined *)0x48473e;
  FUN_004034dc((int *)&local_1c);
  return;
}
