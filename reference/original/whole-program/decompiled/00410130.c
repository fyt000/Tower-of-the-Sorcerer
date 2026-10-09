/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410130.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00410130(int *param_1)

{
  HMENU pHVar1;
  int iVar2;
  UINT uPosition;
  UINT uFlags;
  
  while( true ) {
    pHVar1 = (HMENU)FUN_0041021c((int)param_1);
    iVar2 = GetMenuItemCount(pHVar1);
    if (iVar2 < 1) break;
    uFlags = 0x400;
    uPosition = 0;
    pHVar1 = (HMENU)FUN_0041021c((int)param_1);
    RemoveMenu(pHVar1,uPosition,uFlags);
  }
  FUN_004100a8((int)param_1);
  (**(code **)(*param_1 + 0x28))(param_1,0);
  return;
}

