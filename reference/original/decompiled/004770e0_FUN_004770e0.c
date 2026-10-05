/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 004770e0. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


/* WARNING: Restarted to delay deadcode elimination for space: ram */

void FUN_004770e0(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  byte bVar10;
  int iVar11;
  int *piVar12;
  undefined4 auStack_20 [4];

  bVar10 = 0;
  iVar2 = FUN_0041dad8((int)DAT_0048c51c);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = FUN_0041dad8((int)DAT_0048c520);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = FUN_0041dad8((int)DAT_0048c524);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  switch(event_stack[event_cursor].b) {
  case 1:
  case 2:
  case 3:
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),8);
    }
    if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),0xc);
    }
    scratch_index = (dword)*(short *)(&DAT_0048c74a + event_cursor * 6);
    if (scratch_index == 0x10) {
      FUN_0047f5a8(param_1);
    }
    if (DAT_00489ba4 == '\x01') {
      iVar2 = scratch_index * 5;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      scratch_index = iVar2 >> 2;
    }
    (**(code **)(*DAT_0048c520 + 0x28))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c520 + 0x2c))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    uVar4 = (**(code **)(*DAT_0048c520 + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar4);
    uVar4 = (**(code **)(*DAT_0048c520 + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar4);
    iVar11 = 0;
    iVar2 = 5;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = (short)event_stack[event_cursor].b + -1;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(scratch_index,0,iVar2,auStack_20,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30))
    ;
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(0,0,iVar2 - scratch_index,auStack_20,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(iVar2,0,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) - scratch_index,auStack_20,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(iVar2 + scratch_index,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),
                 auStack_20,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar6 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar6,DAT_0048c578,DAT_0048c57c,piVar5);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = 6;
    break;
  case 4:
    (**(code **)(*DAT_0048c520 + 0x28))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c520 + 0x2c))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    uVar4 = (**(code **)(*DAT_0048c520 + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar4);
    uVar4 = (**(code **)(*DAT_0048c520 + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar4);
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),8);
    }
    if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),0xc);
    }
    scratch_index = (dword)*(short *)(&DAT_0048c74a + event_cursor * 6);
    if (scratch_index == 0x10) {
      FUN_0047f5a8(param_1);
    }
    if (DAT_00489ba4 == '\x01') {
      iVar2 = scratch_index * 5;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      scratch_index = iVar2 >> 2;
    }
    iVar11 = 0;
    iVar2 = 5;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = 3;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(scratch_index,scratch_index,iVar11,auStack_20,iVar2);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(0,0,iVar11 - scratch_index,auStack_20,iVar2 - scratch_index);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(iVar11,scratch_index,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) - scratch_index,
                 auStack_20,iVar2);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(iVar11 + scratch_index,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),
                 auStack_20,iVar2 - scratch_index);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(scratch_index,iVar11,iVar2,auStack_20,
                 *(int *)(*(int *)(param_1 + 0x254) + 0x30) - scratch_index);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(0,iVar11 + scratch_index,iVar2 - scratch_index,auStack_20,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(iVar11,iVar2,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) - scratch_index,auStack_20,
                 *(int *)(*(int *)(param_1 + 0x254) + 0x30) - scratch_index);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(iVar11 + scratch_index,iVar2 + scratch_index,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar6 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar6,DAT_0048c578,DAT_0048c57c,piVar5);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = 6;
    break;
  case 5:
    (**(code **)(*DAT_0048c520 + 0x28))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c520 + 0x2c))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    uVar4 = (**(code **)(*DAT_0048c520 + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar4);
    uVar4 = (**(code **)(*DAT_0048c520 + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar4);
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),8);
    }
    if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),0xc);
    }
    scratch_index = (dword)*(short *)(&DAT_0048c74a + event_cursor * 6);
    if (scratch_index == 0x10) {
      FUN_0047f5a8(param_1);
    }
    if (DAT_00489ba4 == '\x01') {
      iVar2 = scratch_index * 5;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      scratch_index = iVar2 >> 2;
    }
    iVar11 = 0;
    iVar2 = 5;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = 3;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar7 = (int)uVar1 >> 1;
    if (iVar7 < 0) {
      iVar7 = iVar7 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar3 = (int)uVar1 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(iVar3 - scratch_index,iVar7 - scratch_index,iVar11,auStack_20,iVar2);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_0040923c(0,0,scratch_index,auStack_20,scratch_index);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar7 = (int)uVar1 >> 1;
    if (iVar7 < 0) {
      iVar7 = iVar7 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar3 = (int)uVar1 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(iVar3,iVar7 - scratch_index,iVar11 + scratch_index,auStack_20,iVar2);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_0040923c(*(int *)(*(int *)(param_1 + 0x254) + 0x2c) - scratch_index,0,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,scratch_index);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar7 = (int)uVar1 >> 1;
    if (iVar7 < 0) {
      iVar7 = iVar7 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar3 = (int)uVar1 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(iVar3 - scratch_index,iVar7,iVar11,auStack_20,iVar2 + scratch_index);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_0040923c(0,*(int *)(*(int *)(param_1 + 0x254) + 0x30) - scratch_index,scratch_index,
                 auStack_20,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar11 = (int)uVar1 >> 1;
    if (iVar11 < 0) {
      iVar11 = iVar11 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar7 = (int)uVar1 >> 1;
    if (iVar7 < 0) {
      iVar7 = iVar7 + (uint)((uVar1 & 1) != 0);
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar3 = (int)uVar1 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(iVar3,iVar7,iVar11 + scratch_index,auStack_20,iVar2 + scratch_index);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_0040923c(*(int *)(*(int *)(param_1 + 0x254) + 0x2c) - scratch_index,
                 *(int *)(*(int *)(param_1 + 0x254) + 0x30) - scratch_index,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar6 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar6,DAT_0048c578,DAT_0048c57c,piVar5);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = 4;
    break;
  case 6:
    (**(code **)(*DAT_0048c520 + 0x28))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c520 + 0x2c))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    uVar4 = (**(code **)(*DAT_0048c520 + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar4);
    uVar4 = (**(code **)(*DAT_0048c520 + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar4);
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),8);
    }
    if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),0xc);
    }
    scratch_index = (dword)*(short *)(&DAT_0048c74a + event_cursor * 6);
    if (scratch_index == 0x10) {
      FUN_0047f5a8(param_1);
    }
    if (DAT_00489ba4 == '\x01') {
      iVar2 = scratch_index * 5;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      scratch_index = iVar2 >> 2;
    }
    iVar11 = 0;
    iVar2 = 4;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x40c),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = 4;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = 5;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    FUN_0040923c(0,scratch_index * 2,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
                 *(int *)(*(int *)(param_1 + 0x254) + 0x30) + scratch_index * -2);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_0044439c();
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    piVar5 = DAT_0048c51c;
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c51c;
    piVar6 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar6 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar6,DAT_0048c578,DAT_0048c57c,piVar5);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = 6;
    break;
  case 7:
    (**(code **)(*DAT_0048c520 + 0x28))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c520 + 0x2c))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    uVar4 = (**(code **)(*DAT_0048c520 + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar4);
    uVar4 = (**(code **)(*DAT_0048c520 + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar4);
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),8);
    }
    if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),0xc);
    }
    scratch_index = (dword)*(short *)(&DAT_0048c74a + event_cursor * 6);
    if (scratch_index == 0x10) {
      FUN_0047f5a8(param_1);
    }
    if (DAT_00489ba4 == '\x01') {
      iVar2 = scratch_index * 5;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      scratch_index = iVar2 >> 2;
    }
    iVar11 = 0;
    iVar2 = 5;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = 7;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
                 *(int *)(*(int *)(param_1 + 0x254) + 0x30) + scratch_index * -2);
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_0040923c(0,scratch_index * 2,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar6 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar6,DAT_0048c578,DAT_0048c57c,piVar5);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = 6;
    break;
  case 8:
    (**(code **)(*DAT_0048c520 + 0x28))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c520 + 0x2c))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    uVar4 = (**(code **)(*DAT_0048c520 + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar4);
    uVar4 = (**(code **)(*DAT_0048c520 + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar4);
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),8);
    }
    if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),0xc);
    }
    scratch_index = (dword)*(short *)(&DAT_0048c74a + event_cursor * 6);
    if (scratch_index == 0x10) {
      FUN_0047f5a8(param_1);
    }
    if (DAT_00489ba4 == '\x01') {
      iVar2 = scratch_index * 5;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      scratch_index = iVar2 >> 2;
    }
    iVar11 = 0;
    iVar2 = 5;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = 7;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,scratch_index * 2)
    ;
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(0,(iVar2 - scratch_index) * 2,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),
                 auStack_20,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar6 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar6,DAT_0048c578,DAT_0048c57c,piVar5);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = 8;
    break;
  case 9:
    (**(code **)(*DAT_0048c520 + 0x28))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c520 + 0x2c))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    uVar4 = (**(code **)(*DAT_0048c520 + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar4);
    uVar4 = (**(code **)(*DAT_0048c520 + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar4);
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),8);
    }
    if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),0xc);
    }
    scratch_index = (dword)*(short *)(&DAT_0048c74a + event_cursor * 6);
    if (scratch_index == 0x10) {
      FUN_0047f5a8(param_1);
    }
    if (DAT_00489ba4 == '\x01') {
      iVar2 = scratch_index * 5;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      scratch_index = iVar2 >> 2;
    }
    iVar11 = 0;
    iVar2 = 0xc;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = 5;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    FUN_0040923c(0,0,scratch_index * 2,auStack_20,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30))
    ;
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c((iVar2 - scratch_index) * 2,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),
                 auStack_20,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar6 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar6,DAT_0048c578,DAT_0048c57c,piVar5);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = 6;
    break;
  case 10:
    (**(code **)(*DAT_0048c520 + 0x28))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c520 + 0x2c))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    uVar4 = (**(code **)(*DAT_0048c520 + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar4);
    uVar4 = (**(code **)(*DAT_0048c520 + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar4);
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),8);
    }
    if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),0xc);
    }
    scratch_index = (dword)*(short *)(&DAT_0048c74a + event_cursor * 6);
    if (scratch_index == 0x10) {
      FUN_0047f5a8(param_1);
    }
    if (DAT_00489ba4 == '\x01') {
      iVar2 = scratch_index * 5;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      scratch_index = iVar2 >> 2;
    }
    iVar11 = 0;
    iVar2 = 0xc;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = 5;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    FUN_0040923c(0,0,scratch_index * 2,auStack_20,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30))
    ;
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_0040923c(0,0,scratch_index * 2,auStack_20,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30))
    ;
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar6 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar6,DAT_0048c578,DAT_0048c57c,piVar5);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = 6;
    break;
  case 0xb:
    (**(code **)(*DAT_0048c520 + 0x28))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c520 + 0x2c))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    uVar4 = (**(code **)(*DAT_0048c520 + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar4);
    uVar4 = (**(code **)(*DAT_0048c520 + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar4);
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),8);
    }
    if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),0xc);
    }
    scratch_index = (dword)*(short *)(&DAT_0048c74a + event_cursor * 6);
    if (scratch_index == 0x10) {
      FUN_0047f5a8(param_1);
    }
    if (DAT_00489ba4 == '\x01') {
      iVar2 = scratch_index * 5;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      scratch_index = iVar2 >> 2;
    }
    iVar11 = 0;
    iVar2 = 0xc;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = 5;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,scratch_index * 2)
    ;
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,scratch_index * 2)
    ;
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar6 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar6,DAT_0048c578,DAT_0048c57c,piVar5);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = 6;
    break;
  case 0xc:
    (**(code **)(*DAT_0048c520 + 0x28))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c520 + 0x2c))
              (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    uVar4 = (**(code **)(*DAT_0048c520 + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar4);
    uVar4 = (**(code **)(*DAT_0048c520 + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar4);
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),8);
    }
    if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      FUN_0042c464(*(int *)(param_1 + 0x2ec),0xc);
    }
    scratch_index = (dword)*(short *)(&DAT_0048c74a + event_cursor * 6);
    if (scratch_index == 0x10) {
      FUN_0047f5a8(param_1);
    }
    if (DAT_00489ba4 == '\x01') {
      iVar2 = scratch_index * 5;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      scratch_index = iVar2 >> 2;
    }
    iVar11 = 0;
    iVar2 = 0xc;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    iVar11 = 0;
    iVar2 = 5;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar5,0,iVar2,iVar11);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a % 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c550 = ((int)(short)event_stack[event_cursor].a / 0xb) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(0,(iVar2 - scratch_index) * 2,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),
                 auStack_20,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c53c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    FUN_0040923c(0,(iVar2 - scratch_index) * 2,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),
                 auStack_20,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar8 = auStack_20;
    puVar9 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    piVar12 = &DAT_0048c53c;
    piVar5 = (int *)FUN_0041dad8((int)DAT_0048c520);
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_0041a530(piVar6,&DAT_0048c52c,piVar5,piVar12);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8((int)DAT_0048c514);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c524;
    piVar6 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar6,DAT_0048c54c,DAT_0048c550,piVar5);
    piVar5 = DAT_0048c514;
    piVar6 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar6,DAT_0048c578,DAT_0048c57c,piVar5);
    *(undefined *)(original_hero.floor * 0x7b + 0x4b8936 + (int)(short)event_stack[event_cursor].a)
         = 6;
  }
  return;
}
