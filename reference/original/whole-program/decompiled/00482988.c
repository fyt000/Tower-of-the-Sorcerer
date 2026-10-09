/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00482988.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00482988(int param_1)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_1c = &LAB_00482a5f;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  original_hero._344_4_ = 0;
  original_hero._348_4_ = 0;
  piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_8);
  FUN_0040369c((int *)&DAT_0048c5d4,local_8,(undefined4 *)"\\save0.dat");
  FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
  FUN_004045a4((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
  FUN_00402710();
  FUN_00404254((HANDLE *)&DAT_0048c600,original_maps,0x1881,(uint *)0x0);
  FUN_00402710();
  FUN_00404254((HANDLE *)&DAT_0048c600,&original_hero,0x2ac,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048c600);
  FUN_00402710();
  FUN_004237dc(DAT_0048a764);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_00482a66;
  puStack_1c = (undefined *)0x482a5e;
  FUN_004034dc((int *)&local_8);
  return;
}

