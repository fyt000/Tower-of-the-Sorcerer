/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040dfdc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040dfdc(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  undefined uVar1;
  bool bVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined extraout_CL;
  undefined extraout_CL_00;
  undefined extraout_CL_01;
  undefined extraout_CL_02;
  undefined extraout_CL_03;
  int extraout_ECX;
  int iVar7;
  undefined extraout_DL;
  undefined extraout_DL_00;
  undefined extraout_DL_01;
  undefined extraout_DL_02;
  undefined extraout_DL_03;
  undefined extraout_DL_04;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar8;
  undefined uVar9;
  undefined4 *in_FS_OFFSET;
  undefined *puStack_38;
  undefined *puVar10;
  undefined4 uStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  int local_14;
  undefined *local_10;
  undefined4 *local_c;
  int **local_8;
  
  puStack_24 = &stack0xfffffffc;
  uVar9 = SUB41(&stack0xfffffffc,0);
  puVar10 = &stack0xfffffffc;
  local_8 = (int **)0x0;
  local_c = (undefined4 *)0x0;
  local_10 = (undefined *)0x0;
  local_14 = 0;
  puStack_28 = &LAB_0040e1bf;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  local_8 = (int **)FUN_0040831c(*(int **)(param_4 + -8),*(char ***)(param_4 + -0xc));
  uVar1 = (undefined)param_4;
  if (local_8 == (int **)0x0) {
    bVar2 = FUN_0040deec(0,extraout_DL,extraout_CL,&stack0xfffffffc);
    if (!bVar2) {
      iVar7 = param_4;
      FUN_0040d9f8(uVar1,extraout_DL_00,uVar9,param_4);
      FUN_0040e4a4(*(int *)(param_4 + -4),0xd,iVar7);
      goto LAB_0040e1a4;
    }
  }
  piVar3 = FUN_00402c7c(local_8,(int *)&PTR_FUN_00408b48);
  if ((char)piVar3 != '\0') {
    piVar3 = FUN_00402c7c(local_8,(int *)&PTR_FUN_00409144);
    if ((char)piVar3 == '\0') {
      piVar3 = FUN_00402c7c(local_8,(int *)&PTR_FUN_00408bb8);
      if ((char)piVar3 == '\0') {
        uVar8 = *(undefined4 *)(*(int *)(param_4 + -4) + 0x1c);
        FUN_00403570((int *)&local_c,*(int *)(*(int *)(param_4 + -4) + 0x28));
        FUN_004035fc(&local_14,(byte *)(*(int *)(param_4 + -0xc) + 0x1a));
        puStack_38 = &DAT_0040e1d8;
        FUN_00403710((int *)(*(int *)(param_4 + -4) + 0x28),3);
        uVar4 = FUN_0040d9ac(uVar1,extraout_DL_04,extraout_CL_03,param_4);
        if ((char)uVar4 != '\0') {
          uVar6 = FUN_0040831c(*(int **)(*(int *)(param_4 + -4) + 0x1c),*(char ***)(param_4 + -0xc))
          ;
          *(uint *)(*(int *)(param_4 + -4) + 0x1c) = uVar6;
        }
        FUN_0040d8e8(*(undefined4 *)(param_4 + -4),(int *)local_8);
        *(undefined4 *)(*(int *)(param_4 + -4) + 0x1c) = uVar8;
        FUN_0040352c((int *)(*(int *)(param_4 + -4) + 0x28),local_c);
      }
      else {
        iVar7 = param_4;
        uVar4 = FUN_0040d9ac(uVar1,extraout_DL_03,extraout_CL_02,param_4);
        uVar8 = extraout_EDX;
        if ((char)uVar4 != '\0') {
          puVar5 = (undefined4 *)
                   FUN_0040831c(*(int **)(*(int *)(param_4 + -4) + 0x1c),*(char ***)(param_4 + -0xc)
                               );
          uVar4 = FUN_0040987c(local_8,puVar5);
          iVar7 = extraout_ECX;
          uVar8 = extraout_EDX_00;
          if ((char)uVar4 != '\0') goto LAB_0040e1a4;
        }
        FUN_0040db80(local_8,uVar8,iVar7,param_4);
      }
    }
    else {
      bVar2 = FUN_0040deec((char)piVar3,extraout_DL_01,extraout_CL_00,&stack0xfffffffc);
      if (!bVar2) {
        FUN_0040df7c((int)local_8,&local_14,puVar10,(int)&stack0xfffffffc);
        FUN_00403570((int *)&local_10,local_14);
        if (local_10 != (undefined *)0x0) {
          FUN_0040d9f8(uVar1,extraout_DL_02,extraout_CL_01,param_4);
          FUN_0040d784(*(int *)(param_4 + -4),local_10);
        }
      }
    }
  }
LAB_0040e1a4:
  *in_FS_OFFSET = puStack_38;
  FUN_004034fc(&local_14,3);
  return;
}

