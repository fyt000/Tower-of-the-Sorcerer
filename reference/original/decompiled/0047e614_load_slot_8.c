/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 0047e614. Recovered by RecoverSaves.java.
 * Ghidra C-like inspection output; review assembly for inferred types.
 */

void load_slot_8(int param_1)

{
  int *piVar1;
  undefined *puVar2;
  int extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *puStack_8;

  puStack_18 = &stack0xfffffffc;
  puStack_8 = (undefined4 *)0x0;
  puStack_1c = &UNK_0047e79e;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  puVar2 = &stack0xfffffffc;
  if (*(char *)(*(int *)(param_1 + 0x41c) + 0x20) == '\x01') {
    FUN_0042c454(*(int *)(param_1 + 0x41c),'\0');
    puVar2 = puStack_18;
  }
  puStack_18 = puVar2;
  FUN_00450758(param_1);
  piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,0,&puStack_8);
  FUN_0040369c((int *)&DAT_0048c5d4,puStack_8,(undefined4 *)"\\save0.dat");
  FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
  FUN_004045a4((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
  FUN_00402710();
  FUN_00404254((HANDLE *)&DAT_0048c600,original_maps,0x1881,(uint *)0x0);
  FUN_00402710();
  FUN_00404254((HANDLE *)&DAT_0048c600,&original_hero,0x2ac,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048c600);
  FUN_00402710();
  piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,0,&puStack_8);
  FUN_0040369c((int *)&DAT_0048c5d4,puStack_8,(undefined4 *)&UNK_0047e7c8);
  FUN_004102f0(*(int *)(param_1 + 0x37c),0);
  FUN_004102f0(*(int *)(param_1 + 0x380),0);
  FUN_004102f0(*(int *)(param_1 + 900),0);
  FUN_004102f0(*(int *)(param_1 + 0x388),0);
  FUN_004102f0(*(int *)(param_1 + 0x38c),0);
  FUN_004102f0(*(int *)(param_1 + 0x390),0);
  FUN_004102f0(*(int *)(param_1 + 0x394),0);
  FUN_004102f0(*(int *)(param_1 + 0x398),1);
  FUN_0047e7d4(param_1,extraout_EDX,extraout_ECX);
  FUN_00450880(param_1);
  if (*(char *)(*(int *)(param_1 + 0x1b4) + 0x20) == '\0') {
    FUN_0042c454(*(int *)(param_1 + 0x1b4),'\x01');
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &UNK_0047e7a5;
  puStack_1c = (undefined *)0x47e79d;
  FUN_004034dc((int *)&puStack_8);
  return;
}
