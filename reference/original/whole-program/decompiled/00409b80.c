/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409b80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409b80(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  if ((param_2 < 0) || (0x7ffffff < param_2)) {
    (**(code **)*param_1)();
  }
  if ((int)param_1[3] < param_2) {
    FUN_00409b4c(param_1,param_2);
  }
  iVar1 = param_1[2];
  if (iVar1 < param_2) {
    FUN_004029b8((undefined4 *)(param_1[1] + iVar1 * 4),(param_2 - iVar1) * 4,0);
  }
  param_1[2] = param_2;
  return;
}

