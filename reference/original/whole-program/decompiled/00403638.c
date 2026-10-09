/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403638.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403638(int *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  bool bVar3;
  
  bVar3 = true;
  uVar1 = param_3;
  puVar2 = param_2;
  do {
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    bVar3 = *(char *)puVar2 == '\0';
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  } while (!bVar3);
  if (bVar3) {
    uVar1 = ~uVar1;
  }
  FUN_004035bc(param_1,param_2,uVar1 + param_3);
  return;
}

