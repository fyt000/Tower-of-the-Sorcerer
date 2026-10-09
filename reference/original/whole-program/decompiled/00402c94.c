/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402c94.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00402c94(int *param_1,int param_2)

{
  int iVar1;
  UINT UVar2;
  LPVOID pvVar3;
  undefined4 in_stack_00000000;
  
  if (param_1 != (int *)0x0) {
    iVar1 = *param_1;
    while (iVar1 != param_2) {
      iVar1 = *(int *)(iVar1 + -0x14);
      if (iVar1 == 0) {
        iVar1 = 10;
        if (DAT_0048a004 != (code *)0x0) {
          iVar1 = (*DAT_0048a004)(10,in_stack_00000000);
        }
        UVar2 = CONCAT31((int3)((uint)(iVar1 + -1) >> 8),*(undefined *)(iVar1 + 0x4026f8));
        if (iVar1 + -1 < 0) {
          pvVar3 = FUN_00403498();
          UVar2 = *(UINT *)((int)pvVar3 + 4);
        }
        FUN_00404431(UVar2);
        return;
      }
    }
  }
  return;
}

