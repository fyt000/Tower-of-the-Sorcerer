/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409e68.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * root_00409e68(int *param_1,char param_2)

{
  param_1[3] = 1;
  if (param_1[2] != 0) {
    FUN_00409f50(param_1);
  }
  FUN_00402c34((int *)param_1[2]);
  if (param_2 != '\0') {
    FUN_00402e48(param_1);
  }
  return param_1;
}

