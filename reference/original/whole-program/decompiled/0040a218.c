/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a218.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040a218(int *param_1,int *param_2)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *in_FS_OFFSET;
  undefined uVar4;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  uint *local_18;
  uint *local_14;
  undefined local_d;
  int *local_c;
  int *local_8;
  
  puStack_28 = &stack0xfffffffc;
  local_14 = (uint *)0x0;
  local_18 = (uint *)0x0;
  puStack_2c = &LAB_0040a2ad;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  local_d = 0;
  local_c = param_2;
  local_8 = param_1;
  iVar2 = (**(code **)(*param_1 + 0x10))();
  iVar3 = (**(code **)(*local_c + 0x10))();
  if (iVar2 == iVar3) {
    if (-1 < iVar2 + -1) {
      iVar3 = 0;
      uVar4 = true;
      do {
        (**(code **)(*local_8 + 0xc))(local_8,iVar3,&local_14);
        puVar1 = local_14;
        (**(code **)(*local_c + 0xc))(local_c,iVar3,&local_18);
        FUN_00403760(puVar1,local_18);
        if (!(bool)uVar4) goto LAB_0040a292;
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + -1;
        uVar4 = iVar2 == 0;
      } while (!(bool)uVar4);
    }
    local_d = 1;
  }
LAB_0040a292:
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_0040a2b4;
  puStack_2c = (undefined *)0x40a2ac;
  FUN_004034fc((int *)&local_18,2);
  return;
}

