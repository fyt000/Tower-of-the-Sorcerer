/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00484a50.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TTSW10_K6Click(int param_1)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *puStack_8;
  
  puStack_18 = &stack0xfffffffc;
  puStack_8 = (uint *)0x0;
  puStack_1c = &UNK_00484b04;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,0,&puStack_8);
  FUN_004135d4((int *)_DAT_0048c50c[0x72],puStack_8);
  piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,0,&puStack_8);
  FUN_0040352c((int *)&DAT_0048c5dc,puStack_8);
  FUN_0043e08c((int *)_DAT_0048c50c[0x6c],*_DAT_0048c5dc);
  (**(code **)(*(int *)_DAT_0048c50c[0x6d] + 0x8c))((int *)_DAT_0048c50c[0x6d],_DAT_0048c5dc);
  FUN_004237dc(_DAT_0048c50c);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &UNK_00484b0b;
  puStack_1c = (undefined *)0x484b03;
  FUN_004034dc((int *)&puStack_8);
  return;
}

