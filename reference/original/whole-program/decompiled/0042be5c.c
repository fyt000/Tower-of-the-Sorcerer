/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042be5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042be5c(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  int *piVar1;
  POINT local_2c;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  piVar1 = *(int **)(param_4 + -4);
  local_c = piVar1[2];
  local_8 = piVar1[1];
  local_14 = *piVar1;
  local_10 = piVar1[3];
  FUN_00419fa8(*(int **)(*(int *)(param_4 + -8) + 0x10),*(undefined4 *)(param_4 + -0xc));
  local_2c.x = local_14;
  local_2c.y = local_10;
  local_24 = *piVar1;
  local_20 = piVar1[1];
  local_1c = local_c;
  local_18 = local_8;
  FUN_0041a704(*(int **)(param_4 + -8),&local_2c,2);
  FUN_00419fa8(*(int **)(*(int *)(param_4 + -8) + 0x10),*(undefined4 *)(param_4 + 0xc));
  local_1c = local_14 + -1;
  local_2c.x = local_c;
  local_2c.y = local_8;
  local_24 = piVar1[2];
  local_20 = piVar1[3];
  local_18 = local_10;
  local_14 = local_1c;
  FUN_0041a704(*(int **)(param_4 + -8),&local_2c,2);
  return;
}

