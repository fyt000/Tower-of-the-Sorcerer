/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a960.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040a960(int *param_1,int param_2)

{
  int iVar1;
  undefined4 extraout_ECX;
  uint extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined4 *puStack_10;
  int iStack_c;
  int *piStack_8;
  
  puStack_20 = &stack0xfffffffc;
  puStack_10 = (undefined4 *)0x0;
  puStack_24 = &LAB_0040a9d6;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  iStack_c = param_2;
  piStack_8 = param_1;
  FUN_0040d894(param_2,param_2,0);
  iVar1 = (**(code **)(*piStack_8 + 0x10))();
  uVar2 = extraout_ECX;
  uVar3 = extraout_EDX;
  if (-1 < iVar1 + -1) {
    iVar4 = 0;
    do {
      (**(code **)(*piStack_8 + 0xc))(piStack_8,iVar4,&puStack_10);
      FUN_0040e448(iStack_c,puStack_10,extraout_ECX_00);
      iVar4 = iVar4 + 1;
      iVar1 = iVar1 + -1;
      uVar2 = extraout_ECX_01;
      uVar3 = extraout_EDX_00;
    } while (iVar1 != 0);
  }
  FUN_0040d89c(iStack_c,uVar3,uVar2);
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_0040a9dd;
  puStack_24 = (undefined *)0x40a9d5;
  FUN_004034dc((int *)&puStack_10);
  return;
}

