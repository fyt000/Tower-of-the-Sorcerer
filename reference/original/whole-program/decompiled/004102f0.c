/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004102f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004102f0(int param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  uint uIDCheckItem;
  HMENU hMenu;
  int iVar3;
  UINT uCheck;
  
  if (param_2 != *(byte *)(param_1 + 0x28)) {
    if (((*(char *)(param_1 + 0x2b) != '\0') && (*(char *)(param_1 + 0x2d) != '\0')) &&
       (*(int *)(param_1 + 0x44) != 0)) {
      iVar1 = FUN_0041040c(*(int *)(param_1 + 0x44));
      if (-1 < iVar1 + -1) {
        iVar3 = 0;
        do {
          iVar2 = FUN_0041041c(*(int *)(param_1 + 0x44),iVar3);
          if (((param_1 != iVar2) && (*(char *)(iVar2 + 0x2b) != '\0')) &&
             (*(char *)(iVar2 + 0x2d) == *(char *)(param_1 + 0x2d))) {
            FUN_004102f0(iVar2,0);
          }
          iVar3 = iVar3 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
    }
    *(byte *)(param_1 + 0x28) = param_2;
    if (*(int *)(param_1 + 0x44) != 0) {
      uCheck = *(UINT *)(&DAT_0048921c + (uint)param_2 * 4);
      uIDCheckItem = (uint)*(ushort *)(param_1 + 0x30);
      hMenu = (HMENU)FUN_0041021c(*(int *)(param_1 + 0x44));
      CheckMenuItem(hMenu,uIDCheckItem,uCheck);
    }
  }
  return;
}

