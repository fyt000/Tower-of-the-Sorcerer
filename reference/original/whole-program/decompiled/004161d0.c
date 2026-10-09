/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004161d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined root_004161d0(int param_1,undefined param_2)

{
  undefined uVar1;
  byte bVar2;
  int iVar3;
  int *piVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 uStack_10;
  
  uVar1 = root_00412e9c(param_1,param_2);
  uStack_10._0_2_ = CONCAT11(uVar1,param_2);
  uStack_10 = (uint)(ushort)uStack_10;
  iVar3 = FUN_00414ccc(param_1);
  iVar3 = iVar3 + -1;
  if (-1 < iVar3) {
    do {
      if (((byte)uStack_10 & uStack_10._1_1_) != 0) break;
      piVar4 = (int *)FUN_00414c9c(param_1,iVar3);
      bVar2 = FUN_00402cdc(piVar4,CONCAT31((int3)((uint)extraout_EDX >> 8),(byte)uStack_10),
                           extraout_ECX);
      uStack_10._0_2_ = CONCAT11(bVar2 | uStack_10._1_1_,(byte)uStack_10);
      uStack_10 = (uint)(ushort)uStack_10;
      iVar3 = iVar3 + -1;
    } while (iVar3 != -1);
  }
  return uStack_10._1_1_;
}

