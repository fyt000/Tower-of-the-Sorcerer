/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414190.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00414190(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5)

{
  if (*(short *)(param_1 + 0x72) != 0) {
    (**(code **)(param_1 + 0x70))
              (*(undefined4 *)(param_1 + 0x74),param_1,param_2,param_4,param_5,param_3);
  }
  return;
}

