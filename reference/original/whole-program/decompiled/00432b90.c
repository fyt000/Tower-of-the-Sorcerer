/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00432b90.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00432b90(int param_1,int *param_2)

{
  uint uVar1;
  
  if (param_2 == *(int **)(param_1 + 4)) {
    uVar1 = FUN_0041db60(*(int **)(param_1 + 4));
    *(uint *)(param_1 + 0x1c) = uVar1;
    FUN_00432b48(param_1);
    if (*(short *)(param_1 + 0x26) != 0) {
      (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),param_1);
    }
  }
  return;
}

