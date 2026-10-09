/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406114.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 * FUN_00406114(undefined4 *param_1,undefined4 *param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  uVar2 = 0xffffffff;
  puVar4 = param_2;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *(char *)puVar4;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  } while (cVar1 != '\0');
  puVar4 = param_1;
  for (uVar3 = ~uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar4 = *param_2;
    param_2 = param_2 + 1;
    puVar4 = puVar4 + 1;
  }
  for (uVar2 = ~uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined *)puVar4 = *(undefined *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  return param_1;
}

