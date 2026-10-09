/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422768.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00422768(int param_1,undefined4 param_2)

{
  HANDLE pvVar1;
  
  if ((*(char *)(param_1 + 0x119) != '\0') && (*(int *)(param_1 + 0x10c) != 0)) {
    FUN_00413cb8(*(int **)(param_1 + 0x10c),0xb004,0,param_2);
  }
  if (*(char *)(param_1 + 0x11a) == '\x02') {
    pvVar1 = FUN_00421984(param_1);
    if (pvVar1 != (HANDLE)0x0) {
      pvVar1 = FUN_00421984(param_1);
      FUN_00422768((int)pvVar1,param_2);
    }
  }
  return;
}

