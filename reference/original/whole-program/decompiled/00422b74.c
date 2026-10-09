/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422b74.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00422b74(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  HWND hWnd;
  HMENU hMenu;
  BOOL bRevert;
  
  if (((*(char *)(*(int *)(param_4 + -4) + 0x115) != '\0') &&
      ((*(byte *)(*(int *)(param_4 + -4) + 0x114) & 1) != 0)) &&
     (*(char *)(*(int *)(param_4 + -4) + 0x11a) != '\x01')) {
    bRevert = 0;
    hWnd = (HWND)FUN_00416cbc(*(int **)(param_4 + -4));
    hMenu = GetSystemMenu(hWnd,bRevert);
    if (*(char *)(*(int *)(param_4 + -4) + 0x115) == '\x03') {
      DeleteMenu(hMenu,0xf130,0);
      DeleteMenu(hMenu,7,0x400);
      DeleteMenu(hMenu,5,0x400);
      DeleteMenu(hMenu,0xf030,0);
      DeleteMenu(hMenu,0xf020,0);
      DeleteMenu(hMenu,0xf000,0);
      DeleteMenu(hMenu,0xf120,0);
    }
    else {
      if ((*(byte *)(*(int *)(param_4 + -4) + 0x114) & 2) == 0) {
        EnableMenuItem(hMenu,0xf020,1);
      }
      if ((*(byte *)(*(int *)(param_4 + -4) + 0x114) & 4) == 0) {
        EnableMenuItem(hMenu,0xf030,1);
      }
    }
  }
  return;
}

