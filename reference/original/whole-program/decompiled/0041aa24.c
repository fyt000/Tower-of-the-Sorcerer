/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041aa24.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_0041aa24(int *param_1,byte param_2)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 extraout_EDX;
  byte bVar5;
  
  bVar5 = ~*(byte *)(param_1 + 2) & param_2;
  uVar2 = CONCAT31((int3)((uint)param_1 >> 8),DAT_0041aaa4);
  if (DAT_0041aaa4 != bVar5) {
    if ((bVar5 & 1) != 0) {
      uVar2 = (**(code **)(*param_1 + 0x14))();
      if (param_1[1] == 0) {
        uVar3 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf023);
        uVar2 = FUN_004031f8(uVar3);
      }
    }
    if ((bVar5 & 2) != 0) {
      uVar2 = FUN_0041aad0((int)param_1);
    }
    if ((bVar5 & 4) != 0) {
      FUN_0041aafc((int)param_1);
      iVar4 = FUN_0041a028(param_1[4]);
      bVar1 = (byte)(iVar4 + -1);
      uVar2 = CONCAT31((int3)((uint)(iVar4 + -1) >> 8),bVar1 - 4);
      if (bVar1 < 4) {
        bVar5 = bVar5 | 8;
      }
    }
    if ((bVar5 & 8) != 0) {
      uVar2 = FUN_0041ab2c((int)param_1);
    }
    *(byte *)(param_1 + 2) = bVar5 | *(byte *)(param_1 + 2);
  }
  return uVar2;
}

