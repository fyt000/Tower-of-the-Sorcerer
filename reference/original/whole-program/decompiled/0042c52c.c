/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c52c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042c52c(int *param_1,int *param_2)

{
  FUN_00414d88(param_1,param_2);
  param_2[1] = param_2[1] | *(uint *)(&DAT_00489730 + (uint)*(byte *)(param_1 + 0x44) * 4);
  if (((DAT_0048a694 != '\0') && (*(char *)((int)param_1 + 0xc5) != '\0')) &&
     (*(char *)(param_1 + 0x44) == '\x01')) {
    param_2[1] = param_2[1] & 0xff7fffff;
    param_2[2] = param_2[2] | 0x200;
  }
  return;
}

