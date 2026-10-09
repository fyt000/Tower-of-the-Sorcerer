/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416428.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416428(int param_1,undefined4 param_2)

{
  bool bVar1;
  BOOL BVar2;
  undefined2 uVar3;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  
  uVar3 = (undefined2)((uint)param_2 >> 0x10);
  if (((*(byte *)(param_1 + 0x34) & 0x10) != 0) && (*(int *)(param_1 + 0x20) != 0)) {
    bVar1 = FUN_00416e54(param_1);
    uVar3 = extraout_var;
    if (bVar1) {
      BVar2 = IsWindowVisible(*(HWND *)(param_1 + 0xc0));
      uVar3 = extraout_var_00;
      if (BVar2 != 0) {
        FUN_00416bf4(param_1);
        uVar3 = extraout_var_01;
      }
    }
  }
  FUN_00414d24(param_1,CONCAT22(uVar3,0xb011));
  return;
}

