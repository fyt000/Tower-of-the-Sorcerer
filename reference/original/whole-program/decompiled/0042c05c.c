/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c05c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042c05c(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  int aiStack_18 [4];
  
  piVar8 = aiStack_18;
  piVar9 = aiStack_18;
  if ((*(byte *)(param_1 + 7) & 0x10) != 0) {
    piVar1 = (int *)param_1[0x2a];
    FUN_0041a030((int *)piVar1[4],1);
    FUN_0041a20c((int *)piVar1[5],'\x01');
    FUN_0041a73c(piVar1,0,0,param_1[0xc],param_1[0xb]);
  }
  if (*(char *)((int)param_1 + 0xb1) == '\0') {
    if (*(char *)((int)param_1 + 0xb2) == '\0') {
      uVar4 = FUN_0041c594(param_1[0x2b]);
      uVar5 = FUN_0041c57c(param_1[0x2b]);
      FUN_0040923c(0,0,uVar5,piVar9,uVar4);
    }
    else {
      iVar2 = FUN_0041c594(param_1[0x2b]);
      iVar3 = FUN_0041c594(param_1[0x2b]);
      iVar6 = param_1[0xc] - iVar3 >> 1;
      if (iVar6 < 0) {
        iVar6 = iVar6 + (uint)((param_1[0xc] - iVar3 & 1U) != 0);
      }
      iVar3 = FUN_0041c57c(param_1[0x2b]);
      iVar7 = param_1[0xb] - iVar3 >> 1;
      if (iVar7 < 0) {
        iVar7 = iVar7 + (uint)((param_1[0xb] - iVar3 & 1U) != 0);
      }
      iVar3 = FUN_0041c57c(param_1[0x2b]);
      FUN_00409258(iVar7,iVar6,iVar3,piVar8,iVar2);
    }
  }
  else {
    (**(code **)(*param_1 + 0x2c))(param_1,aiStack_18);
  }
  FUN_0041a784((int *)param_1[0x2a],aiStack_18,*(int **)(param_1[0x2b] + 4));
  return;
}

