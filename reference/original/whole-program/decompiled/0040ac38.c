/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ac38.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_0040ac38(int param_1,int param_2)

{
  if ((param_2 < 0) || (*(int *)(param_1 + 0xc) <= param_2)) {
    FUN_00409978(param_1,param_2);
  }
  return *(undefined4 *)(*(int *)(param_1 + 8) + 4 + param_2 * 8);
}

