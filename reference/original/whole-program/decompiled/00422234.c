/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422234.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422234(int param_1,LPCSTR *param_2)

{
  undefined4 uVar1;
  LRESULT LVar2;
  LPCSTR *extraout_EDX;
  LPCSTR *ppCStack_28;
  LPCSTR pCStack_24;
  undefined4 uStack_20;
  LPCSTR pCStack_1c;
  LPCSTR pCStack_18;
  LPCSTR pCStack_14;
  LPCSTR pCStack_10;
  LPCSTR pCStack_c;
  LPCSTR pCStack_8;
  
  if ((*(char *)(param_1 + 0x11a) == '\x01') && ((*(byte *)(param_1 + 0x1c) & 0x10) == 0)) {
    if ((*(int *)(DAT_0048a6f8 + 0x28) == 0) ||
       (*(int *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x134) == 0)) {
      uVar1 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)param_2 >> 8),1),0xf040);
      FUN_004031f8(uVar1);
      param_2 = extraout_EDX;
    }
    ppCStack_28 = param_2 + 0x13;
    pCStack_24 = *param_2;
    uStack_20 = DAT_0048a014;
    pCStack_1c = param_2[3];
    pCStack_18 = param_2[4];
    pCStack_14 = param_2[5];
    pCStack_10 = param_2[6];
    pCStack_c = param_2[1];
    pCStack_8 = param_2[8];
    LVar2 = SendMessageA(*(HWND *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x134),0x220,0,
                         (LPARAM)&ppCStack_28);
    *(LRESULT *)(param_1 + 0xc0) = LVar2;
    *(byte *)(param_1 + 0x11d) = *(byte *)(param_1 + 0x11d) | 0x10;
  }
  else {
    FUN_00414fd0(param_1,param_2);
    *(byte *)(param_1 + 0x11d) = *(byte *)(param_1 + 0x11d) & 0xef;
  }
  return;
}

