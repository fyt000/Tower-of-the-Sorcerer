/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430048.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00430048(int param_1)

{
  int iVar1;
  byte *lpBitmapName;
  HBITMAP pHVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar4;
  byte bVar5;
  undefined **ppuVar6;
  undefined **ppuVar7;
  byte local_54;
  byte local_53 [43];
  undefined4 local_28;
  undefined4 local_24;
  undefined *local_20;
  undefined local_1c;
  undefined *local_18;
  undefined local_14;
  
  FUN_00409224(0,0,&local_28);
  *(undefined4 *)(param_1 + 0x1b4) = local_28;
  *(undefined4 *)(param_1 + 0x1b8) = local_24;
  local_54 = 0;
  ppuVar6 = &PTR_s_MPPLAY_0048980c;
  uVar3 = extraout_ECX;
  uVar4 = extraout_EDX;
  do {
    bVar5 = 0;
    ppuVar7 = &PTR_DAT_00489800;
    do {
      iVar1 = FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)uVar4 >> 8),1),uVar3);
      *(int *)(param_1 + (uint)local_54 * 0x10 + 0x108 + (uint)bVar5 * 4) = iVar1;
      local_20 = *ppuVar7;
      local_1c = 6;
      local_18 = *ppuVar6;
      local_14 = 6;
      lpBitmapName = FUN_004065e8(local_53,(byte *)"%s_%s",&local_20,1);
      pHVar2 = LoadBitmapA(DAT_0048a014,(LPCSTR)lpBitmapName);
      FUN_0041e0ec(*(int *)(param_1 + (uint)local_54 * 0x10 + 0x108 + (uint)bVar5 * 4),pHVar2);
      iVar1 = (**(code **)(**(int **)(param_1 + (uint)local_54 * 0x10 + 0x108 + (uint)bVar5 * 4) +
                          0x20))();
      if (*(int *)(param_1 + 0x1b4) < iVar1) {
        uVar3 = (**(code **)(**(int **)(param_1 + (uint)local_54 * 0x10 + 0x108 + (uint)bVar5 * 4) +
                            0x20))();
        *(undefined4 *)(param_1 + 0x1b4) = uVar3;
      }
      iVar1 = (**(code **)(**(int **)(param_1 + (uint)local_54 * 0x10 + 0x108 + (uint)bVar5 * 4) +
                          0x1c))();
      uVar3 = extraout_ECX_00;
      uVar4 = extraout_EDX_00;
      if (*(int *)(param_1 + 0x1b8) < iVar1) {
        uVar3 = (**(code **)(**(int **)(param_1 + (uint)local_54 * 0x10 + 0x108 + (uint)bVar5 * 4) +
                            0x1c))();
        *(undefined4 *)(param_1 + 0x1b8) = uVar3;
        uVar3 = extraout_ECX_01;
        uVar4 = extraout_EDX_01;
      }
      bVar5 = bVar5 + 1;
      ppuVar7 = ppuVar7 + 1;
    } while (bVar5 != 3);
    local_54 = local_54 + 1;
    ppuVar6 = ppuVar6 + 1;
  } while (local_54 != 9);
  *(int *)(param_1 + 0x1b4) = *(int *)(param_1 + 0x1b4) + 8;
  *(int *)(param_1 + 0x1b8) = *(int *)(param_1 + 0x1b8) + 4;
  return;
}

