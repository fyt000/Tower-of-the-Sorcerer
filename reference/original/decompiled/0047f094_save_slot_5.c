/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 0047f094. Recovered by RecoverSaves.java.
 * Ghidra C-like inspection output; review assembly for inferred types.
 */

void save_slot_5(int param_1)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *puStack_8;

  puStack_18 = &stack0xfffffffc;
  puStack_8 = (undefined4 *)0x0;
  puStack_1c = &UNK_0047f167;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00450758(param_1);
  piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,0,&puStack_8);
  FUN_0040369c(&DAT_0048c5d4,puStack_8,(undefined4 *)&UNK_0047f17c);
  FUN_004102f0(*(int *)(param_1 + 0x35c),0);
  FUN_004102f0(*(int *)(param_1 + 0x360),0);
  FUN_004102f0(*(int *)(param_1 + 0x364),0);
  FUN_004102f0(*(int *)(param_1 + 0x368),0);
  FUN_004102f0(*(int *)(param_1 + 0x36c),1);
  FUN_004102f0(*(int *)(param_1 + 0x370),0);
  FUN_004102f0(*(int *)(param_1 + 0x374),0);
  FUN_004102f0(*(int *)(param_1 + 0x378),0);
  write_original_save(param_1);
  FUN_00450880(param_1);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &UNK_0047f16e;
  puStack_1c = (undefined *)0x47f166;
  FUN_004034dc((int *)&puStack_8);
  return;
}
