/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409ea8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409ea8(int *param_1,int **param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  
  puStack_18 = (undefined *)0x409ec0;
  piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_00408bb8);
  if ((char)piVar1 != '\0') {
    puStack_18 = (undefined *)0x409ecc;
    FUN_00409f3c((int)param_1);
    puStack_1c = &LAB_00409f25;
    uStack_20 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_20;
    puStack_18 = &stack0xfffffffc;
    FUN_00409f50(param_1);
    iVar2 = FUN_00409fc4((int)param_2);
    if (-1 < iVar2 + -1) {
      iVar4 = 0;
      do {
        uVar3 = FUN_00409fcc((int)param_2,iVar4);
        piVar1 = (int *)FUN_00409e9c((int)param_1);
        (**(code **)(*piVar1 + 8))(piVar1,uVar3);
        iVar4 = iVar4 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    *in_FS_OFFSET = uStack_20;
    puStack_18 = (undefined *)0x409f36;
    puStack_1c = (undefined *)0x409f24;
    FUN_00409fb8(param_1);
    return;
  }
  puStack_18 = (undefined *)0x409f36;
  FUN_00409d78(param_1,param_2);
  return;
}

