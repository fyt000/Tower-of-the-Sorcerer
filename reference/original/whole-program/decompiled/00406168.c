/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406168.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 * FUN_00406168(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  bool bVar4;
  
  bVar4 = param_3 == 0;
  iVar1 = param_3;
  puVar3 = param_2;
  if (!bVar4) {
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar4 = *(char *)puVar3 == '\0';
      puVar3 = (undefined4 *)((int)puVar3 + 1);
    } while (!bVar4);
    if (bVar4) {
      iVar1 = iVar1 + 1;
    }
  }
  puVar3 = param_1;
  for (uVar2 = (uint)(param_3 - iVar1) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar3 = *param_2;
    param_2 = param_2 + 1;
    puVar3 = puVar3 + 1;
  }
  for (uVar2 = param_3 - iVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined *)puVar3 = *(undefined *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  *(undefined *)puVar3 = 0;
  return param_1;
}

