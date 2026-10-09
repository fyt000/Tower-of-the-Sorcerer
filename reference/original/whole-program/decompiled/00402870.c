/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402870.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00402870(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  undefined *puVar6;
  
  iVar1 = (int)param_3 >> 2;
  if ((int)param_1 < (int)param_2) {
    puVar3 = (undefined4 *)((int)param_1 + (param_3 - 4));
    puVar5 = (undefined4 *)((int)param_2 + (param_3 - 4));
    if (-1 < iVar1) {
      for (; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + -1;
        puVar5 = puVar5 + -1;
      }
      puVar4 = (undefined *)((int)puVar3 + 3);
      puVar6 = (undefined *)((int)puVar5 + 3);
      for (uVar2 = param_3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar6 = *puVar4;
        puVar4 = puVar4 + -1;
        puVar6 = puVar6 + -1;
      }
    }
  }
  else if ((param_2 != param_1) && (-1 < iVar1)) {
    for (; iVar1 != 0; iVar1 = iVar1 + -1) {
      *param_2 = *param_1;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
    for (uVar2 = param_3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined *)param_2 = *(undefined *)param_1;
      param_1 = (undefined4 *)((int)param_1 + 1);
      param_2 = (undefined4 *)((int)param_2 + 1);
    }
    return;
  }
  return;
}

