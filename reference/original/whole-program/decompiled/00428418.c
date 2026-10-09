/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428418.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00428418(int *param_1,char param_2)

{
  if (param_2 != *(char *)((int)param_1 + 0xb1)) {
    *(char *)((int)param_1 + 0xb1) = param_2;
    FUN_00428364(param_1);
  }
  return;
}

