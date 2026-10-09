/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043f250.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043f250(int *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStackY_3c;
  undefined *puStackY_38;
  undefined *puStackY_34;
  undefined4 uStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  byte bStack_11;
  char *pcStack_10;
  char *pcStack_c;
  int *piStack_8;
  
  puStack_24 = &stack0xfffffffc;
  pcStack_c = (char *)0x0;
  pcStack_10 = (char *)0x0;
  puStack_28 = &LAB_0043f33b;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  piStack_8 = param_1;
  iVar1 = FUN_00403650((int)param_2);
  if (iVar1 != 0) {
    iVar1 = FUN_0043e8c4((int)piStack_8,(byte *)param_2,(byte *)piStack_8[0x56]);
    if (iVar1 != 0) {
      puStackY_34 = (undefined *)0x43f2af;
      FUN_0043da80(param_2,(char *)&bStack_11,&pcStack_c,&pcStack_10);
      puStackY_38 = &LAB_0043f30e;
      uStackY_3c = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStackY_3c;
      puStackY_34 = &stack0xfffffffc;
      uVar2 = FUN_0043f1b4((int)piStack_8);
      if ((byte)uVar2 != bStack_11) {
        *(undefined *)(piStack_8 + 0x52) = 1;
        if ((int *)piStack_8[0x50] == (int *)0x0) {
          FUN_0043e6d4(piStack_8,bStack_11);
        }
        else {
          FUN_0043e08c((int *)piStack_8[0x50],bStack_11);
        }
      }
      *in_FS_OFFSET = uStackY_3c;
      *(undefined *)(piStack_8 + 0x52) = 0;
      return;
    }
  }
  *in_FS_OFFSET = uStack_2c;
  puStack_24 = &LAB_0043f342;
  puStack_28 = (undefined *)0x43f33a;
  FUN_004034fc((int *)&pcStack_10,2);
  return;
}

