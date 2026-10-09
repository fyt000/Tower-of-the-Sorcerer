/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413cb8.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00413cb8(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = param_4;
  local_8 = 0;
  if (param_1 != (int *)0x0) {
    local_14 = param_2;
    local_10 = param_3;
    (**(code **)(*param_1 + 0x40))(param_1,&local_14);
  }
  return local_8;
}

