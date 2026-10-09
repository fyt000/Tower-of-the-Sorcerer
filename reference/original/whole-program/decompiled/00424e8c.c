/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424e8c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00424e8c(int param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x7e) == '\0') {
    if (*(HWND *)(param_1 + 0x20) != (HWND)0x0) {
      SendMessageA(*(HWND *)(param_1 + 0x20),0xb020,1,(LPARAM)&param_4);
    }
  }
  else {
    iVar3 = *(int *)(*(int *)(param_1 + 0x80) + 8);
    if (-1 < iVar3 + -1) {
      iVar2 = 0;
      do {
        piVar1 = (int *)FUN_00409a40(*(undefined4 **)(param_1 + 0x80),iVar2);
        if ((*piVar1 == param_4) && (param_5 == piVar1[1])) {
          FUN_00402668((int)piVar1);
          FUN_004099e4(*(undefined4 **)(param_1 + 0x80),iVar2);
          return;
        }
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  return;
}

