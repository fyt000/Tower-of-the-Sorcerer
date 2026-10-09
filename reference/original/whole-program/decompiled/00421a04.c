/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421a04.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00421a04(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (((*(char *)(param_1 + 0x11a) == '\x02') && (*(int *)(param_1 + 0x134) != 0)) &&
     (iVar1 = FUN_00423bbc(DAT_0048a6fc), -1 < iVar1 + -1)) {
    iVar3 = 0;
    do {
      iVar2 = FUN_00423bb0(DAT_0048a6fc,iVar3);
      if ((*(char *)(iVar2 + 0x11a) == '\x01') && (param_2 = param_2 + -1, param_2 < 0)) {
        return iVar2;
      }
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return 0;
}

