/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c19c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040c19c(int param_1,int **param_2,uint param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  uint extraout_ECX;
  uint extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  uint extraout_ECX_03;
  uint extraout_ECX_04;
  uint uVar6;
  uint extraout_ECX_05;
  int **extraout_EDX;
  int **ppiVar7;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int iVar8;
  undefined4 extraout_EDX_04;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  
  ppiVar7 = param_2;
  while( true ) {
    puStack_20 = (undefined *)0x40c1be;
    bVar3 = FUN_0040ba68(param_1,ppiVar7,param_3);
    if (bVar3) break;
    puStack_20 = (undefined *)0x40c1b6;
    FUN_0040c524(param_1,param_2);
    param_3 = extraout_ECX;
    ppiVar7 = extraout_EDX;
  }
  puStack_20 = (undefined *)0x40c1ca;
  FUN_0040c3d4(param_1,extraout_EDX_00,extraout_ECX_00);
  uVar1 = *(undefined4 *)(param_1 + 0x28);
  uVar2 = *(undefined4 *)(param_1 + 0x24);
  puStack_20 = (undefined *)0x40c1e7;
  uVar4 = FUN_00402cdc((int *)param_2,extraout_EDX_01,extraout_ECX_01);
  *(undefined4 *)(param_1 + 0x28) = uVar4;
  puStack_24 = &LAB_0040c25e;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  puStack_20 = &stack0xfffffffc;
  iVar5 = FUN_00402cdc((int *)param_2,param_1,extraout_ECX_02);
  *(int *)(param_1 + 0x24) = iVar5;
  uVar6 = extraout_ECX_03;
  iVar8 = extraout_EDX_02;
  if (iVar5 == 0) {
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x18);
    iVar8 = param_1;
  }
  while( true ) {
    bVar3 = FUN_0040ba68(param_1,iVar8,uVar6);
    if (bVar3) break;
    FUN_0040bfe8(param_1,(int *)0x0);
    uVar6 = extraout_ECX_04;
    iVar8 = extraout_EDX_03;
  }
  FUN_0040c3d4(param_1,extraout_EDX_04,extraout_ECX_05);
  *in_FS_OFFSET = uStack_28;
  *(undefined4 *)(param_1 + 0x28) = uVar1;
  *(undefined4 *)(param_1 + 0x24) = uVar2;
  return;
}

