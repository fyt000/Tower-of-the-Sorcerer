/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413ad4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413ad4(int **param_1,char param_2)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_EDX;
  tagPOINT local_18;
  LONG local_10;
  LONG local_c;
  
  piVar1 = FUN_00402c7c(param_1,(int *)&PTR_FUN_0041edfc);
  uVar2 = extraout_ECX;
  if ((char)piVar1 != '\0') {
    uVar2 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf04e);
    FUN_004031f8(uVar2);
    uVar2 = extraout_ECX_00;
  }
  if (DAT_0048a69c == (int **)0x0) {
    DAT_0048a69c = param_1;
    if ((*(byte *)((int)param_1 + 0x36) & 1) != 0) {
      GetCursorPos(&local_18);
      FUN_00413278((int *)param_1,&local_18.x,&local_10);
      local_18.x = local_10;
      local_18.y = local_c;
      uVar2 = FUN_004052f4((undefined2 *)&local_18);
      FUN_00413cb8((int *)param_1,0x202,0,uVar2);
      uVar2 = extraout_ECX_01;
    }
    if (param_1 == DAT_0048a69c) {
      FUN_004129a4((int *)param_1,param_2,uVar2);
    }
  }
  return;
}

