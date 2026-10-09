/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043da80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043da80(undefined4 *param_1,char *param_2,char **param_3,char **param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  char **in_FS_OFFSET;
  char *pcStackY_44;
  char *pcStackY_38;
  undefined *puStackY_34;
  char **ppcVar6;
  char *pcStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  undefined4 *local_14;
  undefined4 *local_10;
  char *local_c;
  undefined4 *local_8;
  
  puStack_24 = &stack0xfffffffc;
  local_c = (char *)0x0;
  local_10 = (undefined4 *)0x0;
  local_14 = (undefined4 *)0x0;
  puStack_28 = &LAB_0043dce8;
  pcStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = (char *)&pcStack_2c;
  local_8 = param_1;
  FUN_00402768('\0',(int *)&local_c);
  *param_2 = *local_c;
  FUN_0040352c((int *)param_3,local_8);
  if (**param_3 == '[') {
    cVar1 = FUN_0040ed64(*param_3);
    if (cVar1 == ']') {
      puStackY_34 = (undefined *)0x43dadb;
      ppcVar6 = param_3;
      iVar2 = FUN_00403650((int)*param_3);
      puStackY_34 = (undefined *)0x43daec;
      FUN_00403854((int)*param_3,2,iVar2 - 2,(int *)ppcVar6);
      goto LAB_0043db49;
    }
  }
  FUN_00405f04(*param_3,(int *)&local_10);
  iVar2 = FUN_00403650((int)local_10);
  if (iVar2 == 0) {
    FUN_00405f04(local_c,(int *)&local_10);
  }
  else {
    iVar2 = FUN_00403650((int)local_10);
    FUN_00403894((int *)param_3,1,iVar2);
  }
  iVar2 = FUN_00403650((int)local_10);
  if ((iVar2 < 2) || (*(char *)((int)local_10 + 1) != ':')) {
    *param_2 = '\0';
  }
  else {
    *param_2 = *(char *)local_10;
  }
LAB_0043db49:
  puStackY_34 = &LAB_0043dcc6;
  pcStackY_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = (char *)&pcStackY_38;
  FUN_0040274c((undefined *)local_10);
  FUN_00402710();
  FUN_00405f98((int)*param_3,(int *)&local_14);
  FUN_0040352c((int *)param_4,local_14);
  iVar2 = FUN_00403650((int)*param_3);
  iVar3 = FUN_00403650((int)*param_4);
  if (iVar2 == iVar3 + 1) {
    FUN_0040352c((int *)param_3,(undefined4 *)&DAT_0043dd00);
  }
  else {
    iVar2 = FUN_00403650((int)*param_3);
    iVar3 = FUN_00403650((int)*param_4);
    if (iVar3 < iVar2) {
      iVar2 = FUN_00403650((int)*param_3);
      iVar3 = FUN_00403650((int)*param_4);
      FUN_00403924((int *)param_3,(iVar2 - iVar3) - 1);
    }
    else {
      FUN_00402768('\0',(int *)param_3);
      FUN_00405f04(*param_3,(int *)&local_14);
      iVar2 = FUN_00403650((int)local_14);
      FUN_00403894((int *)param_3,1,iVar2);
      iVar2 = FUN_00403650((int)*param_3);
      if (iVar2 == 0) {
        FUN_0040352c((int *)param_3,(undefined4 *)&DAT_0043dd00);
      }
    }
  }
  iVar2 = FUN_00403650((int)*param_3);
  if (0 < iVar2) {
    FUN_0040274c(*param_3);
    FUN_00402710();
  }
  iVar2 = FUN_00403650((int)*param_4);
  if (0 < iVar2) {
    pcVar4 = FUN_004038dc("*",*param_4);
    if ((int)pcVar4 < 1) {
      pcVar4 = FUN_004038dc("?",*param_4);
      if ((int)pcVar4 < 1) {
        uVar5 = FUN_00405dbc(*param_4);
        if ((char)uVar5 == '\0') {
          FUN_0040274c(*param_4);
          FUN_00402710();
          iVar2 = FUN_00403650((int)*param_3);
          if (iVar2 == 1) {
            FUN_0040369c((int *)param_3,(undefined4 *)&DAT_0043dd00,(undefined4 *)*param_4);
          }
          else {
            pcStackY_44 = *param_4;
            FUN_00403710((int *)param_3,3);
          }
          FUN_004034dc((int *)param_4);
        }
      }
    }
  }
  if (*param_2 == '\0') {
    FUN_0040369c((int *)param_3,local_10,(undefined4 *)*param_3);
  }
  *in_FS_OFFSET = pcStackY_44;
  FUN_0040274c(local_c);
  FUN_00402710();
  return;
}

