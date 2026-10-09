/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041651c.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_0041651c(int **param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  int **ppiVar3;
  LRESULT LVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int extraout_EDX;
  int extraout_EDX_00;
  int iVar5;
  
  if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
    iVar5 = param_2;
    ppiVar3 = param_1;
    if (param_1 != (int **)0x0) {
      do {
        iVar2 = FUN_00402cdc((int *)ppiVar3,iVar5,param_3);
        param_3 = extraout_ECX;
        iVar5 = extraout_EDX;
        if ((iVar2 != 0) &&
           (bVar1 = FUN_00410a80(iVar2), param_3 = extraout_ECX_00, iVar5 = extraout_EDX_00, bVar1))
        {
          return true;
        }
        ppiVar3 = (int **)ppiVar3[8];
      } while (ppiVar3 != (int **)0x0);
    }
    ppiVar3 = FUN_0041fffc(param_1);
    if (((ppiVar3 != (int **)0x0) && (ppiVar3[0x4a] != (int *)0x0)) &&
       (bVar1 = FUN_00410a80((int)ppiVar3[0x4a]), bVar1)) {
      return true;
    }
  }
  LVar4 = FUN_00412200(0xb016,(uint)*(ushort *)(param_2 + 4),*(LPARAM *)(param_2 + 8));
  return LVar4 != 0;
}

