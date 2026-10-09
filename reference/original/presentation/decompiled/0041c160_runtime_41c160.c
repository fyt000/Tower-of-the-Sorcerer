/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; runtime boundary 0041c160. */

void FUN_0041c160(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  int *local_8;
  
  local_8 = (int *)0x0;
  if (param_2 != (undefined4 *)0x0) {
    puStack_18 = (undefined *)0x41c17b;
    iVar1 = FUN_00402b78(param_2);
    puStack_18 = (undefined *)0x41c180;
    local_8 = (int *)(**(code **)(iVar1 + 0xc))(iVar1,1);
    puStack_18 = (undefined *)0x41c18d;
    (**(code **)(*local_8 + 8))(local_8,param_2);
    local_8[2] = param_1;
    local_8[1] = (int)FUN_0041c378;
  }
  puStack_1c = &LAB_0041c1c9;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  puStack_18 = &stack0xfffffffc;
  FUN_00402c34(*(int **)(param_1 + 4));
  *(int **)(param_1 + 4) = local_8;
  FUN_0041c378(param_1);
  *in_FS_OFFSET = uStack_20;
  return;
}

