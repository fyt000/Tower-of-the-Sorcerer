/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430f20.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00430f20(int *param_1,undefined4 param_2,int param_3)

{
  undefined *puVar1;
  char cVar2;
  MCIERROR MVar3;
  int iVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_44;
  undefined *puStack_40;
  undefined *puStack_3c;
  undefined4 *local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined2 local_14;
  undefined *local_10;
  undefined *local_c;
  
  puStack_3c = &stack0xfffffffc;
  local_2c = (undefined4 *)0x0;
  puStack_40 = &LAB_00431172;
  uStack_44 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_44;
  puVar1 = &stack0xfffffffc;
  if (*(char *)((int)param_1 + 0x1d5) != '\0') {
    FUN_00431188(param_1,0,param_3);
    puVar1 = puStack_3c;
  }
  puStack_3c = puVar1;
  local_18 = 0;
  if (*(byte *)(param_1 + 0x7a) != 0) {
    local_10 = (&PTR_DAT_00489830)[*(byte *)(param_1 + 0x7a) & 0x7f];
  }
  if (param_1[0x83] != 0) {
    local_c = FUN_00403814((undefined *)param_1[0x83]);
  }
  param_1[0x77] = 0;
  if (*(char *)((int)param_1 + 0x1e2) == '\0') {
    param_1[0x77] = 2;
  }
  else {
    if (*(char *)(param_1 + 0x78) != '\0') {
      param_1[0x77] = 2;
    }
    *(undefined *)((int)param_1 + 0x1e2) = 0;
  }
  if (*(char *)((int)param_1 + 0x1e3) != '\0') {
    if (*(char *)((int)param_1 + 0x1e1) != '\0') {
      param_1[0x77] = param_1[0x77] | 1;
    }
    *(undefined *)((int)param_1 + 0x1e3) = 0;
  }
  if (param_1[0x83] != 0) {
    param_1[0x77] = param_1[0x77] | 0x200;
  }
  if (*(char *)(param_1 + 0x7a) != '\0') {
    param_1[0x77] = param_1[0x77] | 0x2000;
  }
  if (*(char *)((int)param_1 + 0x213) != '\0') {
    param_1[0x77] = param_1[0x77] | 0x100;
  }
  local_18 = FUN_00416cbc(param_1);
  MVar3 = mciSendCommandA(0,0x803,param_1[0x77],(DWORD_PTR)&local_18);
  param_1[0x7e] = MVar3;
  if (MVar3 == 0) {
    *(undefined *)((int)param_1 + 0x1d5) = 1;
    *(undefined2 *)((int)param_1 + 0x1e6) = local_14;
    iVar4 = FUN_00431fdc((int)param_1,extraout_EDX);
    param_1[0x7d] = iVar4 / 10;
    FUN_00431e44((int)param_1);
    if (*(char *)((int)param_1 + 0x1db) != '\0') {
      FUN_00431cd8((int)param_1,(int *)param_1[0x80]);
      FUN_00431dec((int)param_1,&local_28);
      param_1[0x81] = local_20 - local_28;
      param_1[0x82] = local_1c - local_24;
    }
    if ((*(char *)(param_1 + 0x7a) == '\x02') || (*(char *)(param_1 + 0x7a) == '\v')) {
      FUN_00431c9c((int)param_1,10);
    }
    *(undefined2 *)((int)param_1 + 0x19a) = DAT_00431180;
    if (*(char *)(param_1 + 0x76) != '\0') {
      *(ushort *)((int)param_1 + 0x19a) = DAT_00431184 | *(ushort *)((int)param_1 + 0x19a);
    }
    if (*(char *)((int)param_1 + 0x1d7) != '\0') {
      *(ushort *)((int)param_1 + 0x19a) = *(ushort *)((int)param_1 + 0x19a) | 1;
    }
    if (*(char *)((int)param_1 + 0x1da) != '\0') {
      *(ushort *)((int)param_1 + 0x19a) = *(ushort *)((int)param_1 + 0x19a) | 0x80;
    }
    if (*(char *)((int)param_1 + 0x1d9) != '\0') {
      *(ushort *)((int)param_1 + 0x19a) = *(ushort *)((int)param_1 + 0x19a) | 0x100;
    }
    cVar2 = FUN_0043206c((int)param_1);
    if (cVar2 == '\x02') {
      FUN_00402cdc(param_1,0,extraout_ECX);
    }
    FUN_0043025c(param_1);
  }
  else {
    FUN_00432138((int)param_1,(int *)&local_2c);
    iVar4 = FUN_00407498(0x42fa18,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),local_2c);
    FUN_004031f8(iVar4);
  }
  *in_FS_OFFSET = uStack_44;
  puStack_3c = &LAB_00431179;
  puStack_40 = (undefined *)0x431171;
  FUN_004034dc((int *)&local_2c);
  return;
}

