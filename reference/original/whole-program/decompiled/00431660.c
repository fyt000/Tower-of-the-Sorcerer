/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431660.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00431660(int *param_1,undefined4 param_2)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  MCIERROR MVar8;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  int local_14;
  undefined4 local_10;
  
  FUN_00430e1c((int)param_1,param_2);
  param_1[0x77] = 0;
  if (*(char *)((int)param_1 + 0x1e2) == '\0') {
    param_1[0x77] = 2;
  }
  else {
    if (*(char *)(param_1 + 0x78) != '\0') {
      param_1[0x77] = 2;
    }
    *(undefined *)((int)param_1 + 0x1e2) = 0;
  }
  if (*(char *)((int)param_1 + 0x1e3) != '\0') {
    if (*(char *)((int)param_1 + 0x1e1) != '\0') {
      param_1[0x77] = param_1[0x77] | 1;
    }
    *(undefined *)((int)param_1 + 0x1e3) = 0;
  }
  uVar3 = param_1[0x77];
  cVar1 = FUN_004320f0((int)param_1,extraout_EDX);
  if (cVar1 == '\n') {
    cVar1 = FUN_0043206c((int)param_1);
    if (cVar1 == '\x02') {
      FUN_004320b0((int)param_1);
      uVar3 = FUN_0042f840();
      uVar4 = FUN_00432024((int)param_1,extraout_EDX_00);
      if ((uVar3 & 0xff) == uVar4) {
        uVar5 = FUN_00432024((int)param_1,extraout_EDX_01);
        iVar6 = FUN_00431c24((int)param_1,uVar5);
        FUN_00431c74((int)param_1,iVar6);
        uVar5 = extraout_EDX_02;
      }
      else {
        FUN_004320b0((int)param_1);
        bVar2 = FUN_0042f840();
        iVar6 = FUN_00431c24((int)param_1,bVar2 + 1);
        FUN_00431c74((int)param_1,iVar6);
        uVar5 = extraout_EDX_03;
      }
      FUN_00431250(param_1,uVar5);
      *(undefined *)((int)param_1 + 0x19e) = 0;
      return;
    }
    FUN_004320b0((int)param_1);
    uVar4 = FUN_0042f840();
    uVar7 = FUN_00432024((int)param_1,extraout_EDX_04);
    if ((uVar4 & 0xff) == uVar7) {
      uVar5 = FUN_00432024((int)param_1,extraout_EDX_05);
      local_10 = FUN_00431c24((int)param_1,uVar5);
    }
    else {
      FUN_004320b0((int)param_1);
      bVar2 = FUN_0042f840();
      local_10 = FUN_00431c24((int)param_1,bVar2 + 1);
    }
    param_1[0x77] = uVar3 | 8;
  }
  else {
    param_1[0x77] = uVar3 | 0x200;
  }
  local_14 = FUN_00416cbc(param_1);
  MVar8 = mciSendCommandA((uint)*(ushort *)((int)param_1 + 0x1e6),0x807,param_1[0x77],
                          (DWORD_PTR)&local_14);
  param_1[0x7e] = MVar8;
  return;
}

