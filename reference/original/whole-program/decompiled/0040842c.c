/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040842c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040842c(int *param_1,int *param_2,byte *param_3)

{
  byte *pbVar1;
  byte bVar2;
  code *pcVar3;
  byte bVar4;
  uint uVar5;
  byte *pbVar6;
  
  pbVar6 = (byte *)param_2[4];
  if ((byte *)param_2[4] == (byte *)0x80000000) {
    pbVar6 = param_3;
  }
  pcVar3 = (code *)param_2[2];
  if (*(byte *)((int)param_2 + 0xb) != 0xff) {
    if (0xfd < *(byte *)((int)param_2 + 0xb)) {
      (**(code **)((int)(short)pcVar3 + *param_1))();
      return;
    }
    (*pcVar3)(param_1,pbVar6);
    return;
  }
  pbVar6 = (byte *)(((uint)pcVar3 & 0xffffff) + (int)param_1);
  bVar2 = *(byte *)(*param_2 + 2 + (uint)*(byte *)(*param_2 + 1));
  bVar4 = *param_3;
  if (bVar2 <= *param_3) {
    bVar4 = bVar2;
  }
  *pbVar6 = bVar4;
  pbVar1 = param_3 + 1;
  for (uVar5 = (uint)bVar4; pbVar6 = pbVar6 + 1, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar6 = *pbVar1;
    pbVar1 = pbVar1 + 1;
  }
  return;
}

