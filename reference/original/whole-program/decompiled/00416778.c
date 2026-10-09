/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416778.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416778(int **param_1,int param_2)

{
  int **ppiVar1;
  undefined4 uVar2;
  
  if (((*(byte *)(param_1 + 7) & 0x10) == 0) && (*(short *)(param_2 + 4) != 0x20)) {
    uVar2 = *(undefined4 *)(param_2 + 8);
    ppiVar1 = FUN_0041fffc(param_1);
    uVar2 = FUN_00413cb8((int *)ppiVar1,0xb006,(uint)*(ushort *)(param_2 + 4),uVar2);
    *(undefined4 *)(param_2 + 0xc) = uVar2;
  }
  return;
}

