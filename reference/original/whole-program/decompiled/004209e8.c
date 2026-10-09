/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004209e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004209e8(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_3 != param_2) {
    if ((*(byte *)(param_1 + 0x1c) & 1) == 0) {
      *(undefined *)(*(int *)(param_1 + 0x100) + 0x1e) = 1;
      *(undefined *)(*(int *)(param_1 + 0x104) + 0x1e) = 1;
    }
    FUN_00420424(*(int *)(param_1 + 0x100),0);
    FUN_00420424(*(int *)(param_1 + 0x104),0);
    if (*(char *)(param_1 + 0x108) == '\0') {
      iVar1 = *(int *)(param_1 + 0x100);
      if (*(char *)(iVar1 + 0x1e) != '\0') {
        iVar2 = MulDiv(*(int *)(iVar1 + 0x10),param_2,param_3);
        FUN_004204f8(iVar1,iVar2);
      }
      iVar1 = *(int *)(param_1 + 0x104);
      if (*(char *)(iVar1 + 0x1e) != '\0') {
        iVar2 = MulDiv(*(int *)(iVar1 + 0x10),param_2,param_3);
        FUN_004204f8(iVar1,iVar2);
      }
    }
  }
  *(undefined *)(*(int *)(param_1 + 0x100) + 0x1e) = 0;
  *(undefined *)(*(int *)(param_1 + 0x104) + 0x1e) = 0;
  return;
}

