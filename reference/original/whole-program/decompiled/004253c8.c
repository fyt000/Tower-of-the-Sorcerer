/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004253c8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004253c8(undefined4 param_1,uint param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = FUN_00423bbc(DAT_0048a6fc);
  if (-1 < iVar1 + -1) {
    iVar3 = 0;
    do {
      uVar4 = 0;
      piVar2 = (int *)FUN_00423bb0(DAT_0048a6fc,iVar3);
      FUN_00413cb8(piVar2,param_2 & 0xffff,0,uVar4);
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}

