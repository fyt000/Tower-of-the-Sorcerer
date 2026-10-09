/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040dd50.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0040dd50(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  float10 fVar1;
  float10 fVar2;
  undefined4 uVar3;
  undefined2 uVar4;
  float10 in_ST0;
  
  uVar3 = FUN_0040d9ac((char)*(undefined4 *)(param_4 + 8),param_2,param_3,
                       *(undefined4 *)(param_4 + 8));
  uVar4 = (undefined2)((uint)param_4 >> 0x10);
  if ((char)uVar3 != '\0') {
    FUN_00408590(*(int **)(*(int *)(*(int *)(param_4 + 8) + -4) + 0x1c),
                 *(int **)(*(int *)(param_4 + 8) + -0xc));
    fVar1 = *(float10 *)(param_4 + -10);
    return CONCAT31((int3)(CONCAT22(uVar4,(ushort)(fVar1 < in_ST0) << 8 |
                                          (ushort)(NAN(fVar1) || NAN(in_ST0)) << 10 |
                                          (ushort)(fVar1 == in_ST0) << 0xe) >> 8),
                    (fVar1 == in_ST0) != 0);
  }
  fVar1 = *(float10 *)(param_4 + -10);
  fVar2 = (float10)_DAT_0040dda4;
  return CONCAT31((int3)(CONCAT22(uVar4,(ushort)(fVar1 < fVar2) << 8 |
                                        (ushort)(NAN(fVar1) || NAN(fVar2)) << 10 |
                                        (ushort)(fVar1 == fVar2) << 0xe) >> 8),(fVar1 == fVar2) != 0
                 );
}

