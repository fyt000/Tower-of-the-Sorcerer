/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00433d94.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Removing unreachable block (ram,0x00433d9b) */

void FUN_00433d94(int *param_1,byte param_2)

{
  if (4 < param_2) {
    param_2 = 4;
  }
  if (param_2 != *(byte *)(param_1[0x44] + 0x20)) {
    FUN_00432c38(param_1[0x44],param_2);
    (**(code **)(*param_1 + 0x44))();
  }
  return;
}

