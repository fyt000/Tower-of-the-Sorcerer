/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412cf4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00412cf4(int *param_1)

{
  int iVar1;
  
  if (param_1[0xd] == 0) {
    FUN_0041a9cc();
    return;
  }
  if (param_1[0xe] == 0) {
    if (DAT_0048a6d0[2] == DAT_0048a6d0[3]) {
      FUN_00412ca4();
    }
    iVar1 = (**(code **)(*(int *)param_1[0xd] + 0x30))((int *)param_1[0xd],param_1 + 0xf);
    param_1[0xe] = iVar1;
    FUN_004099a4(DAT_0048a6d0,param_1);
  }
  FUN_0041a9d0(param_1,param_1[0xe]);
  return;
}

