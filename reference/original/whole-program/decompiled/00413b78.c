/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413b78.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00413b78(int param_1,undefined4 param_2,undefined4 param_3,undefined *param_4,
                  undefined param_5,undefined4 param_6)

{
  *param_4 = 1;
  if (*(short *)(param_1 + 0x82) == 0) {
    *param_4 = 0;
  }
  else {
    (**(code **)(param_1 + 0x80))
              (*(undefined4 *)(param_1 + 0x84),param_1,param_2,param_4,param_5,param_6,param_3);
  }
  return;
}

