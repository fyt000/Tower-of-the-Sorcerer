/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043fd80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043fd80(int *param_1,uint *param_2)

{
  undefined in_ZF;
  
  FUN_00403760((uint *)param_1[0x50],param_2);
  if (!(bool)in_ZF) {
    FUN_0040352c(param_1 + 0x50,param_2);
    (**(code **)(*param_1 + 0x94))();
  }
  return;
}

