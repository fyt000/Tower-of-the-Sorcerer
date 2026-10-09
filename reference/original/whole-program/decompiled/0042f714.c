/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f714.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042f714(int *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_2 + 8);
  iVar2 = *(int *)(iVar1 + 8);
  if (iVar2 == 0x701) {
    (**(code **)(*param_1 + 0x84))(param_1,iVar1 + 0xc);
  }
  else if (iVar2 == 0x702) {
    FUN_00402cdc(param_1,iVar1,param_3);
  }
  else if (iVar2 == 0x704) {
    uVar3 = FUN_0042f7c4((int)param_1,*(undefined4 *)(iVar1 + 0x18),*(uint *)(iVar1 + 0x1c));
    if ((char)uVar3 == '\0') {
      *(undefined4 *)(param_2 + 0xc) = 1;
    }
  }
  else if ((iVar2 == 0x708) &&
          (uVar3 = FUN_0042f794((int)param_1,*(undefined4 *)(iVar1 + 0xc),
                                *(undefined4 *)(iVar1 + 0x10)), (char)uVar3 == '\0')) {
    *(undefined4 *)(param_2 + 0xc) = 1;
  }
  return;
}

