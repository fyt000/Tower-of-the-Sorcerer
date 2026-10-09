/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00418160.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00418160(int param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  if (param_2 != (int *)0x0) {
    iVar1 = (**(code **)(*param_2 + 0x1c))();
    uVar2 = extraout_EDX;
    if ((*(int *)(param_1 + 0x20) <= iVar1) &&
       (iVar1 = (**(code **)(*param_2 + 0x20))(), uVar2 = extraout_EDX_00,
       *(int *)(param_1 + 0x24) <= iVar1)) {
      return;
    }
    uVar2 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)uVar2 >> 8),1),0xf024);
    FUN_004031f8(uVar2);
  }
  return;
}

