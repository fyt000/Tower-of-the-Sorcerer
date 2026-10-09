/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00429ef0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00429ef0(int *param_1,int param_2,undefined4 param_3)

{
  HWND pHVar1;
  undefined4 uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  UINT UVar3;
  WPARAM WVar4;
  LPARAM LVar5;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  puStack_1c = &LAB_0042a031;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  switch(*(undefined2 *)(param_2 + 6)) {
  case 1:
    puStack_18 = &stack0xfffffffc;
    uVar2 = FUN_0042961c(param_1);
    (**(code **)(*(int *)param_1[0x40] + 0xc))((int *)param_1[0x40],uVar2,&local_8);
    FUN_004135d4(param_1,local_8);
    FUN_00402cdc(param_1,extraout_EDX,extraout_ECX);
    FUN_00402cdc(param_1,extraout_EDX_00,extraout_ECX_00);
    break;
  case 2:
    puStack_18 = &stack0xfffffffc;
    FUN_00402cdc(param_1,param_2,param_3);
    break;
  case 3:
    *(undefined *)(param_1 + 0x4c) = 1;
    *(undefined *)((int)param_1 + 0x131) = 1;
    puStack_18 = &stack0xfffffffc;
    (**(code **)(*param_1 + 0x78))();
    break;
  case 4:
    *(undefined *)(param_1 + 0x4c) = 0;
    *(undefined *)((int)param_1 + 0x131) = 1;
    puStack_18 = &stack0xfffffffc;
    (**(code **)(*param_1 + 0x7c))();
    break;
  case 5:
    puStack_18 = &stack0xfffffffc;
    FUN_00402cdc(param_1,param_2,param_3);
    break;
  case 7:
    *(undefined *)((int)param_1 + 0x131) = 0;
    FUN_00402cdc(param_1,param_2,param_3);
    FUN_00429e80(param_1);
    if (*(char *)((int)param_1 + 0x131) != '\0') {
      LVar5 = 0;
      WVar4 = 0;
      UVar3 = 0x1f;
      pHVar1 = (HWND)FUN_00416cbc(param_1);
      PostMessageA(pHVar1,UVar3,WVar4,LVar5);
      if (*(char *)(param_1 + 0x4c) == '\0') {
        LVar5 = 0;
        WVar4 = 0;
        UVar3 = 0x14f;
        pHVar1 = (HWND)FUN_00416cbc(param_1);
        PostMessageA(pHVar1,UVar3,WVar4,LVar5);
      }
    }
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0042a038;
  puStack_1c = (undefined *)0x42a030;
  FUN_004034dc((int *)&local_8);
  return;
}

