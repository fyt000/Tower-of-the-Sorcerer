/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c260.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042c260(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  
  if (*(char *)(param_1 + 0x2c) != '\0') {
    iVar1 = FUN_0041c57c(param_1[0x2b]);
    if (0 < iVar1) {
      iVar1 = FUN_0041c594(param_1[0x2b]);
      if (0 < iVar1) {
        uVar2 = FUN_0041c57c(param_1[0x2b]);
        uVar3 = FUN_0041c594(param_1[0x2b]);
        (**(code **)(*param_1 + 0x4c))(param_1,param_1[9],param_1[10],uVar3,uVar2);
      }
    }
  }
  iVar1 = param_1[0x2b];
  piVar4 = FUN_00402c7c(*(int ***)(iVar1 + 4),(int *)&PTR_FUN_004193b4);
  if ((char)piVar4 != '\0') {
    iVar1 = FUN_0041c57c(iVar1);
    if (param_1[0xb] <= iVar1) {
      iVar1 = FUN_0041c594(param_1[0x2b]);
      if (param_1[0xc] <= iVar1) {
        *(ushort *)(param_1 + 0xd) = DAT_0042c310 | *(ushort *)(param_1 + 0xd);
        goto LAB_0042c303;
      }
    }
  }
  *(ushort *)(param_1 + 0xd) = ~DAT_0042c310 & *(ushort *)(param_1 + 0xd);
LAB_0042c303:
  (**(code **)(*param_1 + 0x44))();
  return;
}

