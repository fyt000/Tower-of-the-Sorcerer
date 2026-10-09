/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403894.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403894(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  FUN_00403820(param_1);
  iVar1 = *param_1;
  if (iVar1 != 0) {
    iVar3 = param_2 + -1;
    if (((0 < param_2) && (iVar3 < *(int *)(iVar1 + -4))) && (0 < param_3)) {
      iVar2 = *(int *)(iVar1 + -4) - iVar3;
      if (iVar2 < param_3) {
        param_3 = iVar2;
      }
      FUN_00402870((undefined4 *)((int)(undefined4 *)(iVar1 + iVar3) + param_3),
                   (undefined4 *)(iVar1 + iVar3),iVar2 - param_3);
      FUN_00403924(param_1,*(int *)(*param_1 + -4) - param_3);
    }
  }
  return;
}

