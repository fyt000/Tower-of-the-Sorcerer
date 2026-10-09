/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00407314.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00407314(int **param_1,int param_2)

{
  BYTE *pBVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  undefined *puVar5;
  undefined4 uVar6;
  undefined4 local_2b8 [16];
  byte local_278 [64];
  byte local_238 [256];
  byte *local_138;
  undefined local_134;
  undefined4 *local_130;
  undefined local_12c;
  int local_128;
  undefined local_124;
  char *local_120;
  undefined local_11c;
  undefined *local_118;
  undefined local_114;
  byte local_110 [256];
  
  GetModuleFileNameA(DAT_0048a014,(LPSTR)local_238,0x100);
  pBVar1 = FUN_004072e4(local_238,'\\');
  FUN_00406168(local_2b8,(undefined4 *)(pBVar1 + 1),0x3f);
  pcVar4 = "";
  puVar5 = &DAT_00407490;
  piVar2 = FUN_00402c7c(param_1,(int *)&DAT_00405390);
  if ((char)piVar2 != '\0') {
    pcVar4 = FUN_00403814((undefined *)param_1[1]);
    iVar3 = FUN_004060ac(pcVar4);
    if ((iVar3 != 0) && (pcVar4[iVar3 + -1] != '.')) {
      puVar5 = &DAT_00407494;
    }
  }
  LoadStringA(DAT_0048a014,0xff9e,(LPSTR)local_278,0x40);
  uVar6 = 4;
  FUN_00402b7c((int)*param_1,local_110);
  local_138 = local_110;
  local_134 = 4;
  local_12c = 6;
  local_130 = local_2b8;
  local_128 = FUN_004072d8(param_2);
  local_124 = 5;
  local_11c = 6;
  local_114 = 6;
  local_120 = pcVar4;
  local_118 = puVar5;
  FUN_004065e8(local_238,local_278,&local_138,uVar6);
  LoadStringA(DAT_0048a014,0xff9f,(LPSTR)local_278,0x40);
  if (DAT_0048a035 == '\0') {
    MessageBoxA((HWND)0x0,(LPCSTR)local_238,(LPCSTR)local_278,0x2010);
  }
  else {
    puVar5 = (undefined *)FUN_0040470c(&DAT_0048a208,(char *)local_238);
    FUN_0040468f(puVar5);
    FUN_00402710();
  }
  return;
}

