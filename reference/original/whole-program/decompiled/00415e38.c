/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415e38.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00415e38(int **param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  int **ppiVar3;
  undefined3 extraout_var;
  undefined3 uVar5;
  undefined4 uVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined local_10;
  
  local_10 = 1;
  ppiVar3 = FUN_0041fffc(param_1);
  if (((ppiVar3 != (int **)0x0) && (param_1 != ppiVar3)) && (*(char *)(ppiVar3 + 0x46) != '\0')) {
    cVar1 = '\0';
    uVar5 = 0;
    FUN_00415e38(ppiVar3,param_2);
    if (cVar1 != '\0') goto LAB_00415ebe;
  }
  bVar2 = FUN_0041ff20(*(uint *)(param_2 + 8));
  local_10 = 1;
  uVar5 = extraout_var;
  if ((*(byte *)((int)param_1 + 0x35) & 0x10) == 0) {
    uVar5 = 0;
    FUN_00402cdc((int *)param_1,param_2 + 4,CONCAT31((int3)((uint)extraout_ECX >> 8),bVar2));
    if (*(short *)(param_2 + 4) == 0) goto LAB_00415ebe;
  }
  if ((*(short *)(param_2 + 4) == 0x5d) && (DAT_00415ec8 == bVar2)) {
    uVar4 = FUN_0040922c(0,0);
    uVar5 = 0;
    FUN_00414018(param_1,uVar4,extraout_ECX_00);
  }
  local_10 = 0;
LAB_00415ebe:
  return CONCAT31(uVar5,local_10);
}

