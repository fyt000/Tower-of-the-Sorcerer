/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b714.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040b714(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 uVar6;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 uVar7;
  int iVar8;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  
  if ((DAT_0048a610 == (code *)0x0) || ((int)DAT_0048a61c[2] < 1)) {
    return;
  }
  puStack_1c = (undefined *)0x40b745;
  FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  puStack_20 = &LAB_0040b857;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  puStack_28 = (undefined *)0x40b762;
  puStack_1c = &stack0xfffffffc;
  piVar1 = (int *)FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
  puStack_2c = &LAB_0040b808;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  iVar8 = 0;
  puStack_28 = &stack0xfffffffc;
  do {
    while( true ) {
      if ((int)DAT_0048a61c[2] <= iVar8) {
        *in_FS_OFFSET = uStack_30;
        puStack_28 = &LAB_0040b80f;
        puStack_2c = (undefined *)0x40b807;
        FUN_00402c34(piVar1);
        return;
      }
      piVar2 = (int *)FUN_00409a40(DAT_0048a61c,iVar8);
      iVar3 = (*DAT_0048a610)(piVar2[4]);
      uVar6 = extraout_ECX_00;
      uVar7 = extraout_EDX_00;
      if (iVar3 == 0) break;
LAB_0040b7a3:
      if (iVar3 != 0) {
        pcVar5 = (char *)FUN_0040e968(iVar3,(undefined *)piVar2[5]);
        FUN_0040838c((int *)piVar2[1],(char **)piVar2[3],pcVar5);
        uVar6 = extraout_ECX_02;
        uVar7 = extraout_EDX_02;
      }
      FUN_0040b694(piVar2[1],uVar7,uVar6,(int)&stack0xfffffffc);
      FUN_004099e4(DAT_0048a61c,iVar8);
      FUN_00402c34(piVar2);
    }
    uVar4 = FUN_0040831c((int *)piVar2[1],(char **)piVar2[3]);
    uVar6 = extraout_ECX_01;
    uVar7 = extraout_EDX_01;
    if (uVar4 != 0) goto LAB_0040b7a3;
    FUN_0040b6cc(piVar2[1],extraout_EDX_01,extraout_ECX_01,(int)&stack0xfffffffc);
    iVar8 = iVar8 + 1;
  } while( true );
}

