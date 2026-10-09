/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043f560.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043f560(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  HBITMAP pHVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  iVar1 = FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  *(int *)(param_1 + 0x154) = iVar1;
  pHVar2 = LoadBitmapA(DAT_0048a014,"EXECUTABLE");
  FUN_0041e0ec(iVar1,pHVar2);
  iVar1 = FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
  *(int *)(param_1 + 0x158) = iVar1;
  pHVar2 = LoadBitmapA(DAT_0048a014,"CLOSEDFOLDER");
  FUN_0041e0ec(iVar1,pHVar2);
  iVar1 = FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  *(int *)(param_1 + 0x15c) = iVar1;
  pHVar2 = LoadBitmapA(DAT_0048a014,"UNKNOWNFILE");
  FUN_0041e0ec(iVar1,pHVar2);
  return;
}

