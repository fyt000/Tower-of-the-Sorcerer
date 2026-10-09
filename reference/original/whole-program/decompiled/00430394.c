/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430394.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00430394(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  FUN_00415c64(param_1,param_2);
  if ((*(byte *)(param_1 + 7) & 0x40) == 0) {
    iVar2 = FUN_00430344((int)param_1);
    iVar3 = (param_1[0x6d] + -1) * iVar2 + 1;
    iVar1 = param_1[0x6e];
    iVar4 = (param_1[0xb] + -1) / iVar2;
    param_1[0x6c] = iVar4 + 1;
    iVar2 = iVar4 * iVar2 + 1;
    if (iVar2 < iVar3) {
      iVar2 = iVar3;
    }
    iVar4 = iVar1;
    if (iVar1 <= param_1[0xc]) {
      iVar4 = param_1[0xc];
    }
    if ((iVar2 != param_1[0xb]) || (iVar4 != param_1[0xc])) {
      (**(code **)(*param_1 + 0x4c))(param_1,param_1[9],param_1[10],iVar4,iVar2,param_2,iVar3,iVar1)
      ;
    }
    *(undefined4 *)(param_2 + 0xc) = 0;
  }
  return;
}

