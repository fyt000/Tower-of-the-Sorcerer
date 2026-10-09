/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b998.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040b998(int param_1,undefined *param_2)

{
  int iVar1;
  uint uVar2;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  uint uVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 uVar4;
  undefined4 *in_FS_OFFSET;
  code *in_stack_0000000c;
  undefined4 in_stack_00000010;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint uStack_10;
  int *piStack_c;
  int iStack_8;
  
  puStack_18 = (undefined *)0x40b9b1;
  iStack_8 = param_1;
  iVar1 = FUN_00405a34(param_2,*(undefined **)(param_1 + 0x50));
  if (iVar1 == 0) {
    puStack_18 = (undefined *)0x40b9c1;
    uVar2 = FUN_0040ce90(iStack_8,extraout_EDX,extraout_ECX);
    uVar3 = extraout_ECX_00;
    uVar4 = extraout_EDX_00;
    if ((char)uVar2 != '\n') {
      *(int *)(iStack_8 + 0x10) = *(int *)(iStack_8 + 0x10) + -1;
      puStack_18 = (undefined *)0x40b9d3;
      FUN_0040cf94(iStack_8,extraout_EDX_00,extraout_ECX_00);
      *(undefined *)(iStack_8 + 0x4c) = 1;
      puStack_18 = (undefined *)0x40b9df;
      FUN_0040b8e0(iStack_8,extraout_EDX_01);
      uVar3 = extraout_ECX_01;
      uVar4 = extraout_EDX_02;
    }
    puStack_18 = (undefined *)0x40b9eb;
    piStack_c = (int *)FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)uVar4 >> 8),1),uVar3);
    puStack_1c = &LAB_0040ba4e;
    uStack_20 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_20;
    puStack_18 = &stack0xfffffffc;
    FUN_0040bc08(iStack_8,&uStack_10,4);
    FUN_0040b2e8(piStack_c,uStack_10);
    FUN_0040bc08(iStack_8,(undefined4 *)piStack_c[1],uStack_10);
    *(undefined *)(iStack_8 + 0x4c) = 1;
    (*in_stack_0000000c)(in_stack_00000010,piStack_c);
    *in_FS_OFFSET = uStack_20;
    puStack_18 = &DAT_0040ba55;
    puStack_1c = (undefined *)0x40ba4d;
    FUN_00402c34(piStack_c);
    return;
  }
  return;
}

