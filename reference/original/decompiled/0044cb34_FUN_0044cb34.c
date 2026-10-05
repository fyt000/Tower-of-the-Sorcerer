/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 0044cb34. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_0044cb34(int param_1)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined4 *local_c;
  uint *local_8;

  puStack_1c = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  local_c = (undefined4 *)0x0;
  puStack_20 = &LAB_0044ccb1;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  if (original_hero.floor < 10) {
    puStack_1c = &stack0xfffffffc;
    FUN_0040352c((int *)&DAT_004b8674,(undefined4 *)&DAT_0044ccc8);
  }
  else {
    FUN_0040352c((int *)&DAT_004b8674,(undefined4 *)&DAT_0044ccd4);
  }
  piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
  (**(code **)(*piVar1 + 0xc))(piVar1,0xd4,&local_8);
  FUN_00403658((int *)&local_8,DAT_004b8674);
  FUN_00405b6c(original_hero.floor,(int *)&local_c);
  FUN_00403658((int *)&local_8,local_c);
  piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
  (**(code **)(*piVar1 + 0xc))(piVar1,0xd5,&local_c);
  FUN_00403658((int *)&local_8,local_c);
  FUN_004135d4(*(int **)(param_1 + 0x3f0),local_8);
  FUN_00405b6c(original_hero.hp,(int *)&local_8);
  FUN_004135d4(*(int **)(param_1 + 0x3c8),local_8);
  FUN_00405b6c(original_hero.attack,(int *)&local_8);
  FUN_004135d4(*(int **)(param_1 + 0x3cc),local_8);
  FUN_00405b6c(original_hero.defense,(int *)&local_8);
  FUN_004135d4(*(int **)(param_1 + 0x3d0),local_8);
  FUN_00405b6c(original_hero.gold,(int *)&local_8);
  FUN_004135d4(*(int **)(param_1 + 0x3d4),local_8);
  if (tile_class_or_message == 1) {
    FUN_004135d4(*(int **)(param_1 + 0x1c8),DAT_004b8684);
  }
  else {
    piVar1 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar1 + 0xc))(piVar1,tile_class_or_message + 0x7f,&local_8);
    FUN_004135d4(*(int **)(param_1 + 0x1c8),local_8);
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0044ccb8;
  puStack_20 = (undefined *)0x44ccb0;
  FUN_004034fc((int *)&local_c,2);
  return;
}
