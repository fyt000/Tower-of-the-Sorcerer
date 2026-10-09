/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041061c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041061c(int *param_1,int param_2)

{
  int iVar1;
  
  if ((-1 < param_2) && (param_1[0xf] != 0)) {
    iVar1 = FUN_0041040c((int)param_1);
    if (param_2 < iVar1) goto LAB_0041063d;
  }
  FUN_0040f72c();
LAB_0041063d:
  iVar1 = FUN_00409a40((undefined4 *)param_1[0xf],param_2);
  FUN_004099e4((undefined4 *)param_1[0xf],param_2);
  *(undefined4 *)(iVar1 + 0x44) = 0;
  *(undefined4 *)(iVar1 + 0x88) = 0;
  *(undefined4 *)(iVar1 + 0x8c) = 0;
  if (param_1[9] != 0) {
    FUN_00410130(param_1);
  }
  (**(code **)(*param_1 + 0x28))(param_1,1);
  return;
}

