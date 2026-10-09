/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00429108.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00429108(int *param_1,int *param_2)

{
  FUN_00428888(param_1,param_2);
  param_2[1] = param_2[1] & ~*(uint *)(&DAT_004896c8 + (uint)*(byte *)((int)param_1 + 0x11e) * 4) |
               4 | *(uint *)(&DAT_004896ac + (uint)*(byte *)(param_1 + 0x47) * 4) |
               *(uint *)(&DAT_004896b8 + (uint)*(byte *)((int)param_1 + 0x11d) * 4);
  return;
}

