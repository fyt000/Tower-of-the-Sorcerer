/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00432bc0.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00432bc0(int param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  FUN_00432b48(param_1);
  iVar1 = (**(code **)(**(int **)(param_1 + 4) + 8))(*(int **)(param_1 + 4),param_2);
  if (param_2 != (int *)0x0) {
    iVar1 = (**(code **)(*param_2 + 0x1c))();
    if (0 < iVar1) {
      uVar2 = FUN_0041db60(param_2);
      *(uint *)(param_1 + 0x1c) = uVar2;
      iVar3 = (**(code **)(*param_2 + 0x20))();
      iVar4 = (**(code **)(*param_2 + 0x1c))();
      iVar1 = iVar3 / iVar4;
      if (iVar3 % iVar4 == 0) {
        iVar3 = (**(code **)(*param_2 + 0x20))();
        iVar1 = (**(code **)(*param_2 + 0x1c))();
        iVar3 = iVar3 / iVar1;
        if (4 < iVar3) {
          iVar3 = 1;
        }
        iVar1 = FUN_00432c38(param_1,(char)iVar3);
      }
    }
  }
  return iVar1;
}

