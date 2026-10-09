/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043fbc4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043fbc4(int param_1,undefined4 param_2,LONG *param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  RECT *pRVar8;
  undefined4 *in_FS_OFFSET;
  int *piVar9;
  undefined4 uStack_5c;
  undefined *puStack_58;
  undefined *puStack_54;
  undefined *puStack_44;
  int aiStack_40 [4];
  int aiStack_30 [4];
  RECT RStack_20;
  int *piStack_10;
  int iStack_c;
  undefined4 uStack_8;
  
  puStack_54 = &stack0xfffffffc;
  puStack_44 = (undefined *)0x0;
  pRVar8 = &RStack_20;
  for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
    pRVar8->left = *param_3;
    param_3 = param_3 + 1;
    pRVar8 = (RECT *)&pRVar8->top;
  }
  puStack_58 = &LAB_0043fcf8;
  uStack_5c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_5c;
  piStack_10 = *(int **)(param_1 + 0x108);
  uStack_8 = param_2;
  FUN_0041a664(piStack_10,&RStack_20);
  iStack_c = 2;
  if (*(char *)(param_1 + 0x16c) != '\0') {
    piVar1 = (int *)(**(code **)(**(int **)(param_1 + 0x100) + 0x14))
                              (*(int **)(param_1 + 0x100),uStack_8);
    if (piVar1 != (int *)0x0) {
      iVar6 = (**(code **)(*piVar1 + 0x1c))();
      piVar9 = aiStack_30;
      iVar2 = (**(code **)(*piVar1 + 0x20))();
      FUN_00409258(0,0,iVar2,piVar9,iVar6);
      piVar9 = aiStack_30;
      iVar6 = (**(code **)(*piVar1 + 0x1c))();
      iVar6 = iVar6 + -1;
      piVar3 = (int *)FUN_0041dad8((int)piVar1);
      uVar4 = FUN_0041a924(piVar3,0,iVar6);
      iVar6 = (**(code **)(*piVar1 + 0x1c))();
      piVar3 = aiStack_40;
      iVar2 = (**(code **)(*piVar1 + 0x20))();
      iVar5 = (**(code **)(*piVar1 + 0x1c))();
      uVar7 = (RStack_20.top + RStack_20.bottom) - iVar5;
      iVar5 = (int)uVar7 >> 1;
      if (iVar5 < 0) {
        iVar5 = iVar5 + (uint)((uVar7 & 1) != 0);
      }
      FUN_00409258(RStack_20.left + 2,iVar5,iVar2,piVar3,iVar6);
      FUN_0041a32c(piStack_10,aiStack_40,(int)piVar1,uVar4,piVar9);
      iStack_c = (**(code **)(*piVar1 + 0x20))();
      iStack_c = iStack_c + 6;
    }
  }
  (**(code **)(**(int **)(param_1 + 0x100) + 0xc))(*(int **)(param_1 + 0x100),uStack_8,&puStack_44);
  FUN_0041a7c0(piStack_10,RStack_20.left + iStack_c,RStack_20.top,puStack_44);
  *in_FS_OFFSET = uStack_5c;
  puStack_54 = &LAB_0043fcff;
  puStack_58 = (undefined *)0x43fcf7;
  FUN_004034dc((int *)&puStack_44);
  return;
}

