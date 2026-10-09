/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00425454.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00425454(int param_1,uint *param_2)

{
  undefined in_ZF;
  
  FUN_00403760(*(uint **)(param_1 + 0x34),param_2);
  if (!(bool)in_ZF) {
    FUN_0040352c((int *)(param_1 + 0x34),param_2);
    if (*(short *)(param_1 + 0xa6) != 0) {
      (**(code **)(param_1 + 0xa4))(*(undefined4 *)(param_1 + 0xa8),param_1);
    }
  }
  return;
}

