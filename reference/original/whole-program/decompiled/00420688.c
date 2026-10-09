/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420688.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00420688(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  byte bVar6;
  int local_20 [4];
  
  bVar6 = 0;
  piVar4 = local_20;
  FUN_0042070c((int)param_1);
  iVar1 = FUN_004131bc(param_1);
  iVar2 = FUN_0041f7d8(iVar1,*(int *)(param_1[0x41] + 0x10));
  iVar3 = FUN_00413178(param_1);
  iVar1 = param_1[0x40];
  iVar3 = FUN_0041f7d8(*(int *)(iVar1 + 0x10),iVar3);
  FUN_00409258(-*(int *)(iVar1 + 0xc),-*(int *)(param_1[0x41] + 0xc),iVar3,piVar4,iVar2);
  piVar4 = local_20;
  piVar5 = param_3;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar5 = *piVar4;
    piVar4 = piVar4 + (uint)bVar6 * -2 + 1;
    piVar5 = piVar5 + (uint)bVar6 * -2 + 1;
  }
  FUN_00414990(param_1,param_2,param_3);
  return;
}

