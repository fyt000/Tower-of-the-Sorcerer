/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004028cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004028cc(byte *param_1,byte *param_2,byte param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  bVar3 = *param_2;
  bVar2 = *param_1 + bVar3;
  if (((!CARRY1(*param_1,bVar3)) && (bVar2 <= param_3)) ||
     (bVar3 = param_3 - *param_1, bVar2 = param_3, *param_1 <= param_3 && bVar3 != 0)) {
    bVar1 = *param_1;
    *param_1 = bVar2;
    pbVar5 = param_2 + 1;
    pbVar6 = param_1 + bVar1 + 1;
    for (uVar4 = (uint)bVar3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar6 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      pbVar6 = pbVar6 + 1;
    }
  }
  return;
}

