/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004227b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004227b8(int *param_1,char param_2)

{
  int iVar1;
  int iVar2;
  HWND pHVar3;
  UINT UVar4;
  WPARAM WVar5;
  
  if ((((((*(byte *)((int)param_1 + 0x11d) & 8) == 0) && (*(int *)(DAT_0048a6f8 + 0x28) != 0)) &&
       (*(int *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x128) != 0)) &&
      (param_1 != *(int **)(DAT_0048a6f8 + 0x28))) &&
     ((*(char *)((int)param_1 + 0x11a) == '\x01' ||
      (*(char *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x11a) != '\x02')))) {
    iVar1 = 0;
    if ((((*(byte *)(param_1 + 7) & 0x10) == 0) && (param_1[0x4a] != 0)) &&
       ((*(char *)(param_1[0x4a] + 0x34) != '\0' || (*(char *)((int)param_1 + 0x11a) == '\x01')))) {
      iVar1 = param_1[0x4a];
    }
    iVar2 = *(int *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x128);
    if (param_2 == '\0') {
      FUN_00410cac(iVar2,iVar1);
    }
    else {
      FUN_00410c90(iVar2,iVar1);
      if ((*(char *)((int)param_1 + 0x11a) == '\x01') && (*(char *)((int)param_1 + 0x116) == '\x02')
         ) {
        iVar2 = FUN_00413178(param_1);
        iVar1 = FUN_004131bc(param_1);
        iVar2 = iVar2 + iVar1 * 0x10000;
        WVar5 = 0;
        UVar4 = 5;
        iVar1 = iVar2;
        pHVar3 = (HWND)FUN_00416cbc(param_1);
        SendMessageA(pHVar3,UVar4,WVar5,iVar1);
        WVar5 = 2;
        UVar4 = 5;
        pHVar3 = (HWND)FUN_00416cbc(param_1);
        SendMessageA(pHVar3,UVar4,WVar5,iVar2);
      }
    }
  }
  return;
}

