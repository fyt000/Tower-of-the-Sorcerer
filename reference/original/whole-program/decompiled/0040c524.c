/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c524.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040c524(int param_1,int **param_2)

{
  int iVar1;
  int iVar2;
  char **ppcVar3;
  int *piVar4;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  int iVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_48;
  code *pcStack_44;
  undefined *puStack_40;
  undefined4 uStack_3c;
  code *pcStack_38;
  undefined *puStack_34;
  undefined4 uStack_30;
  code *pcStack_2c;
  undefined *puStack_28;
  int **local_18;
  int **local_14;
  int local_c;
  int **local_8;
  
  puStack_28 = &stack0xfffffffc;
  puStack_34 = &stack0xfffffffc;
  local_c = 0;
  pcStack_2c = thunk_FUN_00403140;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  pcStack_38 = thunk_FUN_00403010;
  uStack_3c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_3c;
  puStack_40 = (undefined *)0x40c55f;
  local_8 = param_2;
  FUN_0040cdf4(param_1,&local_c,0);
  pcStack_44 = thunk_FUN_00403010;
  uStack_48 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_48;
  iVar5 = 1;
  puStack_40 = &stack0xfffffffc;
  iVar1 = FUN_00403650(local_c);
  local_14 = local_8;
  *(undefined *)(param_1 + 0x4c) = 1;
  iVar2 = iVar5;
  while( true ) {
    for (; (iVar5 <= iVar1 && (*(char *)(local_c + -1 + iVar5) != '.')); iVar5 = iVar5 + 1) {
    }
    FUN_00403854(local_c,iVar2,iVar5 - iVar2,(int *)(param_1 + 0x50));
    if (iVar1 < iVar5) break;
    iVar2 = FUN_00402d04((int)*local_14);
    ppcVar3 = (char **)FUN_00408230(iVar2,*(undefined **)(param_1 + 0x50));
    if (ppcVar3 == (char **)0x0) {
      FUN_0040bbfc(param_1,extraout_EDX,extraout_ECX);
    }
    local_18 = (int **)0x0;
    if (**ppcVar3 == '\a') {
      local_18 = (int **)FUN_0040831c((int *)local_14,ppcVar3);
    }
    piVar4 = FUN_00402c7c(local_18,(int *)&PTR_FUN_00408b48);
    if ((char)piVar4 == '\0') {
      FUN_0040c508(piVar4,extraout_EDX_00,extraout_ECX_00,(int)&stack0xfffffffc);
    }
    local_14 = local_18;
    iVar5 = iVar5 + 1;
    iVar2 = iVar5;
  }
  iVar2 = FUN_00402d04((int)*local_14);
  iVar2 = FUN_00408230(iVar2,*(undefined **)(param_1 + 0x50));
  if (iVar2 == 0) {
    *(undefined *)(param_1 + 0x4c) = 0;
    (*(code *)(*local_14)[1])(local_14,param_1);
    *(undefined *)(param_1 + 0x4c) = 1;
    if (*(int *)(param_1 + 0x50) != 0) {
      FUN_0040bbfc(param_1,extraout_EDX_01,extraout_ECX_01);
    }
  }
  else {
    root_0040c848(param_1,local_14,iVar2);
  }
  *in_FS_OFFSET = uStack_48;
  *in_FS_OFFSET = uStack_3c;
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_0040c6ec;
  pcStack_2c = (code *)0x40c6e4;
  FUN_004034dc(&local_c);
  return;
}

