/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004214f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004214f0(int *param_1,int param_2)

{
  if ((*(byte *)((int)param_1 + 0x36) & 8) != 0) {
    param_1[0x52] = param_2;
    *(byte *)(param_1 + 0x17) = DAT_00421518 | *(byte *)(param_1 + 0x17);
    return;
  }
  FUN_00413190(param_1,param_2);
  return;
}

