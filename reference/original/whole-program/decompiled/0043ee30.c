/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043ee30.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043ee30(int param_1,int param_2,LONG *param_3)

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
  undefined4 uStack_64;
  undefined *puStack_60;
  undefined *puStack_5c;
  undefined *puStack_4c;
  LPSTR pCStack_48;
  int aiStack_44 [4];
  int aiStack_34 [4];
  RECT RStack_24;
  int *piStack_14;
  int iStack_10;
  int iStack_c;
  int iStack_8;
  
  puStack_5c = &stack0xfffffffc;
  pCStack_48 = (LPSTR)0x0;
  puStack_4c = (undefined *)0x0;
  pRVar8 = &RStack_24;
  for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
    pRVar8->left = *param_3;
    param_3 = param_3 + 1;
    pRVar8 = (RECT *)&pRVar8->top;
  }
  puStack_60 = &LAB_0043ef98;
  uStack_64 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_64;
  piStack_14 = *(int **)(param_1 + 0x108);
  iStack_8 = param_2;
  FUN_0041a664(piStack_14,&RStack_24);
  iStack_c = 0x10;
  iStack_10 = iStack_8 * 4 + 2;
  piVar1 = (int *)(**(code **)(**(int **)(param_1 + 0x100) + 0x14))
                            (*(int **)(param_1 + 0x100),iStack_8);
  if (piVar1 != (int *)0x0) {
    if (piVar1 == *(int **)(param_1 + 0x14c)) {
      iVar6 = FUN_0043e5a8(*(int *)(param_1 + 0x158));
      iStack_10 = (iVar6 + 1) * 4 + 2;
    }
    iStack_c = (**(code **)(*piVar1 + 0x20))();
    iVar6 = (**(code **)(*piVar1 + 0x1c))();
    piVar9 = aiStack_34;
    iVar2 = (**(code **)(*piVar1 + 0x20))();
    FUN_00409258(0,0,iVar2,piVar9,iVar6);
    piVar9 = aiStack_34;
    iVar6 = (**(code **)(*piVar1 + 0x1c))();
    iVar6 = iVar6 + -1;
    piVar3 = (int *)FUN_0041dad8((int)piVar1);
    uVar4 = FUN_0041a924(piVar3,0,iVar6);
    iVar6 = (**(code **)(*piVar1 + 0x1c))();
    piVar3 = aiStack_44;
    iVar2 = (**(code **)(*piVar1 + 0x20))();
    iVar5 = (**(code **)(*piVar1 + 0x1c))();
    uVar7 = (RStack_24.top + RStack_24.bottom) - iVar5;
    iVar5 = (int)uVar7 >> 1;
    if (iVar5 < 0) {
      iVar5 = iVar5 + (uint)((uVar7 & 1) != 0);
    }
    FUN_00409258(RStack_24.left + iStack_10,iVar5,iVar2,piVar3,iVar6);
    FUN_0041a32c(piStack_14,aiStack_44,(int)piVar1,uVar4,piVar9);
  }
  (**(code **)(**(int **)(param_1 + 0x100) + 0xc))(*(int **)(param_1 + 0x100),iStack_8,&puStack_4c);
  FUN_0043e894(param_1,puStack_4c,&pCStack_48);
  FUN_0041a7c0(piStack_14,RStack_24.left + iStack_c + iStack_10 + 4,RStack_24.top,pCStack_48);
  *in_FS_OFFSET = uStack_64;
  puStack_5c = &LAB_0043ef9f;
  puStack_60 = (undefined *)0x43ef97;
  FUN_004034fc((int *)&puStack_4c,2);
  return;
}

