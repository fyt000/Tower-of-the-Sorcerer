/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042ab74.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042ab74(int *param_1,int *param_2)

{
  undefined *puVar1;
  
  FUN_00414d88(param_1,param_2);
  FUN_00414d4c(param_1,(int)param_2,"LISTBOX");
  puVar1 = &DAT_00489708;
  if (*(char *)(param_1 + 0x46) != '\0') {
    puVar1 = &DAT_00489710;
  }
  param_2[1] = param_2[1] | 0x300041U |
               *(uint *)(&DAT_004896f4 + (uint)*(byte *)(param_1 + 0x45) * 4) |
               *(uint *)(&DAT_00489700 + (uint)*(byte *)((int)param_1 + 0x117) * 4) |
               *(uint *)(puVar1 + (uint)*(byte *)((int)param_1 + 0x116) * 4) |
               *(uint *)(&DAT_00489718 + (uint)*(byte *)((int)param_1 + 0x115) * 4) |
               *(uint *)(&DAT_00489720 + (uint)(param_1[0x43] != 0) * 4) |
               *(uint *)(&DAT_00489664 + (uint)*(byte *)(param_1 + 0x41) * 4) |
               *(uint *)(&DAT_00489728 + (uint)(param_1[0x47] != 0) * 4);
  if (((DAT_0048a694 != '\0') && (*(char *)((int)param_1 + 0xc5) != '\0')) &&
     (*(char *)(param_1 + 0x41) == '\x01')) {
    param_2[1] = param_2[1] & 0xff7fffff;
    param_2[2] = param_2[2] | 0x200;
  }
  return;
}

