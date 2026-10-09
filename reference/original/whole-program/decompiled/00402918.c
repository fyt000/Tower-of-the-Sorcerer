/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402918.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00402918(undefined4 *param_1,undefined4 *param_2,byte param_3)

{
  uint uVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *puVar4;
  
  if (param_3 < *(byte *)param_2) {
    *(byte *)param_1 = param_3;
    puVar3 = (undefined *)((int)param_2 + 1);
    puVar4 = (undefined *)((int)param_1 + 1);
    for (uVar1 = (uint)param_3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    return;
  }
  uVar1 = *(byte *)param_2 + 1;
  uVar2 = uVar1 & 3;
  for (uVar1 = uVar1 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *param_1 = *param_2;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  }
  for (; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined *)param_1 = *(undefined *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  return;
}

