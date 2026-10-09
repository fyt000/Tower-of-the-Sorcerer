/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d170.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040d170(int param_1,int *param_2,undefined4 *param_3)

{
  if (*(short *)(param_1 + 0x3e) != 0) {
    (**(code **)(param_1 + 0x3c))(*(undefined4 *)(param_1 + 0x40),param_1,param_2,param_3);
  }
  (**(code **)(*param_2 + 0x18))(param_2,*param_3);
  return;
}

