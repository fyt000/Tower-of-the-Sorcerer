/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428888.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00428888(int *param_1,int *param_2)

{
  FUN_00414d88(param_1,param_2);
  FUN_00414d4c(param_1,(int)param_2,"EDIT");
  param_2[1] = param_2[1] | 0xc0U | *(uint *)(&DAT_00489664 + (uint)*(byte *)(param_1 + 0x41) * 4) |
               *(uint *)(&DAT_0048967c + (uint)(*(char *)((int)param_1 + 0x105) != '\0') * 4) |
               *(uint *)(&DAT_00489684 + (uint)*(byte *)((int)param_1 + 0x106) * 4) |
               *(uint *)(&DAT_0048968c + (uint)*(byte *)((int)param_1 + 0x10b) * 4) |
               *(uint *)(&DAT_00489698 + (uint)*(byte *)((int)param_1 + 0x109) * 4) |
               *(uint *)(&DAT_004896a0 + (uint)*(byte *)((int)param_1 + 0x10a) * 4);
  if (((DAT_0048a694 != '\0') && (*(char *)((int)param_1 + 0xc5) != '\0')) &&
     (*(char *)(param_1 + 0x41) == '\x01')) {
    param_2[1] = param_2[1] & 0xff7fffff;
    param_2[2] = param_2[2] | 0x200;
  }
  return;
}

