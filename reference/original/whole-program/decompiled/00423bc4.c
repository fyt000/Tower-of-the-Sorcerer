/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423bc4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423bc4(int param_1)

{
  if ((*(int *)(param_1 + 0x40) != *(int *)(param_1 + 0x48)) &&
     (*(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x40), *(short *)(param_1 + 0x5a) != 0)) {
    (**(code **)(param_1 + 0x58))(*(undefined4 *)(param_1 + 0x5c),param_1);
  }
  if ((*(int *)(param_1 + 0x3c) != *(int *)(param_1 + 0x44)) &&
     (*(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x3c), *(short *)(param_1 + 0x52) != 0)) {
    (**(code **)(param_1 + 0x50))(*(undefined4 *)(param_1 + 0x54),param_1);
  }
  return;
}

