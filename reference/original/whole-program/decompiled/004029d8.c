/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004029d8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004029d8(byte *param_1,int *param_2)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  
  pbVar5 = param_1;
  if (param_1 == (byte *)0x0) {
LAB_00402a33:
    pbVar5 = pbVar5 + 1;
  }
  else {
    uVar1 = 0;
    do {
      pbVar4 = pbVar5;
      bVar2 = *pbVar4;
      pbVar5 = pbVar4 + 1;
    } while (bVar2 == 0x20);
    if ((bVar2 != 0x2d) && (bVar2 != 0x2b)) {
      if (bVar2 != 0x24) goto LAB_00402a04;
      bVar2 = *pbVar5;
      pbVar5 = pbVar4 + 2;
      if (bVar2 == 0) goto LAB_00402a33;
      do {
        if (0x60 < bVar2) {
          bVar2 = bVar2 - 0x20;
        }
        bVar3 = bVar2 - 0x30;
        if (9 < bVar3) {
          if (5 < (byte)(bVar2 + 0xbf)) goto LAB_00402a3a;
          bVar3 = bVar2 - 0x37;
        }
        if (0xfffffff < uVar1) goto LAB_00402a3a;
        uVar1 = uVar1 * 0x10 + (uint)bVar3;
        bVar2 = *pbVar5;
        pbVar5 = pbVar5 + 1;
      } while (bVar2 != 0);
LAB_00402a2a:
      iVar6 = 0;
      goto LAB_00402a2d;
    }
    bVar2 = *pbVar5;
    pbVar5 = pbVar4 + 2;
LAB_00402a04:
    if (bVar2 != 0) {
      do {
        if ((9 < (byte)(bVar2 - 0x30)) || (0xccccccc < uVar1)) goto LAB_00402a3a;
        uVar1 = uVar1 * 10 + (uint)(byte)(bVar2 - 0x30);
        bVar2 = *pbVar5;
        pbVar5 = pbVar5 + 1;
      } while (bVar2 != 0);
      if (-1 < (int)uVar1) goto LAB_00402a2a;
    }
  }
LAB_00402a3a:
  iVar6 = (int)pbVar5 - (int)param_1;
LAB_00402a2d:
  *param_2 = iVar6;
  return;
}

