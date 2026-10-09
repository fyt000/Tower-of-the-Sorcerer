/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041671c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041671c(int **param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  int **ppiVar3;
  undefined4 uVar4;
  
  *(undefined4 *)(param_2 + 0xc) = 1;
  bVar1 = FUN_0041651c(param_1,param_2,param_3);
  if (bVar1) {
    return;
  }
  if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
    iVar2 = FUN_00413cb8((int *)param_1,0xb02e,(uint)*(ushort *)(param_2 + 4),param_1);
    if (iVar2 != 0) {
      return;
    }
    uVar4 = *(undefined4 *)(param_2 + 8);
    ppiVar3 = FUN_0041fffc(param_1);
    iVar2 = FUN_00413cb8((int *)ppiVar3,0xb005,(uint)*(ushort *)(param_2 + 4),uVar4);
    if (iVar2 != 0) {
      return;
    }
  }
  *(undefined4 *)(param_2 + 0xc) = 0;
  return;
}

