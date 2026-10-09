/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430bf8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00430bf8(int **param_1)

{
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  FUN_00413758(param_1,'\0');
  if ((*(char *)(param_1 + 0x67) != '\0') && (*(char *)((int)param_1 + 0x19d) != '\0')) {
    *(undefined *)((int)param_1 + 0x19d) = 0;
    FUN_00430420((int *)param_1,*(byte *)((int)param_1 + 0x19e),(int)param_1[0x68]);
    root_00430b24(param_1,*(undefined *)((int)param_1 + 0x19e));
    if ((*(char *)(param_1 + 0x84) != '\0') &&
       ((param_1[0x7e] == (int *)0x0 && (*(char *)((int)param_1 + 0x1d5) != '\0')))) {
      FUN_00402cdc((int *)param_1,
                   CONCAT31((int3)((uint)extraout_EDX >> 8),*(undefined *)((int)param_1 + 0x19e)),
                   extraout_ECX);
      FUN_0043025c((int *)param_1);
    }
  }
  *(undefined *)(param_1 + 0x67) = 0;
  return;
}

