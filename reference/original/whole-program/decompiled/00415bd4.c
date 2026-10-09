/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415bd4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00415bd4(int *param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  BOOL BVar3;
  
  if ((((*(char *)((int)param_1 + 0xc5) == '\0') || ((*(byte *)(param_1 + 0xd) & 0x10) == 0)) ||
      (param_1[8] == 0)) || ((*(byte *)(*(int *)(param_2 + 8) + 0x18) & 8) != 0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if ((*(uint *)(*(int *)(param_2 + 8) + 0x18) & 3) != 3) {
    BVar3 = IsWindowVisible((HWND)param_1[0x30]);
    if (BVar3 != 0) {
      bVar1 = true;
      goto LAB_00415c24;
    }
  }
  bVar1 = false;
LAB_00415c24:
  if ((bool)(bVar1 & bVar2)) {
    FUN_00416bf4((int)param_1);
  }
  FUN_00416e60((int)param_1);
  (**(code **)(*param_1 + -0x10))(param_1,param_2);
  if ((bVar2) && ((bVar1 || ((*(byte *)(*(int *)(param_2 + 8) + 0x18) & 0xc0) != 0)))) {
    FUN_00416bf4((int)param_1);
  }
  return;
}

