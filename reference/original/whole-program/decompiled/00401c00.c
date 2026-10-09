/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401c00.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00401c00(uint *param_1,uint param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)((int)(uint *)(param_2 - 4) + (int)param_1);
  if (0xf < (int)param_2) {
    *puVar1 = 0x80000007;
    FUN_00401dbc((uint **)param_1,(uint *)(param_2 - 4));
    return;
  }
  if (3 < (int)param_2) {
    *param_1 = param_2 | 0x80000002;
    *puVar1 = param_2 | 0x80000002;
  }
  return;
}

