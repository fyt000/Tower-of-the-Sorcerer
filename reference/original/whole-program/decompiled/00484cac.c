/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00484cac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00484cac(int *param_1)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  if (DAT_00489ba4 == '\0') {
    iVar1 = FUN_00423ba8();
    if (799 < iVar1) {
      FUN_004102f0(param_1[0x11f],1);
      FUN_004102f0(param_1[0x11e],0);
      DAT_00489ba4 = 1;
      FUN_00417dc4((int *)param_1[0x6c]);
      FUN_00417dc4((int *)param_1[0x71]);
      FUN_00417dc4((int *)param_1[0x103]);
      FUN_00484f48(param_1);
      FUN_0047d4a4((int)param_1);
      FUN_00454de8((int)param_1,extraout_EDX,extraout_ECX);
      FUN_00450880((int)param_1);
      return;
    }
  }
  iVar1 = FUN_00423ba8();
  if (iVar1 < 800) {
    FUN_0042cf78((uint *)"Cannot. Need display size 800x600.");
  }
  return;
}

