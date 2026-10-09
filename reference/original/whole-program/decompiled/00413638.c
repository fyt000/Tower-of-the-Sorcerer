/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413638.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413638(int *param_1)

{
  int iVar1;
  
  *(undefined *)((int)param_1 + 0x39) = 0;
  iVar1 = FUN_00419da4(param_1[0x11]);
  if (iVar1 != param_1[0x16]) {
    *(byte *)(param_1 + 0x17) = *(byte *)(param_1 + 0x17) | 0x10;
    iVar1 = FUN_00419da4(param_1[0x11]);
    param_1[0x16] = iVar1;
  }
  FUN_00413cb8(param_1,0xb00e,0,0);
  return;
}

