/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415f34.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00415f34(int **param_1,int param_2)

{
  byte bVar1;
  int **ppiVar2;
  undefined3 extraout_var;
  undefined local_10;
  
  local_10 = 1;
  ppiVar2 = FUN_0041fffc(param_1);
  if (((ppiVar2 != (int **)0x0) && (param_1 != ppiVar2)) && (*(char *)(ppiVar2 + 0x46) != '\0')) {
    ppiVar2 = (int **)FUN_00415f34(ppiVar2,param_2);
    if ((char)ppiVar2 != '\0') goto LAB_00415f90;
  }
  if ((*(byte *)((int)param_1 + 0x35) & 0x10) == 0) {
    bVar1 = FUN_0041ff20(*(uint *)(param_2 + 8));
    ppiVar2 = (int **)FUN_00402cdc((int *)param_1,param_2 + 4,CONCAT31(extraout_var,bVar1));
    if (*(short *)(param_2 + 4) == 0) goto LAB_00415f90;
  }
  local_10 = 0;
LAB_00415f90:
  return CONCAT31((int3)((uint)ppiVar2 >> 8),local_10);
}

