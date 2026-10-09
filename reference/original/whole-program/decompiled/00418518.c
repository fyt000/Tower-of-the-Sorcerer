/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00418518.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00418518(int *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  int *piVar5;
  undefined4 uStack_74;
  undefined4 uStack_68;
  undefined *puStack_64;
  undefined *puStack_60;
  undefined4 uStack_5c;
  undefined *puStack_58;
  undefined *puStack_54;
  int aiStack_44 [4];
  int aiStack_34 [4];
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  int iStack_18;
  int *piStack_14;
  int *piStack_10;
  int *piStack_c;
  int *piStack_8;
  
  puStack_54 = (undefined *)0x418534;
  FUN_0040af50(param_2,&iStack_1c,4);
  puStack_54 = (undefined *)0x418543;
  FUN_0040af50(param_2,&iStack_20,4);
  puStack_54 = (undefined *)0x41854f;
  piStack_8 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX)
  ;
  puStack_58 = &LAB_00418752;
  uStack_5c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_5c;
  puStack_60 = (undefined *)0x418567;
  puStack_54 = &stack0xfffffffc;
  iVar1 = FUN_0040af00(param_2);
  puStack_60 = (undefined *)0x418573;
  (**(code **)(*piStack_8 + 0x3c))(piStack_8,param_2);
  puStack_60 = (undefined *)0x41857f;
  FUN_0040af10(param_2,iStack_1c + iVar1);
  puStack_60 = (undefined *)0x41858b;
  piStack_10 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                                   extraout_ECX_00);
  puStack_64 = &LAB_00418735;
  uStack_68 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_68;
  puStack_60 = &stack0xfffffffc;
  (**(code **)(*piStack_10 + 0x3c))(piStack_10,param_2);
  piStack_c = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                                  extraout_ECX_01);
  (**(code **)(*piStack_c + 0x2c))(piStack_c,param_1[9]);
  (**(code **)(*piStack_c + 0x28))(piStack_c,param_1[8]);
  piStack_14 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                                   extraout_ECX_02);
  (**(code **)(*piStack_14 + 0x2c))(piStack_14,param_1[9]);
  (**(code **)(*piStack_14 + 0x28))(piStack_14,param_1[8]);
  uStack_74 = 0x418604;
  FUN_0040923c(0,0,param_1[9],aiStack_34,param_1[8]);
  uStack_74 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_74;
  iVar1 = (**(code **)(*piStack_8 + 0x1c))();
  if (-1 < iVar1 / param_1[8] + -1) {
    iStack_18 = 0;
    iStack_24 = iVar1 / param_1[8];
    do {
      if (iStack_20 == 0) break;
      iVar1 = (**(code **)(*piStack_8 + 0x20))();
      iVar1 = iVar1 / param_1[9];
      if (-1 < iVar1 + -1) {
        iVar4 = 0;
        do {
          if (iStack_20 == 0) break;
          FUN_00409258(iVar4 * param_1[9],iStack_18 * param_1[8],param_1[9],aiStack_44,param_1[8]);
          piVar5 = aiStack_44;
          piVar2 = (int *)FUN_0041dad8((int)piStack_8);
          piVar3 = (int *)FUN_0041dad8((int)piStack_c);
          FUN_0041a530(piVar3,aiStack_34,piVar2,piVar5);
          FUN_00409258(iVar4 * param_1[9],iStack_18 * param_1[8],param_1[9],aiStack_44,param_1[8]);
          piVar5 = aiStack_44;
          piVar2 = (int *)FUN_0041dad8((int)piStack_10);
          piVar3 = (int *)FUN_0041dad8((int)piStack_14);
          FUN_0041a530(piVar3,aiStack_34,piVar2,piVar5);
          FUN_00417ad0(param_1,piStack_c,piStack_14);
          iStack_20 = iStack_20 + -1;
          iVar4 = iVar4 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
      iStack_18 = iStack_18 + 1;
      iStack_24 = iStack_24 + -1;
    } while (iStack_24 != 0);
  }
  *in_FS_OFFSET = uStack_74;
  FUN_00402c34(piStack_c);
  FUN_00402c34(piStack_14);
  return;
}

