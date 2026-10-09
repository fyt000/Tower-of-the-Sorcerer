/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a7e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040a7e0(int *param_1,int *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  int iStack_8;
  
  puStack_18 = &stack0xfffffffc;
  iStack_8 = 0;
  puStack_1c = &LAB_0040a835;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  puVar1 = (undefined4 *)(**(code **)(*param_1 + 0x44))();
  FUN_00403608(&iStack_8,puVar1);
  iVar2 = FUN_00403650(iStack_8);
  FUN_0040af88(param_2,iStack_8,iVar2);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040a83c;
  puStack_1c = (undefined *)0x40a834;
  FUN_004034dc(&iStack_8);
  return;
}

