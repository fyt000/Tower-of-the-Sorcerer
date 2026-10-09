/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004296cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004296cc(int *param_1,int *param_2)

{
  FUN_00414d88(param_1,param_2);
  FUN_00414d4c(param_1,(int)param_2,"COMBOBOX");
  param_2[1] = param_2[1] | 0x200240U |
               *(uint *)(&DAT_004896d0 + (uint)*(byte *)((int)param_1 + 0x109) * 4) |
               *(uint *)(&DAT_004896e4 + (uint)*(byte *)(param_1 + 0x42) * 4);
  if ((DAT_0048a694 != '\0') && (*(char *)((int)param_1 + 0xc5) != '\0')) {
    param_2[2] = param_2[2] | 0x200;
  }
  return;
}

