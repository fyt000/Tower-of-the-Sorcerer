/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413098.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413098(int *param_1,undefined4 param_2)

{
  (**(code **)(*param_1 + 0x4c))(param_1,param_2,param_1[10],param_1[0xc],param_1[0xb]);
  *(byte *)(param_1 + 0x17) = *(byte *)(param_1 + 0x17) | 1;
  return;
}

