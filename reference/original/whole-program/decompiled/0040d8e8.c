/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d8e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040d8e8(undefined4 param_1,int *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  
  puStack_24 = (undefined *)0x40d901;
  iVar2 = FUN_00402d04(*param_2);
  puStack_24 = (undefined *)0x40d906;
  iVar2 = FUN_004081a0(iVar2);
  iVar2 = (int)*(short *)(iVar2 + 8);
  if (0 < iVar2) {
    puStack_24 = (undefined *)0x40d922;
    puVar3 = (undefined4 *)FUN_00402650(iVar2 << 2);
    puStack_28 = &LAB_0040d991;
    uStack_2c = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_2c;
    puStack_24 = &stack0xfffffffc;
    iVar4 = FUN_00402d04(*param_2);
    FUN_0040829c(iVar4,puVar3);
    if (-1 < iVar2 + -1) {
      iVar4 = 0;
      do {
        puVar1 = (undefined4 *)puVar3[iVar4];
        uVar5 = FUN_004082ec(param_2,(int)puVar1);
        if ((char)uVar5 != '\0') {
          FUN_0040e318(param_1,param_2,puVar1);
        }
        iVar4 = iVar4 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    *in_FS_OFFSET = uStack_2c;
    puStack_24 = (undefined *)0x40d998;
    puStack_28 = (undefined *)0x40d990;
    FUN_00402668((int)puVar3);
    return;
  }
  puStack_24 = (undefined *)0x40d9a3;
  (**(code **)(*param_2 + 4))(param_2,param_1);
  return;
}

