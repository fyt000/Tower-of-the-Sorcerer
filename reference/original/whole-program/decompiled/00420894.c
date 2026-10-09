/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420894.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00420894(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int iStack_20;
  int iStack_1c;
  int aiStack_18 [2];
  
  if (param_2 != (int *)0x0) {
    (**(code **)(*param_2 + 0x2c))(param_2,&local_30);
    local_30 = local_30 - (uint)*(ushort *)(param_1[0x40] + 0x1a);
    local_28 = local_28 + (uint)*(ushort *)(param_1[0x40] + 0x1a);
    local_2c = local_2c - (uint)*(ushort *)(param_1[0x41] + 0x1a);
    local_24 = local_24 + (uint)*(ushort *)(param_1[0x41] + 0x1a);
    FUN_0041324c(param_2,&local_30,aiStack_18);
    FUN_00413278(param_1,aiStack_18,&iStack_20);
    local_30 = iStack_20;
    local_2c = iStack_1c;
    FUN_0041324c(param_2,&local_28,aiStack_18);
    FUN_00413278(param_1,aiStack_18,&iStack_20);
    iVar1 = local_30;
    local_28 = iStack_20;
    local_24 = iStack_1c;
    if (local_30 < 0) {
      FUN_00420424(param_1[0x40],*(int *)(param_1[0x40] + 0xc) + local_30);
    }
    else {
      iVar2 = FUN_00413178(param_1);
      iVar3 = local_28;
      if (iVar2 < local_28) {
        iVar2 = FUN_00413178(param_1);
        if (iVar2 < iVar3 - iVar1) {
          local_28 = FUN_00413178(param_1);
          local_28 = local_28 + local_30;
        }
        iVar1 = param_1[0x40];
        iVar3 = FUN_00413178(param_1);
        FUN_00420424(iVar1,(*(int *)(iVar1 + 0xc) + local_28) - iVar3);
      }
    }
    iVar1 = local_2c;
    if (local_2c < 0) {
      FUN_00420424(param_1[0x41],*(int *)(param_1[0x41] + 0xc) + local_2c);
    }
    else {
      iVar2 = FUN_004131bc(param_1);
      iVar3 = local_24;
      if (iVar2 < local_24) {
        iVar2 = FUN_004131bc(param_1);
        if (iVar2 < iVar3 - iVar1) {
          local_24 = FUN_004131bc(param_1);
          local_24 = local_24 + local_2c;
        }
        iVar1 = param_1[0x41];
        iVar3 = FUN_004131bc(param_1);
        FUN_00420424(iVar1,(*(int *)(iVar1 + 0xc) + local_24) - iVar3);
      }
    }
  }
  return;
}

