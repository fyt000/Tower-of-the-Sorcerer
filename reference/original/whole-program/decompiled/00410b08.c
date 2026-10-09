/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410b08.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00410b08(HMENU param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  UINT UVar3;
  char *lpString;
  UINT uIDItem;
  
  iVar1 = GetMenuItemCount(param_1);
  lpString = (char *)(param_4 + -0x200);
  uIDItem = 0;
  while (((int)uIDItem < iVar1 && (lpString < (char *)(param_4 - 5U)))) {
    GetMenuStringA(param_1,uIDItem,lpString,(int)(char *)(param_4 - 5U) - (int)lpString,0x400);
    puVar2 = (undefined4 *)FUN_004060c4(lpString);
    UVar3 = GetMenuState(param_1,uIDItem,0x400);
    if ((UVar3 & 2) != 0) {
      puVar2 = (undefined4 *)FUN_0040613c(puVar2,(undefined4 *)&DAT_00410bcc);
    }
    if ((UVar3 & 0x40) != 0) {
      puVar2 = (undefined4 *)FUN_0040613c(puVar2,(undefined4 *)&DAT_00410bd0);
    }
    if ((UVar3 & 1) != 0) {
      puVar2 = (undefined4 *)FUN_0040613c(puVar2,(undefined4 *)&DAT_00410bd4);
    }
    lpString = FUN_0040613c(puVar2,(undefined4 *)&DAT_00410bd8);
    uIDItem = uIDItem + 1;
  }
  return;
}

