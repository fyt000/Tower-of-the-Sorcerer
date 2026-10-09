/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431d60.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00431d60(int param_1,int param_2,char param_3)

{
  FUN_00412f9c(param_1,param_2,param_3);
  if ((param_3 == '\x01') && (param_2 == *(int *)(param_1 + 0x200))) {
    if (*(char *)(param_1 + 0x1d5) != '\0') {
      FUN_00431da0(param_1);
    }
    *(undefined4 *)(param_1 + 0x200) = 0;
  }
  return;
}

