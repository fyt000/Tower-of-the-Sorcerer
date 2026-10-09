/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413118.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413118(int param_1,undefined4 *param_2)

{
  *param_2 = *(undefined4 *)(param_1 + 0x24);
  param_2[1] = *(undefined4 *)(param_1 + 0x28);
  param_2[2] = *(int *)(param_1 + 0x24) + *(int *)(param_1 + 0x2c);
  param_2[3] = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x30);
  return;
}

