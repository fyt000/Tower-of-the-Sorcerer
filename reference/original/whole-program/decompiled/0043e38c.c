/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043e38c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043e38c(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  byte *pbStack_8;
  
  puStack_18 = &stack0xfffffffc;
  pbStack_8 = (byte *)0x0;
  puStack_1c = &LAB_0043e3ef;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00413eac((int)param_1);
  iVar1 = FUN_0042961c(param_1);
  if (-1 < iVar1) {
    uVar2 = FUN_0042961c(param_1);
    (**(code **)(*(int *)param_1[0x40] + 0xc))((int *)param_1[0x40],uVar2,&pbStack_8);
    FUN_0043e08c(param_1,*pbStack_8);
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0043e3f6;
  puStack_1c = (undefined *)0x43e3ee;
  FUN_004034dc((int *)&pbStack_8);
  return;
}

