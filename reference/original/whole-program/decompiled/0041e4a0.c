/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e4a0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_0041e4a0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if ((*(int *)(iVar1 + 0xc) == 0) && (*(int *)(iVar1 + 8) == 0)) {
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  return 0;
}

