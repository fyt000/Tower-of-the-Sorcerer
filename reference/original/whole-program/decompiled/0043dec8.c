/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043dec8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043dec8(int *param_1)

{
  LPCSTR lpRootPathName;
  UINT UVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 extraout_EDX_06;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *in_FS_OFFSET;
  bool bVar4;
  undefined *puVar5;
  undefined4 uStack_34;
  undefined *puStack_30;
  undefined *puStack_2c;
  undefined4 uStack_1c;
  undefined uStack_18;
  byte bStack_17;
  byte *pbStack_14;
  DWORD DStack_d;
  byte bStack_9;
  int *piStack_8;
  
  puStack_2c = &stack0xfffffffc;
  pbStack_14 = (byte *)0x0;
  puStack_30 = &LAB_0043e06b;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  piStack_8 = param_1;
  FUN_004295b4(param_1);
  DStack_d = GetLogicalDrives();
  uVar3 = 0;
  uVar2 = extraout_EDX;
  do {
    bVar4 = uVar3 < 0x1f;
    if (uVar3 < 0x20) {
      bVar4 = (*(byte *)((int)&DStack_d + ((int)uVar3 >> 3)) >> (uVar3 & 7) & 1) != 0;
    }
    if (bVar4) {
      bStack_9 = (char)uVar3 + 0x61;
      FUN_004035ec((int *)&pbStack_14,CONCAT31((int3)((uint)uVar2 >> 8),bStack_9));
      FUN_00403658((int *)&pbStack_14,(undefined4 *)&DAT_0043e084);
      lpRootPathName = FUN_00403814(pbStack_14);
      UVar1 = GetDriveTypeA(lpRootPathName);
      uVar2 = extraout_EDX_00;
      if (*(char *)((int)piStack_8 + 0x15d) == '\x01') {
        bStack_9 = FUN_004028b0(bStack_9);
        uVar2 = extraout_EDX_01;
      }
      switch(UVar1 & 0xff) {
      case 2:
        bStack_17 = bStack_9;
        uStack_18 = 1;
        FUN_004028fc(&uStack_1c,(undefined4 *)&uStack_18);
        FUN_004028cc((byte *)&uStack_1c,&DAT_0043e088,2);
        FUN_004035fc((int *)&pbStack_14,(byte *)&uStack_1c);
        (**(code **)(*(int *)piStack_8[0x40] + 0x30))
                  ((int *)piStack_8[0x40],pbStack_14,piStack_8[0x58]);
        uVar2 = extraout_EDX_02;
        break;
      case 3:
        puVar5 = &stack0xfffffffc;
        FUN_0043d838((uint)bStack_9,&pbStack_14);
        FUN_0043de34(pbStack_14,piStack_8[0x59],extraout_ECX,(int)puVar5);
        uVar2 = extraout_EDX_03;
        break;
      case 4:
        puVar5 = &stack0xfffffffc;
        FUN_0043d9ac((uint)bStack_9,&pbStack_14);
        FUN_0043de34(pbStack_14,piStack_8[0x5a],extraout_ECX_00,(int)puVar5);
        uVar2 = extraout_EDX_04;
        break;
      case 5:
        puVar5 = &stack0xfffffffc;
        FUN_0043d838((uint)bStack_9,&pbStack_14);
        FUN_0043de34(pbStack_14,piStack_8[0x5b],extraout_ECX_01,(int)puVar5);
        uVar2 = extraout_EDX_05;
        break;
      case 6:
        puVar5 = &stack0xfffffffc;
        FUN_0043d838((uint)bStack_9,&pbStack_14);
        FUN_0043de34(pbStack_14,piStack_8[0x5c],extraout_ECX_02,(int)puVar5);
        uVar2 = extraout_EDX_06;
      }
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 != 0x1a);
  *in_FS_OFFSET = uStack_34;
  puStack_2c = &LAB_0043e072;
  puStack_30 = (undefined *)0x43e06a;
  FUN_004034dc((int *)&pbStack_14);
  return;
}

