/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430d78.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void root_00430d78(int *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int extraout_EDX;
  int extraout_EDX_00;
  int iVar3;
  
  iVar3 = param_2;
  if ((*(char *)(param_1 + 0x84) != '\0') &&
     (cVar2 = FUN_0043206c((int)param_1), param_3 = extraout_ECX, iVar3 = extraout_EDX,
     cVar2 == '\x01')) {
    if (*(char *)((int)param_1 + 0x1d7) != '\0') {
      *(ushort *)((int)param_1 + 0x19a) = *(ushort *)((int)param_1 + 0x19a) | 1;
    }
    if (*(char *)((int)param_1 + 0x1da) != '\0') {
      *(ushort *)((int)param_1 + 0x19a) = *(ushort *)((int)param_1 + 0x19a) | 0x80;
    }
    *(ushort *)((int)param_1 + 0x19a) = ~_DAT_00430e18 & *(ushort *)((int)param_1 + 0x19a);
    FUN_0043025c(param_1);
    param_3 = extraout_ECX_00;
    iVar3 = extraout_EDX_00;
  }
  iVar1 = *(int *)(param_2 + 4);
  if (iVar1 == 1) {
    *(undefined *)(param_1 + 0x7f) = 0;
  }
  else if (iVar1 == 2) {
    *(undefined *)(param_1 + 0x7f) = 1;
  }
  else if (iVar1 == 4) {
    *(undefined *)(param_1 + 0x7f) = 2;
  }
  else if (iVar1 == 8) {
    *(undefined *)(param_1 + 0x7f) = 3;
  }
  FUN_00402cdc(param_1,iVar3,param_3);
  return;
}

