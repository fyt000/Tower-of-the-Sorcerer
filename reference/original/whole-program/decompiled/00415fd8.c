/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415fd8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00415fd8(int param_1,undefined4 param_2)

{
  if (*(short *)(param_1 + 0xe2) != 0) {
    (**(code **)(param_1 + 0xe0))(*(undefined4 *)(param_1 + 0xe4),param_1,param_2);
  }
  return;
}

