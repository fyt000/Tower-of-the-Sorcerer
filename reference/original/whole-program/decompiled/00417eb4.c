/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417eb4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417eb4(int *param_1,HIMAGELIST param_2)

{
  int iVar1;
  int *piVar2;
  HDC pHVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int i;
  undefined4 *in_FS_OFFSET;
  int iVar4;
  UINT UVar5;
  undefined4 uStack_3c;
  RECT local_24;
  int local_14;
  int *local_10;
  int *local_c;
  HIMAGELIST local_8;
  
  uStack_3c = 0x417ed6;
  local_8 = param_2;
  FUN_0040923c(0,0,param_1[9],&local_24.left,param_1[8]);
  local_c = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
  (**(code **)(*local_c + 0x28))(local_c,param_1[8]);
  (**(code **)(*local_c + 0x2c))(local_c,param_1[9]);
  local_10 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                                 extraout_ECX_00);
  (**(code **)(*local_10 + 0x28))(local_10,param_1[8]);
  (**(code **)(*local_10 + 0x2c))(local_10,param_1[9]);
  uStack_3c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_3c;
  iVar1 = ImageList_GetImageCount(local_8);
  if (-1 < iVar1 + -1) {
    i = 0;
    local_14 = iVar1;
    do {
      piVar2 = (int *)FUN_0041dad8((int)local_c);
      FUN_0041a664(piVar2,&local_24);
      UVar5 = 0;
      iVar4 = 0;
      iVar1 = 0;
      pHVar3 = (HDC)FUN_0041a950(piVar2);
      ImageList_Draw(local_8,i,pHVar3,iVar1,iVar4,UVar5);
      piVar2 = (int *)FUN_0041dad8((int)local_10);
      FUN_0041a664(piVar2,&local_24);
      UVar5 = 0x10;
      iVar4 = 0;
      iVar1 = 0;
      pHVar3 = (HDC)FUN_0041a950(piVar2);
      ImageList_Draw(local_8,i,pHVar3,iVar1,iVar4,UVar5);
      FUN_00417ad0(param_1,local_c,local_10);
      i = i + 1;
      local_14 = local_14 + -1;
    } while (local_14 != 0);
  }
  *in_FS_OFFSET = uStack_3c;
  FUN_00402c34(local_c);
  FUN_00402c34(local_10);
  return;
}

