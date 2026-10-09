/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043a3fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043a3fc(void)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_2c;
  code *pcStack_28;
  undefined *puStack_24;
  undefined4 uStack_20;
  code *pcStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  pcStack_1c = thunk_FUN_00403140;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  piVar1 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
  puStack_24 = (undefined *)0x43a42d;
  (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_8);
  puStack_24 = (undefined *)0x43a43f;
  FUN_0040369c((int *)&DAT_0048a76c,local_8,(undefined4 *)"\\save0.dat");
  puStack_24 = (undefined *)0x43a44f;
  FUN_0040414d((undefined4 *)&DAT_0048a770,DAT_0048a76c);
  pcStack_28 = thunk_FUN_00402f4c;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  puStack_24 = &stack0xfffffffc;
  FUN_0040458d((HANDLE *)&DAT_0048a770,(HANDLE)0x1);
  FUN_00402710();
  FUN_004041f0((HANDLE *)&DAT_0048a770,&DAT_0048ab68,0x1881,(uint *)0x0);
  FUN_00402710();
  FUN_004041f0((HANDLE *)&DAT_0048a770,&DAT_0048a8bc,0x2ac,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048a770);
  FUN_00402710();
  *in_FS_OFFSET = uStack_2c;
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0043a4e7;
  pcStack_1c = (code *)0x43a4df;
  FUN_004034dc((int *)&local_8);
  return;
}

