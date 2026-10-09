/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00433b6c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00433b6c(int **param_1,uint param_2)

{
  undefined *puVar1;
  int *piVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 uVar3;
  undefined uVar4;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar5;
  char cVar6;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  uint *puStack_c;
  int iStack_8;
  
  puStack_1c = &stack0xfffffffc;
  iStack_8 = 0;
  puStack_c = (uint *)0x0;
  puStack_20 = &LAB_00433c6f;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  cVar6 = (char)param_2;
  if (cVar6 == *(char *)((int)param_1 + 0x115)) goto LAB_00433c51;
  puVar1 = &stack0xfffffffc;
  if (cVar6 != '\0') {
    if ((cVar6 == '\x01') || (cVar6 == '\x04')) {
      uVar4 = 1;
    }
    else {
      uVar4 = 0;
    }
    FUN_0042a3e8(param_1,uVar4);
    if ((cVar6 == '\x02') || (cVar6 == '\x05')) {
      uVar4 = 1;
    }
    else {
      uVar4 = 0;
    }
    *(undefined *)((int)param_1 + 0x105) = uVar4;
    uVar3 = extraout_ECX;
    uVar5 = extraout_EDX;
    if ((*(byte *)(param_1 + 7) & 1) == 0) {
LAB_00433bdf:
      if ((*(byte *)(param_1 + 7) & 1) == 0) goto LAB_00433be5;
    }
    else {
      FUN_004135a4((int *)param_1,&iStack_8);
      uVar3 = extraout_ECX_00;
      uVar5 = extraout_EDX_00;
      if (iStack_8 != 0) goto LAB_00433bdf;
LAB_00433be5:
      if (*(ushort *)(&DAT_00489890 + (param_2 & 0xff) * 2) != 0) {
        FUN_00405bf0((uint)*(ushort *)(&DAT_00489890 + (param_2 & 0xff) * 2),(int *)&puStack_c);
        FUN_004135d4((int *)param_1,puStack_c);
        uVar3 = extraout_ECX_01;
        uVar5 = extraout_EDX_01;
      }
    }
    param_1[0x42] = *(int **)(&DAT_004898a8 + (param_2 & 0xff) * 4);
    piVar2 = (int *)FUN_0043268c(param_2,uVar5,uVar3);
    FUN_00432bc0((int)param_1[0x44],piVar2);
    FUN_00433d94((int *)param_1,2);
    *(undefined *)((int)param_1 + 0x121) = 0;
    puVar1 = puStack_1c;
  }
  puStack_1c = puVar1;
  *(char *)((int)param_1 + 0x115) = cVar6;
  (*(code *)(*param_1)[0x11])();
LAB_00433c51:
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_00433c76;
  puStack_20 = (undefined *)0x433c66;
  FUN_004034dc((int *)&puStack_c);
  puStack_20 = (undefined *)0x433c6e;
  FUN_004034dc(&iStack_8);
  return;
}

