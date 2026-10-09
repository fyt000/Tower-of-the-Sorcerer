/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004173fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004173fc(int *param_1)

{
  LONG LVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined *puStack_8;
  
  puStack_18 = &stack0xfffffffc;
  puStack_8 = (undefined *)0x0;
  puStack_1c = &UNK_00417479;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  (**(code **)(*param_1 + -0x10))();
  FUN_004135a4(param_1,(int *)&puStack_8);
  LVar1 = FUN_0041a830((int *)param_1[0x40],puStack_8);
  FUN_004130d8(param_1,LVar1 + 6);
  FUN_004135a4(param_1,(int *)&puStack_8);
  LVar1 = FUN_0041a874((int *)param_1[0x40],puStack_8);
  FUN_004130f8(param_1,LVar1 + 4);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &UNK_00417480;
  puStack_1c = (undefined *)0x417478;
  FUN_004034dc((int *)&puStack_8);
  return;
}

