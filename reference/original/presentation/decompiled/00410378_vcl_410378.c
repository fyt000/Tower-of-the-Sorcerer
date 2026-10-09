/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00410378.
 * Inferred types and shared tails require assembly review. */

void FUN_00410378(int *param_1,byte param_2)

{
  int iVar1;
  uint uIDEnableItem;
  HMENU hMenu;
  UINT uEnable;
  
  if (param_2 != *(byte *)((int)param_1 + 0x29)) {
    *(byte *)((int)param_1 + 0x29) = param_2;
    if ((DAT_00489080 == 2) && (iVar1 = FUN_0041040c((int)param_1), iVar1 != 0)) {
      (**(code **)(*param_1 + 0x28))(param_1,1);
      return;
    }
    if (param_1[0x11] != 0) {
      uEnable = *(UINT *)(&DAT_00489224 + (uint)param_2 * 4);
      uIDEnableItem = (uint)*(ushort *)(param_1 + 0xc);
      hMenu = (HMENU)FUN_0041021c(param_1[0x11]);
      EnableMenuItem(hMenu,uIDEnableItem,uEnable);
    }
    (**(code **)(*param_1 + 0x28))(param_1,0);
  }
  return;
}

