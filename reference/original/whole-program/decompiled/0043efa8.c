/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043efa8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043efa8(int param_1,int param_2,int *param_3)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 *puVar5;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined4 *local_18;
  undefined4 *local_14;
  int local_10;
  char *local_c;
  int *local_8;
  
  puStack_28 = &stack0xfffffffc;
  local_c = (char *)0x0;
  local_10 = 0;
  local_14 = (undefined4 *)0x0;
  local_18 = (undefined4 *)0x0;
  puStack_2c = &LAB_0043f11f;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  local_8 = param_3;
  FUN_004034dc(param_3);
  iVar2 = (**(code **)(**(int **)(param_1 + 0x100) + 0x10))();
  if (param_2 < iVar2) {
    FUN_00403570((int *)&local_c,*(int *)(param_1 + 0x158));
    iVar2 = (**(code **)(**(int **)(param_1 + 0x100) + 0x14))(*(int **)(param_1 + 0x100),param_2);
    if (param_2 == 0) {
      FUN_00405f04(local_c,(int *)&local_14);
      FUN_0040369c(local_8,local_14,(undefined4 *)&DAT_0043f138);
    }
    else if (iVar2 == *(int *)(param_1 + 0x14c)) {
      (**(code **)(**(int **)(param_1 + 0x100) + 0xc))(*(int **)(param_1 + 0x100),param_2,&local_14)
      ;
      FUN_0043d5cc(local_c,local_14,local_8);
    }
    else if (iVar2 == *(int *)(param_1 + 0x154)) {
      FUN_00403570(local_8,(int)local_c);
    }
    else {
      local_10 = 0;
      FUN_00405f04(local_c,(int *)&local_14);
      iVar2 = FUN_00403650((int)local_14);
      FUN_00403894((int *)&local_c,1,iVar2);
      iVar2 = 0;
      while (iVar4 = iVar2, param_2 + 1 != local_10) {
        iVar4 = iVar2 + 1;
        iVar3 = FUN_00403650((int)local_c);
        if (iVar3 < iVar4) break;
        iVar3 = FUN_0040ed20(local_c[iVar2]);
        if (iVar3 == 0) {
          pcVar1 = local_c + iVar2;
          iVar2 = iVar4;
          if (*pcVar1 == '\\') {
            local_10 = local_10 + 1;
          }
        }
        else {
          iVar2 = iVar2 + 2;
        }
      }
      FUN_00403854((int)local_c,1,iVar4 - 1,(int *)&local_14);
      puVar5 = local_14;
      FUN_00405f04(*(char **)(param_1 + 0x158),(int *)&local_18);
      FUN_0040369c(local_8,local_18,puVar5);
    }
  }
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_0043f126;
  puStack_2c = (undefined *)0x43f116;
  FUN_004034fc((int *)&local_18,2);
  puStack_2c = (undefined *)0x43f11e;
  FUN_004034dc((int *)&local_c);
  return;
}

