/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422fc4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422fc4(int *param_1,int param_2)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  bool bVar2;
  
  (**(code **)(*param_1 + -0x10))(param_1,param_2);
  if (*(char *)((int)param_1 + 0x11a) == '\x01') {
    iVar1 = FUN_00416cbc(param_1);
    bVar2 = iVar1 == *(int *)(param_2 + 8);
    root_00422704(param_1,bVar2);
    if ((bVar2) && ((*(byte *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x36) & 4) != 0)) {
      FUN_00402cdc(*(int **)(DAT_0048a6f8 + 0x28),CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                   extraout_ECX);
    }
  }
  return;
}

