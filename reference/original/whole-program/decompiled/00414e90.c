/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414e90.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414e90(int *param_1)

{
  ATOM AVar1;
  undefined4 uVar2;
  BOOL BVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar4;
  undefined auStack_c0 [7];
  byte bStack_b9;
  int iStack_a4;
  WNDCLASSA WStack_9c;
  CHAR aCStack_74 [64];
  tagWNDCLASSA tStack_34;
  int iStack_c;
  undefined uStack_8;
  
  (**(code **)(*param_1 + 0x5c))(param_1,auStack_c0);
  if ((iStack_a4 == 0) && ((bStack_b9 & 0x40) != 0)) {
    iStack_c = param_1[2];
    uStack_8 = 0xb;
    uVar2 = FUN_0040753c(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf02f,0,&iStack_c);
    FUN_004031f8(uVar2);
  }
  param_1[0x2b] = (int)WStack_9c.lpfnWndProc;
  BVar3 = GetClassInfoA(DAT_0048a014,aCStack_74,&tStack_34);
  if ((BVar3 == 0) || (tStack_34.lpfnWndProc != root_0041212c)) {
    if (BVar3 != 0) {
      UnregisterClassA(aCStack_74,DAT_0048a014);
    }
    WStack_9c.lpfnWndProc = root_0041212c;
    WStack_9c.hInstance = DAT_0048a014;
    WStack_9c.lpszClassName = aCStack_74;
    AVar1 = RegisterClassA(&WStack_9c);
    if (AVar1 == 0) {
      uVar2 = FUN_004074cc(0x411138,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),0xf02c);
      FUN_004031f8(uVar2);
    }
  }
  DAT_0048927c = param_1;
  (**(code **)(*param_1 + 0x60))(param_1,auStack_c0);
  if (param_1[0x30] == 0) {
    uVar2 = FUN_004074cc(0x411138,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),0xf02d);
    FUN_004031f8(uVar2);
  }
  FUN_0040626c(param_1[0x10]);
  param_1[0x10] = 0;
  FUN_00416e60((int)param_1);
  uVar4 = 1;
  uVar2 = FUN_00419c90(param_1[0x11]);
  FUN_00413cb8(param_1,0x30,uVar2,uVar4);
  return;
}

