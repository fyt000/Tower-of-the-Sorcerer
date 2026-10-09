/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043ed24.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043ed24(int param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  HBITMAP pHVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  piVar1 = FUN_0043e5e0((int *)&PTR_FUN_0043c958,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  *(int **)(param_1 + 0x150) = piVar1;
  pHVar2 = LoadBitmapA(DAT_0048a014,"OPENFOLDER");
  FUN_0041e0ec((int)piVar1,pHVar2);
  piVar1 = FUN_0043e5e0((int *)&PTR_FUN_0043c958,CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                        extraout_ECX);
  *(int **)(param_1 + 0x14c) = piVar1;
  pHVar2 = LoadBitmapA(DAT_0048a014,"CLOSEDFOLDER");
  FUN_0041e0ec((int)piVar1,pHVar2);
  piVar1 = FUN_0043e5e0((int *)&PTR_FUN_0043c958,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                        extraout_ECX_00);
  *(int **)(param_1 + 0x154) = piVar1;
  pHVar2 = LoadBitmapA(DAT_0048a014,"CURRENTFOLDER");
  FUN_0041e0ec((int)piVar1,pHVar2);
  return;
}

