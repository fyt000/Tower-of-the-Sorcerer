/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402680.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00402680(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    if (param_2 == 0) {
      *param_1 = 0;
      iVar1 = (*(code *)PTR_FUN_0048900c)(iVar1);
      if (iVar1 == 0) {
        return;
      }
      FUN_004026d0(CONCAT31((int3)((uint)iVar1 >> 8),2));
      return;
    }
    iVar1 = (*(code *)PTR_FUN_00489010)(iVar1);
    if (iVar1 != 0) {
      *param_1 = iVar1;
      return;
    }
LAB_004026b1:
    FUN_004026d0(CONCAT31((int3)((uint)iVar1 >> 8),1));
    return;
  }
  if (param_2 != 0) {
    iVar1 = (*(code *)PTR_FUN_00489008)(param_2);
    if (iVar1 == 0) goto LAB_004026b1;
    *param_1 = iVar1;
  }
  return;
}

