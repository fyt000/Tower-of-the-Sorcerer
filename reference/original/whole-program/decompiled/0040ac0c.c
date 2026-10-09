/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ac0c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040ac0c(int param_1,int param_2,int *param_3)

{
  if ((param_2 < 0) || (*(int *)(param_1 + 0xc) <= param_2)) {
    FUN_00409978(param_1,param_2);
  }
  FUN_00403570(param_3,*(int *)(*(int *)(param_1 + 8) + param_2 * 8));
  return;
}

