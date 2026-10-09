/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004097c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_004097c4(int *param_1,int *param_2,uint param_3)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  bool bVar6;
  
  uVar1 = 0;
  uVar3 = param_3 & 3;
  uVar2 = param_3 >> 2;
  bVar6 = uVar2 == 0;
  do {
    piVar4 = param_1;
    piVar5 = param_2;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    piVar5 = param_2 + 1;
    piVar4 = param_1 + 1;
    bVar6 = *param_1 == *param_2;
    param_1 = piVar4;
    param_2 = piVar5;
  } while (bVar6);
  if (bVar6) {
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      bVar6 = *(char *)piVar4 == *(char *)piVar5;
      piVar4 = (int *)((int)piVar4 + 1);
      piVar5 = (int *)((int)piVar5 + 1);
    } while (bVar6);
    if (bVar6) {
      uVar1 = 1;
    }
  }
  return uVar1;
}

