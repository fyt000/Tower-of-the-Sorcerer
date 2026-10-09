/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040da50.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040da50(uint param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  uint extraout_ECX_02;
  uint uVar2;
  uint uVar3;
  undefined4 *in_FS_OFFSET;
  bool bVar4;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined *)0x0;
  puStack_1c = &LAB_0040dad4;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  iVar1 = FUN_004081a0(*(int *)(param_4 + -0x10));
  iVar1 = *(int *)(iVar1 + 1);
  FUN_0040e4a4(*(int *)(param_4 + -4),0xb,extraout_ECX);
  uVar3 = 0;
  uVar2 = extraout_ECX_00;
  do {
    bVar4 = uVar3 < 0x1f;
    if (uVar3 < 0x20) {
      bVar4 = (param_1 >> (uVar3 & 0x1f) & 1) != 0;
    }
    if (bVar4) {
      FUN_004081ac(iVar1,uVar3,(int *)&local_8);
      FUN_0040e400(*(int *)(param_4 + -4),local_8,extraout_ECX_01);
      uVar2 = extraout_ECX_02;
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 != 0x20);
  FUN_0040e400(*(int *)(param_4 + -4),(undefined *)0x0,uVar2);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040dadb;
  puStack_1c = (undefined *)0x40dad3;
  FUN_004034dc((int *)&local_8);
  return;
}

