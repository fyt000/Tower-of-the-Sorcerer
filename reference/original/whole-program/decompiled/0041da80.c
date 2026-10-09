/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041da80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041da80(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (1 < *(int *)(iVar1 + 4)) {
    FUN_0041d7fc(param_1,*(HGDIOBJ *)(iVar1 + 0xc),*(HPALETTE *)(iVar1 + 0x10),
                 *(char *)(iVar1 + 0x24),*(int *)(iVar1 + 0x18),*(int *)(iVar1 + 0x14));
    return;
  }
  FUN_00402c34(*(int **)(iVar1 + 8));
  *(undefined4 *)(iVar1 + 8) = 0;
  *(undefined4 *)(iVar1 + 0x1c) = 0;
  *(undefined4 *)(iVar1 + 0x20) = 0;
  *(undefined *)(iVar1 + 0x25) = 0;
  return;
}

