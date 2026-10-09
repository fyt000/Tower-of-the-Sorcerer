/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004230a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004230a4(int param_1,int param_2)

{
  int iVar1;
  HANDLE pvVar2;
  ULONG_PTR UVar3;
  undefined extraout_DL;
  undefined uVar4;
  
  uVar4 = SUB41(&stack0xfffffffc,0);
  iVar1 = *(int *)(param_2 + 8);
  if (*(int *)(iVar1 + 4) == 1) {
    for (pvVar2 = FUN_004121e4(*(HWND *)(iVar1 + 0xc));
        (pvVar2 != (HANDLE)0x0 && (*(int *)((int)pvVar2 + 0xd0) == 0));
        pvVar2 = *(HANDLE *)((int)pvVar2 + 0x20)) {
    }
    if (pvVar2 == (HANDLE)0x0) {
      return;
    }
    UVar3 = *(ULONG_PTR *)((int)pvVar2 + 0xd0);
  }
  else {
    UVar3 = FUN_00423064(*(int *)(param_1 + 0x128),(char)iVar1,(char)param_2,&stack0xfffffffc);
    if (UVar3 == 0) {
      UVar3 = FUN_00423064(*(int *)(param_1 + 0x50),extraout_DL,uVar4,&stack0xfffffffc);
    }
  }
  if ((*(byte *)(param_1 + 0x114) & 8) == 0) {
    FUN_0042524c(DAT_0048a6f8,UVar3);
  }
  else {
    FUN_00425258(DAT_0048a6f8,8,UVar3);
  }
  return;
}

