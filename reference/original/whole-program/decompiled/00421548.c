/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421548.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00421548(int *param_1,undefined4 param_2,undefined4 param_3)

{
  if ((*(byte *)((int)param_1 + 0x11d) & 1) == 0) {
    FUN_00413500(param_1,param_2,param_3);
  }
  else {
    if ((char)param_2 == '\0') {
      *(byte *)((int)param_1 + 0x11d) = *(byte *)((int)param_1 + 0x11d) & 0xfd;
      return;
    }
    *(byte *)((int)param_1 + 0x11d) = *(byte *)((int)param_1 + 0x11d) | 2;
  }
  return;
}

