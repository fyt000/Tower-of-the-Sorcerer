/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423ffc.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00423ffc(int param_1,undefined4 param_2,int *param_3)

{
  undefined4 uVar1;
  int iVar2;
  HICON pHVar3;
  BYTE *pBVar4;
  char *pcVar5;
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_fffffee0;
  undefined4 in_stack_fffffee4;
  undefined4 local_105;
  char local_5;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_fffffee0,in_stack_fffffee4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  local_5 = (char)param_2;
  FUN_0040e4b8(param_1,0,param_3);
  uVar1 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  *(undefined4 *)(param_1 + 0x70) = uVar1;
  uVar1 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),extraout_ECX_01);
  *(undefined4 *)(param_1 + 0x80) = uVar1;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0x80000018;
  *(undefined4 *)(param_1 + 0x54) = 500;
  *(undefined4 *)(param_1 + 0x58) = 0x32;
  *(undefined4 *)(param_1 + 0x5c) = 0x9c4;
  *(undefined *)(param_1 + 100) = 0;
  *(undefined *)(param_1 + 0x7d) = 1;
  iVar2 = FUN_0041e39c(0x4194a4,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),extraout_ECX_02);
  *(int *)(param_1 + 0x78) = iVar2;
  pHVar3 = LoadIconA(DAT_0048a014,"MAINICON");
  FUN_0041e728(iVar2,pHVar3);
  iVar2 = *(int *)(param_1 + 0x78);
  *(int *)(iVar2 + 8) = param_1;
  *(code **)(iVar2 + 4) = root_00425404;
  GetModuleFileNameA(DAT_0048a014,(LPSTR)&local_105,0x100);
  OemToCharA((LPCSTR)&local_105,(LPSTR)&local_105);
  pBVar4 = FUN_0040ed98((BYTE *)&local_105,'\\');
  if (pBVar4 != (BYTE *)0x0) {
    FUN_00406114(&local_105,(undefined4 *)(pBVar4 + 1));
  }
  pcVar5 = FUN_00406200((char *)&local_105,'.');
  if (pcVar5 != (char *)0x0) {
    *pcVar5 = '\0';
  }
  CharLowerA((LPSTR)((int)&local_105 + 1));
  FUN_00403638((int *)(param_1 + 0x6c),&local_105,0x100);
  if (DAT_0048a034 == '\0') {
    FUN_004241e4(param_1);
  }
  *(undefined *)(param_1 + 0x39) = 1;
  *(undefined *)(param_1 + 0x3a) = 1;
  if (local_5 != '\0') {
    *in_FS_OFFSET = in_stack_fffffee0;
  }
  return param_1;
}

