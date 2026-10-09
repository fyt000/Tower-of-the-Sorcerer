/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419d80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00419d80(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_34 [11];
  
  puVar2 = &DAT_0048949c;
  puVar3 = local_34;
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  local_34[0] = param_2;
  FUN_00419c6c(param_1,local_34);
  return;
}

