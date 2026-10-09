/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417208.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_00417208(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  BOOL BVar2;
  HFONT pHVar3;
  int *extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_fffffe8c;
  undefined4 in_stack_fffffe90;
  undefined4 local_15c [55];
  LOGFONTA local_80 [2];
  char local_5;
  
  if ((char)param_2 != '\0') {
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_fffffe8c,in_stack_fffffe90);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  local_5 = (char)param_2;
  FUN_00417538((int)param_1,0,param_3);
  FUN_004136e8(param_1,0x80ffff);
  local_15c[0] = 0x154;
  BVar2 = SystemParametersInfoA(0x29,0,local_15c,0);
  if (BVar2 == 0) {
    iVar1 = param_1[0x40];
    FUN_00419dec(*(int **)(iVar1 + 0xc),(undefined4 *)&DAT_004172c0);
    FUN_00419e4c(*(int **)(iVar1 + 0xc),9);
    FUN_0041a20c(*(int **)(iVar1 + 0x14),'\x01');
  }
  else {
    iVar1 = param_1[0x40];
    pHVar3 = CreateFontIndirectA(local_80);
    FUN_00419d80(*(int **)(iVar1 + 0xc),pHVar3);
    FUN_0041a20c(*(int **)(iVar1 + 0x14),'\x01');
  }
  if (local_5 != '\0') {
    *in_FS_OFFSET = in_stack_fffffe8c;
  }
  return param_1;
}

