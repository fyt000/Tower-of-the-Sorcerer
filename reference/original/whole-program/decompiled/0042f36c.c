/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f36c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042f36c(int *param_1)

{
  HWND pHVar1;
  undefined4 uVar2;
  undefined4 *in_FS_OFFSET;
  UINT UVar3;
  undefined4 uVar4;
  WPARAM WVar5;
  LPARAM LVar6;
  
  FUN_00428944(param_1);
  LVar6 = 0x2c0001;
  WVar5 = 0;
  UVar3 = 0x445;
  pHVar1 = (HWND)FUN_00416cbc(param_1);
  SendMessageA(pHVar1,UVar3,WVar5,LVar6);
  LVar6 = FUN_00419b00(param_1[0x12]);
  WVar5 = 0;
  UVar3 = 0x443;
  pHVar1 = (HWND)FUN_00416cbc(param_1);
  SendMessageA(pHVar1,UVar3,WVar5,LVar6);
  if (param_1[0x51] != 0) {
    uVar2 = FUN_0042f574((int)param_1);
    FUN_0042f580((int)param_1,0);
    uVar4 = *in_FS_OFFSET;
    *in_FS_OFFSET = &stack0xffffffe8;
    (**(code **)(*(int *)param_1[0x50] + 0x54))((int *)param_1[0x50],param_1[0x51]);
    FUN_00402c34((int *)param_1[0x51]);
    param_1[0x51] = 0;
    *in_FS_OFFSET = uVar4;
    FUN_0042f580((int)param_1,(char)uVar2);
    return;
  }
  FUN_0042872c(param_1,*(byte *)((int)param_1 + 0x151));
  return;
}

