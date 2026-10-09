/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412a30.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00412a30(char param_1)

{
  int **ppiVar1;
  bool bVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined3 extraout_var;
  uint uVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  int local_10;
  undefined4 local_c;
  int *local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_8 = (int *)0x0;
  DAT_0048a69c = 0;
  puStack_20 = &LAB_00412b8f;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  FUN_00412540(DAT_0048a6a0,DAT_0048a6b0);
  local_8 = DAT_0048a6a0;
  if (DAT_0048a6cc == 0) {
    puStack_2c = (undefined *)0x412a8c;
    SetCursor(DAT_0048a6c4);
  }
  else {
    FUN_00418408(DAT_0048a6cc);
  }
  puStack_2c = &LAB_00412b69;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  ppiVar1 = DAT_0048a6a8;
  piVar3 = FUN_00402c7c(DAT_0048a6a8,(int *)&PTR_FUN_004115fc);
  if ((char)piVar3 == '\0') {
    local_10 = DAT_0048a6bc;
    local_c = DAT_0048a6c0;
    uVar4 = DAT_0048a6c0;
  }
  else {
    uVar4 = FUN_00413278((int *)ppiVar1,&DAT_0048a6bc,&local_10);
  }
  if (DAT_0048a6c8 != '\0') {
    bVar2 = FUN_00412780(CONCAT31((int3)((uint)uVar4 >> 8),1));
    if ((bVar2) && (param_1 != '\0')) {
      uVar4 = CONCAT31(extraout_var,1);
      goto LAB_00412af1;
    }
  }
  uVar4 = 0;
LAB_00412af1:
  DAT_0048a6a0 = (int *)0x0;
  uVar5 = 3;
  if ((char)uVar4 == '\0') {
    uVar5 = 4;
    DAT_0048a6bc = 0;
    DAT_0048a6c0 = 0;
    local_10 = 0;
    local_c = 0;
  }
  FUN_004126c4(DAT_0048a6ac,uVar5,local_8,&DAT_0048a6bc,DAT_0048a6a8);
  (**(code **)(*local_8 + 8))(local_8,DAT_0048a6a8,local_10,uVar4,local_c);
  DAT_0048a6a8 = (int **)0x0;
  *in_FS_OFFSET = uVar4;
  DAT_0048a6a0 = (int *)0x0;
  return;
}

