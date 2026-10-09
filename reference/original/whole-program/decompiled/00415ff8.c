/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415ff8.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00415ff8(int **param_1,int param_2)

{
  int **ppiVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  undefined local_10;
  
  local_10 = 1;
  ppiVar1 = FUN_0041fffc(param_1);
  uVar2 = extraout_ECX;
  if (((ppiVar1 != (int **)0x0) && (param_1 != ppiVar1)) && (*(char *)(ppiVar1 + 0x46) != '\0')) {
    ppiVar1 = (int **)FUN_00415ff8(ppiVar1,param_2);
    uVar2 = extraout_ECX_00;
    if ((char)ppiVar1 != '\0') goto LAB_00416049;
  }
  if ((*(byte *)((int)param_1 + 0x35) & 0x10) == 0) {
    ppiVar1 = (int **)FUN_00402cdc((int *)param_1,param_2 + 4,uVar2);
    if (*(char *)(param_2 + 4) == '\0') goto LAB_00416049;
  }
  local_10 = 0;
LAB_00416049:
  return CONCAT31((int3)((uint)ppiVar1 >> 8),local_10);
}

