/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e254.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041e254(int param_1,int *param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  int local_20;
  undefined local_1c [10];
  int local_12;
  
  iVar2 = *(int *)(param_1 + 0x10);
  FUN_0041dbe0(param_1,param_2,param_3);
  local_20 = FUN_0040af1c(*(int **)(iVar2 + 8));
  if (local_20 != 0) {
    local_20 = local_20 + 0xe;
  }
  if ((char)param_3 != '\0') {
    FUN_0040af88(param_2,&local_20,4);
  }
  if (local_20 != 0) {
    FUN_004029b8((undefined4 *)local_1c,0xe,0);
    local_1c._0_2_ = 0x4d42;
    local_1c._2_4_ = local_20;
    local_12 = (*(int *)(iVar2 + 0x20) - *(int *)(iVar2 + 0x1c)) + 0xe;
    FUN_0040af88(param_2,local_1c,0xe);
    piVar1 = *(int **)(iVar2 + 8);
    iVar2 = FUN_0040af1c(piVar1);
    FUN_0040af88(param_2,piVar1[1],iVar2);
  }
  return;
}

