/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004102c8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004102c8(int *param_1,uint *param_2)

{
  undefined in_ZF;
  
  FUN_00403760((uint *)param_1[8],param_2);
  if (!(bool)in_ZF) {
    FUN_0040352c(param_1 + 8,param_2);
    (**(code **)(*param_1 + 0x28))(param_1,1);
  }
  return;
}

