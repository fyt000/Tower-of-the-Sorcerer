/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042018c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042018c(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int iVar3;
  undefined *puVar4;
  
  if (*(char *)(*(int *)(param_1 + 4) + 0x108) != '\0') {
    iVar1 = FUN_00414ccc(*(int *)(param_1 + 4));
    if (-1 < iVar1 + -1) {
      iVar3 = 0;
      do {
        if (*(char *)(param_1 + 0x18) == '\0') {
          puVar4 = &stack0xfffffffc;
          iVar2 = FUN_00414c9c(*(int *)(param_1 + 4),iVar3);
          FUN_004200fc(iVar2,extraout_EDX,extraout_ECX,(int)puVar4);
        }
        else {
          puVar4 = &stack0xfffffffc;
          iVar2 = FUN_00414c9c(*(int *)(param_1 + 4),iVar3);
          FUN_00420144(iVar2,extraout_EDX_00,extraout_ECX_00,(int)puVar4);
        }
        iVar3 = iVar3 + 1;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    FUN_004204e0(param_1,(uint)*(ushort *)(param_1 + 0x1a));
  }
  return;
}

