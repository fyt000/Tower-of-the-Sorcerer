/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c150.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042c150(int param_1,undefined4 param_2,undefined4 param_3)

{
  int **ppiVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_1c;
  undefined *puStack_18;
  undefined *puStack_14;
  
  if (*(int *)(*(int *)(param_1 + 0xac) + 4) == 0) {
    puStack_14 = (undefined *)0x42c175;
    piVar2 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
    puStack_18 = &LAB_0042c1c9;
    uStack_1c = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_1c;
    puStack_14 = &stack0xfffffffc;
    (**(code **)(*piVar2 + 0x2c))(piVar2,*(undefined4 *)(param_1 + 0x2c));
    (**(code **)(*piVar2 + 0x28))(piVar2,*(undefined4 *)(param_1 + 0x30));
    FUN_0041c160(*(int *)(param_1 + 0xac),piVar2);
    *in_FS_OFFSET = uStack_1c;
    puStack_14 = (undefined *)0x42c1d0;
    puStack_18 = (undefined *)0x42c1c8;
    FUN_00402c34(piVar2);
    return;
  }
  ppiVar1 = *(int ***)(*(int *)(param_1 + 0xac) + 4);
  puStack_14 = (undefined *)0x42c1e8;
  piVar2 = FUN_00402c7c(ppiVar1,(int *)&PTR_FUN_004193b4);
  if ((char)piVar2 == '\0') {
    puStack_14 = (undefined *)0x42c206;
    uVar3 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf042);
    puStack_14 = (undefined *)0x42c20b;
    FUN_004031f8(uVar3);
  }
  else {
    puStack_14 = (undefined *)0x42c1f3;
    FUN_0041dad8((int)ppiVar1);
  }
  return;
}

