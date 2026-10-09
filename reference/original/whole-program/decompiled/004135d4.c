/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004135d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004135d4(int *param_1,uint *param_2)

{
  undefined *puVar1;
  undefined4 *in_FS_OFFSET;
  undefined uVar2;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  uVar2 = 1;
  puStack_1c = &LAB_0041362a;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_004135a4(param_1,(int *)&local_8);
  FUN_00403760(local_8,param_2);
  if (!(bool)uVar2) {
    puVar1 = FUN_00403814((undefined *)param_2);
    FUN_00413580(param_1,puVar1);
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_00413631;
  puStack_1c = (undefined *)0x413629;
  FUN_004034dc((int *)&local_8);
  return;
}

