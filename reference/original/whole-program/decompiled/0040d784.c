/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d784.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040d784(int param_1,undefined *param_2)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  uint extraout_ECX_02;
  
  iVar1 = FUN_00405a34(param_2,"False");
  if (iVar1 == 0) {
    FUN_0040e4a4(param_1,8,extraout_ECX);
    return;
  }
  iVar1 = FUN_00405a34(param_2,&DAT_0040d80c);
  if (iVar1 == 0) {
    FUN_0040e4a4(param_1,9,extraout_ECX_00);
  }
  else {
    iVar1 = FUN_00405a34(param_2,&DAT_0040d81c);
    if (iVar1 == 0) {
      FUN_0040e4a4(param_1,0xd,extraout_ECX_01);
    }
    else {
      FUN_0040e4a4(param_1,7,extraout_ECX_01);
      FUN_0040e400(param_1,param_2,extraout_ECX_02);
    }
  }
  return;
}

