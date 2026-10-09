/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041bea8.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined root_0041bea8(int *param_1,int *param_2)

{
  bool bVar1;
  char cVar2;
  undefined uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_34;
  code *pcStack_30;
  undefined *puStack_2c;
  undefined4 uStack_28;
  code *pcStack_24;
  undefined *puStack_20;
  
  if (param_2 != (int *)0x0) {
    puStack_20 = (undefined *)0x41bec0;
    iVar4 = FUN_00402b78(param_1);
    puStack_20 = (undefined *)0x41bec9;
    iVar5 = FUN_00402b78(param_2);
    if (iVar4 == iVar5) {
      bVar1 = true;
      goto LAB_0041bed3;
    }
  }
  bVar1 = false;
LAB_0041bed3:
  puStack_20 = (undefined *)0x41bedd;
  cVar2 = (**(code **)(*param_1 + 0x18))();
  if (cVar2 == '\0') {
    puStack_20 = (undefined *)0x41bee8;
    cVar2 = (**(code **)(*param_2 + 0x18))();
    if (cVar2 == '\0') {
      if (!bVar1) {
        return 0;
      }
      puStack_20 = (undefined *)0x41bf26;
      piVar6 = (int *)FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX
                                  );
      pcStack_24 = thunk_FUN_00403140;
      uStack_28 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_28;
      puStack_2c = (undefined *)0x41bf41;
      puStack_20 = &stack0xfffffffc;
      (**(code **)(*param_1 + 0x30))(param_1,piVar6);
      puStack_2c = (undefined *)0x41bf4d;
      piVar7 = (int *)FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                                   extraout_ECX_00);
      pcStack_30 = thunk_FUN_00403140;
      uStack_34 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_34;
      puStack_2c = &stack0xfffffffc;
      (**(code **)(*param_2 + 0x30))(param_2,piVar7);
      FUN_0041be68(piVar6,piVar7);
      *in_FS_OFFSET = uStack_34;
      puStack_2c = &LAB_0041bf93;
      pcStack_30 = (code *)0x41bf8b;
      uVar3 = FUN_00402c34(piVar7);
      return uVar3;
    }
  }
  puStack_20 = (undefined *)0x41bef3;
  cVar2 = (**(code **)(*param_1 + 0x18))();
  if (cVar2 != '\0') {
    puStack_20 = (undefined *)0x41befe;
    cVar2 = (**(code **)(*param_2 + 0x18))();
    if (cVar2 != '\0') {
      return 1;
    }
  }
  return 0;
}

