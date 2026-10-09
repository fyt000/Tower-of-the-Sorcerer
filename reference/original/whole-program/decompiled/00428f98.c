/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428f98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00428f98(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  HWND hWnd;
  LRESULT LVar3;
  undefined4 uVar4;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined uVar5;
  UINT Msg;
  WPARAM wParam;
  uint *lParam;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  uint *local_c;
  uint *local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  local_c = (uint *)0x0;
  puStack_20 = &LAB_0042904b;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  FUN_00405a6c(param_2,(char **)&local_8);
  iVar1 = FUN_00403650((int)local_8);
  iVar2 = FUN_00413554(*(int **)(param_1 + 8));
  uVar5 = iVar1 == iVar2;
  if ((bool)uVar5) {
    FUN_004135a4(*(int **)(param_1 + 8),(int *)&local_c);
    FUN_00403760(local_8,local_c);
    if ((bool)uVar5) goto LAB_0042902d;
  }
  wParam = 0;
  Msg = 0xc;
  lParam = local_8;
  hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  LVar3 = SendMessageA(hWnd,Msg,wParam,(LPARAM)lParam);
  if (LVar3 == 0) {
    uVar4 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf0b3);
    FUN_004031f8(uVar4);
  }
  FUN_00413cb8(*(int **)(param_1 + 8),0xb012,0,0);
LAB_0042902d:
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_00429052;
  puStack_20 = (undefined *)0x429042;
  FUN_004034dc((int *)&local_c);
  puStack_20 = (undefined *)0x42904a;
  FUN_004034dc((int *)&local_8);
  return;
}

