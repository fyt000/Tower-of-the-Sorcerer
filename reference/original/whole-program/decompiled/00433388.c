/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00433388.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00433388(int param_1,int *param_2,int *param_3,LPRECT param_4,int *param_5,int param_6,
                 int param_7,byte param_8,undefined *param_9)

{
  undefined4 uVar1;
  int iVar2;
  LPCSTR lpchText;
  HDC hdc;
  uint uVar3;
  LONG *pLVar4;
  LPRECT ptVar5;
  byte bVar6;
  UINT format;
  LONG local_44 [4];
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int *local_c;
  int local_8;
  
  bVar6 = 0;
  local_c = param_2;
  local_8 = param_1;
  FUN_00409224(param_3[2] - *param_3,param_3[3] - param_3[1],&local_1c);
  if (*(int *)(local_8 + 4) == 0) {
    FUN_00409224(0,0,&local_24);
  }
  else {
    uVar1 = (**(code **)(**(int **)(local_8 + 4) + 0x1c))();
    iVar2 = (**(code **)(**(int **)(local_8 + 4) + 0x20))();
    FUN_00409224(iVar2 / (int)(uint)*(byte *)(local_8 + 0x20),uVar1,&local_24);
  }
  iVar2 = FUN_00403650((int)param_9);
  if (iVar2 < 1) {
    FUN_0040923c(0,0,0,local_44,0);
    pLVar4 = local_44;
    ptVar5 = param_4;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      ptVar5->left = *pLVar4;
      pLVar4 = pLVar4 + (uint)bVar6 * -2 + 1;
      ptVar5 = (LPRECT)((int)ptVar5 + (uint)bVar6 * -8 + 4);
    }
    FUN_00409224(0,0,&local_2c);
  }
  else {
    FUN_0040923c(0,0,param_3[2] - *param_3,local_44,0);
    pLVar4 = local_44;
    ptVar5 = param_4;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      ptVar5->left = *pLVar4;
      pLVar4 = pLVar4 + (uint)bVar6 * -2 + 1;
      ptVar5 = (LPRECT)((int)ptVar5 + (uint)bVar6 * -8 + 4);
    }
    format = 0x400;
    ptVar5 = param_4;
    iVar2 = FUN_00403650((int)param_9);
    lpchText = FUN_00403814(param_9);
    hdc = (HDC)FUN_0041a950(local_c);
    DrawTextA(hdc,lpchText,iVar2,ptVar5,format);
    FUN_00409224(param_4->right - param_4->left,param_4->bottom - param_4->top,&local_2c);
  }
  if (param_8 < 2) {
    uVar3 = (local_18 - local_20) + 1;
    iVar2 = (int)uVar3 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar3 & 1) != 0);
    }
    param_5[1] = iVar2;
    uVar3 = (local_18 - local_28) + 1;
    local_10 = (int)uVar3 >> 1;
    if (local_10 < 0) {
      local_10 = local_10 + (uint)((uVar3 & 1) != 0);
    }
  }
  else {
    uVar3 = (local_1c - local_24) + 1;
    iVar2 = (int)uVar3 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar3 & 1) != 0);
    }
    *param_5 = iVar2;
    uVar3 = (local_1c - local_2c) + 1;
    local_14 = (int)uVar3 >> 1;
    if (local_14 < 0) {
      local_14 = local_14 + (uint)((uVar3 & 1) != 0);
    }
  }
  if ((local_2c == 0) || (local_24 == 0)) {
    param_6 = 0;
  }
  if (param_7 == -1) {
    if (param_6 == -1) {
      FUN_00409224(local_24 + local_2c,local_20 + local_28,&local_34);
      if (param_8 < 2) {
        local_34 = local_1c - local_34;
      }
      else {
        local_34 = local_18 - local_30;
      }
      param_7 = local_34 / 3;
      param_6 = param_7;
    }
    else {
      FUN_00409224(local_24 + param_6 + local_2c,local_20 + param_6 + local_28,&local_34);
      if (param_8 < 2) {
        uVar3 = (local_1c - local_34) + 1;
        param_7 = (int)uVar3 >> 1;
        if (param_7 < 0) {
          param_7 = param_7 + (uint)((uVar3 & 1) != 0);
        }
      }
      else {
        uVar3 = (local_18 - local_30) + 1;
        param_7 = (int)uVar3 >> 1;
        if (param_7 < 0) {
          param_7 = param_7 + (uint)((uVar3 & 1) != 0);
        }
      }
    }
  }
  else if (param_6 == -1) {
    FUN_00409224(local_1c - (param_7 + local_24),local_18 - (param_7 + local_20),&local_34);
    if (param_8 < 2) {
      param_6 = local_34 - local_2c >> 1;
      if (param_6 < 0) {
        param_6 = param_6 + (uint)((local_34 - local_2c & 1U) != 0);
      }
    }
    else {
      param_6 = local_30 - local_28 >> 1;
      if (param_6 < 0) {
        param_6 = param_6 + (uint)((local_30 - local_28 & 1U) != 0);
      }
    }
  }
  if (param_8 == 0) {
    *param_5 = param_7;
    local_14 = param_7 + local_24 + param_6;
  }
  else if (param_8 == 1) {
    local_24 = (local_1c - param_7) - local_24;
    *param_5 = local_24;
    local_14 = (local_24 - param_6) - local_2c;
  }
  else if (param_8 == 2) {
    param_5[1] = param_7;
    local_10 = param_7 + local_20 + param_6;
  }
  else if (param_8 == 3) {
    local_20 = (local_18 - param_7) - local_20;
    param_5[1] = local_20;
    local_10 = (local_20 - param_6) - local_28;
  }
  *param_5 = *param_5 + *param_3;
  param_5[1] = param_5[1] + param_3[1];
  OffsetRect(param_4,*param_3 + local_14,param_3[1] + local_10);
  return;
}

