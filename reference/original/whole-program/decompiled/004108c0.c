/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004108c0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined FUN_004108c0(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  int iVar4;
  int iVar5;
  undefined local_5;
  
  local_5 = 0;
  if ((((*(char *)(param_4 + -1) == '\0') &&
       (*(uint *)(param_4 + -8) == (uint)*(ushort *)(param_1 + 0x30))) ||
      ((*(char *)(param_4 + -1) == '\x01' && (*(int *)(param_4 + -8) == *(int *)(param_1 + 0x24)))))
     || ((*(char *)(param_4 + -1) == '\x02' &&
         (*(uint *)(param_4 + -8) == (uint)*(ushort *)(param_1 + 0x40))))) {
    *(int *)(param_4 + -0xc) = param_1;
    local_5 = 1;
  }
  else {
    iVar2 = FUN_0041040c(param_1);
    if (-1 < iVar2 + -1) {
      iVar4 = 0;
      do {
        iVar5 = param_4;
        iVar3 = FUN_0041041c(param_1,iVar4);
        cVar1 = FUN_004108c0(iVar3,extraout_EDX,extraout_ECX,iVar5);
        if (cVar1 != '\0') {
          return 1;
        }
        iVar4 = iVar4 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return local_5;
}

