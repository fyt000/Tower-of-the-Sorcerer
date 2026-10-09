/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a714.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040a714(int *param_1,int param_2,uint param_3)

{
  bool bVar1;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint uVar2;
  uint extraout_ECX_01;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  undefined4 extraout_EDX_01;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  int iStack_8;
  
  puStack_18 = &stack0xfffffffc;
  iStack_8 = 0;
  puStack_1c = &LAB_0040a77a;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_0040c3cc(param_2,param_2,param_3);
  (**(code **)(*param_1 + 0x38))();
  uVar2 = extraout_ECX;
  uVar3 = extraout_EDX;
  while( true ) {
    bVar1 = FUN_0040ba68(param_2,uVar3,uVar2);
    if (bVar1) break;
    FUN_0040ce30(param_2,&iStack_8,extraout_ECX_01);
    (**(code **)(*param_1 + 0x2c))(param_1,iStack_8);
    uVar2 = extraout_ECX_00;
    uVar3 = extraout_EDX_00;
  }
  FUN_0040c3d4(param_2,extraout_EDX_01,extraout_ECX_01);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040a781;
  puStack_1c = (undefined *)0x40a779;
  FUN_004034dc(&iStack_8);
  return;
}

