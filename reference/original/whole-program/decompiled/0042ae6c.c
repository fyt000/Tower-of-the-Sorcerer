/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042ae6c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042ae6c(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int **ppiVar5;
  undefined4 *puVar6;
  byte bVar7;
  undefined4 local_94 [4];
  tagRECT local_84;
  undefined4 local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  undefined4 local_60;
  undefined4 local_5c;
  int local_58;
  int local_54;
  undefined4 local_50;
  undefined4 local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40 [4];
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  undefined4 *local_24;
  undefined4 local_1c;
  int local_18;
  undefined4 *local_14;
  int local_c;
  int local_8;
  
  bVar7 = 0;
  ppiVar5 = (int **)(param_4 + -4);
  local_1c = 0xbc2b;
  local_14 = &local_5c;
  local_18 = FUN_00416cbc(*ppiVar5);
  local_5c = 2;
  local_50 = 1;
  local_4c = 0;
  local_44 = *(undefined4 *)(*(int *)(param_4 + -8) + 4);
  local_58 = FUN_00416cbc(*ppiVar5);
  local_48 = FUN_00416cbc(*ppiVar5);
  local_2c = 0xbc2c;
  local_28 = FUN_00416cbc(*ppiVar5);
  local_24 = &local_74;
  local_74 = 2;
  local_70 = FUN_00416cbc(*ppiVar5);
  iVar3 = 0;
  iVar1 = FUN_0042aa80(*ppiVar5);
  GetClipBox(*(HDC *)(*(int *)(param_4 + -8) + 4),&local_84);
  local_8 = (*ppiVar5)[0xc];
  local_c = (*ppiVar5)[0xb];
  if (0 < local_8) {
    do {
      local_6c = iVar1;
      iVar2 = (**(code **)(*(int *)(*ppiVar5)[0x40] + 0x10))();
      if (iVar1 < iVar2) {
        local_60 = (**(code **)(*(int *)(*ppiVar5)[0x40] + 0x14))((int *)(*ppiVar5)[0x40],iVar1);
      }
      local_68 = local_c;
      local_64 = (*ppiVar5)[0x44];
      local_30 = local_60;
      local_54 = iVar1;
      FUN_00402d0c(*ppiVar5,(ushort *)&local_2c);
      FUN_0040923c(0,iVar3,local_68,local_94,local_64 + iVar3);
      puVar4 = local_94;
      puVar6 = local_40;
      for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar4;
        puVar4 = puVar4 + (uint)bVar7 * -2 + 1;
        puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
      }
      FUN_00402d0c(*ppiVar5,(ushort *)&local_1c);
      iVar3 = iVar3 + local_64;
      iVar1 = iVar1 + 1;
      iVar2 = (**(code **)(*(int *)(*ppiVar5)[0x40] + 0x10))();
    } while ((iVar1 < iVar2) && (iVar3 < local_8));
  }
  return;
}

