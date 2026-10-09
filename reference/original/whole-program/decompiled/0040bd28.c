/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040bd28.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040bd28(int param_1,int *param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int **ppiVar4;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  uint extraout_ECX_02;
  uint extraout_ECX_03;
  uint extraout_ECX_04;
  uint extraout_ECX_05;
  uint uVar5;
  uint extraout_ECX_06;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 uVar6;
  undefined4 extraout_EDX_06;
  int iVar7;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  
  iVar7 = 0;
  puStack_18 = (undefined *)0x40bd3e;
  FUN_00409f3c((int)param_2);
  puStack_1c = &LAB_0040bdd3;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  uVar5 = extraout_ECX;
  uVar6 = extraout_EDX;
  puStack_18 = &stack0xfffffffc;
  while( true ) {
    bVar2 = FUN_0040ba68(param_1,uVar6,uVar5);
    if (bVar2) break;
    cVar1 = FUN_0040bbec(param_1,extraout_EDX_06,extraout_ECX_06);
    if ((byte)(cVar1 - 2U) < 3) {
      iVar7 = FUN_0040c360(param_1,extraout_EDX_00,extraout_ECX_00);
    }
    while( true ) {
      iVar3 = FUN_00409fc4((int)param_2);
      if (iVar7 < iVar3) break;
      FUN_00409e9c((int)param_2);
    }
    ppiVar4 = (int **)FUN_00409fcc((int)param_2,iVar7);
    FUN_0040c3cc(param_1,extraout_EDX_01,extraout_ECX_01);
    uVar5 = extraout_ECX_02;
    uVar6 = extraout_EDX_02;
    while( true ) {
      bVar2 = FUN_0040ba68(param_1,uVar6,uVar5);
      if (bVar2) break;
      FUN_0040c524(param_1,ppiVar4);
      uVar5 = extraout_ECX_03;
      uVar6 = extraout_EDX_03;
    }
    FUN_0040c3d4(param_1,extraout_EDX_04,extraout_ECX_04);
    iVar7 = iVar7 + 1;
    uVar5 = extraout_ECX_05;
    uVar6 = extraout_EDX_05;
  }
  FUN_0040c3d4(param_1,extraout_EDX_06,extraout_ECX_06);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040bdda;
  puStack_1c = (undefined *)0x40bdd2;
  FUN_00409fb8(param_2);
  return;
}

