/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004028fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004028fc(undefined4 *param_1,undefined4 *param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(byte *)param_2 + 1 & 3;
  uVar2 = *(byte *)param_2 + 1 >> 2;
  for (; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_1 = *param_2;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  }
  for (; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined *)param_1 = *(undefined *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  return;
}

