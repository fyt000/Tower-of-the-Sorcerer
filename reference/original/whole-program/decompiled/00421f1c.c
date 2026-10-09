/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421f1c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00421f1c(int *param_1,int *param_2)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined3 uVar8;
  
  iVar4 = FUN_00414d88(param_1,param_2);
  if (param_1[8] == 0) {
    iVar4 = *(int *)(DAT_0048a6f8 + 0x20);
    param_2[7] = iVar4;
    param_2[1] = param_2[1] & 0xbffcffff;
  }
  param_2[9] = 8;
  if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
    if ((byte)(*(char *)((int)param_1 + 0x11b) - 1U) < 2) {
      param_2[3] = -0x80000000;
      param_2[4] = -0x80000000;
    }
    bVar3 = *(byte *)(param_1 + 0x45);
    uVar6 = (uint)bVar3;
    bVar1 = *(byte *)((int)param_1 + 0x115);
    if ((*(char *)((int)param_1 + 0x11a) == '\x01') && ((bVar1 == 0 || (bVar1 == 3)))) {
      bVar1 = 2;
    }
    uVar5 = (uint)bVar1;
    switch(uVar5) {
    case 0:
      if (param_1[8] == 0) {
        param_2[1] = param_2[1] | 0x80000000;
      }
      uVar6 = (uint)DAT_004220ec;
      break;
    case 1:
    case 4:
      param_2[1] = param_2[1] | 0xc00000;
      break;
    case 2:
    case 5:
      param_2[1] = param_2[1] | 0xc40000;
      if ((*(char *)((int)param_1 + 0x11b) == '\x01') ||
         (uVar5 = 0, *(char *)((int)param_1 + 0x11b) == '\x03')) {
        uVar5 = 0;
        param_2[5] = -0x80000000;
        param_2[6] = -0x80000000;
      }
      break;
    case 3:
      uVar6 = param_2[1] | 0x80c00000;
      param_2[1] = uVar6;
      param_2[2] = 0x101;
      if (DAT_0048a694 == '\0') {
        uVar6 = param_2[1] | 0x400080;
        param_2[1] = uVar6;
      }
      uVar5 = CONCAT31((int3)(uVar6 >> 8),DAT_004220f0 & bVar3);
      param_2[9] = 0x2808;
      uVar6 = uVar5;
    }
    uVar7 = uVar5 & 0xffffff00;
    if ((byte)(bVar1 - 4) < 2) {
      param_2[2] = 0x80;
      uVar7 = CONCAT31((int3)(uVar5 >> 8),DAT_004220f4 & (byte)uVar6);
      uVar6 = uVar7;
    }
    iVar4 = CONCAT31((int3)(uVar7 >> 8),bVar1) + -1;
    bVar3 = (byte)iVar4;
    uVar8 = (undefined3)((uint)iVar4 >> 8);
    iVar4 = CONCAT31(uVar8,bVar3 - 2);
    if (bVar3 < 2) {
      if ((*(char *)((int)param_1 + 0x11a) != '\x01') || ((uVar6 & 1) != 0)) {
        if ((uVar6 & 2) != 0) {
          param_2[1] = param_2[1] | 0x20000;
        }
        if ((uVar6 & 4) != 0) {
          param_2[1] = param_2[1] | 0x10000;
        }
      }
      cVar2 = *(char *)((int)param_1 + 0x116);
      iVar4 = CONCAT31(uVar8,cVar2);
      if (cVar2 == '\x01') {
        param_2[1] = param_2[1] | 0x20000000;
      }
      else if (cVar2 == '\x02') {
        param_2[1] = param_2[1] | 0x1000000;
      }
    }
    else {
      *(undefined *)((int)param_1 + 0x116) = 0;
    }
    if ((uVar6 & 1) != 0) {
      param_2[1] = param_2[1] | 0x80000;
    }
    if ((uVar6 & 8) != 0) {
      param_2[2] = param_2[2] | 0x400;
    }
    if (*(char *)((int)param_1 + 0x11a) == '\x01') {
      param_2[10] = (int)&DAT_00404eac;
    }
  }
  else {
    param_2[1] = param_2[1] | 0xcf0000;
  }
  return iVar4;
}

