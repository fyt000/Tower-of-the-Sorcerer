/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004166d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004166d0(int **param_1,int param_2)

{
  uint uVar1;
  int **ppiVar2;
  int iVar3;
  undefined4 uVar4;
  
  if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
    *(undefined4 *)(param_2 + 0xc) = 1;
    uVar1 = FUN_00413cb8((int *)param_1,0x87,0,0);
    if ((uVar1 & 0x80) == 0) {
      uVar4 = *(undefined4 *)(param_2 + 8);
      ppiVar2 = FUN_0041fffc(param_1);
      iVar3 = FUN_00413cb8((int *)ppiVar2,0xb006,(uint)*(ushort *)(param_2 + 4),uVar4);
      if (iVar3 != 0) {
        return;
      }
    }
    *(undefined4 *)(param_2 + 0xc) = 0;
  }
  return;
}

