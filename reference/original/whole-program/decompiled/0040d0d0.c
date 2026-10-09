/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d0d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040d0d0(int param_1,undefined4 param_2)

{
  undefined *puVar1;
  bool bVar2;
  uint uVar3;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  uint extraout_ECX_02;
  uint extraout_ECX_03;
  uint extraout_ECX_04;
  uint extraout_ECX_05;
  uint extraout_ECX_06;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 uVar4;
  undefined4 extraout_EDX_04;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  int iStack_10;
  int iStack_c;
  byte bStack_5;
  
  puStack_20 = &stack0xfffffffc;
  uVar3 = 0;
  iStack_10 = 0;
  puStack_24 = &UNK_0040d161;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  puVar1 = &stack0xfffffffc;
  if ((char)param_2 != '\0') {
    FUN_0040c3dc(param_1,&bStack_5,&iStack_c);
    FUN_0040cdf4(param_1,&iStack_10,extraout_ECX);
    FUN_0040cdf4(param_1,&iStack_10,extraout_ECX_00);
    uVar3 = extraout_ECX_01;
    param_2 = extraout_EDX;
    puVar1 = puStack_20;
  }
  while( true ) {
    puStack_20 = puVar1;
    bVar2 = FUN_0040ba68(param_1,param_2,uVar3);
    if (bVar2) break;
    FUN_0040d084(param_1,extraout_EDX_01,extraout_ECX_03);
    uVar3 = extraout_ECX_02;
    param_2 = extraout_EDX_00;
    puVar1 = puStack_20;
  }
  FUN_0040c3d4(param_1,extraout_EDX_01,extraout_ECX_03);
  uVar3 = extraout_ECX_04;
  uVar4 = extraout_EDX_02;
  while( true ) {
    bVar2 = FUN_0040ba68(param_1,uVar4,uVar3);
    if (bVar2) break;
    root_0040d0d0(param_1,1);
    uVar3 = extraout_ECX_05;
    uVar4 = extraout_EDX_03;
  }
  FUN_0040c3d4(param_1,extraout_EDX_04,extraout_ECX_06);
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &UNK_0040d168;
  puStack_24 = (undefined *)0x40d160;
  FUN_004034dc(&iStack_10);
  return;
}

