/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004132bc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004132bc(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  byte bVar3;
  int local_1c;
  int local_18;
  int local_14;
  
  if (param_2 != param_3) {
    bVar3 = DAT_004133c8;
    if ((*(byte *)(param_1 + 7) & 1) != 0) {
      bVar3 = *(byte *)(param_1 + 0x17);
    }
    if ((bVar3 & 1) == 0) {
      iVar2 = param_1[9];
    }
    else {
      iVar2 = MulDiv(param_1[9],param_2,param_3);
    }
    if ((bVar3 & 2) == 0) {
      local_1c = param_1[10];
    }
    else {
      local_1c = MulDiv(param_1[10],param_2,param_3);
    }
    if (((bVar3 & 4) == 0) || ((*(byte *)((int)param_1 + 0x35) & 1) != 0)) {
      local_18 = param_1[0xb];
    }
    else {
      local_18 = MulDiv(param_1[9] + param_1[0xb],param_2,param_3);
      local_18 = local_18 - iVar2;
    }
    if (((bVar3 & 8) == 0) || ((*(byte *)((int)param_1 + 0x35) & 2) != 0)) {
      local_14 = param_1[0xc];
    }
    else {
      local_14 = MulDiv(param_1[10] + param_1[0xc],param_2,param_3);
      local_14 = local_14 - local_1c;
    }
    (**(code **)(*param_1 + 0x4c))(param_1,iVar2,local_1c,local_14,local_18);
    if ((*(char *)((int)param_1 + 0x39) == '\0') && ((bVar3 & 0x10) != 0)) {
      piVar1 = (int *)param_1[0x11];
      iVar2 = FUN_00419e30((int)piVar1);
      iVar2 = MulDiv(iVar2,param_2,local_14);
      FUN_00419e4c(piVar1,iVar2);
    }
  }
  *(undefined *)(param_1 + 0x17) = DAT_004133cc;
  return;
}

