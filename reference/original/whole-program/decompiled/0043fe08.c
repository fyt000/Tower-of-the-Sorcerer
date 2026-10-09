/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043fe08.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043fe08(int *param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar5;
  undefined4 *puStack_2c;
  undefined uStack_28;
  char acStack_24 [4];
  undefined uStack_20;
  char *pcStack_1c;
  undefined uStack_18;
  byte *pbStack_14;
  char cStack_d;
  uint *puStack_c;
  char *pcStack_8;
  
  pbStack_14 = (byte *)0x0;
  pcStack_8 = (char *)0x0;
  puStack_c = (uint *)0x0;
  uVar5 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffbc;
  (**(code **)(*param_1 + 0x98))(param_1,&pbStack_14);
  iVar2 = FUN_0043c180(pbStack_14,(byte *)param_2);
  if (iVar2 != 0) {
    iVar2 = FUN_00403650((int)param_2);
    if (iVar2 != 0) {
      FUN_0043da80(param_2,&cStack_d,&pcStack_8,(char **)&puStack_c);
      piVar1 = (int *)param_1[0x53];
      if (piVar1 == (int *)0x0) {
        acStack_24[0] = cStack_d;
        uStack_20 = 2;
        pcStack_1c = pcStack_8;
        uStack_18 = 0xb;
        FUN_0040661c((byte *)"%s:%s",acStack_24,1,(int *)&pbStack_14);
        FUN_0043fd08(param_1,pbStack_14);
      }
      else {
        (**(code **)(*piVar1 + 0x8c))(piVar1,param_2);
      }
      pcVar3 = FUN_004038dc("*",(char *)puStack_c);
      if ((int)pcVar3 < 1) {
        pcVar3 = FUN_004038dc("?",(char *)puStack_c);
        if ((int)pcVar3 < 1) {
          iVar2 = FUN_00403650((int)puStack_c);
          if (0 < iVar2) {
            FUN_0043fab4(param_1,(byte *)puStack_c);
            uVar4 = FUN_00405dbc((undefined *)puStack_c);
            if ((char)uVar4 == '\0') {
              uStack_28 = 0xb;
              uVar5 = 0;
              puStack_2c = param_2;
              uVar4 = FUN_0040753c(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf0a2,0,
                                   &puStack_2c);
              FUN_004031f8(uVar4);
            }
            else {
              FUN_0043fa68(param_1,(int *)&pbStack_14);
              if (pbStack_14 == (byte *)0x0) {
                FUN_0043fd80(param_1,puStack_c);
                FUN_0043fab4(param_1,(byte *)puStack_c);
              }
            }
          }
          goto LAB_0043ff50;
        }
      }
      FUN_0043fd80(param_1,puStack_c);
    }
  }
LAB_0043ff50:
  *in_FS_OFFSET = uVar5;
  FUN_004034dc((int *)&pbStack_14);
  FUN_004034fc((int *)&puStack_c,2);
  return;
}

