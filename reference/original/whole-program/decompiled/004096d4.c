/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004096d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004096d4(undefined **param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined **ppuVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  int iVar2;
  undefined4 uStack_120;
  undefined *puStack_11c;
  undefined *puStack_118;
  byte local_108 [256];
  undefined *local_8;
  
  puStack_118 = &stack0xfffffffc;
  local_8 = (undefined *)0x0;
  puStack_11c = &LAB_0040975b;
  uStack_120 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_120;
  if ((param_1 != &PTR_FUN_00409144) && (param_1 != *(undefined ***)(param_4 + -8))) {
    iVar2 = param_4;
    ppuVar1 = (undefined **)FUN_00402bb8((int)param_1);
    FUN_004096d4(ppuVar1,extraout_EDX,extraout_ECX,iVar2);
    FUN_00402b7c((int)param_1,local_108);
    FUN_004035fc((int *)&local_8,local_108);
    FUN_004095cc(local_8,(int **)(param_4 + -4));
  }
  *in_FS_OFFSET = uStack_120;
  puStack_118 = &LAB_00409762;
  puStack_11c = (undefined *)0x40975a;
  FUN_004034dc((int *)&local_8);
  return;
}

