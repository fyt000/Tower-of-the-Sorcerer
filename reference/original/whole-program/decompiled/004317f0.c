/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004317f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004317f0(int *param_1,undefined4 param_2)

{
  uint uVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  MCIERROR MVar7;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  int iStack_18;
  int iStack_14;
  
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
  uVar1 = param_1[0x77];
  cVar2 = FUN_004320f0((int)param_1,extraout_EDX);
  if (cVar2 != '\n') {
    param_1[0x77] = uVar1 | 0x100;
LAB_00431977:
    iStack_18 = FUN_00416cbc(param_1);
    MVar7 = mciSendCommandA((uint)*(ushort *)((int)param_1 + 0x1e6),0x807,param_1[0x77],
                            (DWORD_PTR)&iStack_18);
    param_1[0x7e] = MVar7;
    return;
  }
  uVar5 = FUN_004320b0((int)param_1);
  FUN_004320b0((int)param_1);
  bVar3 = FUN_0042f840();
  iVar6 = FUN_00431c24((int)param_1,(uint)bVar3);
  cVar2 = FUN_0043206c((int)param_1);
  if (cVar2 != '\x02') {
    cVar2 = FUN_0042f840();
    iStack_14 = iVar6;
    if (cVar2 != '\x01') {
      cVar2 = root_0042f844(uVar5);
      cVar4 = root_0042f844(iVar6);
      if (cVar2 == cVar4) {
        cVar2 = root_0042f84c(uVar5);
        cVar4 = root_0042f84c(iVar6);
        if (cVar2 == cVar4) {
          FUN_004320b0((int)param_1);
          bVar3 = FUN_0042f840();
          iStack_14 = FUN_00431c24((int)param_1,bVar3 - 1);
        }
      }
    }
    param_1[0x77] = uVar1 | 8;
    goto LAB_00431977;
  }
  cVar2 = FUN_0042f840();
  if (cVar2 != '\x01') {
    cVar2 = root_0042f844(uVar5);
    cVar4 = root_0042f844(iVar6);
    if (cVar2 == cVar4) {
      cVar2 = root_0042f84c(uVar5);
      cVar4 = root_0042f84c(iVar6);
      if (cVar2 == cVar4) {
        FUN_004320b0((int)param_1);
        bVar3 = FUN_0042f840();
        iVar6 = FUN_00431c24((int)param_1,bVar3 - 1);
        FUN_00431c74((int)param_1,iVar6);
        uVar5 = extraout_EDX_00;
        goto LAB_004318f8;
      }
    }
  }
  FUN_00431c74((int)param_1,iVar6);
  uVar5 = extraout_EDX_01;
LAB_004318f8:
  FUN_00431250(param_1,uVar5);
  *(undefined *)((int)param_1 + 0x19e) = 0;
  return;
}

