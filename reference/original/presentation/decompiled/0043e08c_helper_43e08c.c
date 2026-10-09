/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0043e08c.
 * Inferred types and shared tails require assembly review. */

void FUN_0043e08c(int *param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 uVar5;
  undefined4 extraout_ECX_03;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  WPARAM WVar6;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  int local_10;
  byte *local_c;
  byte local_5;
  undefined3 extraout_var;
  
  puStack_20 = &stack0xfffffffc;
  local_c = (byte *)0x0;
  puStack_24 = &LAB_0043e1b3;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  local_5 = param_2;
  iVar3 = FUN_0042961c(param_1);
  if (-1 < iVar3) {
    bVar1 = FUN_004028b0(local_5);
    bVar2 = FUN_004028b0(*(byte *)(param_1 + 0x57));
    if (bVar1 == bVar2) goto LAB_0043e19d;
  }
  if (local_5 == 0) {
    *(undefined *)(param_1 + 0x57) = 0;
    FUN_00429638(param_1,0xffffffff);
    uVar5 = extraout_ECX;
    uVar4 = extraout_EDX;
  }
  else {
    if (*(char *)((int)param_1 + 0x15d) == '\x01') {
      bVar1 = FUN_004028b0(local_5);
      *(byte *)(param_1 + 0x57) = bVar1;
    }
    else {
      bVar1 = FUN_004028b0(local_5);
      *(byte *)(param_1 + 0x57) = bVar1 + 0x20;
    }
    local_10 = (**(code **)(*(int *)param_1[0x40] + 0x10))();
    uVar5 = extraout_ECX_00;
    uVar4 = extraout_EDX_00;
    if (-1 < local_10 + -1) {
      WVar6 = 0;
      do {
        (**(code **)(*(int *)param_1[0x40] + 0xc))((int *)param_1[0x40],WVar6,&local_c);
        bVar1 = FUN_004028b0(*local_c);
        uVar4 = CONCAT31(extraout_var,bVar1);
        bVar2 = FUN_004028b0(*(byte *)(param_1 + 0x57));
        if ((bVar1 == bVar2) && (local_c[1] == 0x3a)) {
          FUN_00429638(param_1,WVar6);
          uVar5 = extraout_ECX_02;
          uVar4 = extraout_EDX_01;
          break;
        }
        WVar6 = WVar6 + 1;
        local_10 = local_10 + -1;
        uVar5 = extraout_ECX_01;
      } while (local_10 != 0);
    }
  }
  if ((int *)param_1[0x56] != (int *)0x0) {
    FUN_0043e6d4((int *)param_1[0x56],*(byte *)(param_1 + 0x57));
    uVar5 = extraout_ECX_03;
    uVar4 = extraout_EDX_02;
  }
  FUN_00402cdc(param_1,uVar4,uVar5);
LAB_0043e19d:
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_0043e1ba;
  puStack_24 = (undefined *)0x43e1b2;
  FUN_004034dc((int *)&local_c);
  return;
}

