/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040fe64.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040fe64(int param_1,HMENU param_2)

{
  undefined *puVar1;
  ushort uVar2;
  int iVar3;
  int *piVar4;
  DWORD DVar5;
  LPCSTR pCVar6;
  UINT_PTR uIDNewItem;
  uint uVar7;
  int *in_FS_OFFSET;
  byte bVar8;
  int iStack_5c;
  int iStack_50;
  undefined *puStack_4c;
  undefined *puStack_48;
  int local_38;
  MENUITEMINFOA local_34;
  
  puStack_48 = &stack0xfffffffc;
  local_38 = 0;
  local_34.hbmpItem = (HBITMAP)0x0;
  puStack_4c = &LAB_00410069;
  iStack_50 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_50;
  puVar1 = &stack0xfffffffc;
  if (*(char *)(param_1 + 0x2c) == '\0') goto LAB_0041004b;
  FUN_00403570((int *)&local_34.hbmpItem,*(int *)(param_1 + 0x20));
  iVar3 = FUN_0041040c(param_1);
  if (iVar3 < 1) {
    if (*(short *)(param_1 + 0x40) != 0) {
      iVar3 = *(int *)(param_1 + 0x44);
      if ((iVar3 != 0) && (*(int *)(iVar3 + 0x44) == 0)) {
        piVar4 = FUN_00402c7c(*(int ***)(iVar3 + 4),(int *)&PTR_FUN_0040f538);
        if ((char)piVar4 != '\0') goto LAB_0040fefc;
      }
      FUN_0040f848(*(ushort *)(param_1 + 0x40),&local_38);
      iStack_5c = local_38;
      FUN_00403710((int *)&local_34.hbmpItem,3);
    }
  }
  else {
    local_34.hSubMenu = (HMENU)FUN_0041021c(param_1);
  }
LAB_0040fefc:
  DVar5 = GetVersion();
  uVar2 = (ushort)DVar5 & 0xff;
  bVar8 = uVar2 == 4;
  if (uVar2 < 4) {
    FUN_00403760(*(uint **)(param_1 + 0x20),(uint *)&DAT_0041008c);
    uVar7 = *(uint *)(&DAT_00489238 + (bVar8 & 0x7f) * 4) |
            *(uint *)(&DAT_0048922c + (uint)*(byte *)(param_1 + 0x2e) * 4) |
            *(uint *)(&DAT_0048921c + (uint)*(byte *)(param_1 + 0x28) * 4) |
            *(uint *)(&DAT_00489224 + (uint)*(byte *)(param_1 + 0x29) * 4);
    iVar3 = FUN_0041040c(param_1);
    if (iVar3 < 1) {
      pCVar6 = FUN_00403814((undefined *)local_34.hbmpItem);
      InsertMenuA(param_2,0xffffffff,uVar7 | 0x400,(uint)*(ushort *)(param_1 + 0x30),pCVar6);
      puVar1 = puStack_48;
    }
    else {
      pCVar6 = FUN_00403814(*(undefined **)(param_1 + 0x20));
      uIDNewItem = FUN_0041021c(param_1);
      InsertMenuA(param_2,0xffffffff,uVar7 | 0x410,uIDNewItem,pCVar6);
      puVar1 = puStack_48;
    }
  }
  else {
    local_34.cbSize = 0x2c;
    local_34.fMask = 0x3f;
    FUN_00403760(*(uint **)(param_1 + 0x20),(uint *)&DAT_0041008c);
    local_34.fType =
         *(uint *)(&DAT_0048926c + (bVar8 & 0x7f) * 4) |
         *(uint *)(&DAT_00489264 + (uint)*(byte *)(param_1 + 0x2b) * 4) |
         *(uint *)(&DAT_00489240 + (uint)*(byte *)(param_1 + 0x2e) * 4);
    local_34.fState =
         *(uint *)(&DAT_0048924c + (uint)*(byte *)(param_1 + 0x28) * 4) |
         *(uint *)(&DAT_0048925c + (uint)*(byte *)(param_1 + 0x29) * 4) |
         *(uint *)(&DAT_00489254 + (uint)*(byte *)(param_1 + 0x2a) * 4);
    local_34.wID = (UINT)*(ushort *)(param_1 + 0x30);
    local_34.hSubMenu = (HMENU)0x0;
    local_34.hbmpChecked = (HBITMAP)0x0;
    local_34.hbmpUnchecked = (HBITMAP)0x0;
    local_34.dwTypeData = FUN_00403814((undefined *)local_34.hbmpItem);
    iVar3 = FUN_0041040c(param_1);
    if (0 < iVar3) {
      local_34.hSubMenu = (HMENU)FUN_0041021c(param_1);
    }
    InsertMenuItemA(param_2,0xffffffff,1,&local_34);
    puVar1 = puStack_48;
  }
LAB_0041004b:
  puStack_48 = puVar1;
  *in_FS_OFFSET = iStack_5c;
  FUN_004034dc(&local_38);
  FUN_004034dc((int *)&local_34.hbmpItem);
  return;
}

