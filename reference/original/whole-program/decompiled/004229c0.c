/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004229c0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_004229c0(int param_1,byte param_2)

{
  int *piVar1;
  int *piVar2;
  undefined3 uVar4;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int *piVar5;
  byte bStack_1b;
  int iStack_18;
  
  bStack_1b = 0;
  piVar1 = (int *)FUN_00421984(param_1);
  if (piVar1 != (int *)0x0) {
    bStack_1b = FUN_00402cdc(piVar1,CONCAT31((int3)((uint)extraout_EDX >> 8),param_2),extraout_ECX);
  }
  piVar2 = (int *)FUN_004219b8(param_1);
  if (-1 < (int)piVar2 + -1) {
    iStack_18 = 0;
    piVar5 = piVar2;
    do {
      uVar4 = (undefined3)((uint)piVar2 >> 8);
      if ((param_2 & bStack_1b) != 0) goto LAB_00422a5e;
      piVar2 = (int *)FUN_00421a04(param_1,iStack_18);
      if (piVar2 != piVar1) {
        uVar3 = FUN_00402cdc(piVar2,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),param_2),
                             extraout_ECX_00);
        bStack_1b = (byte)uVar3 | bStack_1b;
        piVar2 = (int *)CONCAT31((int3)((uint)uVar3 >> 8),bStack_1b);
      }
      iStack_18 = iStack_18 + 1;
      piVar5 = (int *)((int)piVar5 + -1);
    } while (piVar5 != (int *)0x0);
  }
  uVar4 = (undefined3)((uint)piVar2 >> 8);
  if ((param_2 & bStack_1b) == 0) {
    bStack_1b = 0;
    uVar4 = 0;
    root_004161d0(param_1,param_2);
  }
LAB_00422a5e:
  return CONCAT31(uVar4,bStack_1b);
}

