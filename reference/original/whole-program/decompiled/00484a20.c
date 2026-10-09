/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00484a20.
 * Inferred types, shared tails and runtime effects require assembly review. */

void TTSW10_K5Click(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x420);
  if (*(char *)(iVar1 + 0x28) == '\x01') {
    FUN_004102f0(iVar1,0);
    DAT_00489ba1 = 0;
    return;
  }
  FUN_004102f0(iVar1,1);
  DAT_00489ba1 = 1;
  return;
}

