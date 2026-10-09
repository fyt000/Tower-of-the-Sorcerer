/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ed64.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined FUN_0040ed64(undefined *param_1)

{
  uint uVar1;
  BYTE *pBVar2;
  int iVar3;
  undefined uVar4;
  
  uVar4 = 0;
  uVar1 = FUN_00403650((int)param_1);
  pBVar2 = FUN_00403814(param_1);
  iVar3 = FUN_0040ed28(pBVar2,param_1 + ((uVar1 & 0xffff) - 1));
  if (iVar3 == 0) {
    uVar4 = param_1[(uVar1 & 0xffff) - 1];
  }
  return uVar4;
}

