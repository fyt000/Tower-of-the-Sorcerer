/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043c124.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043c124(byte *param_1,byte **param_2)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  byte *pbVar4;
  
  uVar1 = FUN_00403650((int)param_1);
  FUN_00403924((int *)param_2,uVar1);
  pbVar4 = *param_2;
  do {
    if (uVar1 == 0) {
      return;
    }
    bVar3 = *param_1;
    iVar2 = FUN_0040ed20(bVar3);
    if (iVar2 == 0) {
      if ((0x40 < bVar3) && (bVar3 < 0x5b)) {
        bVar3 = bVar3 + 0x20;
      }
    }
    else {
      *pbVar4 = bVar3;
      param_1 = param_1 + 1;
      pbVar4 = pbVar4 + 1;
      uVar1 = uVar1 - 1;
      if (uVar1 == 0) {
        return;
      }
      bVar3 = *param_1;
    }
    *pbVar4 = bVar3;
    param_1 = param_1 + 1;
    pbVar4 = pbVar4 + 1;
    uVar1 = uVar1 - 1;
  } while( true );
}

