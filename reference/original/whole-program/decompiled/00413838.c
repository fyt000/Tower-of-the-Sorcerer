/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413838.
 * Inferred types, shared tails and runtime effects require assembly review. */

HDC FUN_00413838(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  HDC hdc;
  undefined4 local_10;
  undefined local_c;
  
  if (*(int *)(param_1 + 0x20) == 0) {
    local_10 = *(undefined4 *)(param_1 + 8);
    local_c = 0xb;
    uVar1 = FUN_0040753c(0x41117c,CONCAT31((int3)((uint)param_2 >> 8),1),0xf02f,0,&local_10);
    FUN_004031f8(uVar1);
  }
  hdc = (HDC)(**(code **)(**(int **)(param_1 + 0x20) + 0x30))();
  SetViewportOrgEx(hdc,*(int *)(param_1 + 0x24),*(int *)(param_1 + 0x28),(LPPOINT)0x0);
  IntersectClipRect(hdc,0,0,*(int *)(param_1 + 0x2c),*(int *)(param_1 + 0x30));
  return hdc;
}

